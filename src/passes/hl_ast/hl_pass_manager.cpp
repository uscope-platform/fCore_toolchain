//
// Created by fils on 06/07/2021.
//

#include "passes/hl_ast/hl_pass_manager.h"

std::shared_ptr<hl_ast_node> hl_pass_manager::run_pass(const std::shared_ptr<hl_ast_node> &subtree,
                                                       const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    std::shared_ptr<hl_ast_node> ret_val;
    switch (pass->get_pass_type()) {
        case NODE_PASS:{
            ret_val = process_nodes(subtree, pass)[0];
            break;
        }
        case LEAF_PASS:{
            ret_val = process_leaves(subtree, pass);
            break;
        }
        default:
            break;
    }
    return ret_val;
}

std::shared_ptr<hl_ast_node> hl_pass_manager::process_leaves(const std::shared_ptr<hl_ast_node> &subtree,
                                                             const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    std::vector<std::shared_ptr<hl_ast_node>> content =  subtree->get_content();
    std::shared_ptr<hl_ast_node> result;
    if(!subtree->is_terminal()){
        for(auto &i :content){
            i = process_leaves(i, pass);
        }
        subtree->set_content(content);
    } else{
        result = process_terminal_by_type(subtree, pass);
    }
    return result;
}

std::vector<std::shared_ptr<hl_ast_node>> hl_pass_manager::process_nodes(const std::shared_ptr<hl_ast_node> &subtree,
                                                                         const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    return std::vector<std::shared_ptr<hl_ast_node>>();
}

std::shared_ptr<hl_expression_node>
hl_pass_manager::process_expression(const std::shared_ptr<hl_expression_node> &subtree,
                                    const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    std::shared_ptr<hl_expression_node> result = std::make_shared<hl_expression_node>(subtree->get_type());
    std::shared_ptr<hl_ast_node> rhs = process_terminal_by_type(subtree->get_rhs(), pass);
    std::shared_ptr<hl_ast_node> lhs = process_terminal_by_type(subtree->get_lhs(), pass);

    result->set_rhs(rhs);
    result->set_lhs(lhs);

    return std::static_pointer_cast<hl_expression_node>(pass->process_leaf(result));

}

std::shared_ptr<hl_ast_operand> hl_pass_manager::process_operand(const std::shared_ptr<hl_ast_operand> &subtree,
                                                                    const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    return subtree;
}

std::shared_ptr<hl_function_call_node>
hl_pass_manager::process_function_call(const std::shared_ptr<hl_function_call_node> &subtree,
                                    const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    return subtree;
}

std::shared_ptr<hl_definition_node>
hl_pass_manager::process_definition(const std::shared_ptr<hl_definition_node> &subtree,
                                    const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    return subtree;
}

std::shared_ptr<hl_ast_node>
hl_pass_manager::process_terminal_by_type(const std::shared_ptr<hl_ast_node> &subtree,
                                          const std::shared_ptr<pass_base<hl_ast_node>> &pass) {
    std::shared_ptr<hl_ast_node> res;
    switch (subtree->node_type) {
        case hl_ast_node_type_expr:
            res = process_expression(std::static_pointer_cast<hl_expression_node>(subtree), pass);
            break;
        case hl_ast_node_type_function_call:
            res = process_function_call(std::static_pointer_cast<hl_function_call_node>(subtree), pass);
            break;
        case hl_ast_node_type_operand:
            res = process_operand(std::static_pointer_cast<hl_ast_operand>(subtree), pass);
            break;
        case hl_ast_node_type_definition:
            res = process_definition(std::static_pointer_cast<hl_definition_node>(subtree),pass);
            break;
        default:
            break;
    };
    return res;
}
