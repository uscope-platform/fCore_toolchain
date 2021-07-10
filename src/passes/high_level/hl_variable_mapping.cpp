//
// Created by fils on 09/07/2021.
//

#include "passes/high_level/hl_variable_mapping.h"

hl_variable_mapping::hl_variable_mapping(std::shared_ptr<variable_map> &v) : pass_base<hl_ast_node>("high level variable mapping"){
    var_map = v;
}

std::shared_ptr<hl_ast_node> hl_variable_mapping::process_global(std::shared_ptr<hl_ast_node> element) {
    for(auto &i:element->get_content()){
        process_var(i);
    }
    return element;
}

void hl_variable_mapping::process_var(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type == hl_ast_node_type_definition) {
        std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(element);
        if (node->is_initialized()) process_var(node->get_initializer());
        std::shared_ptr<variable> var = std::make_shared<variable>(false,node->get_name());
        var_map->insert(node->get_name(), var);
    } else if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        if (node->get_lhs() != nullptr) process_var(node->get_lhs());
        if (node->get_rhs() != nullptr) process_var(node->get_rhs());

    } else if(element->node_type == hl_ast_node_type_operand){
        std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(element);
        std::shared_ptr<variable> var;
        std::string var_name;
        if(op->get_type() == integer_immediate_operand){
            var_name = std::to_string(op->get_int_value());
            var = std::make_shared<variable>(true, var_name, false);
        } else if(op->get_type()==float_immediate_operand){
            var_name = std::to_string(op->get_float_val());
            var = std::make_shared<variable>(true,var_name, true);
        } else if(op->get_type()==variable_operand){
            var_name = op->get_name();
            var = std::make_shared<variable>(false,var_name);
        }
        var_map->insert(var_name, var);
    }
}
