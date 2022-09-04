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


stream_pass_manager::stream_pass_manager(std::unordered_map<std::string, std::shared_ptr<variable>> &iom, int dal) {
    iom_map = iom;
    dump_ast_level = dal;
    std::shared_ptr<variable_map> var_map = std::make_shared<variable_map>();

    passes.push_back(std::make_shared<constant_merging>());
    passes.push_back(std::make_shared<variable_mapping>(var_map));
    passes.push_back(std::make_shared<variable_lifetime_mapping>(var_map));
    passes.push_back(std::make_shared<register_allocation>(var_map, iom_map));
    enabled_passes = {true, true, true, true};

}

instruction_stream stream_pass_manager::process_stream(instruction_stream stream) {
    int pass_n = 0;
    if(dump_ast_level>0) pre_opt_dump = stream.dump();
    instruction_stream ret_val = std::move(stream);
    for(auto &pass:passes){
        if(enabled_passes[pass_n]){
            ret_val = apply_pass(ret_val, pass);
            if(dump_ast_level>1){
                nlohmann::json ast_dump;
                ast_dump["pass_name"] = pass->get_name();
                ast_dump["ast"]= ret_val.dump();
                in_opt_dump.push_back(ast_dump);
            }
        }
        pass_n++;
    }
    if(dump_ast_level>0) post_opt_dump = ret_val.dump();
    return ret_val;
}

instruction_stream
stream_pass_manager::apply_pass(const instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass) {
    instruction_stream retval;
    for(auto &instr:in_stream){
        auto proc_val = pass->apply_pass(instr);
        if(proc_val!= nullptr)
            retval.push_back(proc_val);
    }
    return retval;
}

nlohmann::json stream_pass_manager::get_dump() {
    nlohmann::json retval;

    retval["pre-opt"] = pre_opt_dump;
    retval["in-opt"] = in_opt_dump;
    retval["post-opt"] = post_opt_dump;

    return retval;
}
