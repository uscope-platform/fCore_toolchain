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


#include "emulator/v1/emulator_manager.hpp"


namespace fcore::emulator {


    emulator_manager::emulator_manager() {
        debug_autogen = false;
        current_channel = 0;
        multichannel_debug = true;
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

    std::vector<deployer_interconnect_slot> emulator_manager::get_interconnects() {

        std::map<std::string, std::set<std::string>> interconnect_exposed_outputs;

        std::vector<deployer_interconnect_slot> res;
        for(auto &i:emu_spec.interconnects) {
            for(auto &c:i.channels) {
                std::vector<deployer_interconnect_slot> slots;
                switch(c.type) {
                    case dma_link_scalar:
                        slots.push_back(process_scalar_channel(c,i.source_core_id));
                        break;
                    case dma_link_scatter:
                        slots = process_scatter_channel(c,i.source_core_id);
                        break;
                    case dma_link_gather:
                        slots = process_gather_channel(c,i.source_core_id);
                        break;
                    case dma_link_vector:
                        slots = process_vector_channel(c,i.source_core_id);
                        break;
                    case dma_link_2d_vector:
                        slots = process_2d_vector_channel(c,i.source_core_id);
                        break;
                }
                interconnect_exposed_outputs[i.source_core_id].insert(c.source.io_name);
                res.insert(res.end(), slots.begin(), slots.end());
            }
        }

        for(auto &core:emu_spec.cores) {
            for(auto &out: core.outputs) {
                for(int j = 0; j<out.address.size(); j++){
                    for(int i = 0; i<core.channels; i++){
                        if(!interconnect_exposed_outputs[core.id].contains(out.name)){
                            fcore::deployer_interconnect_slot e;
                            e.source_id = core.id;
                            e.destination_bus_address = get_free_address(out.address[j] + 1000*i, res);
                            e.source_io_address = out.address[j];
                            e.source_channel = i;
                            e.destination_channel = 0;
                            e.type = 'o';

                            e.metadata.is_signed = out.metadata.is_signed;
                            e.metadata.type = out.metadata.type;
                            e.metadata.width = out.metadata.width;

                            res.push_back(e);
                        }
                    }
                }
            }
        }
        return res;
    }

    uint16_t emulator_manager::get_free_address(uint16_t original_addr, const std::vector<deployer_interconnect_slot> &bm) {
        if(is_bus_address_free(original_addr, bm)){
            return original_addr;
        }

        for(uint32_t i = bm.size(); i<(1<<16); i++){
            if(is_bus_address_free(i, bm)){
                return i;
            }
        }
        throw std::runtime_error("Unable to find free bus address");
    }

    bool emulator_manager::is_bus_address_free(uint16_t addr, const std::vector<deployer_interconnect_slot> &bm) {
        if (std::ranges::any_of(bm,  [&addr](const fcore::deployer_interconnect_slot& e) { return e.destination_bus_address == addr;})){
            return false;
        } else{
            return true;
        }
    }

    std::optional<debug_checkpoint> emulator_manager::emulate() {
        interactive_restart_point = 0;
        ic_manager.clear_repeater();
        ic_manager.set_runners(runners);
        outputs_manager.set_runners(runners);

        sequencer.calculate_sequence();
        outputs_manager.set_simulation_frequency(sequencer.get_simulation_frequency());

        for (auto &val: *runners | std::views::values) {
            val.set_multichannel_debug(multichannel_debug);
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
                if(!sequencer.is_empty_step()){
                    if(!is_in_progress) {
                        current_channel = 0;
                        interactive_restart_point = 0;
                    }
                    do {
                        spdlog::trace("Start round {0} on channel {1}, from instruction {2}", sequencer.get_current_step(), current_channel, interactive_restart_point);
                        runners->at(core.id).inputs_phase(core, current_channel);
                        runners->at(core.id).emulation_phase(current_channel, interactive_restart_point);
                        runners->at(core.id).reset_instruction_pointer();
                        interactive_restart_point = 0;
                        currently_active_core = sequencer.get_next_core_by_order(core.order);
                        current_channel++;
                    } while (current_channel < core.n_channels);
                    is_in_progress = false;
                    interconnects_phase(emu_spec.interconnects, core);
                }
            }
            sequencer.advance_emulation();
            outputs_manager.process_outputs(running_cores);
        } while (!sequencer.sim_complete());
    }


