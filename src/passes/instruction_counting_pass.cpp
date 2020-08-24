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

#include "fcore_has/passes/instruction_counting_pass.hpp"

void instruction_counting_pass::analyze_element(ast_t element) {
    if(element->type==type_instr){
        int count = element->inst.instruction_count();
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
