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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.05/07/2021.
//

#include <gtest/gtest.h>
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "tools/variable_map.hpp"
#include "tools/define_map.hpp"
#include "tools/variable.hpp"
#include "frontend/C/C_language_parser.hpp"
#include "passes/hl_passes.hpp"
#include "passes/high_level/function_mapping.hpp"
#include "passes/high_level/hl_pass_manager.hpp"
#include "passes/high_level/normalization_pass.hpp"
#include "tools/high_level_ast_lowering.hpp"

#include <memory>
#include <fstream>


TEST(HlPassesTest, divisionImplementation) {


    std::string input_file = "test_division_implementation.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep, {1,2,3,4,5,8,9,10});
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> result = parser.AST;




    std::shared_ptr<variable> var = std::make_shared<variable>("constant",6);
    std::shared_ptr<hl_ast_operand> op_1= std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> rec_exp = std::make_shared<hl_expression_node>(expr_reciprocal);
    rec_exp->set_rhs(op_1);

    var = std::make_shared<variable>("intermediate_expr_0");
    std::shared_ptr<hl_definition_node> rec_def = std::make_shared<hl_definition_node>("intermediate_expr_0", c_type_int, var);
    rec_def->set_initializer(rec_exp);

    var = std::make_shared<variable>("constant", 4);
    op_1= std::make_shared<hl_ast_operand>(var);




    var = std::make_shared<variable>("intermediate_expr_0");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> mult_exp = std::make_shared<hl_expression_node>(expr_mult);
    mult_exp->set_lhs(op_1);
    mult_exp->set_rhs(op_2);

    var = std::make_shared<variable>("a");
    std::shared_ptr<hl_definition_node> mult_def = std::make_shared<hl_definition_node>("a", c_type_int, var);
    mult_def->set_initializer(mult_exp);


    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->set_content({rec_def, mult_def});

    EXPECT_EQ( *gold_standard, *result);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(parser.AST->get_content()[0])->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(result)->pretty_print()<< std::endl;
    }
}

TEST(HlPassesTest, functionMapping) {

    std::shared_ptr<variable> var = std::make_shared<variable>("constant",6);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

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

    hl_pass_manager manager = create_hl_pass_manager(ep, {});

    manager.run_morphing_passes(ast);

    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> pass = std::static_pointer_cast<function_mapping>(manager.morphing_passes[0])->get_map_ref();

    EXPECT_EQ( *func_1, *pass->at("test_1"));
    EXPECT_EQ( *func_2, *pass->at("test_2"));

}

TEST(HlPassesTest, functionInlining) {


    std::string input_file = "test_function_inlining.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5});

    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> res = parser.AST->get_content()[0];

    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_code_block);
    // CALL BODY
    std::shared_ptr<variable> var = std::make_shared<variable>("c");
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("c", c_type_int, var);
    std::shared_ptr<hl_expression_node> exadd = std::make_shared<hl_expression_node>(expr_add);

    var = std::make_shared<variable>("constant",2);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("t");
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

    exadd->set_rhs(op_2);
    exadd->set_lhs(op_1);
    def->set_initializer(exadd);

    exadd = std::make_shared<hl_expression_node>(expr_add);

    var = std::make_shared<variable>("c");
    op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("t");
    op_2 = std::make_shared<hl_ast_operand>(var);

    exadd->set_rhs(op_2);
    exadd->set_lhs(op_1);

    gold_standard->set_content({def, exadd});
    EXPECT_EQ(*res, *gold_standard);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << res->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << gold_standard->pretty_print()<< std::endl;
    }

}

TEST(HlPassesTest, normalization) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,8,9,10});
    manager.run_morphing_passes(parser.AST);

    normalization_pass p;
    std::shared_ptr<hl_ast_node> raw_result = p.process_global(parser.AST);

    std::shared_ptr<variable> var = std::make_shared<variable>("intermediate_expr_0");
    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("intermediate_expr_0", c_type_int, var);



    var = std::make_shared<variable>("constant", 4);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);



    var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_mult);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_1->set_initializer(ex_1);

    var = std::make_shared<variable>("a");
    var->set_variable_class(variable_output_type);
    var->set_bound_reg(10);
    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("a", c_type_int, var);


    var = std::make_shared<variable>("intermediate_expr_0");
    op_1 = std::make_shared<hl_ast_operand>(var);


    var = std::make_shared<variable>("constant",6);
    op_2 = std::make_shared<hl_ast_operand>(var);

    ex_1= std::make_shared<hl_expression_node>(expr_add);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_2->set_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->set_content({def_1, def_2});

    EXPECT_EQ( *gold_standard, *raw_result);

}

