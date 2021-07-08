//
// Created by fils on 08/07/2021.
//

#include "passes/hl_ast/inlined_function_elimination.h"



inlined_function_elimination::inlined_function_elimination(std::string entry_point_name) : pass_base("inlined function elimination pass") {
    entry_point = std::move(entry_point_name);
}

std::vector<std::shared_ptr<hl_ast_node>>
inlined_function_elimination::process_node(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;

    if(element->node_type == hl_ast_node_type_function_def){
        std::shared_ptr<hl_function_def_node> node = std::static_pointer_cast<hl_function_def_node>(element);
        if(node->get_name() == entry_point)
            retval.push_back(element);
    } else{
        retval.push_back(element);
    }

    return retval;
}

