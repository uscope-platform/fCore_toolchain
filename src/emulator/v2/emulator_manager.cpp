//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "emulator/v2/emulator_manager.hpp"


namespace fcore::emulator_v2 {


    emulator_manager::emulator_manager() {
        debug_autogen = false;
        current_channel = 0;
        multichannel_debug = true;
        runners = std::make_shared<std::unordered_map<std::string, emulator_runner>>();
        interactive_restart_point = 0;
    }

    std::vector<deployed_program> emulator_manager::deploy_programs() {
        std::vector<deployed_program> ret;
        auto bundles = get_programs();
        for(int i = 0; i<bundles.size(); i++) {
            deployed_program dp;
            dp.index = i;
            dp.order = bundles[i].execution_order;
            dp.sampling_frequency = bundles[i].sampling_frequency;
            dp.n_channels = bundles[i].active_channels;
            dp.name = bundles[i].name;
            dp.program = bundles[i].program;
            for(int j = 0; j<bundles[i].input.size(); j++) {
                dp.inputs.push_back({});
                dp.inputs[j].name = bundles[i].input[j].name;
                dp.inputs[j].data = bundles[i].input[j].data;
                dp.inputs[j].metadata.is_signed = bundles[i].input[j].metadata.is_signed;
                dp.inputs[j].metadata.type = bundles[i].input[j].metadata.type;
                dp.inputs[j].metadata.width = bundles[i].input[j].metadata.width;
                dp.inputs[j].source_type = bundles[i].input[j].source_type;
            }
            ret.push_back(dp);
        }
        return ret;
    }

    void emulator_manager::process() {

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
            sequencer.add_core(core.id, core.sampling_frequency, core.order, core.channels);

        }
        outputs_manager.process_specs(ic_manager.get_bus_engine());
        sequencer.setup_run(emu_spec.emulation_time);


        outputs_manager.set_initial_values(emu_spec.get_outputs_initial_values());

