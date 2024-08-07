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
                    interconnects_phase(emu_spec.interconnects, core, sequencer.get_enabled_cores());
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
                backend.set_program(emulator_builder::sanitize_program(prog.program.binary));
                backend.set_efi_selector(prog.efi_selector);
                backend.set_comparator_type(prog.comparator_type);
                backend.run_round(emulators_memory[info.id][channel]);
            }
    }

    void emulator_manager::interconnects_phase(const std::vector<emulator::emulator_interconnect> &specs, const core_step_metadata& info, std::unordered_map<std::string, bool> enabled_cores) {

        for(auto &conn:specs){
            if(info.id == conn.source_core_id){

                for(auto &ch:conn.channels){

                    switch (ch.type) {
                        case emulator::dma_link_scalar:
                            run_scalar_transfer(ch, conn.source_core_id, conn.destination_core_id, enabled_cores[conn.source_core_id]);
                            break;
                        case emulator::dma_link_scatter:
                            run_scatter_transfer(ch, conn.source_core_id, conn.destination_core_id, enabled_cores[conn.source_core_id]);
                            break;
                        case emulator::dma_link_gather:
                            run_gather_transfer(ch, conn.source_core_id, conn.destination_core_id, enabled_cores[conn.source_core_id]);
                            break;
                        case emulator::dma_link_vector:
                            run_vector_transfer(ch, conn.source_core_id, conn.destination_core_id, enabled_cores[conn.source_core_id]);
                            break;
                        case emulator::dma_link_2d_vector:
                            run_2d_vector_transfer(ch, conn.source_core_id, conn.destination_core_id, enabled_cores[conn.source_core_id]);
                            break;
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

    void emulator_manager::run_scalar_transfer(
            const emulator::dma_channel &c,
            const std::string &src_core,
            const std::string &dst_core,
            bool enabled
    ) {
        spdlog::trace("SCALAR TRANSFER");
        auto src_addr = translate_address(src_core, c.source.address[0], 0);
        auto dst_addr = translate_address(dst_core, c.destination.address[0], 0);

        transfer_register(src_core, dst_core, src_addr, dst_addr, 0, 0, enabled);

    }

    void emulator_manager::run_scatter_transfer(
            const emulator::dma_channel &c,
            const std::string &src_core,
            const std::string &dst_core,
            bool enabled
            ) {
        spdlog::trace("SCATTER TRANSFER");
        for(int i = 0; i<c.length; i++){
            auto src_addr = translate_address(src_core, c.source.address[0], i);
            auto dst_addr = translate_address(dst_core, c.destination.address[0], 0);

            transfer_register(src_core, dst_core, src_addr, dst_addr, 0, i, enabled);
        }
    }

    void emulator_manager::run_gather_transfer(
            const emulator::dma_channel &c,
            const std::string &src_core,
            const std::string &dst_core,
            bool enabled
            ) {

        spdlog::trace("GATHER TRANSFER");
        for(int i = 0; i<c.length; i++){
            auto src_addr = translate_address(src_core, c.source.address[0], 0);
            auto dst_addr = translate_address(dst_core, c.destination.address[0], i);

            transfer_register(src_core, dst_core, src_addr, dst_addr, i, 0, enabled);
        }
    }

    void emulator_manager::run_vector_transfer(
            const emulator::dma_channel &c,
            const std::string &src_core,
            const std::string &dst_core,
            bool enabled
            ) {
        spdlog::trace("VECTOR TRANSFER");
        for(int i = 0; i<c.length; i++){
            auto src_addr = translate_address(src_core, c.source.address[0], 0);
            auto dst_addr = translate_address(dst_core, c.destination.address[0], 0);

            transfer_register(src_core, dst_core, src_addr, dst_addr, i, i, enabled);
        }
    }

    void emulator_manager::run_2d_vector_transfer(
            const emulator::dma_channel &c,
            const std::string &src_core,
            const std::string &dst_core,
            bool enabled
            ) {
        spdlog::trace("2D VECTOR TRANSFER");
        for(int j = 0; j<c.stride; j++){
            for(int i = 0; i<c.length; i++){
                auto src_addr = translate_address(src_core, c.source.address[j], 0);
                auto dst_addr = translate_address(dst_core, c.destination.address[j], 0);

                transfer_register(src_core, dst_core, src_addr, dst_addr, i, i, enabled);
            }
        }
        int i = 0;
    }

    void emulator_manager::transfer_register(const std::string& src_core, const std::string& dst_core,
                                             uint32_t src_addr, uint32_t dst_addr,
                                             uint32_t src_channel, uint32_t dst_channel,
                                             bool src_enabled) {

        spdlog::trace("REGISTER TO REGISTER TRANSFER: source {0} | target {1} | source pair ({2}, {3}) | target pair ({4}, {5})", src_core,dst_core, src_channel,src_addr, dst_channel,dst_addr);

        if(dst_channel>=emulators_memory[dst_core].size()){
            throw std::runtime_error("Attempted write to unavailable channel: " + std::to_string(dst_channel) + " of core: " + dst_core);
        }
        if(src_enabled){
            if(src_channel>=emulators_memory[src_core].size()){
                throw std::runtime_error("Attempted read from unavailable channel: " + std::to_string(src_channel) + " of core: " + src_core);
            }
            auto val = emulators_memory[src_core][src_channel]->at(src_addr);
            output_repeater.add_output(src_core, src_addr,src_channel, val);
             emulators_memory[dst_core][dst_channel]->at(dst_addr) = val;
        } else {
            auto val = output_repeater.get_output(src_core, src_addr, src_channel);
            emulators_memory[dst_core][dst_channel]->at(dst_addr) = val;
        }
    }

    uint32_t emulator_manager::translate_address(const std::string& core_id, uint32_t io_addr, uint32_t offset) {

        auto bundle =get_bundle_by_name(core_id);

        if(auto a = io_map_entry::get_io_map_entry_by_io_addr(bundle.io, io_addr + offset)){
            auto core_addr = a->core_addr;
            spdlog::trace("ADDRESS TRANSLATION: core {0} | io address {1} | core address {2}", core_id, io_addr + offset, core_addr);
            return core_addr;
        } else{
            throw std::runtime_error("Unable to find io address " + std::to_string(io_addr + offset) + " in the source address map for core: " + core_id);
        }
    }


}