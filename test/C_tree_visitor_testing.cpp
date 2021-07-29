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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.01/07/2021.
//

#include <gtest/gtest.h>
#include <fstream>

#include "tools/define_map.hpp"
#include "tools/variable_map.hpp"
#include "frontend/C/C_language_parser.hpp"
#include "data_structures/high_level_ast/hl_ast_operand.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "data_structures/high_level_ast/hl_ast_conditional_node.hpp"

TEST( cTreeVisitor, unaryExpressions) {
    std::string input_file = "test_unary_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

    std::shared_ptr<hl_expression_node> res_1 = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());
    std::shared_ptr<hl_expression_node> res_2 = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[1])->get_initializer());
    std::shared_ptr<hl_expression_node> res_3 = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[2])->get_initializer());



    std::stack<std::shared_ptr<hl_expression_node>> gold_standard;
    // a = !b;
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(variable_operand);
    op->set_name("b");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "b");
    op->set_variable(var);
    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_not_l);
    gs_1->set_rhs(op);

    // c = -~d;
    op = std::make_shared<hl_ast_operand>(variable_operand);
    op->set_name("d");
    var = std::make_shared<variable>(false, "d");
    op->set_variable(var);

    std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_not_b);
    exp->set_rhs(op);
    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_neg);
    gs_2->set_rhs(exp);


    // e = !(~f);
    op = std::make_shared<hl_ast_operand>(variable_operand);
    op->set_name("f");
    var = std::make_shared<variable>(false, "f");
    op->set_variable(var);

    exp = std::make_shared<hl_expression_node>(expr_not_b);
    exp->set_rhs(op);
    std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_not_l);
    gs_3->set_rhs(exp);


    EXPECT_EQ(*res_1, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res_1)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_3)->pretty_print()<< std::endl;
    }
    EXPECT_EQ(*res_2, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res_2)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_3)->pretty_print()<< std::endl;
    }
    EXPECT_EQ(*res_3, *gs_3);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res_3)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_3)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, multiplicativeExpressions) {
    std::string input_file = "test_multiplicative_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

    // a = !b;
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_mult);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_div);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    var = std::make_shared<variable>(true, std::to_string(6));
    op_2->set_variable(var);

    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_modulo);
    gs_3->set_lhs(gs_2);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(3);
    var = std::make_shared<variable>(true, std::to_string(3));
    op_2->set_variable(var);

    gs_3->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());



    EXPECT_EQ(*res, *gs_3);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_3)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, additiveExpressions) {
    std::string input_file = "test_additive_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_add);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_sub);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    var = std::make_shared<variable>(true, std::to_string(6));
    op_2->set_variable(var);

    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());

    EXPECT_EQ(*res, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, shiftExpressions) {
    std::string input_file = "test_shift_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_rsh);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_lsh);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    var = std::make_shared<variable>(true, std::to_string(6));
    op_2->set_variable(var);

    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());

    EXPECT_EQ(*res, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, relationalExpressions) {
    std::string input_file = "test_relational_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_gt);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_lt);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    var = std::make_shared<variable>(true, std::to_string(6));
    op_2->set_variable(var);
    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_gte);
    gs_3->set_lhs(gs_2);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(3);
    var = std::make_shared<variable>(true, std::to_string(3));
    op_2->set_variable(var);
    gs_3->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_4 = std::make_shared<hl_expression_node>(expr_lte);
    gs_4->set_lhs(gs_3);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(7);
    var = std::make_shared<variable>(true, std::to_string(7));
    op_2->set_variable(var);
    gs_4->set_rhs(op_2);
    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());

    EXPECT_EQ(*res, *gs_4);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_4)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, equalityExpressions) {
    std::string input_file = "test_equality_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_eq);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_neq);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    var = std::make_shared<variable>(true, std::to_string(6));
    op_2->set_variable(var);

    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());

    EXPECT_EQ(*res, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
    }
}



TEST( cTreeVisitor, andBinExpressions) {
    std::string input_file = "test_andb_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_and_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());

    EXPECT_EQ(*res, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
    }
}

TEST( cTreeVisitor, exOrBinExpressions) {
    std::string input_file = "test_exorb_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());

    EXPECT_EQ(*res, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
    }
}




TEST( cTreeVisitor, orLogExpressions) {
    std::string input_file = "test_orl_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_or_l);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());

    EXPECT_EQ(*res, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
    }
}

