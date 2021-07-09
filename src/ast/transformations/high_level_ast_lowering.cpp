//
// Created by fils on 09/07/2021.
//

#include "ast/transformations/high_level_ast_lowering.h"

high_level_ast_lowering::high_level_ast_lowering() {
    output_ast = std::make_shared<ll_ast_node>(ll_type_program_head);
}



void high_level_ast_lowering::translate() {
    for(const auto &i:input_ast->get_content()){
        std::shared_ptr<ll_ast_node> lowered_instr = translate_node(i);
        output_ast->add_content(lowered_instr);
    }
}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(const std::shared_ptr<hl_ast_node>& input) {
    switch (input->node_type) {
        case hl_ast_node_type_definition:{
            std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(input);
            return translate_node(node);
        }
        case hl_ast_node_type_operand: {
            std::shared_ptr<hl_ast_operand> node = std::static_pointer_cast<hl_ast_operand>(input);
            return translate_node(node);
        }
        case hl_ast_node_type_expr:{
            std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(input);
            return translate_node(node);
        }
        case hl_ast_node_type_program_root:
            throw std::runtime_error("ERROR: program_root nodes should not reach the ast lowering stage");
            break;
        case hl_ast_node_type_loop:
            throw std::runtime_error("ERROR: loop nodes should not reach the ast lowering stage");
            break;
        case hl_ast_node_type_conditional:
            throw std::runtime_error("ERROR: conditional nodes should not reach the ast lowering stage");
            break;
        case hl_ast_node_type_function_call:
            throw std::runtime_error("ERROR: function call nodes should not reach the ast lowering stage");
            break;
        case hl_ast_node_type_function_def:
            throw std::runtime_error("ERROR: function definition nodes should not reach the ast lowering stage");
            break;
        default:
            throw std::runtime_error("ERROR: unknown type nodes should not reach the ast lowering stage");
    }

}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(std::shared_ptr<hl_expression_node> input) {
    std::shared_ptr<ll_instruction_node> retval = std::make_shared<ll_instruction_node>();

    return retval;
}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(std::shared_ptr<hl_definition_node> input) {
    std::shared_ptr<ll_instruction_node> retval = std::make_shared<ll_instruction_node>();

    return retval;

}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(std::shared_ptr<hl_ast_operand> input) {
    std::shared_ptr<ll_instruction_node> retval = std::make_shared<ll_instruction_node>();

    return retval;
}



