// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

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