TEST(HlPassesTest, function_elimination) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,8,9,10});
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> raw_result =parser.AST;

    std::shared_ptr<variable> var = std::make_shared<variable>("intermediate_expr_0");
    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("intermediate_expr_0", c_type_int, var);


    var = std::make_shared<variable>("constant", 4);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


    var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_mult);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_1->set_initializer(ex_1);

    var = std::make_shared<variable>("a");
    var->set_variable_class(variable_output_type);
    var->set_bound_reg(10);
    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("a", c_type_int, var);


    var = std::make_shared<variable>("intermediate_expr_0");
    op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("constant",6);
    op_2 = std::make_shared<hl_ast_operand>(var);

    ex_1= std::make_shared<hl_expression_node>(expr_add);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_2->set_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->set_content({def_1, def_2});

    EXPECT_EQ( *gold_standard, *raw_result);

}

TEST(HlPassesTest, hl_ast_lowering) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,8,9,10});
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    high_level_ast_lowering tranlator;

    tranlator.set_input_ast(normalized_ast);
    tranlator.translate();
    std::shared_ptr<ll_ast_node> result = tranlator.get_output_ast();

    int i = 0;

    std::shared_ptr<variable> op_a = std::make_shared<variable>("constant", 4);
    std::shared_ptr<variable> op_b = std::make_shared<variable>("constant", 5);
    std::shared_ptr<variable> dest = std::make_shared<variable>("intermediate_expr_0");

    std::shared_ptr<ll_register_instr_node> op_1 = std::make_shared<ll_register_instr_node>("mul", op_a, op_b, dest);


    op_a = std::make_shared<variable>("intermediate_expr_0");
    op_b = std::make_shared<variable>("constant", 6);
    dest = std::make_shared<variable>("a");

    std::shared_ptr<ll_register_instr_node> op_2 = std::make_shared<ll_register_instr_node>( "add", op_a, op_b, dest);

    std::shared_ptr<ll_ast_node> golden_standard = std::make_shared<ll_ast_node>(ll_type_program_head);
    golden_standard->set_content({op_1, op_2});

    ASSERT_EQ(*golden_standard, *result);
}

TEST(HlPassesTest, intrinsics_implementation) {


    std::string input_file = "test_intrinsics_implementation.c";
    std::ifstream ifs(input_file);


    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();


    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,8,9,10});
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    std::shared_ptr<variable> var = std::make_shared<variable>("intermediate_expr_0");
    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("intermediate_expr_0", c_type_int, var);

    var = std::make_shared<variable>("constant", 4);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_mult);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_1->set_initializer(ex_1);

    var = std::make_shared<variable>("a");
    var->set_variable_class(variable_output_type);
    var->set_bound_reg(10);
    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("a", c_type_int, var);

    var = std::make_shared<variable>("intermediate_expr_0");
    op_1 = std::make_shared<hl_ast_operand>(var);

    var = std::make_shared<variable>("constant", 6);
    op_2 = std::make_shared<hl_ast_operand>(var);

    ex_1= std::make_shared<hl_expression_node>(expr_add);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_2->set_initializer(ex_1);

    var = std::make_shared<variable>("b");
    std::shared_ptr<hl_definition_node> def_3 = std::make_shared<hl_definition_node>("b", c_type_float, var);

    var = std::make_shared<variable>("a");
    var->set_variable_class(variable_output_type);
    var->set_bound_reg(10);
    op_1 = std::make_shared<hl_ast_operand>(var);

    ex_1= std::make_shared<hl_expression_node>(expr_itf);
    ex_1->set_rhs(op_1);
    def_3->set_initializer(ex_1);

    var = std::make_shared<variable>("c");
    std::shared_ptr<hl_definition_node> def_4 = std::make_shared<hl_definition_node>("c", c_type_float, var);


    var = std::make_shared<variable>("a");
    var->set_variable_class(variable_output_type);
    var->set_bound_reg(10);
    op_1 = std::make_shared<hl_ast_operand>(var);


    var = std::make_shared<variable>("constant",100);
    op_2 = std::make_shared<hl_ast_operand>(var);

    ex_1= std::make_shared<hl_expression_node>(expr_satp);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_4->set_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->set_content({def_1, def_2 , def_3, def_4});

    ASSERT_EQ(*gold_standard, *normalized_ast);

}


