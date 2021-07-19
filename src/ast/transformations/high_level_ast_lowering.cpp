// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.09/07/2021.
//

#include "ast/transformations/high_level_ast_lowering.hpp"

high_level_ast_lowering::high_level_ast_lowering(std::shared_ptr<variable_map> &m) {
    output_ast = std::make_shared<ll_ast_node>(ll_type_program_head);
    var_map = m;
    expr_instruction_mapping = {
            {expr_add, "add"},
            {expr_sub, "sub"},
            {expr_mult, "mul"},
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
            {expr_reciprocal, "rec"},
            {expr_itf, "itf"},
            {expr_fti, "fti"},
            {expr_satp, "satp"},
            {expr_satn, "satn"}
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
            std::shared_ptr<variable> dest = var_map->at(node->get_name());
            return translate_node(node, dest);
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

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest) {
    if(input->is_unary()){
        return process_unary_expression(input,dest);
    } else{
        return process_regular_expression(input,dest);
    }
}

std::shared_ptr<ll_ast_node> high_level_ast_lowering::translate_node(const std::shared_ptr<hl_definition_node>& input, const std::shared_ptr<variable>& dest) {
    std::shared_ptr<ll_instruction_node> retval = std::make_shared<ll_instruction_node>();
    if(input->is_initialized()){
        if(input->get_initializer()->node_type == hl_ast_node_type_expr){
            return translate_node(std::static_pointer_cast<hl_expression_node>(input->get_initializer()), dest);
        } else if(input->get_initializer()->node_type == hl_ast_node_type_operand){
            return translate_node(std::static_pointer_cast<hl_ast_operand>(input->get_initializer()), dest);
        }
    }
    return retval;

}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::process_unary_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest) {

    std::shared_ptr<ll_instruction_node> retval;
    expression_type_t op_type = input->get_type();
    std::string opcode = expr_instruction_mapping[op_type];
    if(!fcore_implemented_operations[op_type]) throw std::runtime_error("ERROR: The required operation is not implementable on the fCore hardware");

    std::shared_ptr<variable> op_b = var_map->at(*std::static_pointer_cast<hl_ast_operand>(input->get_rhs()));
    std::vector<std::shared_ptr<variable>> args = {op_b, dest};
    retval = std::make_shared<ll_instruction_node>(fcore_op_types[opcode], opcode, args);
    return retval;
}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::process_regular_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest) {

    std::shared_ptr<ll_instruction_node> retval;
    expression_type_t op_type = input->get_type();
    std::string opcode = expr_instruction_mapping[op_type];
    if(!fcore_implemented_operations[op_type]) throw std::runtime_error("ERROR: The required operation is not implementable on the fCore hardware");

    std::shared_ptr<variable> op_a = var_map->at(*std::static_pointer_cast<hl_ast_operand>(input->get_lhs()));
    std::shared_ptr<variable> op_b = var_map->at(*std::static_pointer_cast<hl_ast_operand>(input->get_rhs()));
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b, dest};
    retval = std::make_shared<ll_instruction_node>(fcore_op_types[opcode], opcode, args);
    return retval;

}

std::shared_ptr<ll_ast_node>
high_level_ast_lowering::translate_node(const std::shared_ptr<hl_ast_operand>& input, std::shared_ptr<variable> dest) {


    std::shared_ptr<ll_instruction_node> retval;
    std::shared_ptr<variable> var;
    if(input->get_type() == integer_immediate_operand){
        var = std::make_shared<variable>(true, std::to_string(input->get_int_value()));
    } else if (input->get_type() == float_immediate_operand){
        var= std::make_shared<variable>(true, std::to_string(input->get_float_val()), true);
    } else{
        throw std::runtime_error("feature not implemented yet");
    }
    std::vector<std::shared_ptr<variable>> args = {std::move(dest), var};
    retval = std::make_shared<ll_instruction_node>(isa_load_constant_instruction, "ldc", args);
    return retval;

}
