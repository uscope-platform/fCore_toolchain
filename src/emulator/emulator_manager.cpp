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


    emulator_manager::emulator_manager() {
        debug_autogen = false;
        runners = std::make_shared<std::unordered_map<std::string, emulator_runner>>();
        interactive_restart_point = 0;
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

            outputs_manager.add_specs(core.id,  core.outputs, core.channels);

            sequencer.add_core(core.id, core.sampling_frequency, core.order, core.channels);

        }

        for(auto &ic:emu_spec.interconnects){
            outputs_manager.add_interconnect_outputs(ic, emu_spec.cores);
        }

        sequencer.setup_run(emu_spec.emulation_time);

        check_bus_duplicates();

        for(auto &p:programs){
            emulator_runner r(p);
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

    std::optional<debug_checkpoint> emulator_manager::emulate(bool interactive) {
        interactive_restart_point = 0;
        ic_manager.clear_repeater();
        ic_manager.set_runners(runners);
        outputs_manager.set_runners(runners);

        sequencer.calculate_sequence();
        outputs_manager.set_simulation_frequency(sequencer.get_simulation_frequency());


        spdlog::info("EMULATION START");
        try{
            currently_active_core = sequencer.get_core_by_order(1);
            run_cores();
            spdlog::info("EMULATION DONE");
            return {};
        } catch (BreakpointException &ex) {
            ex.data.next_program = currently_active_core;
            ex.data.inputs = runners->at(ex.data.core_name).get_inputs();
            interactive_restart_point = ex.data.breakpoint;
            return ex.data;
        }
    }


    std::optional<debug_checkpoint> emulator_manager::continue_emulation() {
        try{
            run_cores();
            spdlog::info("EMULATION DONE");
            return {};
        } catch (BreakpointException &ex) {
            ex.data.next_program = currently_active_core;
            ex.data.inputs = runners->at(ex.data.core_name).get_inputs();
            interactive_restart_point = ex.data.breakpoint;
            return ex.data;
        }
    }


    void emulator_manager::run_cores() {
        do{
            auto running_cores = sequencer.get_running_cores();

            for(auto &core:running_cores){
                if(!sequencer.is_empty_step()){
                    for(int j = 0; j<core.n_channels; ++j) {
                        runners->at(core.id).inputs_phase(core, j);
                        runners->at(core.id).emulation_phase(j, interactive_restart_point);
                        interactive_restart_point = 0;
                        currently_active_core = sequencer.get_next_core_by_order(core.step_n);
                    }
                    interconnects_phase(emu_spec.interconnects, core);
                }
            }
            sequencer.advance_emulation();
            outputs_manager.process_outputs(running_cores);
        } while (!sequencer.sim_complete());
    }


    debug_checkpoint emulator_manager::step_over() {
        auto current_core = sequencer.get_core_by_id(currently_active_core);
        auto checkpoint = runners->at(currently_active_core).step_over();
        if(checkpoint.completed_round){
            interconnects_phase(emu_spec.interconnects, current_core);
            if(sequencer.is_last_in_sequence(currently_active_core)){
                sequencer.advance_emulation();
                outputs_manager.process_outputs(sequencer.get_running_cores());
            }
            currently_active_core = sequencer.get_next_core_by_order(current_core.step_n);
            // TODO: This implementation does not take into account multirate emulations (use a do while loop)
        }
        checkpoint.inputs = runners->at(checkpoint.core_name).get_inputs();
        checkpoint.next_program = currently_active_core;
        return checkpoint;
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


    void emulator_manager::check_bus_duplicates() {
        if(bus_map.check_duplicates()){
            auto duplicates = bus_map.get_duplicates().dump();
            throw std::domain_error(duplicates);
        }
    }

    std::unordered_map<std::string, disassembled_program> emulator_manager::disassemble() {
        std::unordered_map<std::string, disassembled_program> ret;

        for(auto &p:get_programs()){
            fcore_dis d(p.program.binary);
            ret[p.name] = d.get_diassembled_object();
        }
        return ret;
    }

    void emulator_manager::add_breakpoint(const std::string &s, uint32_t addr) {
        runners->at(s).add_breakpoint(addr);
    }

    void emulator_manager::remove_breakpoint(const std::string &s, uint32_t addr) {
        runners->at(s).remove_breakpoint(addr);
    }

    void emulator_manager::set_specs(const nlohmann::json &spec_file) {
        runners->clear();
        sequencer.clear();
        outputs_manager.clear();
        bus_map.clear();
        emu_spec.set_specs(spec_file);
    }

    std::set<uint32_t> emulator_manager::get_breakpoints(const std::string &id) {
        if(runners->contains(id)){
            return runners->at(id).get_breakpoints();
        } else {
            return {};
        }
    }


}