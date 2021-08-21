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

#include "passes/high_level/intrinsics_implementation_pass.hpp"

intrinsics_implementation_pass::intrinsics_implementation_pass() : pass_base<hl_ast_node>("intrinsics implementation pass") {
    substitutions = {
        std::make_pair("itf", expr_itf),
        std::make_pair("fti", expr_fti),
        std::make_pair("satp", expr_satp),
        std::make_pair("satn", expr_satn)
    };
    n_arguments = {
        std::make_pair("itf", 1),
        std::make_pair("fti", 1),
        std::make_pair("satp", 2),
        std::make_pair("satn", 2)
    };
}

std::shared_ptr<hl_ast_node>
intrinsics_implementation_pass::process_leaf(std::shared_ptr<hl_ast_node> element) {

    std::shared_ptr<hl_ast_node> node = process_node_by_type(element);

    return node;
}

std::shared_ptr<hl_ast_node>
intrinsics_implementation_pass::process_node_by_type(const std::shared_ptr<hl_ast_node>& element) {
    std::shared_ptr<hl_ast_node> retval = element;

    if(element->node_type==hl_ast_node_type_function_call){
        std::shared_ptr<hl_function_call_node> call = std::static_pointer_cast<hl_function_call_node>(element);
        retval = process_function_call(call);
    }

    return retval;
}

std::shared_ptr<hl_ast_node>
intrinsics_implementation_pass::process_function_call(const std::shared_ptr<hl_function_call_node> &element) {

    for(auto &item:element->get_arguments()){
        item = process_node_by_type(item);
    }

    unsigned int matches = substitutions.count(element->get_name());
    if(matches == 0) {
        return element;
    }

    std::shared_ptr<hl_expression_node> retval = std::make_shared<hl_expression_node>(substitutions[element->get_name()]);

    if(n_arguments[element->get_name()]>1){
        retval->set_lhs(element->get_arguments()[0]);
        retval->set_rhs(element->get_arguments()[1]);
    } else {
        retval->set_rhs(element->get_arguments()[0]);
    }

    return retval;
}