TEST( cTreeVisitor, andLogExpressions) {
    std::string input_file = "test_andl_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_and_l);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer());

    EXPECT_EQ(*res, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, assignmentExpressions) {
    std::string input_file = "test_assignment_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    //std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.block_content;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");
    var = std::make_shared<variable>(false, "test");
    op_3->set_variable(var);
    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_assign);
    gs_2->set_lhs(op_3);
    gs_2->set_rhs(gs_1);



    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(parser.visitor.current_block_item);

    EXPECT_EQ(*res, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, function_def) {
    std::string input_file = "test_assignment_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::shared_ptr<hl_function_def_node> results = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");
    var = std::make_shared<variable>(false, "test");
    op_3->set_variable(var);
    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_assign);
    gs_2->set_lhs(op_3);
    gs_2->set_rhs(gs_1);

    std::shared_ptr<hl_function_def_node> gs_3 = std::make_shared<hl_function_def_node>();

    std::vector<std::shared_ptr<hl_ast_node>> res_body;
    res_body.push_back(gs_2);

    gs_3->set_body(res_body);
    std::string f_name = "main";
    gs_3->set_name(f_name);
    gs_3->set_return_type(c_type_int);

    std::shared_ptr<hl_function_def_node> res = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);

    EXPECT_EQ(*res, *gs_3);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_function_def_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_function_def_node>(gs_3)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, function_call) {
    std::string input_file = "test_function_call.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::shared_ptr<hl_function_def_node> result = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(4);
    var = std::make_shared<variable>(true, std::to_string(4));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_add);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_3->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_3->set_variable(var);

    std::string func_name = "test";
    std::vector<std::shared_ptr<hl_ast_node>> args = {gs_1, op_3};
    std::shared_ptr<hl_function_call_node> gs_3 = std::make_shared<hl_function_call_node>(func_name, args);


    std::shared_ptr<hl_function_call_node> res = std::static_pointer_cast<hl_function_call_node>(result->get_body()[0]);


    EXPECT_EQ(*res, *gs_3);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_function_call_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_function_call_node>(gs_3)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, definition) {
    std::string input_file = "test_definition.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();



    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    var = std::make_shared<variable>(false, "test");
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("test",c_type_int, var);
    def->set_initializer(gs_1);
    std::shared_ptr<hl_definition_node> res = std::static_pointer_cast<hl_definition_node>(parser.visitor.ext_decl[0]);

    EXPECT_EQ(*res, *def);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_definition_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_definition_node>(def)->pretty_print()<< std::endl;
    }
}



TEST( cTreeVisitor, returnTest) {
    std::string input_file = "test_return.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::shared_ptr<hl_function_def_node> func_def = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);
    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(func_def->get_return());

    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "c");
    op_1->set_variable(var);
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_2->set_variable(var);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");
    var = std::make_shared<variable>(false, "test");
    op_3->set_variable(var);
    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_assign);
    gs_2->set_lhs(op_3);
    gs_2->set_rhs(gs_1);


    EXPECT_EQ(*res, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
    }

}




TEST( cTreeVisitor, ConditionalTest) {
    std::string input_file = "test_conditional.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::shared_ptr<hl_ast_conditional_node> result = std::static_pointer_cast<hl_ast_conditional_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[0]);

    std::shared_ptr<hl_ast_conditional_node> gold_standard = std::make_shared<hl_ast_conditional_node>();
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "a");
    std::shared_ptr<hl_definition_node> def_node = std::make_shared<hl_definition_node>("a", c_type_int, var);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(2);
    var = std::make_shared<variable>(true, std::to_string(2));
    op_1->set_variable(var);

    def_node->set_initializer(op_1);
    gold_standard->set_if_block({def_node});
    var = std::make_shared<variable>(false, "a");
    def_node = std::make_shared<hl_definition_node>("a", c_type_int, var);
    op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(3);
    var = std::make_shared<variable>(true, std::to_string(3));
    op_1->set_variable(var);

    def_node->set_initializer(op_1);
    gold_standard->set_else_block({def_node});

    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(variable_operand);
    op_2->set_name("i");
    var = std::make_shared<variable>(false, "i");
    op_2->set_variable(var);

    op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(0);
    var = std::make_shared<variable>(true, std::to_string(0));
    op_1->set_variable(var);

    std::shared_ptr<hl_expression_node> condition = std::make_shared<hl_expression_node>(expr_eq);
    condition->set_lhs(op_2);
    condition->set_rhs(op_1);
    gold_standard->set_condition(condition);

    EXPECT_EQ(*result, *gold_standard);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << result->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << gold_standard->pretty_print()<< std::endl;
    }

}

