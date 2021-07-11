// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.05/07/2021.
//

#include <gtest/gtest.h>
#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_ast_operand.hpp"
#include "ast/high_level/hl_expression_node.hpp"
#include "frontend/variable_map.hpp"
#include "frontend/define_map.hpp"
#include "frontend/C/C_language_parser.hpp"
#include "passes/hl_passes.hpp"
#include "passes/high_level/function_mapping.hpp"
#include "passes/high_level/hl_pass_manager.hpp"
#include "passes/high_level/normalization_pass.hpp"
#include "ast/transformations/high_level_ast_lowering.hpp"

#include <memory>
#include <fstream>


TEST(HlPassesTest, divisionImplementation) {


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> lvl_1 = std::make_shared<hl_expression_node>(expr_mult);
    lvl_1->set_lhs(op_1);
    lvl_1->set_rhs(op_2);

    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(7);

    std::shared_ptr<hl_expression_node> lvl_2 = std::make_shared<hl_expression_node>(expr_div);
    lvl_2->set_lhs(lvl_1);
    lvl_2->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");
    std::shared_ptr<hl_expression_node> lvl_3 = std::make_shared<hl_expression_node>(expr_assign);
    lvl_3->set_lhs(op_3);
    lvl_3->set_rhs(lvl_2);

    std::shared_ptr<hl_ast_node> ast = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    ast->add_content(lvl_3);


    std::string ep = "main";
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    hl_pass_manager manager = create_hl_pass_manager(ep, variables_map);

    manager.run_morphing_passes(ast);



    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_mult);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(7);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_reciprocal);
    gs_2->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_mult);
    gs_3->set_lhs(gs_1);
    gs_3->set_rhs(gs_2);

    op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");

    std::shared_ptr<hl_expression_node> gs_4 = std::make_shared<hl_expression_node>(expr_assign);
    gs_4->set_lhs(op_3);
    gs_4->set_rhs(gs_3);

    std::shared_ptr<hl_ast_node> result = ast->get_content()[0];


    EXPECT_EQ( *gs_4, *result);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(ast->get_content()[0])->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(result)->pretty_print()<< std::endl;
    }
}



TEST(HlPassesTest, functionMapping) {


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> lvl_1 = std::make_shared<hl_expression_node>(expr_mult);
    lvl_1->set_lhs(op_1);
    lvl_1->set_rhs(op_2);

    std::shared_ptr<hl_function_def_node> func_1 = std::make_shared<hl_function_def_node>();
    std::string fn = "test_1";
    func_1->set_name(fn);
    func_1->add_content(lvl_1);

    std::shared_ptr<hl_function_def_node> func_2 = std::make_shared<hl_function_def_node>();
    fn = "test_2";
    func_2->set_name(fn);
    func_2->add_content(lvl_1);


    std::shared_ptr<hl_ast_node> ast = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    ast->add_content(func_1);
    ast->add_content(func_2);




    std::string ep = "main";
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    hl_pass_manager manager = create_hl_pass_manager(ep, variables_map);

    manager.run_morphing_passes(ast);

    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> pass = std::static_pointer_cast<function_mapping>(manager.morphing_passes[0])->get_map_ref();

    EXPECT_EQ( *func_1, *pass->at("test_1"));
    EXPECT_EQ( *func_2, *pass->at("test_2"));

}

TEST(HlPassesTest, functionInlining) {


    std::string input_file = "test_function_inlining.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    hl_pass_manager manager = create_hl_pass_manager(ep, variables_map);

    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_function_def_node> res = std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0]);

    std::shared_ptr<hl_function_def_node> gold_standard = std::make_shared<hl_function_def_node>();
    gold_standard->set_name("main");
    // PARAMETERS
    std::shared_ptr<hl_definition_node> par_1 = std::make_shared<hl_definition_node>("a", c_type_int);
    std::shared_ptr<hl_definition_node> par_2 = std::make_shared<hl_definition_node>("b", c_type_int);
    gold_standard->set_parameters_list({par_1, par_2});
    // CALL EXPRESSION
    std::shared_ptr<hl_expression_node> ex_call = std::make_shared<hl_expression_node>(expr_call);
    // CALL NODE
    std::shared_ptr<hl_ast_operand> arg_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    arg_1->set_immediate(2);
    std::shared_ptr<hl_ast_operand> arg_2 = std::make_shared<hl_ast_operand>(variable_operand);
    arg_2->set_name("t");
    std::vector<std::shared_ptr<hl_ast_node>> arguments = {arg_1, arg_2};
    std::shared_ptr<hl_function_call_node> func = std::make_shared<hl_function_call_node>("add", arguments);
    // CALL BODY
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("c", c_type_int);
    std::shared_ptr<hl_expression_node> exadd = std::make_shared<hl_expression_node>(expr_add);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(2);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(variable_operand);
    op_2->set_name("t");
    exadd->set_rhs(op_2);
    exadd->set_lhs(op_1);
    def->set_initializer(exadd);
    func->set_body({def});
    exadd = std::make_shared<hl_expression_node>(expr_add);
    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    op_2 = std::make_shared<hl_ast_operand>(variable_operand);
    op_2->set_name("t");
    exadd->set_rhs(op_2);
    exadd->set_lhs(op_1);
    func->set_return(exadd);
    gold_standard->set_body({ex_call});
    gold_standard->set_return_type(c_type_int);
    EXPECT_EQ(*res, *gold_standard);

}



