//
// Created by fils on 07/07/2021.
//

#include "passes/independent/normalization_pass.h"

normalization_pass::normalization_pass() = default;


std::shared_ptr<hl_ast_node> normalization_pass::run_pass(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::shared_ptr<hl_function_def_node> ep = std::static_pointer_cast<hl_function_def_node>(element->get_content()[0]);

    std::vector<std::shared_ptr<hl_ast_node>> normalized_body;

    std::shared_ptr<hl_function_def_node> new_ep = std::static_pointer_cast<hl_function_def_node>(hl_ast_node::deep_copy(ep));

    for(auto &i: ep->get_body()){
        std::shared_ptr<hl_ast_node> tmp_res = process_node_by_type_top(i);
        normalized_body.insert(normalized_body.end(), additional_statements.begin(), additional_statements.end());
        normalized_body.push_back(tmp_res);
    }

    new_ep->set_parameters_list({});
    new_ep->set_body(normalized_body);
    // PARAMETERS LIST AND RETURN VALUE ARE DISCARDED BECAUSE  USELESS FOR THE FEMTOCORE AS IPUTS AND OUTPUTS OF THE PROGRAM
    // ARE DETERMINED BY PRAGMAS SINCE THEY NEED TO BE BOUND TO SPECIFIC REGISTERS

    retval->add_content(new_ep);
    return retval;
}

std::shared_ptr<hl_ast_node> normalization_pass::process_node_by_type_top(std::shared_ptr<hl_ast_node> n) {
    std::shared_ptr<hl_ast_node> retval;
    if(n->node_type== hl_ast_node_type_expr){
        retval = process_node_exp(std::static_pointer_cast<hl_expression_node>(n));
    } else if(n->node_type == hl_ast_node_type_definition){
        retval = process_node_def(std::static_pointer_cast<hl_definition_node>(n));
    }
    return retval;
}

//TODO: make recursion working
std::vector<std::pair<int, std::shared_ptr<hl_ast_node>>> normalization_pass::process_node_expr_inner(std::shared_ptr<hl_expression_node> n) {
    std::vector<std::pair<int, std::shared_ptr<hl_ast_node>>> retval;
    if(n->is_unary()){
        if(n->get_rhs()->node_type==hl_ast_node_type_operand){
            retval.emplace_back(0, n);
        } else{
            std::vector<std::pair<int, std::shared_ptr<hl_ast_node>>> extracted_exp = process_node_expr_inner(std::static_pointer_cast<hl_expression_node>(n->get_rhs()));
            std::shared_ptr<hl_expression_node> lower_level_expr  = produce_normalized_expression(n, extracted_exp);

            std::shared_ptr<hl_ast_operand> intermediate_def = extract_intermediate_expression(lower_level_expr, 2);
            retval.emplace_back(2, intermediate_def);
        }
    } else{
        if(n->get_rhs()->node_type==hl_ast_node_type_operand && n->get_lhs()->node_type==hl_ast_node_type_operand){
            retval.emplace_back(0, n);
        } else {
            if(n->get_lhs()->node_type!=hl_ast_node_type_operand){
                std::vector<std::pair<int, std::shared_ptr<hl_ast_node>>> extracted_exp = process_node_expr_inner(std::static_pointer_cast<hl_expression_node>(n->get_lhs()));
                std::shared_ptr<hl_expression_node> lower_level_expr  = produce_normalized_expression(n, extracted_exp);

                std::shared_ptr<hl_ast_operand> intermediate_def = extract_intermediate_expression(lower_level_expr,1);
                retval.emplace_back(1, intermediate_def);
            }
            if(n->get_rhs()->node_type!=hl_ast_node_type_operand) {
                std::vector<std::pair<int, std::shared_ptr<hl_ast_node>>> extracted_exp = process_node_expr_inner(std::static_pointer_cast<hl_expression_node>(n->get_rhs()));
                std::shared_ptr<hl_expression_node> lower_level_expr  = produce_normalized_expression(n, extracted_exp);

                std::shared_ptr<hl_ast_operand> intermediate_def = extract_intermediate_expression(lower_level_expr,1);
                retval.emplace_back(2, intermediate_def);
            }
        }
    }

    return retval;
}

std::shared_ptr<hl_definition_node> normalization_pass::process_node_def(std::shared_ptr<hl_definition_node> n) {
    std::shared_ptr<hl_definition_node> retval = std::static_pointer_cast<hl_definition_node>(hl_ast_node::deep_copy(n));

    if(n->get_initializer() != nullptr){
        std::vector<std::pair<int, std::shared_ptr<hl_ast_node>>> intermediate = process_node_expr_inner(n->get_initializer());
        std::shared_ptr<hl_expression_node> tmp_ret =produce_normalized_expression(n->get_initializer(), intermediate);
        retval->set_initializer(tmp_ret);
    }

    return retval;
}

std::shared_ptr<hl_ast_operand>
normalization_pass::extract_intermediate_expression(std::shared_ptr<hl_expression_node> n, int side) {
    operand_type_t type_lhs = std::static_pointer_cast<hl_ast_operand>(n->get_lhs())->get_type();
    operand_type_t type_rhs = std::static_pointer_cast<hl_ast_operand>(n->get_rhs())->get_type();
    c_types_t expr_type;
    if(type_lhs == float_immediate_operand && type_rhs == float_immediate_operand){
        expr_type = c_type_float;
    } else if(type_lhs == integer_immediate_operand && type_rhs == integer_immediate_operand){
        expr_type = c_type_int;
    } else if(type_rhs == float_immediate_operand){
        expr_type = c_type_float;

    } else if(type_lhs == float_immediate_operand){
        expr_type = c_type_float;
    }
    std::string name = "intermediate_expr_" + std::to_string(intermediate_ordinal);
    std::shared_ptr<hl_definition_node> intermediate_def = std::make_shared<hl_definition_node>(name, expr_type);
    if(side == 1)
        intermediate_def->set_initializer(std::static_pointer_cast<hl_expression_node>(n->get_lhs()));
    else if(side==2)
        intermediate_def->set_initializer(std::static_pointer_cast<hl_expression_node>(n->get_rhs()));

    additional_statements.push_back(intermediate_def);

    std::shared_ptr<hl_ast_operand> ret = std::make_shared<hl_ast_operand>(variable_operand);
    ret->set_name(name);
    return ret;
}

std::shared_ptr<hl_expression_node> normalization_pass::process_node_exp(std::shared_ptr<hl_expression_node> n) {
    return std::shared_ptr<hl_expression_node>();
}

std::shared_ptr<hl_expression_node>
normalization_pass::produce_normalized_expression(std::shared_ptr<hl_expression_node> original_node,
                                                  const std::vector<std::pair<int, std::shared_ptr<hl_ast_node>>>& extracted_intermediate) {

    std::shared_ptr<hl_expression_node> tmp_ret = std::static_pointer_cast<hl_expression_node>(hl_ast_node::deep_copy(original_node));
    for(auto &i: extracted_intermediate){
        switch (i.first) {
            case 0:
                return original_node;
                break;
            case 1:
                tmp_ret->set_lhs(i.second);
                break;
            case 2:
                tmp_ret->set_rhs(i.second);
                break;
        }
    }
    return tmp_ret;
}

