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

#include "passes/ll_ast/load_intercalation_pass.hpp"

load_intercalation_pass::load_intercalation_pass() : pass_base<ll_ast_node>("load intercalation pass") {

}


std::shared_ptr<ll_ast_node> load_intercalation_pass::process_leaf(std::shared_ptr<ll_ast_node> element) {
    std::shared_ptr<ll_ast_node> container = std::make_shared<ll_ast_node>(ll_type_code_block);

    bool float_present = false;
    if(element->type == ll_type_instr){
        std::shared_ptr<ll_instruction_node> node = std::static_pointer_cast<ll_instruction_node>(element);
        instruction_t current_instr = node->getStringInstr();
        if(current_instr.opcode == "ldc"){
            float desired_constant = std::stof(current_instr.arguments[1]->to_str());

            std::vector<std::shared_ptr<ll_ast_node>> block_content;

            //CREATE FRACT NUMERATOR MULTIPLICATION
            std::shared_ptr<ll_instruction_node> constant = std::make_shared<ll_instruction_node>(INTERCALATED_CONSTANT,desired_constant);
            block_content.push_back(node);
            block_content.push_back(constant);


            container->set_content(block_content);
            return container;
        }

    }
    return element;

}

