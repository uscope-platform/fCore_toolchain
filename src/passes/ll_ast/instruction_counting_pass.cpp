// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#include "passes/low_level/instruction_counting_pass.hpp"

instruction_counting_pass::instruction_counting_pass() : pass_base<ll_ast_node>("instruction counting pass"){

}

void instruction_counting_pass::analyze_element(std::shared_ptr<ll_ast_node> element) {
    if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);
        int count = node->instruction_count();
        if(count>=0)
            instruction_count += count;
        else
            throw std::runtime_error("Instruction counting in brancing code is not supported");
    }

}

std::vector<int> instruction_counting_pass::get_analysis_result() {
    std::vector<int> result_count = {instruction_count};
    return result_count;
}

