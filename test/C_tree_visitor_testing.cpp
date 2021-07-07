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
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

    std::shared_ptr<hl_expression_node> res_1 = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();
    std::shared_ptr<hl_expression_node> res_2 = std::static_pointer_cast<hl_definition_node>(results[1])->get_initializer();
    std::shared_ptr<hl_expression_node> res_3 = std::static_pointer_cast<hl_definition_node>(results[2])->get_initializer();



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

    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

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

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();



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
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


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

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();

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
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


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

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();

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
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

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
    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();

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
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


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

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();

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
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_and_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();

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
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();

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
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_or_l);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();

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
    std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_and_l);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_definition_node>(results[0])->get_initializer();

    EXPECT_EQ(*res, *gs_1);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, assignmentExpressions) {
    std::string input_file = "test_assignment_expressions.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    //std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.block_content;


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");
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

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::shared_ptr<hl_function_def_node> results = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");
    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_assign);
    gs_2->set_lhs(op_3);
    gs_2->set_rhs(gs_1);

    std::shared_ptr<hl_function_def_node> gs_3 = std::make_shared<hl_function_def_node>();

    std::vector<std::shared_ptr<hl_ast_node>> res_body;
    res_body.push_back(gs_2);

    gs_3->set_body(res_body);
    std::string f_name = "main";
    gs_3->set_name(f_name);
    gs_3->set_type(c_type_int);

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

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
    std::shared_ptr<hl_function_def_node> result = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(4);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_add);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_3->set_immediate(5);
    std::string func_name = "test";
    std::vector<std::shared_ptr<hl_ast_node>> args = {gs_1, op_3};
    std::shared_ptr<hl_function_call_node> gs_3 = std::make_shared<hl_function_call_node>(func_name, args);

    std::shared_ptr<hl_expression_node> res_exp = std::static_pointer_cast<hl_expression_node>(result->get_body()[0]);
    std::shared_ptr<hl_function_call_node> res = std::static_pointer_cast<hl_function_call_node>(res_exp->get_rhs());


    EXPECT_EQ(*res, *gs_3);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_function_call_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_function_call_node>(gs_3)->pretty_print()<< std::endl;
    }
}


TEST( cTreeVisitor, definition) {
    std::string input_file = "test_definition.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();



    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("test",c_type_int);
    def->set_initializer(gs_1);
    std::shared_ptr<hl_definition_node> res = std::static_pointer_cast<hl_definition_node>(parser.visitor.ext_decl[0]);

    EXPECT_EQ(*res, *def);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_definition_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_definition_node>(def)->pretty_print()<< std::endl;
    }
}



TEST( cFrontend, returnTest) {
    std::string input_file = "test_return.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::shared_ptr<hl_function_def_node> func_def = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);
    std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(func_def->get_return());

    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");
    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_assign);
    gs_2->set_lhs(op_3);
    gs_2->set_rhs(gs_1);


    EXPECT_EQ(*res, *gs_2);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
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