TEST(HlPassesTest, normalization) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    hl_pass_manager manager = create_hl_pass_manager(ep, variables_map);
    manager.run_morphing_passes(parser.AST);

    normalization_pass p;
    std::shared_ptr<hl_ast_node> raw_result = p.process_global(parser.AST);


    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("intermediate_expr_0", c_type_int);

    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(4);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_mult);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_1->set_initializer(ex_1);

    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("a", c_type_int);

    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("intermediate_expr_0");
    op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);

    ex_1= std::make_shared<hl_expression_node>(expr_add);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_2->set_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_function_def_node> gold_standard = std::make_shared<hl_function_def_node>();
    gold_standard->set_name("main");
    gold_standard->set_return_type(c_type_int);
    gold_standard->set_body({def_1, def_2});

    std::shared_ptr<hl_function_def_node> result = std::static_pointer_cast<hl_function_def_node>(raw_result->get_content()[0]);

    EXPECT_EQ( *gold_standard, *result);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << result->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << gold_standard->pretty_print()<< std::endl;
    }
}



TEST(HlPassesTest, function_elimination) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    hl_pass_manager manager = create_hl_pass_manager(ep, variables_map);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> raw_result = manager.run_global_passes(parser.AST);

    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("intermediate_expr_0", c_type_int);

    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(4);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_mult);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_1->set_initializer(ex_1);

    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("a", c_type_int);

    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("intermediate_expr_0");
    op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);

    ex_1= std::make_shared<hl_expression_node>(expr_add);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_2->set_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->set_content({def_1, def_2});

    EXPECT_EQ( *gold_standard, *raw_result);

}


TEST(HlPassesTest, variable_mapping_pass) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    hl_pass_manager manager = create_hl_pass_manager(ep, variables_map);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = manager.run_global_passes(parser.AST);


    std::shared_ptr<variable_map> gold_standard = std::make_shared<variable_map>();
    std::shared_ptr<variable> v_1 = std::make_shared<variable>(true, "6", false);
    gold_standard->insert("6", v_1);
    std::shared_ptr<variable> v_2 = std::make_shared<variable>(true, "5", false);
    gold_standard->insert("5", v_2);
    std::shared_ptr<variable> v_3 = std::make_shared<variable>(true, "4", false);
    gold_standard->insert("4", v_3);
    std::shared_ptr<variable> v_4 = std::make_shared<variable>(false, "intermediate_expr_0");
    gold_standard->insert("intermediate_expr_0", v_4);
    std::shared_ptr<variable> v_5 = std::make_shared<variable>(false, "a");
    gold_standard->insert("a", v_5);


    ASSERT_EQ(*variables_map, *gold_standard);


}


TEST(HlPassesTest, hl_ast_lowering) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    hl_pass_manager manager = create_hl_pass_manager(ep, variables_map);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = manager.run_global_passes(parser.AST);

    high_level_ast_lowering tranlator(variables_map);

    tranlator.set_input_ast(normalized_ast);
    tranlator.translate();
    std::shared_ptr<ll_ast_node> result = tranlator.get_output_ast();

    int i = 0;

    std::shared_ptr<variable> op_a = std::make_shared<variable>(true, "4", false);
    std::shared_ptr<variable> op_b = std::make_shared<variable>(true, "5", false);
    std::shared_ptr<variable> dest = std::make_shared<variable>(false, "intermediate_expr_0");
    std::vector<std::shared_ptr<variable>> args_1 = {op_a, op_b, dest};
    std::shared_ptr<ll_instruction_node> op_1 = std::make_shared<ll_instruction_node>(isa_register_instruction, "mul", args_1);


    op_a = std::make_shared<variable>(false, "intermediate_expr_0");
    op_b = std::make_shared<variable>(true, "6", true);
    dest = std::make_shared<variable>(false, "a");
    std::vector<std::shared_ptr<variable>> args_2 = {op_a, op_b, dest};
    std::shared_ptr<ll_instruction_node> op_2 = std::make_shared<ll_instruction_node>(isa_register_instruction, "add", args_2);

    std::shared_ptr<ll_ast_node> golden_standard = std::make_shared<ll_ast_node>(ll_type_program_head);
    golden_standard->set_content({op_1, op_2});

    ASSERT_EQ(*golden_standard, *result);
}

