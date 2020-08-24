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

#include "load_intercalation_pass.hpp"

ast_t load_intercalation_pass::process_leaf(ast_t element) {
    std::shared_ptr<code_element> container = std::make_shared<code_element>(type_code_block);



    bool float_present = false;
    if(element->type == type_instr){
        instruction_t current_instr = element->inst.getStringInstr();
        if(current_instr.opcode == "ldc"){
            float desired_constant = std::stof(current_instr.arguments[1]->to_str());

            std::vector<std::shared_ptr<code_element>> block_content;

            //CREATE FRACT NUMERATOR MULTIPLICATION
            instruction constant_inst = instruction(INTERCALATED_CONSTANT,desired_constant);
            std::shared_ptr<code_element> load_inst = std::make_shared<code_element>(type_instr, element->inst);
            std::shared_ptr<code_element> constant = std::make_shared<code_element>(type_instr, constant_inst);
            block_content.push_back(load_inst);
            block_content.push_back(constant);


            container->set_content(block_content);
            return container;
        }

    }
    return element;

}
