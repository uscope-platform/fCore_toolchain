//
// Created by fils on 05/07/2021.
//

#include "passes/hl_ast/function_inlining_pass.h"


function_inlining_pass::function_inlining_pass() : pass_base<hl_ast_node>("function inlining pass"){

}

std::shared_ptr<hl_ast_node> function_inlining_pass::process_leaf(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = element;
    if(element->node_type == hl_ast_node_type_function_call){
        std::shared_ptr<hl_function_call_node> f_call = std::static_pointer_cast<hl_function_call_node>(element);
        std::shared_ptr<hl_function_def_node> f_def = functions_map->at(f_call->get_name());
        for(auto &i: f_def->get_body()){

        }

        int i = 0;
    }
    return ret_val;
}

void function_inlining_pass::set_functions_map(
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> map) {
    functions_map = std::move(map);
}