TEST( cTreeVisitor, loopTest) {
    std::string input_file = "test_loop_ast.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::shared_ptr<hl_ast_loop_node> result = std::static_pointer_cast<hl_ast_loop_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[3]);


    std::shared_ptr<hl_ast_loop_node> gold_standard = std::make_shared<hl_ast_loop_node>();

    // LOOP BODY
    std::shared_ptr<hl_expression_node> loop_body = std::make_shared<hl_expression_node>(expr_assign);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("j");
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "j");
    op_1->set_variable(var);

    loop_body->set_lhs(op_1);
    std::shared_ptr<hl_expression_node> body_add_expr = std::make_shared<hl_expression_node>(expr_add);
    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("a");
    var = std::make_shared<variable>(false, "a");
    op_1->set_variable(var);

    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(variable_operand);
    op_2->set_name("h");
    var = std::make_shared<variable>(false, "h");
    op_2->set_variable(var);

    body_add_expr->set_lhs(op_1);
    body_add_expr->set_lhs(op_2);
    loop_body->set_rhs(body_add_expr);
    gold_standard->set_loop_content({loop_body});
    // LOOP INIT CONDITION
    var = std::make_shared<variable>(false, "i");
    std::shared_ptr<hl_definition_node> init_def = std::make_shared<hl_definition_node>("i", c_type_int, var);
    std::shared_ptr<hl_ast_operand> def_val = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    def_val->set_immediate(0);
    var = std::make_shared<variable>(true, std::to_string(0));
    def_val->set_variable(var);

    init_def->set_initializer(def_val);
    gold_standard->set_init_statement(init_def);
    // LOOP CONDITION
    std::shared_ptr<hl_expression_node> loop_cond = std::make_shared<hl_expression_node>(expr_lt);
    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("i");
    var = std::make_shared<variable>(false, "i");
    op_1->set_variable(var);

    op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(4);
    var = std::make_shared<variable>(true, std::to_string(4));
    op_2->set_variable(var);

    loop_cond->set_rhs(op_2);
    loop_cond->set_lhs(op_1);
    gold_standard->set_condition(loop_cond);
    // LOOP ITERATION EXPR
    std::shared_ptr<hl_expression_node> loop_iter = std::make_shared<hl_expression_node>(expr_incr_pre);
    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("i");
    var = std::make_shared<variable>(false, "i");
    op_1->set_variable(var);

    loop_iter->set_rhs(op_1);
    gold_standard->set_iteration_expr(loop_iter);

    EXPECT_EQ(*result, *gold_standard);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << result->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << gold_standard->pretty_print()<< std::endl;
    }

}




TEST( cTreeVisitor, array_test){
    std::string input_file = "test_array.c";
    std::ifstream ifs(input_file);


    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::vector<std::shared_ptr<hl_ast_node>> result = std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body();

    std::vector<std::shared_ptr<hl_ast_node>> gold_standard;
    std::shared_ptr<variable> var = std::make_shared<variable>(false, "array_test");
    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("array_test", c_type_int, var);
    def_1->set_is_array(true);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(5);
    var = std::make_shared<variable>(true, std::to_string(5));
    op_1->set_variable(var);

    def_1->set_dimensions({op_1});
    var = std::make_shared<variable>(false, "test_matrix");
    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("test_matrix", c_type_int, var);
    def_2->set_is_array(true);
    op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(2);
    var = std::make_shared<variable>(true, std::to_string(2));
    op_1->set_variable(var);

    def_2->set_dimensions({op_1, op_1});
    var = std::make_shared<variable>(false, "b");
    var->type = variable_output_type;
    var->set_bound_reg(4);
    std::shared_ptr<hl_definition_node> def_3 = std::make_shared<hl_definition_node>("b", c_type_int, var);

    std::shared_ptr<hl_expression_node> ex = std::make_shared<hl_expression_node>(expr_add);
    op_1 = std::make_shared<hl_ast_operand>(array_operand);
    op_1->set_name("array_test");
    var = std::make_shared<variable>(false, "array_test");
    op_1->set_variable(var);

    //lhs
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(0);
    var = std::make_shared<variable>(true, std::to_string(0));
    op_2->set_variable(var);
    op_1->set_array_index(op_2);
    ex->set_lhs(op_1);
    //rhs
    op_1 = std::make_shared<hl_ast_operand>(array_operand);
    op_1->set_name("test_matrix");
    var = std::make_shared<variable>(false, "test_matrix");
    op_1->set_variable(var);

    op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(1);
    var = std::make_shared<variable>(true, std::to_string(1));
    op_2->set_variable(var);

    op_1->set_array_index(op_2);
    ex->set_rhs(op_1);
    def_3->set_initializer(ex);

    gold_standard.push_back(def_1);
    gold_standard.push_back(def_2);
    gold_standard.push_back(def_3);

    ASSERT_TRUE(hl_ast_node::compare_vectors(result, gold_standard));

}