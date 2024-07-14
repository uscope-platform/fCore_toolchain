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


    emulator_manager::emulator_manager(nlohmann::json &spec, bool dbg, const std::string& s_f) :
    emu_spec(spec, s_f + "/emulator_spec_schema.json"){
        debug_autogen = dbg;

        emu_length = 1;

    }

    void emulator_manager::process() {
        bus_map.clear();

        emulator_builder e_b(debug_autogen);


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

        interconnects = load_interconnects(emu_spec.interconnects);
        sequencer.setup_run(emu_spec.emulation_time);

        check_bus_duplicates();
    }

    std::vector<program_bundle> emulator_manager::get_programs() {
        bus_map.clear();
        emulator_builder e_b(debug_autogen);
        std::vector<program_bundle> res;

        for(auto &core:emu_spec.cores){

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
                std::vector<emulator::emulator_interconnect> src = {};
                std::vector<emulator::emulator_interconnect> dst = {};
                for(auto &ic:emu_spec.interconnects){
                    if(core.id == ic.source_core_id) src.push_back(ic);
                    if(core.id == ic.destination_core_id) dst.push_back(ic);
                }
                b.program = e_b.compile_program(core, dst, src, b.io);
                b.program_length = e_b.get_program_info();

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
        output_repeater.clear();
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
                        inputs_phase(core, sel_prog, j);
                        execution_phase(core, sel_prog, j);
                    }
                    interconnects_phase(core, sequencer.get_enabled_cores());
                }

                outputs_manager.process_outputs(
                        core.id,
                        emulators_memory[core.id],
                        core.running,
                        sel_prog.active_channels,
                        sel_prog.io
                );
            }

        }
        spdlog::info("EMULATION DONE");
    }


    void emulator_manager::inputs_phase(const core_step_metadata& info, program_bundle &prog, uint32_t  channel) {

        // APPLY INPUTS (ONLY WHEN THE EMULATOR IS RUN TO AVOID POTENTIALLY DESTROYING THE OUTPUTS IN MEMORY)
        if(info.running){
            for(auto &in:prog.input){
                uint32_t core_reg = 0;
                auto io_addr = in.address[0];

                if(auto core_addr = io_map_entry::get_io_map_entry_by_io_addr(prog.io, io_addr)){
                    core_reg = core_addr->core_addr;
                } else {
                    throw std::runtime_error("unable to find input address in the core io map during input phase");
                }

                if(core_reg != 0){
                    uint32_t input_val;
                    if(in.data_type==emulator::type_float){
                        std::vector<float> in_vect = std::get<std::vector<float>>(in.data[channel]);
                        if(in.source_type == emulator::constant_input){
                            input_val = emulator_backend::float_to_uint32(in_vect[0]);
                        } else  {
                            input_val = emulator_backend::float_to_uint32(in_vect[info.step_n]);
                        }
                    } else {

                        std::vector<uint32_t> in_vect = std::get<std::vector<uint32_t>>(in.data[channel]);
                        if(in.source_type == emulator::constant_input){
                            input_val = in_vect[0];
                        } else  {
                            input_val = in_vect[info.step_n];
                        }
                    }
                    emulators_memory[info.id][in.channel[channel]]->at(core_reg) = input_val;
                }
            }
        }

    }

    void emulator_manager::execution_phase(const core_step_metadata& info, program_bundle &prog, uint32_t  channel) {

            if(info.running){
                // TODO: implement progress tracing

                backend.set_core_name(info.id);
                backend.set_program(emulator_builder::sanitize_program(prog.program));
                backend.set_efi_selector(prog.efi_selector);
                backend.set_comparator_type(prog.comparator_type);
                backend.run_round(emulators_memory[info.id][channel]);
            }
    }

    void emulator_manager::interconnects_phase(const core_step_metadata& info, std::unordered_map<std::string, bool> enabled_cores) {

        for(auto &conn:interconnects){
            if(info.id == conn.source){

                for(auto &reg:conn.connections){
                    uint32_t first_address, second_address;

                    auto src_prog =get_bundle_by_name(conn.source);
                    auto dst_prog =get_bundle_by_name(conn.destination);


                    if(auto a = io_map_entry::get_io_map_entry_by_io_addr(src_prog.io, reg.first.address)){
                        first_address = a->core_addr;
                    } else{
                        throw std::runtime_error("Unable to find io address in the source address map");
                    }
                    if(auto a = io_map_entry::get_io_map_entry_by_io_addr(dst_prog.io, reg.second.address)){
                        second_address = a->core_addr;
                    } else{
                        throw std::runtime_error("Unable to find io address in the destination address map");
                    }

                    if(enabled_cores[conn.source]){

                        auto val = emulators_memory[conn.source][reg.first.channel]->at(first_address);
                        output_repeater.add_output(conn.source, first_address, val);
                        emulators_memory[conn.destination][reg.second.channel]->at(second_address) = val;
                    } else {
                        auto val = output_repeater.get_output(conn.source, first_address);
                        emulators_memory[conn.destination][reg.second.channel]->at(second_address) = val;
                    }
                }
            }
        }
    }



    std::string emulator_manager::get_results() {
        nlohmann::json res;
        for(auto &item:programs){
            nlohmann::json j;
            nlohmann::json outputs_json;

            j["outputs"] = outputs_manager.get_emulation_output(item.name);
            j["error_code"] = errors[item.name];
            res[item.name] = j;
        }


        res["timebase"] = outputs_manager.get_timebase();
        return res.dump(4);
    }


    std::vector<interconnect_t> emulator_manager::load_interconnects(const std::vector<emulator::emulator_interconnect>& itc) {
        std::vector<interconnect_t> res;
        for(auto &item:itc){
            interconnect_t i;
            i.source = item.source_core_id;
            i.destination = item.destination_core_id;
            for(auto &ch: item.channels){
                register_spec_t rs_s;
                register_spec_t rs_d;

                uint32_t source_ch = ch.source.channel[0];
                uint32_t source_addr= ch.source.address[0];
                uint32_t dest_ch = ch.destination.channel[0];
                uint32_t dest_addr = ch.destination.address[0];

                switch (ch.type) {
                    case emulator::dma_link_scatter:
                        for(uint32_t j = 0; j<ch.length; j++){
                            rs_s.channel = source_ch+j;
                            rs_s.address = source_addr;
                            rs_d.channel = dest_ch;
                            rs_d.address = dest_addr+j;
                            bus_map.add_entry(item.source_core_id, "interconnect", dest_addr, ch.name);
                            i.connections.emplace_back(rs_s,rs_d);
                        }
                        break;
                    case emulator::dma_link_vector:
                        for(uint32_t j = 0; j<ch.length; j++){
                            rs_s.channel = source_ch+j;
                            rs_s.address = source_addr;
                            rs_d.channel = dest_ch+j;
                            rs_d.address = dest_addr;
                            bus_map.add_entry(item.source_core_id, "interconnect", dest_addr, ch.name);
                            i.connections.emplace_back(rs_s,rs_d);
                        }
                        break;
                    case emulator::dma_link_scalar:
                        rs_s.channel = source_ch;
                        rs_s.address = source_addr;
                        rs_d.channel = dest_ch;
                        rs_d.address = dest_addr;
                        bus_map.add_entry(item.source_core_id, "interconnect", dest_addr, ch.name);
                        i.connections.emplace_back(rs_s,rs_d);
                        break;
                    case emulator::dma_link_gather:
                        for(uint32_t  j = 0; j<ch.length; j++){
                            rs_s.channel = source_ch;
                            rs_s.address = source_addr+j;
                            rs_d.channel = dest_ch+j;
                            rs_d.address = dest_addr;
                            bus_map.add_entry(item.source_core_id, "interconnect", dest_addr, ch.name);
                            i.connections.emplace_back(rs_s,rs_d);
                        }
                        break;
                    case emulator::dma_link_2d_vector:
                        uint32_t transfer_stride = ch.stride;
                        for (uint32_t  k = 0; k < transfer_stride; k++) {
                            for(uint32_t  j = 0; j<ch.length; j++) {
                                rs_s.channel = source_ch + j;
                                rs_s.address = source_addr + k;
                                rs_d.channel = dest_ch + j;
                                rs_d.address = dest_addr + k;
                                bus_map.add_entry(item.source_core_id, "interconnect", dest_addr + k, ch.name);
                                i.connections.emplace_back(rs_s, rs_d);
                            }
                        }
                        break;
                }

            }
            res.push_back(i);
        }
        return res;
    }

    std::shared_ptr<std::vector<uint32_t>> emulator_manager::get_memory_snapshot(const std::string &core_id, int channel) {
        return emulators_memory[core_id][channel];
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
            if(item.data_type == emulator::type_float){
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
            emulators_memory[item.name] = pool;


            auto mem = io_remap_memory_init(item.memories, item.io);

            for(auto &init_val: mem){
                // TODO: Add support for per channel initialization
                for(const auto& reg_file:emulators_memory[item.name]){
                    reg_file.second->at(init_val.first) = init_val.second;
                }
            }
        }
    }


}