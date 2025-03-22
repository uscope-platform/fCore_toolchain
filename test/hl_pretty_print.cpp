// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <gtest/gtest.h>
#include <fstream>

#include "data_structures/high_level_ast/high_level_ast.hpp"

using namespace fcore;

TEST( hl_pretty_print, operand){
    std::vector<std::shared_ptr<ast_node>> init;
    std::shared_ptr<variable> var = std::make_shared<variable>("array");
    std::shared_ptr<ast_operand> gold_standard = std::make_shared<ast_operand>(var);
    var->set_type(var_type_array);
    var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<ast_operand> idx_op1 = std::make_shared<ast_operand>(var);
    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<ast_operand> idx_op2 = std::make_shared<ast_operand>(var);
    gold_standard->set_array_index({idx_op1, idx_op2});

    auto result = gold_standard->pretty_print();
    ASSERT_EQ(result, "array[5][6]");

    result = gold_standard->pretty_print();
    var = std::make_shared<variable>("const", 12);
    gold_standard = std::make_shared<ast_operand>(var);

    result = gold_standard->pretty_print();
    ASSERT_EQ(result, "12");

    var = std::make_shared<variable>("const", 6.5f);
    gold_standard = std::make_shared<ast_operand>(var);

    result = gold_standard->pretty_print();
    ASSERT_EQ(result, "6.500000");

    var = std::make_shared<variable>("const");
    gold_standard = std::make_shared<ast_operand>(var);

    result = gold_standard->pretty_print();
    ASSERT_EQ(result, "const");

}

TEST( hl_pretty_print, expression){
    std::vector<std::shared_ptr<ast_node>> init;

    std::shared_ptr<ast_expression> gold_standard = std::make_shared<ast_expression>(ast_expression::ADD);

    std::shared_ptr<variable> var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<ast_operand> op_l = std::make_shared<ast_operand>(var);

    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<ast_operand> op_r = std::make_shared<ast_operand>(var);

    gold_standard->set_lhs(op_l);
    gold_standard->set_rhs(op_r);

    auto result = gold_standard->pretty_print();

    ASSERT_EQ(result, "5+6");
}

TEST( hl_pretty_print, definition){
    std::vector<std::shared_ptr<ast_node>> init;
    std::shared_ptr<variable> var;
    std::shared_ptr<ast_operand> op;

    // vector constant init
    for(int i = 1; i<6;++i){
        var = std::make_shared<variable>("constant", i);
        op = std::make_shared<ast_operand>(var);
        init.push_back(op);
    }

    var = std::make_shared<variable>("array_test");
    var->set_type(var_type_array);
    std::shared_ptr<ast_definition> gold_standard = std::make_shared<ast_definition>("array_test", c_type_int, var);

    gold_standard->set_array_initializer(init);
    std::vector<int> shape = {5};
    gold_standard->set_array_shape(shape);


    auto result = gold_standard->pretty_print();
    ASSERT_EQ(result, "int array_test = {1, 2, 3, 4, 5}");

    // scalar constant init
    var = std::make_shared<variable>("scalar_test");

    gold_standard = std::make_shared<ast_definition>("scalar_test", c_type_int, var);
    var = std::make_shared<variable>("constant", 12);
    op = std::make_shared<ast_operand>(var);

    gold_standard->set_scalar_initializer(op);


    result = gold_standard->pretty_print();
    ASSERT_EQ(result, "int scalar_test = 12");
    // scalar function call init
    var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<ast_operand> op_l = std::make_shared<ast_operand>(var);
    std::string name = "test";
    std::vector<std::shared_ptr<ast_node>> args = {op_l};
    std::shared_ptr<ast_call> f_call = std::make_shared<ast_call>(name, args);


    gold_standard->set_scalar_initializer(f_call);

    result = gold_standard->pretty_print();
    ASSERT_EQ(result, "int scalar_test = test( 5 )");

    // vector function call init

    init.clear();

    for(int i = 0; i<2;++i){
        init.push_back(f_call);
    }

    var = std::make_shared<variable>("array_test");
    var->set_type(var_type_array);
    gold_standard = std::make_shared<ast_definition>("array_test", c_type_int, var);

    gold_standard->set_array_initializer(init);
    shape = {2};
    gold_standard->set_array_shape(shape);

    result = gold_standard->pretty_print();
    ASSERT_EQ(result, "int array_test = {test( 5 ), test( 5 )}");



}

TEST( hl_pretty_print, conditional){
    std::vector<std::shared_ptr<ast_node>> init;

    std::shared_ptr<ast_conditional> gold_standard = std::make_shared<ast_conditional>();

    std::shared_ptr<ast_expression> expr = std::make_shared<ast_expression>(ast_expression::ADD);
    std::shared_ptr<variable> var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<ast_operand> op_l = std::make_shared<ast_operand>(var);

    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<ast_operand> op_r = std::make_shared<ast_operand>(var);

    expr->set_lhs(op_l);
    expr->set_rhs(op_r);

    gold_standard->set_condition(expr);

    expr = std::make_shared<ast_expression>(ast_expression::ADD);
    var = std::make_shared<variable>("constant", 7);
    op_r = std::make_shared<ast_operand>(var);
    expr->set_lhs(op_l);
    expr->set_rhs(op_r);
    gold_standard->set_if_block({expr});

    expr = std::make_shared<ast_expression>(ast_expression::ADD);
    var = std::make_shared<variable>("constant", 8);
    op_r = std::make_shared<ast_operand>(var);
    expr->set_lhs(op_l);
    expr->set_rhs(op_r);
    gold_standard->set_else_block({expr});

    auto result = gold_standard->pretty_print();
    ASSERT_EQ(result,"if (5+6) {\n5+7;\n} else {\n5+8;\n}");
}

