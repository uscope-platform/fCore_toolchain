//
// Created by fils on 07/07/2021.
//

#include "passes/hl_ast/function_mapping.h"


function_mapping::function_mapping() : pass_base<hl_ast_node>("function mapping pass"){

}

std::vector<std::shared_ptr<hl_ast_node>> function_mapping::process_node(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;
    retval.push_back(element);
    if(element->node_type == hl_ast_node_type_function_def){
        std::shared_ptr<hl_function_def_node> node = std::static_pointer_cast<hl_function_def_node>(element);
        functions_map[node->get_name()] = node;
    }

    return retval;
}

std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>>
function_mapping::get_map_ref() {
    return std::make_shared<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>>(functions_map);
}


