// Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "emulator/emulator_manager.hpp"


namespace fcore {


    emulator_manager::emulator_manager(nlohmann::json &spec, bool dbg) :
    emu_spec(spec){
        debug_autogen = dbg;
        emulators_memory = std::make_shared<std::unordered_map<std::string, core_memory_pool_t>>();
        common_io_memory = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<uint32_t>>>>();
        runners = std::make_shared<std::unordered_map<std::string, emulator_runner>>();
    }

    void emulator_manager::process() {
        bus_map.clear();

        if(emu_spec.cores.empty()){
            throw std::runtime_error("No cores section found in the emulator specification file");
        }
        // Parse specification file;

        programs = get_programs();

        for(auto &e: errors){
            if(!e.second.empty()){
                throw std::runtime_error("CORE " + e.first + ": " + e.second);
            }
        }

        for(auto &core:emu_spec.cores){

            outputs_manager.add_specs(core.id,  core.outputs, get_bundle_by_name(core.id).active_channels);

            sequencer.add_core(core.id, core.sampling_frequency, core.order);

        }

        for(auto &ic:emu_spec.interconnects){
            outputs_manager.add_interconnect_outputs(ic, emu_spec.cores);
        }

        sequencer.setup_run(emu_spec.emulation_time);

        check_bus_duplicates();

        for(auto &p:programs){
            emulator_runner r(p);
            r.set_emulators_memory(emulators_memory);
            r.set_common_io(common_io_memory);
            runners->insert({p.name, r});
        }
    }

    std::vector<program_bundle> emulator_manager::get_programs() {
        bus_map.clear();
        emulator_builder e_b(debug_autogen);
        e_b.set_profiler(profiler);
        std::vector<program_bundle> res;

        for(auto &core:emu_spec.cores){

            if (profiler != nullptr) profiler->set_active_program(core.id);

            program_bundle b;
            b.name = core.id;
            b.input = core.inputs;
            b.memories = core.memories;
            b.sampling_frequency = core.sampling_frequency;
            b.execution_order = core.order;
            b.active_channels = core.channels;
            b.efi_selector = e_b.get_efi_implementation(core.options["efi_implementation"]);
            b.comparator_type = e_b.get_comparator_type(core.options["comparators"]);

            try{

                b.program = e_b.compile_program(core, emu_spec.interconnects, b.io);

            } catch(std::runtime_error &e){
                errors[core.id] = e.what();
            }


            res.push_back(b);
        }
        check_bus_duplicates();
        return res;
    }

    void emulator_manager::emulate() {
        allocate_memory();
        ic_manager.clear_repeater();
        ic_manager.set_runners(runners);
        outputs_manager.set_runners(runners);
        run_cores();
    }

    void emulator_manager::run_cores() {

        sequencer.calculate_sequence();
        outputs_manager.set_simulation_frequency(sequencer.get_simulation_frequency());

        spdlog::info("EMULATION START");
        while(!sequencer.sim_complete()){

            auto running_cores = sequencer.get_running_cores();

            for(auto &core:running_cores){

                auto sel_prog = get_bundle_by_name(core.id);
                if(!sequencer.is_empty_step()){
                    for(int j = 0; j<sel_prog.active_channels; ++j) {
                        runners->at(core.id).inputs_phase(core, j);
                        runners->at(core.id).emulation_phase(j);
                    }
                    interconnects_phase(emu_spec.interconnects, core);
                }

                outputs_manager.process_outputs(
                        core.id,
                        core.running,
                        sel_prog.active_channels
                );
            }

        }
        spdlog::info("EMULATION DONE");
    }


    void emulator_manager::interconnects_phase(const std::vector<emulator::emulator_interconnect> &specs, const core_step_metadata& info) {
        for(auto &conn:specs){
            if(info.id == conn.source_core_id){
                ic_manager.run_interconnect(conn, sequencer.get_enabled_cores());
            }
        }
    }



    nlohmann::json emulator_manager::get_results() {
        nlohmann::json res;
        for(auto &item:programs){
            nlohmann::json j;
            nlohmann::json outputs_json;

            j["outputs"] = outputs_manager.get_emulation_output(item.name);
            j["error_code"] = errors[item.name];
            res[item.name] = j;
        }


        res["timebase"] = outputs_manager.get_timebase();
        return res;
    }


    std::shared_ptr<std::vector<uint32_t>> emulator_manager::get_memory_snapshot(const std::string &core_id, int channel) {
        return emulators_memory->at(core_id)[channel];
    }

    std::unordered_map<unsigned int, uint32_t>
    emulator_manager::io_remap_memory_init(std::vector<emulator::emulator_memory_specs> &mem,
                                                  std::set<io_map_entry> &io_set) {
        std::unordered_map<unsigned int, uint32_t> ret;

        for(auto &item: mem){
            uint32_t io_address = item.address[0];
            uint32_t core_address;
            if(auto a = io_map_entry::get_io_map_entry_by_io_addr(io_set, io_address)){
                core_address = a->core_addr;
            } else {
                throw std::runtime_error("unable to find input address in the core io map during memory initialization phase");
            }
            if(item.metadata.type == emulator::type_float){
                auto values = std::get<std::vector<float>>(item.value);
                ret[core_address] = emulator_backend::float_to_uint32(values[0]);
            } else {
                auto values = std::get<std::vector<uint32_t>>(item.value);
                ret[core_address] = values[0];
            }
        }

        return ret;
    }

    void emulator_manager::check_bus_duplicates() {
        if(bus_map.check_duplicates()){
            auto duplicates = bus_map.get_duplicates().dump();
            throw std::domain_error(duplicates);
        }
    }

    void emulator_manager::allocate_memory() {

        for(auto &item:programs){
            core_memory_pool_t pool;
            for(int i = 0; i<item.active_channels; i++){
                pool[i] = std::make_shared<std::vector<uint32_t>>(2 << (fcore_register_address_width - 1), 0);
            }
            emulators_memory->insert({item.name, pool});
            common_io_memory->insert({item.name, std::make_shared<std::vector<uint32_t>>(32, 0)});

            auto mem = io_remap_memory_init(item.memories, item.io);

            for(auto &init_val: mem){
                // TODO: Add support for per channel initialization
                for(const auto& reg_file:emulators_memory->at(item.name)){
                    reg_file.second->at(init_val.first) = init_val.second;
                }
            }
        }
    }

    std::unordered_map<std::string, std::string> emulator_manager::disassemble() {
        std::unordered_map<std::string, std::string> ret;

        for(auto &p:get_programs()){
            fcore_dis d(p.program.binary);
            ret[p.name] = d.get_disassenbled_program();

        }
        return ret;
    }


}