TEST( hl_pretty_print, loop){
    std::vector<std::shared_ptr<ast_node>> init;

    std::shared_ptr<ast_loop> gold_standard = std::make_shared<ast_loop>();

    std::shared_ptr<ast_expression> expr = std::make_shared<ast_expression>(ast_expression::ADD);
    std::shared_ptr<variable> var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<ast_operand> op_l = std::make_shared<ast_operand>(var);

    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<ast_operand> op_r = std::make_shared<ast_operand>(var);

    expr->set_lhs(op_l);
    expr->set_rhs(op_r);

    gold_standard->set_condition(expr);

    expr = std::make_shared<ast_expression>(ast_expression::ADD);
    var = std::make_shared<variable>("constant", 7);
    op_r = std::make_shared<ast_operand>(var);
    expr->set_lhs(op_l);
    expr->set_rhs(op_r);
    gold_standard->set_iteration_expr(expr);

    expr = std::make_shared<ast_expression>(ast_expression::ADD);
    var = std::make_shared<variable>("constant", 8);
    op_r = std::make_shared<ast_operand>(var);
    expr->set_lhs(op_l);
    expr->set_rhs(op_r);
    gold_standard->set_loop_content({expr});

    var = std::make_shared<variable>("constant", 9);
    std::shared_ptr<ast_definition> def = std::make_shared<ast_definition>("test", c_type_int, var);

    gold_standard->set_init_statement(def);

    auto result = gold_standard->pretty_print();
    ASSERT_EQ(result, "for (int test; 5+6; 5+7) {\n5+8;\n}");
}


TEST( hl_pretty_print, function_call){
    std::vector<std::shared_ptr<ast_node>> init;

    std::shared_ptr<variable> var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<ast_operand> op_l = std::make_shared<ast_operand>(var);
    std::string name = "test";
    std::vector<std::shared_ptr<ast_node>> args = {op_l};
    std::shared_ptr<ast_call> gold_standard = std::make_shared<ast_call>(name, args);

    auto result = gold_standard->pretty_print();
    ASSERT_EQ(result, "test( 5 )");
}


TEST( hl_pretty_print, function_def){
    std::vector<std::shared_ptr<ast_node>> init;

    std::shared_ptr<ast_function_def> gold_standard = std::make_shared<ast_function_def>();
    gold_standard->set_name("test");

    std::shared_ptr<variable> var = std::make_shared<variable>("array_test");
    var->set_type(var_type_array);
    std::shared_ptr<ast_definition> def = std::make_shared<ast_definition>("array_test", c_type_int, var);
    gold_standard->set_parameters_list({def});

    std::shared_ptr<ast_expression> exp = std::make_shared<ast_expression>(ast_expression::MULT);
    var = std::make_shared<variable>("constant", 5);
    std::shared_ptr<ast_operand> op_l = std::make_shared<ast_operand>(var);
    var = std::make_shared<variable>("constant", 6);
    std::shared_ptr<ast_operand> op_r = std::make_shared<ast_operand>(var);
    exp->set_lhs(op_l);
    exp->set_rhs(op_r);
    gold_standard->set_body({exp});


    exp = std::make_shared<ast_expression>(ast_expression::MULT);
    var = std::make_shared<variable>("constant", 7);
    op_l = std::make_shared<ast_operand>(var);
    var = std::make_shared<variable>("constant", 8);
    op_r = std::make_shared<ast_operand>(var);
    exp->set_lhs(op_l);
    exp->set_rhs(op_r);
    gold_standard->set_return(exp);

    auto result = gold_standard->pretty_print();
      ASSERT_EQ(result, "void test(int array_test) {\n    5*6\n    return 7*8\n}");

}



TEST( hl_pretty_print, struct_def){

    auto struct_def = std::make_shared<ast_struct>("parameters");
    auto var = std::make_shared<variable>("gain");
    auto def = std::make_shared<ast_definition>("gain", c_type_float, var);
    struct_def->add_definition(def);

    var = std::make_shared<variable>("phase");
    def = std::make_shared<ast_definition>("phase", c_type_float, var);
    struct_def->add_definition(def);

    auto result =  struct_def->pretty_print();
    std::string check = "struct parameters {\n    float gain;\n    float phase;\n};\n";

    ASSERT_EQ(result, check);

}



TEST(hl_pretty_print, complex_expression) {

    auto e_add = std::make_shared<ast_expression>(ast_expression::ADD);
    auto var = std::make_shared<variable>("constant", 2.9f);
    auto op = std::make_shared<ast_operand>(var);
    e_add->set_lhs(op);
    var = std::make_shared<variable>("constant", 5.1f);
    op = std::make_shared<ast_operand>(var);
    e_add->set_rhs(op);

    auto e_mul = std::make_shared<ast_expression>(ast_expression::MULT);
    e_mul->set_rhs(e_add);
    var = std::make_shared<variable>("constant", 3.3f);
    op = std::make_shared<ast_operand>(var);
    e_mul->set_lhs(op);

    auto e_div = std::make_shared<ast_expression>(ast_expression::DIV);
    e_div->set_lhs(e_mul);
    var = std::make_shared<variable>("constant", 7.0f);
    op = std::make_shared<ast_operand>(var);
    e_div->set_rhs(op);

    auto result = e_div->pretty_print();
    std::string reference = "(3.300000*(2.900000+5.100000))/7.000000";
    EXPECT_EQ(result, reference);

}
