//
// Created by fils on 09/07/2021.
//

#include "ast/transformations/high_level_ast_lowering.h"

high_level_ast_lowering::high_level_ast_lowering() {
    output_ast = std::make_shared<ll_ast_node>(ll_type_program_head);
    expr_instruction_mapping = {
            {expr_add, "add"},
            {expr_sub, "sub"},
            {expr_mult, "sub"},
            {expr_incr_pre, "add"},
            {expr_incr_post, "add"},
            {expr_decr_pre, "sub"},
            {expr_decr_post, "sub"},
            {expr_and_b, "and"},
            {expr_or_b, "or"},
            {expr_not_b, "not"},
            {expr_xor_b, "xor"},
            {expr_eq, "beq"},
            {expr_neq, "bne"},
            {expr_neg, "sub"},
            {expr_lt, "bgt"},
            {expr_gt, "bgt"},
            {expr_lte, "ble"},
            {expr_gte, "ble"},
            {expr_reciprocal, "rec"}
    };
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
        case hl_ast_node_type_operand:
            throw std::runtime_error("ERROR: standalone operands nodes should not reach the ast lowering stage");
        case hl_ast_node_type_expr:
            throw std::runtime_error("ERROR: standalone expression nodes should not reach the ast lowering stage");
        case hl_ast_node_type_program_root:
            throw std::runtime_error("ERROR: program_root nodes should not reach the ast lowering stage");
        case hl_ast_node_type_loop:
            throw std::runtime_error("ERROR: loop nodes should not reach the ast lowering stage");
        case hl_ast_node_type_conditional:
            throw std::runtime_error("ERROR: conditional nodes should not reach the ast lowering stage");
        case hl_ast_node_type_function_call:
            throw std::runtime_error("ERROR: function call nodes should not reach the ast lowering stage");
        case hl_ast_node_type_function_def:
            throw std::runtime_error("ERROR: function definition nodes should not reach the ast lowering stage");
        default:
            throw std::runtime_error("ERROR: unknown type nodes should not reach the ast lowering stage");
    }

}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(std::shared_ptr<hl_expression_node> input) {
    if(input->is_unary()){
        return process_unary_expression(input);
    } else{
        return process_regular_expression(input);
    }
}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(std::shared_ptr<hl_definition_node> input) {
    std::shared_ptr<ll_instruction_node> retval = std::make_shared<ll_instruction_node>();
    if(input->is_initialized()){
        return translate_node(std::static_pointer_cast<hl_expression_node>(input->get_initializer()));
    }
    return retval;

}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::process_unary_expression(std::shared_ptr<hl_expression_node> input) {
    operand_type_t rhs_type = std::static_pointer_cast<hl_ast_operand>(input->get_rhs())->get_type();

    std::shared_ptr<ll_instruction_node> retval;
    expression_type_t op_type = input->get_type();
    std::string opcode = expr_instruction_mapping[op_type];
    if(!fcore_implemented_operations[op_type]) throw std::runtime_error("ERROR: The required operation is not implementable on the fCore hardware");

    switch (op_type) {
        case expr_reciprocal:{
            std::shared_ptr<variable> op = std::make_shared<variable>(false, "r3");
            std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
            std::vector<std::shared_ptr<variable>> args = {op, dest};
            retval = std::make_shared<ll_instruction_node>(fcore_op_types[opcode], opcode, args);
            break;
        }
        case expr_not_b:{
            std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r2");
            std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r3");
            std::vector<std::shared_ptr<variable>> args = {op_a, dest};
            retval = std::make_shared<ll_instruction_node>(fcore_op_types[opcode], opcode, args);
            break;
        }
        case expr_neg:{
            std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r2");
            std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r3");
            std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
            std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};
            retval = std::make_shared<ll_instruction_node>(fcore_op_types[opcode], opcode, args);
            break;
        }
        case expr_incr_pre:{
            std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r2");
            std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r3");
            std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
            std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};
            retval = std::make_shared<ll_instruction_node>(fcore_op_types[opcode], opcode, args);
            break;
        }
        case expr_incr_post:{
            std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r2");
            std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r3");
            std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
            std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};
            retval = std::make_shared<ll_instruction_node>(fcore_op_types[opcode], opcode, args);
            break;
        }
        case expr_decr_post:{
            std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r2");
            std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r3");
            std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
            std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};
            retval = std::make_shared<ll_instruction_node>(fcore_op_types[opcode], opcode, args);
            break;
        }
        case expr_decr_pre:{
            std::shared_ptr<variable> op_a = std::make_shared<variable>(false, "r2");
            std::shared_ptr<variable> op_b = std::make_shared<variable>(false, "r3");
            std::shared_ptr<variable> dest = std::make_shared<variable>(false, "r4");
            std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};
            retval = std::make_shared<ll_instruction_node>(fcore_op_types[opcode], opcode, args);
            break;
        }
    }
    return retval;
}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::process_regular_expression(std::shared_ptr<hl_expression_node> input) {
    operand_type_t lhs_type = std::static_pointer_cast<hl_ast_operand>(input->get_lhs())->get_type();
    operand_type_t rhs_type = std::static_pointer_cast<hl_ast_operand>(input->get_rhs())->get_type();

    std::shared_ptr<ll_instruction_node> retval;
    expression_type_t op_type = input->get_type();
    std::string opcode = expr_instruction_mapping[op_type];
    if(!fcore_implemented_operations[op_type]) throw std::runtime_error("ERROR: The required operation is not implementable on the fCore hardware");

    switch (op_type) {

    }
    return retval;

}
