//
// Created by fils on 07/07/2021.
//

#include "passes/independent/normalization_pass.h"

normalization_pass::normalization_pass() = default;


std::shared_ptr<hl_ast_node> normalization_pass::run_pass(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval;

    std::shared_ptr<hl_function_def_node> main = std::static_pointer_cast<hl_function_def_node>(element->get_content()[0]);

    std::vector<std::shared_ptr<hl_ast_node>> normalized_body;

    for(auto &i: main->get_body()){
        std::vector<std::shared_ptr<hl_ast_node>> tmp_res = process_node_by_type(i);
        normalized_body.insert(normalized_body.end(), tmp_res.begin(), tmp_res.end());
    }

    return retval;
}

std::vector<std::shared_ptr<hl_ast_node>> normalization_pass::process_node_by_type(std::shared_ptr<hl_ast_node> n) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;
    if(n->node_type== hl_ast_node_type_expr){
        retval = process_node(std::static_pointer_cast<hl_expression_node>(n));
    } else if(n->node_type == hl_ast_node_type_definition){
        retval = process_node(std::static_pointer_cast<hl_definition_node>(n));
    }
    return retval;
}

std::vector<std::shared_ptr<hl_ast_node>> normalization_pass::process_node(std::shared_ptr<hl_expression_node> n) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;
    if(n->is_unary()){
        if(n->get_rhs()->node_type==hl_ast_node_type_operand){
            retval.push_back(n);
        } else{
            std::vector<std::shared_ptr<hl_ast_node>> lower_level_expr = process_node_by_type(n->get_rhs());
        }
    } else{
        if(n->get_rhs()->node_type==hl_ast_node_type_operand && n->get_lhs()->node_type==hl_ast_node_type_operand){
            retval.push_back(n);
        } else {
            if(n->get_lhs()->node_type!=hl_ast_node_type_operand){
                std::vector<std::shared_ptr<hl_ast_node>> lower_level_expr_l = process_node_by_type(n->get_lhs());
                int i = 0;
            }
            if(n->get_rhs()->node_type!=hl_ast_node_type_operand) {
                std::vector<std::shared_ptr<hl_ast_node>> lower_level_expr_r = process_node_by_type(n->get_rhs());
                int i = 0;
            }
        }
    }

    return retval;
}

std::vector<std::shared_ptr<hl_ast_node>> normalization_pass::process_node(std::shared_ptr<hl_definition_node> n) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;

    if(n->get_initializer() != nullptr){
        retval = process_node(n->get_initializer());
    }

    return retval;
}