TEST(HlPassesTest, loop_unrolling_array) {


    std::string input_file = "test_loop_unrolling_pass.c";
    std::ifstream ifs(input_file);


    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();


    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,6,7,8});
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    for(int i = 5; i<7; ++i){
        //DEFINITION
        std::shared_ptr<variable> def_var = std::make_shared<variable>("j");
        def_var->set_type(var_type_array);
        std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("j", c_type_int, def_var);
        std::shared_ptr<variable> idx_var = std::make_shared<variable>("i", i);
        std::shared_ptr<hl_ast_operand> op_idx = std::make_shared<hl_ast_operand>(idx_var);
        def->set_array_index({op_idx});
        //INITIALIZER
        std::shared_ptr<hl_expression_node> expr = std::make_shared<hl_expression_node>(expr_add);
        // LHS
        def_var = std::make_shared<variable>("a");
        def_var->set_type(var_type_array);
        std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(def_var);
        idx_var = std::make_shared<variable>("i", i);
        op_idx = std::make_shared<hl_ast_operand>(idx_var);
        op->set_array_index({op_idx});
        expr->set_lhs(op);
        //RHS
        def_var = std::make_shared<variable>("h");
        def_var->set_type(var_type_array);
        op = std::make_shared<hl_ast_operand>(def_var);
        idx_var = std::make_shared<variable>("i", i);
        op_idx = std::make_shared<hl_ast_operand>(idx_var);
        op->set_array_index({op_idx});
        expr->set_rhs(op);
        def->set_initializer(expr);
        gold_standard->add_content(def);
    }
    ASSERT_EQ(*normalized_ast, *gold_standard);
}


TEST(HlPassesTest, test_matrix_scalarization) {


    std::string input_file = "test_matrix_scalarization.c";
    std::ifstream ifs(input_file);


    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();


    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep,{1,2,3,4,5,6,7,8, 9});
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = parser.AST;

    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);



    std::shared_ptr<hl_expression_node> ex = std::make_shared<hl_expression_node>(expr_assign);
    // FIRST EXPRESSION LHS
    std:std::shared_ptr<variable> var = std::make_shared<variable>("_fcmglr_flattened_array_a_0_1");
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
    ex->set_lhs(op);
    // FIRST EXPRESSION RHS
    std::shared_ptr<hl_expression_node> ex_inner = std::make_shared<hl_expression_node>(expr_mult);
    var = std::make_shared<variable>("_fcmglr_flattened_array_b_0");
    op = std::make_shared<hl_ast_operand>(var);
    ex_inner->set_lhs(op);
    var = std::make_shared<variable>("constant", 2);
    op = std::make_shared<hl_ast_operand>(var);
    ex_inner->set_rhs(op);
    ex->set_rhs(ex_inner);
    gold_standard->add_content(ex);

    ex = std::make_shared<hl_expression_node>(expr_assign);
    // SECOND EXPRESSION LHS
    var = std::make_shared<variable>("_fcmglr_flattened_array_b_2");
     op = std::make_shared<hl_ast_operand>(var);
    ex->set_lhs(op);
    // SECOND EXPRESSION RHS
    ex_inner = std::make_shared<hl_expression_node>(expr_mult);
    var = std::make_shared<variable>("_fcmglr_flattened_array_a_1_1");
    op = std::make_shared<hl_ast_operand>(var);
    ex_inner->set_lhs(op);
    var = std::make_shared<variable>("constant", 2);
    op = std::make_shared<hl_ast_operand>(var);
    ex_inner->set_rhs(op);
    ex->set_rhs(ex_inner);
    gold_standard->add_content(ex);
    ASSERT_EQ(*normalized_ast, *gold_standard);
}
