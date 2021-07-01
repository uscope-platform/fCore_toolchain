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
    EXPECT_EQ(*res_2, *gs_2);
    EXPECT_EQ(*res_3, *gs_3);
}

/*TEST( cFrontend, parser_main) {
    std::string input_file = "test_main_add.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();
}*/