//
// Created by fils on 28/07/2021.
//

#include "passes/instruction_stream/stream_pass_manager.hpp"


stream_pass_manager::stream_pass_manager() {

    std::shared_ptr<variable_map> var_map = std::make_shared<variable_map>();

    passes.push_back(std::make_shared<variable_mapping>(var_map));
    passes.push_back(std::make_shared<variable_lifetime_mapping>(var_map));
    passes.push_back(std::make_shared<register_allocation>(var_map));
}

instruction_stream stream_pass_manager::process_stream(instruction_stream stream) {
    instruction_stream ret_val = std::move(stream);
    for(auto &pass:passes){
        ret_val = apply_pass(ret_val, pass);
    }

    return ret_val;
}

instruction_stream
stream_pass_manager::apply_pass(const instruction_stream& in_stream, const std::shared_ptr<stream_pass_base>& pass) {
    instruction_stream retval;
    for(auto &instr:in_stream){
        retval.push_back(pass->apply_pass(instr));
    }
    return retval;
}