    debug_checkpoint emulator_manager::step_over() {
        spdlog::trace("step over of core: {0}, channel {1}", currently_active_core, current_channel);
        auto current_core = sequencer.get_core_by_id(currently_active_core);
        auto checkpoint = runners->at(currently_active_core).step_over(current_channel);
        interactive_restart_point++;
        if(checkpoint.completed_round){
            interconnects_phase(emu_spec.interconnects, current_core);
            runners->at(currently_active_core).reset_instruction_pointer();
            if (current_channel==current_core.n_channels-1) {
                current_channel = 0;
                if(sequencer.is_last_in_sequence(currently_active_core)){
                    sequencer.advance_emulation();
                    outputs_manager.process_outputs(sequencer.get_running_cores());
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

deployer_interconnect_slot emulator_manager::process_scalar_channel(const dma_channel &c, const std::string &source_core) {
    deployer_interconnect_slot e;
    e.source_id = source_core;
    e.destination_bus_address =  c.destination.address[0];
    e.destination_channel = c.destination.channel[0];
    e.source_io_address = c.source.address[0];
    e.source_channel = c.source.channel[0];
    e.type = "o";
    e.metadata.type = type_float;
    e.metadata.is_signed = false;
    e.metadata.width = 32;
    return e;
}

std::vector<deployer_interconnect_slot> emulator_manager::process_scatter_channel(const dma_channel &c, const std::string &source_core) {
    std::vector<deployer_interconnect_slot>ret;
    for(uint32_t i = 0; i<c.length; i++){
        deployer_interconnect_slot e;
        e.source_id  = source_core;
        e.source_io_address = c.source.address[0] + i;
        e.source_channel = c.destination.channel[0];
        e.destination_bus_address =  c.destination.address[0];
        e.destination_channel = c.destination.channel[0] + i;
        e.type = "o";
        e.metadata.type = type_float;
        e.metadata.is_signed = false;
        e.metadata.width = 32;
        ret.push_back(e);
    }
        return ret;
}

std::vector<deployer_interconnect_slot> emulator_manager::process_gather_channel(const fcore::emulator::dma_channel &c, const std::string &source_core) {
        std::vector<deployer_interconnect_slot>ret;
        for(uint32_t i = 0; i<c.length; i++){
        deployer_interconnect_slot e;
        e.source_id = source_core;
        e.source_io_address = c.source.address[0];
        e.source_channel =  c.destination.channel[0] + i;
        e.destination_bus_address =  c.destination.address[0] + i;
        e.destination_channel = c.destination.channel[0];
        e.type = "o";
        e.metadata.type = type_float;
        e.metadata.is_signed = false;
        e.metadata.width = 32;
        ret.push_back(e);
    }
    return ret;
}

std::vector<deployer_interconnect_slot> emulator_manager::process_vector_channel(const fcore::emulator::dma_channel &c, const std::string &source_core) {
    std::vector<deployer_interconnect_slot>ret;
    for(uint32_t i = 0; i<c.length; i++){
        deployer_interconnect_slot e;
        e.source_id = source_core;
        e.source_io_address = c.source.address[0];
        e.source_channel = c.source.channel[0] + i;
        e.destination_bus_address =  c.destination.address[0];
        e.destination_channel = c.destination.channel[0] + i;
        e.type = "o";
        e.metadata.type = type_float;
        e.metadata.is_signed = false;
        e.metadata.width = 32;
        ret.push_back(e);
    }
    return ret;
}

std::vector<deployer_interconnect_slot> emulator_manager::process_2d_vector_channel(const fcore::emulator::dma_channel &c, const std::string &source_core) {
    std::vector<deployer_interconnect_slot>ret;
    for(uint32_t j = 0; j<c.stride; j++){
        for(uint32_t i = 0; i<c.length; i++){
            deployer_interconnect_slot e;
            e.source_id = source_core;
            e.source_io_address = c.source.address[0] + j;
            e.source_channel = c.source.channel[0] + i;
            e.destination_bus_address =  c.destination.address[0] + j;
            e.destination_channel = c.destination.channel[0] + i;
            e.type = "o";
            e.metadata.type = type_float;
            e.metadata.is_signed = false;
            e.metadata.width = 32;
            ret.push_back(e);
        }
    }

        return ret;

}

uint64_t emulator_manager::get_rom_address(const std::string &core) {
    for(auto &p:emu_spec.cores) {
        if(p.id == core) {
            return p.deployment.rom_address;
        }
    }
    return 0;
}

uint64_t emulator_manager::get_control_address(const std::string &core) {
    for(auto &p:emu_spec.cores) {
        if(p.id == core) {
            return p.deployment.rom_address;
        }
    }
    return 0;
}
}
