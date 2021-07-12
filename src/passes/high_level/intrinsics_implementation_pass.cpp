//
// Created by fils on 12/07/2021.
//

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


