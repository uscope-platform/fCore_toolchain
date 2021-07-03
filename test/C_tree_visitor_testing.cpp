//
// Created by fils on 01/07/2021.
//

#include <gtest/gtest.h>
#include <fstream>

#include "frontend/define_map.h"
#include "frontend/variable_map.hpp"
#include "frontend/C/C_language_parser.h"
#include "code_elements/hl_ast/hl_ast_operand.h"
#include "code_elements/hl_ast/hl_expression_node.h"


TEST( cTreeVisitor, unaryExpressions) {
    std::string input_file = "test_unary_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;

    std::shared_ptr<hl_expression_node> res_3 = results.top();
    results.pop();
    std::shared_ptr<hl_expression_node> res_2 = results.top();
    results.pop();
    std::shared_ptr<hl_expression_node> res_1 = results.top();
    results.pop();


    std::stack<std::shared_ptr<hl_expression_node>> gold_standard;
    // a = !b;
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(variable_operand);
    op->set_name("b");
    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_not_l);
    gs_1->set_rhs(op);

    // c = -~d;
    op = std::make_shared<hl_ast_operand>(variable_operand);
    op->set_name("d");
    std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_not_b);
    exp->set_rhs(op);
    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_neg);
    gs_2->set_rhs(exp);


    // e = !(~f);
    op = std::make_shared<hl_ast_operand>(variable_operand);
    op->set_name("f");
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

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;

    // a = !b;
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_mult);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_div);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_modulo);
    gs_3->set_lhs(gs_2);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(3);
    gs_3->set_rhs(op_2);
    std::shared_ptr<hl_expression_node> res = results.top();

    EXPECT_EQ(*res, *gs_3);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_3)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, additiveExpressions) {
    std::string input_file = "test_additive_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_add);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_sub);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = results.top();

    EXPECT_EQ(*res, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, shiftExpressions) {
    std::string input_file = "test_shift_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_rsh);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_lsh);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = results.top();

    EXPECT_EQ(*res, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, relationalExpressions) {
    std::string input_file = "test_relational_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;

    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_gt);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_lt);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_gte);
    gs_3->set_lhs(gs_2);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(3);
    gs_3->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_4 = std::make_shared<hl_expression_node>(expr_lte);
    gs_4->set_lhs(gs_3);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(7);
    gs_4->set_rhs(op_2);
    std::shared_ptr<hl_expression_node> res = results.top();

    EXPECT_EQ(*res, *gs_4);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_4)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, equalityExpressions) {
    std::string input_file = "test_equality_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_eq);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_neq);
    gs_2->set_lhs(gs_1);
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);
    gs_2->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = results.top();

    EXPECT_EQ(*res, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
    }
}



TEST( cTreeVisitor, andBinExpressions) {
    std::string input_file = "test_andb_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_and_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> res = results.top();

    EXPECT_EQ(*res, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
    }
}

TEST( cTreeVisitor, exOrBinExpressions) {
    std::string input_file = "test_exorb_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> res = results.top();

    EXPECT_EQ(*res, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
    }
}




TEST( cTreeVisitor, orLogExpressions) {
    std::string input_file = "test_orl_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_or_l);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = results.top();

    EXPECT_EQ(*res, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
    }
}




TEST( cTreeVisitor, andLogExpressions) {
    std::string input_file = "test_andl_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::stack<std::shared_ptr<hl_expression_node>> results = parser.visitor.expressions_stack;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_and_l);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> res = results.top();

    EXPECT_EQ(*res, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
    }
}







TEST( cFrontend, parser_main) {
    std::string input_file = "test_main_add.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
}