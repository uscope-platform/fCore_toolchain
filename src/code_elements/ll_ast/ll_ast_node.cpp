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

#include "code_elements/ll_ast/ll_ast_node.hpp"
#include "code_elements/ll_ast/ll_loop_node.h"
#include "code_elements/ll_ast/ll_ast_pragma.h"
#include "code_elements/ll_ast/ll_instruction_node.h"

ll_ast_node::ll_ast_node() {

}

ll_ast_node::ll_ast_node(ll_ast_node_type_t block_type) {
    type = block_type;
}



bool ll_ast_node::is_terminal() {

    return false;
}

std::shared_ptr<ll_ast_node> ll_ast_node::deep_copy_element(const std::shared_ptr<ll_ast_node> &element) {
    std::shared_ptr<ll_ast_node> result;

    if(element->type == ll_type_for_block) {
        std::shared_ptr<ll_loop_node> loop_elem = std::static_pointer_cast<ll_loop_node>(element);
        std::shared_ptr<ll_loop_node> loop_res = std::make_shared<ll_loop_node>();

        loop_res->set_loop_start(loop_elem->get_loop_start());
        loop_res->set_advance(loop_elem->get_advance());
        loop_res->set_loop_end(loop_elem->get_loop_end());
        result = std::static_pointer_cast<ll_ast_node>(loop_res);
    } else if(element->type == ll_type_pragma){
        std::shared_ptr<ll_ast_pragma> pragma_elem = std::static_pointer_cast<ll_ast_pragma>(element);
        std::shared_ptr<ll_ast_pragma> pragma_res = std::make_shared<ll_ast_pragma>(pragma_elem->get_directive());
        result = std::static_pointer_cast<ll_ast_node>(pragma_res);
    } else if(element->type == ll_type_instr ){
        std::shared_ptr<ll_instruction_node> instr_elem = std::static_pointer_cast<ll_instruction_node>(element);
        std::shared_ptr<ll_instruction_node> instr_res = std::make_shared<ll_instruction_node>(instr_elem->get_type());
        instr_res->setStringInstr(instr_elem->getStringInstr());

        result = std::static_pointer_cast<ll_ast_node>(instr_res);
    } else {
        ll_ast_node copied_elem;
        result = std::make_shared<ll_ast_node>(copied_elem);
    }

    if(element->has_content()){
        std::vector<std::shared_ptr<ll_ast_node>> children;
        for(auto &item:element->get_content()){
            std::shared_ptr<ll_ast_node> child = deep_copy_element(item);
            children.push_back(child);
        }
        result->set_content(children);
    }
    result->type = element->type;

    return result;
}