        for(auto &p:programs){
            emulator_runner r(p, ic_manager.get_bus_engine());
            runners->insert({p.name, r});
        }
    }

    std::vector<program_bundle> emulator_manager::get_programs() {
        auto bus_engine = ic_manager.get_bus_engine();
        emulator_builder e_b(debug_autogen, bus_engine);
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

                b.program = e_b.compile_program(core, b.io);

            } catch(std::runtime_error &e){
                errors[core.id] = e.what();
            }

            res.push_back(b);
        }
        return res;
    }

    std::vector<deployed_core_inputs> emulator_manager::get_inputs(const std::string &core) {
        std::vector<deployed_core_inputs> ret;
        auto engine = ic_manager.get_bus_engine();
        for(const auto& prog:emu_spec.cores) {
            if(core == prog.id) {
                for(auto &in : prog.inputs) {
                    deployed_core_inputs dci;
                    dci.name = in.name;
                    for(int i = 0; i<in.vector_size; i++) {
                        dci.address.push_back(engine->get_input_address(core, in.name, i));
                    }
                    dci.channel = in.channel;
                    dci.data = in.data;
                    dci.metadata.is_signed = in.metadata.is_signed;
                    dci.metadata.type = in.metadata.type;
                    dci.metadata.width = in.metadata.width;
                    dci.source_type = in. source_type;
                    dci.waveform_parameters = in.waveform_parameters;
                    ret.push_back(dci);
                }
                return ret;
            }
        }
        throw std::runtime_error("Could not find core " + core);
    }

    std::vector<deployer_interconnect_slot> emulator_manager::process_scalar_channel(const interconnect_descriptor &ic) {
        deployer_interconnect_slot e;
        e.source_id = ic.source.core_name;
        e.source_name = ic.source.port_name;
        e.destination_id = ic.destination.core_name;
        e.destination_name = ic.destination.port_name;
        e.destination_bus_address = ic.destination_addresses[0];
        e.source_io_address = ic.source_addresses[0];
        e.source_channel = 0;
        e.destination_channel =0;
        e.type = 'c';
        e.metadata = ic.source_metadata;
        return {e};
    }

    std::vector<deployer_interconnect_slot> emulator_manager::process_scatter_channel(const interconnect_descriptor &ic) {
        std::vector<deployer_interconnect_slot> ret;
        for(int i = 0; i<ic.destination_shape.channels; i++){
            deployer_interconnect_slot e;
            e.source_id = ic.source.core_name;
            e.source_name = ic.source.port_name;
            e.destination_id = ic.destination.core_name;
            e.destination_name = ic.destination.port_name;
            e.destination_bus_address = ic.destination_addresses[0];
            e.source_io_address = ic.source_addresses[i];
            e.source_channel = 0;
            e.destination_channel =i;
            e.type = 'c';
            e.metadata = ic.source_metadata;
            ret.push_back(e);
        }
        return ret;
    }

    std::vector<deployer_interconnect_slot> emulator_manager::process_gather_channel(const interconnect_descriptor &ic) {
        std::vector<deployer_interconnect_slot> ret;
        for(int i = 0; i<ic.source_shape.channels; i++){
            deployer_interconnect_slot e;
            e.source_id = ic.source.core_name;
            e.source_name = ic.source.port_name;
            e.destination_id = ic.destination.core_name;
            e.destination_name = ic.destination.port_name;
            e.destination_bus_address = ic.destination_addresses[i];
            e.source_io_address = ic.source_addresses[0];
            e.source_channel = i;
            e.destination_channel =0;
            e.type = 'c';
            e.metadata = ic.source_metadata;
            ret.push_back(e);
        }
        return ret;
    }

    std::vector<deployer_interconnect_slot> emulator_manager::process_vector_channel(const interconnect_descriptor &ic) {
        std::vector<deployer_interconnect_slot> ret;
        for(int i = 0; i<ic.source_shape.channels; i++){
            deployer_interconnect_slot e;
            e.source_id = ic.source.core_name;
            e.source_name = ic.source.port_name;
            e.destination_id = ic.destination.core_name;
            e.destination_name = ic.destination.port_name;
            e.destination_bus_address = ic.destination_addresses[0];
            e.source_io_address = ic.source_addresses[0];
            e.source_channel = i;
            e.destination_channel =i;
            e.type = 'c';
            e.metadata = ic.source_metadata;
            ret.push_back(e);
        }
        return ret;
    }

    std::vector<deployer_interconnect_slot> emulator_manager::process_2d_vector_channel(const interconnect_descriptor &ic) {
        std::vector<deployer_interconnect_slot> ret;
        for(int i = 0; i<ic.source_shape.size; i++) {
            for(int j = 0; j<ic.source_shape.channels; j++) {
                deployer_interconnect_slot e;
                e.source_id = ic.source.core_name;
                e.source_name = ic.source.port_name;
                e.destination_id = ic.destination.core_name;
                e.destination_name = ic.destination.port_name;
                e.destination_bus_address = ic.destination_addresses[i];
                e.source_io_address = ic.source_addresses[i];
                e.source_channel = j;
                e.destination_channel = j;
                e.type = 'c';
                e.metadata = ic.source_metadata;
                ret.push_back(e);
            }
        }
        return ret;
    }

    std::vector<deployer_interconnect_slot> emulator_manager::
    process_partial_channel(const interconnect_descriptor &ic) {
        deployer_interconnect_slot e;
        e.source_id = ic.source.core_name;
        e.source_name = ic.source.port_name;
        e.destination_id = ic.destination.core_name;
        e.destination_name = ic.destination.port_name;
        e.destination_bus_address = ic.destination_addresses[0];
        e.source_io_address = ic.source_addresses[0];
        e.source_channel = ic.partial_channels.first;
        e.destination_channel = ic.partial_channels.second;
        e.type = 'c';
        e.metadata = ic.source_metadata;
        return {e};
    }


    std::vector<deployer_interconnect_slot> emulator_manager::get_interconnects() {

        auto engine = ic_manager.get_bus_engine();
        std::map<std::string, std::set<std::string>> interconnect_exposed_outputs;

        std::vector<deployer_interconnect_slot> slots;
        std::vector<deployer_interconnect_slot> s;
        for(const auto& i: engine->get_interconnects()) {
            switch(i.get_type()) {
                case dma_link_scalar:
                    s = process_scalar_channel(i);
                    break;
                case dma_link_scatter:
                    s = process_scatter_channel(i);
                    break;
                case dma_link_gather:
                    s = process_gather_channel(i);
                    break;
                case dma_link_vector:
                    s = process_vector_channel(i);
                    break;
                case dma_link_2d_vector:
                    s = process_2d_vector_channel(i);
                    break;
                case dma_link_partial:
                    s = process_partial_channel(i);
                    break;
            }
            interconnect_exposed_outputs[i.source.core_name].insert(i.source.port_name);
            slots.insert(slots.begin(), s.begin(), s.end());
        }

        for(auto &core:emu_spec.cores) {
            for(auto &out: core.outputs) {
                std::vector<uint32_t> addresses;
                if(!interconnect_exposed_outputs[core.id].contains(out.name)) {
                    for(int i = 0; i<out.vector_size; i++) {
                        for(int j = 0; j<core.channels; j++) {
                            deployer_interconnect_slot e;
                            e.source_id = core.id;
                            e.source_name = out.name;
                            e.destination_bus_address = engine->get_free_address(core.id, out.name, i);
                            e.destination_channel = j;

                            e.source_io_address =  engine->get_output_address(core.id, out.name, i);
                            e.source_channel = j;
                            e.type = 'o';

                            e.metadata.is_signed = out.metadata.is_signed;
                            e.metadata.type = out.metadata.type;
                            e.metadata.width = out.metadata.width;

                            slots.push_back(e);
                        }

                    }
                }

            }

            for(auto &mem: core.memories) {
                std::vector<uint32_t> addresses;
                if(!interconnect_exposed_outputs[core.id].contains(mem.name)) {
                    for(int i = 0; i<mem.vector_size; i++) {
                        for(int j = 0; j<core.channels; j++) {
                            if(mem.is_output) {
                                deployer_interconnect_slot e;
                                e.source_id = core.id;
                                e.source_name = mem.name;
                                e.destination_bus_address = engine->get_free_address(core.id, mem.name, i);
                                e.destination_channel = j;

                                e.source_io_address =  engine->get_output_address(core.id, mem.name, i);
                                e.source_channel = j;
                                e.type = 'm';

                                e.metadata.is_signed = mem.metadata.is_signed;
                                e.metadata.type = mem.metadata.type;
                                e.metadata.width = mem.metadata.width;

                                slots.push_back(e);
                            }

                        }

                    }
                }

            }
        }
        return slots;
    }

    std::optional<debug_checkpoint> emulator_manager::emulate() {
        interactive_restart_point = 0;
        ic_manager.clear_repeater();
        ic_manager.set_runners(runners);
        outputs_manager.set_runners(runners);

        sequencer.calculate_sequence();
        auto sim_freq = sequencer.get_simulation_frequency();
        outputs_manager.set_simulation_frequency(sim_freq);

        for (auto &val: *runners | std::views::values) {
            val.set_multichannel_debug(multichannel_debug);
        }


        for(auto &core:emu_spec.cores) {
            for(auto &in:core.inputs) {
                if(in.source_type == waveform_input) {
                    runners->at(core.id).add_waveform(in.name, in.waveform_parameters);
                }
            }
            runners->at(core.id).set_wavegen_sampling_frequency(sim_freq);
        }

        spdlog::info("EMULATION START");
        try{
            currently_active_core = sequencer.get_core_by_order(1);
            run_cores(false);
            spdlog::info("EMULATION DONE");
            return {};
        } catch (BreakpointException &ex) {
            interactive_restart_point = ex.data.breakpoint;
            return augment_checkpoint_info(ex.data);
        }
    }


    std::optional<debug_checkpoint> emulator_manager::continue_emulation() {
        try{
            run_cores(true);
            auto end_state = runners->at(currently_active_core).get_end_state();
            end_state.next_program = "";
            end_state.inputs =  runners->at(currently_active_core).get_inputs();
            end_state.progress = sequencer.get_progress();
            end_state.progress.channel = current_channel-1;

            spdlog::info("EMULATION DONE");
            return end_state;
        } catch (BreakpointException &ex) {
            interactive_restart_point = ex.data.breakpoint;
            return augment_checkpoint_info(ex.data);
        }
    }


    void emulator_manager::run_cores(bool in_progress) {
        bool is_in_progress = in_progress;
        do{
            auto running_cores = sequencer.get_running_cores();

            for(auto &core:running_cores){
                if(!sequencer.is_empty_step() && core.running){
                    if(!is_in_progress) {
                        current_channel = 0;
                        interactive_restart_point = 0;
                    }
                    do {
                        spdlog::trace("Start round {} for core {} on channel {}, from instruction {}",
                        sequencer.get_current_step(),core.id, current_channel, interactive_restart_point);
                        runners->at(core.id).inputs_phase(core, current_channel);
                        runners->at(core.id).emulation_phase(current_channel, interactive_restart_point);
                        runners->at(core.id).reset_instruction_pointer();
                        interactive_restart_point = 0;
                        currently_active_core = sequencer.get_next_core_by_order(core.order);
                        current_channel++;
                    } while (current_channel < core.n_channels);
                    is_in_progress = false;
                } else {
                    runners->at(core.id).advance_inputs();
                }
                outputs_manager.process_outputs(running_cores, core.id);
                ic_manager.run_interconnect(core.id, sequencer.get_enabled_cores());
            }
            sequencer.advance_emulation();
        } while (!sequencer.sim_complete());
    }


    debug_checkpoint emulator_manager::step_over() {
        spdlog::trace("step over of core: {0}, channel {1}", currently_active_core, current_channel);
        auto current_core = sequencer.get_core_by_id(currently_active_core);
        auto checkpoint = runners->at(currently_active_core).step_over(current_channel);
        interactive_restart_point++;
        if(checkpoint.completed_round){
            ic_manager.run_interconnect(current_core.id, sequencer.get_enabled_cores());
            runners->at(currently_active_core).reset_instruction_pointer();
            if (current_channel==current_core.n_channels-1) {
                current_channel = 0;
                if(sequencer.is_last_in_sequence(currently_active_core)){
                    sequencer.advance_emulation();
                    outputs_manager.process_outputs(sequencer.get_running_cores(), "");
                }
            } else {
                current_channel++;
            }

            currently_active_core = sequencer.get_next_core_by_order(current_core.order);
            if(sequencer.sim_complete()){
                checkpoint.status = "complete";
            } else {
                checkpoint.status = "in_progress";
            }
            interactive_restart_point = 0;
            // TODO: This implementation does not take into account multirate emulations (use a do while loop)
        }
        checkpoint.inputs = runners->at(checkpoint.core_name).get_inputs();
        checkpoint.next_program = currently_active_core;
        checkpoint.progress = sequencer.get_progress();
        checkpoint.progress.channel = current_channel;

        return checkpoint;
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


        res["timebase"] = sequencer.get_timebase();
        return res;
    }


    std::unordered_map<std::string, std::vector<memory_init_value>> emulator_manager::get_memory_init_values() {

        auto engine = ic_manager.get_bus_engine();
        std::unordered_map<std::string, std::vector<memory_init_value>> ret;
        for(auto &core:emu_spec.cores) {
            for(const auto& mem_init: core.memories) {
                memory_init_value val;
                for(int i = 0; i<mem_init.vector_size; i++) {
                    uint32_t address;
                    if(mem_init.is_input) {
                        address= engine->get_input_address(core.id, mem_init.name, i);
                    } else {
                        address= engine->get_output_address(core.id, mem_init.name, i);
                    }
                    val.address.push_back(address);
                }
                val.value = mem_init.value;
                ret[core.id].push_back(val);
            }
        }
        return ret;
    }


    std::unordered_map<std::string, disassembled_program> emulator_manager::disassemble() {
        std::unordered_map<std::string, disassembled_program> ret;

        for(auto &p:get_programs()){
            fcore_dis d(p.program.binary);
            auto obj = d.get_diassembled_object();

            for(auto &[io_addr, table_entry]: obj.translation_table) {
                for(auto &io_entry:p.io) {
                    if(io_addr == io_entry.io_addr) {
                        table_entry.name = io_entry.io_name;
                    }
                }
            }

            for(auto &[io_addr, table_entry]: obj.common_io_translation_table) {
                for(auto &io_entry:p.io) {
                    if(io_addr == io_entry.io_addr) {
                        table_entry.name = io_entry.io_name;
                    }
                }
            }

            ret[p.name] = obj;
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
        emu_spec.parse(spec_file);
        ic_manager.set_emulation_specs(emu_spec);
    }

    std::set<uint32_t> emulator_manager::get_breakpoints(const std::string &id) {
        if(runners->contains(id)){
            return runners->at(id).get_breakpoints();
        } else {
            return {};
        }
    }

    void emulator_manager::set_multichannel_debug(bool mc) {
        multichannel_debug = mc;
    }

    debug_checkpoint emulator_manager::augment_checkpoint_info(debug_checkpoint &in) {
        debug_checkpoint d = in;
        d.next_program = currently_active_core;
        d.inputs = runners->at(d.core_name).get_inputs();
        d.progress = sequencer.get_progress();
        d.progress.channel = current_channel;
        return d;
    }


}