//
// Created by fils on 17/07/2021.
//

#include "passes/high_level/declaration_instantiation_combining_pass.h"

declaration_instantiation_combining_pass::declaration_instantiation_combining_pass() : pass_base<hl_ast_node>("declaration/instantiation combining pass") {

}

std::shared_ptr<hl_ast_node>
declaration_instantiation_combining_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> new_content;
    std::vector<std::shared_ptr<hl_ast_node>> content = element->get_content();
    for(int i = 0; i<content.size(); i++){
        if(content[i]->node_type == hl_ast_node_type_definition){
            std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(content[i]);
            if(!node->is_initialized()){
                for(int j = i; j<content.size(); j++){
                    if(content[j]->node_type == hl_ast_node_type_expr){
                        std::shared_ptr<hl_expression_node> expr = std::static_pointer_cast<hl_expression_node>(content[j]);
                        if(expr->get_type()==expr_assign){
                            if(std::static_pointer_cast<hl_definition_node>(expr->get_lhs())->get_name() == node->get_name()){
                                node->set_initializer(expr->get_rhs());
                                new_content.push_back(node);
                                break;
                            }
                        }
                    }
                }
            } else{
                new_content.push_back(node);
            }
        } else if(content[i]->node_type == hl_ast_node_type_expr){
            std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(content[i]);
            if(node->get_type()!=expr_assign){
                new_content.push_back(node);
            }
        } else {
            new_content.push_back(content[i]);
        }
    }

    element->set_content(new_content);
    return element;
}
