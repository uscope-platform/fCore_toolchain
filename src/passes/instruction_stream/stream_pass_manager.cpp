// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
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

#include "passes/instruction_stream/stream_pass_manager.hpp"


namespace fcore{

    stream_pass_manager::stream_pass_manager(std::shared_ptr<instrumentation_core> &prof,
                                            mode m,
                                            uint8_t n_channels
    ) {
        constructs_pass_manager( prof, m, n_channels);
    }

    stream_pass_manager::stream_pass_manager(
        std::vector<int> &io_res,
        std::shared_ptr<instrumentation_core> &prof,
        mode m
        ) {

        constructs_pass_manager( prof, m, 1);
    }


    void
    stream_pass_manager::constructs_pass_manager(
        std::shared_ptr<instrumentation_core> &prof,
        mode m,
        uint8_t n_channels
    ) {
        allocation_map = std::make_shared<std::map<std::string, std::vector<io_map_entry>>>();
        bindings_map = std::make_shared<std::map<std::string, memory_range_t>>();
        optimizer_mode = m;
        ic = std::make_shared<instruction_count>();
        auto var_map = std::make_shared<variable_map>();
        auto  io_assignment_map = std::make_shared<std::map<std::string, std::pair<int, int>>>();
        passes.push_back(std::make_shared<virtual_operations_implementation>());
        passes.push_back(std::make_shared<uninitialized_variable_detection>());
        passes.push_back(std::make_shared<ternary_deconfliction>());
        passes.push_back(std::make_shared<ternary_reduction>());
        passes.push_back(std::make_shared<io_constant_tracking>(io_assignment_map));
        passes.push_back(std::make_shared<constant_merging>(io_assignment_map));
        passes.push_back(std::make_shared<variable_mapping>(var_map));
        passes.push_back(std::make_shared<variable_lifetime_mapping>(var_map));
        passes.push_back(std::make_shared<register_allocation>(var_map, bindings_map, allocation_map));
        passes.push_back(std::make_shared<zero_assignment_removal_pass>());
        passes.push_back(std::make_shared<bound_register_assignment>());
        passes.push_back(std::make_shared<stall_insertion>(n_channels));
        passes.push_back(std::make_shared<result_deconfliction>(n_channels));
        passes.push_back(std::make_shared<instruction_counting_pass>(ic));

        profiler = prof;
        if(profiler != nullptr) profiler->set_phase("stream processing");
    }


    instruction_stream stream_pass_manager::process_stream(instruction_stream stream) {
        int pass_n = 0;
        instruction_stream ret_val = std::move(stream);
        for(auto &pass:passes){

            bool pass_enabled = pass->pass_type == global_pass;
            pass_enabled |= pass->pass_type == high_level_pass && optimizer_mode == high_level_language;
            pass_enabled |= pass->pass_type == asm_pass && optimizer_mode == asm_language;

            if(pass_enabled){
                if(profiler != nullptr)  profiler->start_event(pass->get_name(), false);
                ret_val = apply_pass(ret_val, pass);
                if(profiler != nullptr) profiler->end_event(pass->get_name());
            }
            pass_n++;
        }
        return ret_val;
    }

    instruction_stream
    stream_pass_manager::apply_pass(instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass) {
        instruction_stream retval;
        pass->setup();
        if (pass->is_standalone) {
            retval = pass->standalone(in_stream);
        } else {
            for(int i = 0; i<pass->n_scans;i++){
                for(auto instr : in_stream){
                    if(pass->is_mutable){
                        if(pass->is_vector) {
                            auto pass_result = pass->apply_vector_mutable_pass(instr, i);
                            for(auto &item:pass_result) retval.push_back(item);
                        } else {
                            if(auto proc_val = pass->apply_mutable_pass(instr, i))
                                retval.push_back(proc_val.value());
                        }
                    } else {
                        if(auto proc_val = pass->apply_pass(instr, i))
                            retval.push_back(proc_val.value());
                    }
                }
                pass->inter_pass();
            }
        }

        return retval;
    }


}

