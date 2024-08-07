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

#include "tools/define_map.hpp"
#include "frontend/C/C_language_parser.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{
    TEST( cTreeVisitor, unaryExpressions) {

        std::istringstream test_content(R""""(
            int a = !b;

            int c = -~d;

            int e = !(~f);
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        parser.parse(std::unordered_map<std::string, variable_class_t>());
        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

        std::shared_ptr<hl_expression_node> res_1 = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());
        std::shared_ptr<hl_expression_node> res_2 = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[1])->get_scalar_initializer());
        std::shared_ptr<hl_expression_node> res_3 = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[2])->get_scalar_initializer());


        std::stack<std::shared_ptr<hl_expression_node>> gold_standard;
        // a = !b;

        std::shared_ptr<variable> var = std::make_shared<variable>( "b");
        std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_not_l);
        gs_1->set_rhs(op);

        // c = -~d;
        var = std::make_shared<variable>( "d");
        op = std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_not_b);
        exp->set_rhs(op);
        std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_neg);
        gs_2->set_rhs(exp);


        // e = !(~f);

        var = std::make_shared<variable>( "f");
        op = std::make_shared<hl_ast_operand>(var);

        exp = std::make_shared<hl_expression_node>(expr_not_b);
        exp->set_rhs(op);
        std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_not_l);
        gs_3->set_rhs(exp);


        EXPECT_EQ(*res_1, *gs_1);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res_1)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
        }
        EXPECT_EQ(*res_2, *gs_2);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res_2)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
        }
        EXPECT_EQ(*res_3, *gs_3);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res_3)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_3)->pretty_print()<< std::endl;
        }
    }



    TEST( cTreeVisitor, hex_constant) {

        std::istringstream test_content(R""""(
            int a = 0xff;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        parser.parse(std::unordered_map<std::string, variable_class_t>());
        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

        auto res = std::static_pointer_cast<hl_ast_operand>(std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer())->get_int_value();

        EXPECT_EQ(res, 0xff);
    }

    TEST( cTreeVisitor, multiplicativeExpressions) {

        std::istringstream test_content(R""""(
            int test = c*5/6%3;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

        // a = !b;

        std::shared_ptr<variable> var = std::make_shared<variable>( "c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant",5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_mult);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_div);
        gs_2->set_lhs(gs_1);
        var = std::make_shared<variable>("constant",6);
        op_2= std::make_shared<hl_ast_operand>(var);

        gs_2->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_modulo);
        gs_3->set_lhs(gs_2);

        var = std::make_shared<variable>("constant", 3);
        op_2= std::make_shared<hl_ast_operand>(var);
        gs_3->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());



        EXPECT_EQ(*res, *gs_3);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_3)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, additiveExpressions) {

        std::istringstream test_content(R""""(
           int test = c+5-6;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;



        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant",5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_add);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_sub);
        gs_2->set_lhs(gs_1);
        var = std::make_shared<variable>("constant",6);
        op_2= std::make_shared<hl_ast_operand>(var);

        gs_2->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());

        EXPECT_EQ(*res, *gs_2);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, shiftExpressions) {
        std::istringstream test_content(R""""(
            int test = c>>5<<6;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;



        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant",5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_rsh);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_lsh);
        gs_2->set_lhs(gs_1);

        var = std::make_shared<variable>("constant",6);
        op_2= std::make_shared<hl_ast_operand>(var);

        gs_2->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());

        EXPECT_EQ(*res, *gs_2);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, relationalExpressions) {
        std::istringstream test_content(R""""(
            int test = c>5<6>=3<=7;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;


        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant",5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_gt);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_lt);
        gs_2->set_lhs(gs_1);

        var = std::make_shared<variable>("constant", 6);
        op_2= std::make_shared<hl_ast_operand>(var);
        gs_2->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_gte);
        gs_3->set_lhs(gs_2);

        var = std::make_shared<variable>("constant",3);
        op_2= std::make_shared<hl_ast_operand>(var);
        gs_3->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> gs_4 = std::make_shared<hl_expression_node>(expr_lte);
        gs_4->set_lhs(gs_3);

        var = std::make_shared<variable>("constant",7);
        op_2= std::make_shared<hl_ast_operand>(var);
        gs_4->set_rhs(op_2);
        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());

        EXPECT_EQ(*res, *gs_4);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_4)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, equalityExpressions) {
        std::istringstream test_content(R""""(
            int test = c==5!=6;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;



        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_eq);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_neq);
        gs_2->set_lhs(gs_1);

        var = std::make_shared<variable>("constant",6);
        op_2= std::make_shared<hl_ast_operand>(var);

        gs_2->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());

        EXPECT_EQ(*res, *gs_2);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_2)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, andBinExpressions) {

        std::istringstream test_content(R""""(
            int test = c&5;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;

        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_and_b);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);


        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());

        EXPECT_EQ(*res, *gs_1);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, exOrBinExpressions) {

        std::istringstream test_content(R""""(
            int test = c^5;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;



        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);


        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());

        EXPECT_EQ(*res, *gs_1);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, orLogExpressions) {

        std::istringstream test_content(R""""(
            int test = c||5;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;



        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_or_l);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());

        EXPECT_EQ(*res, *gs_1);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, andLogExpressions) {

        std::istringstream test_content(R""""(
            int test = c&&5;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.ext_decl;



        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_and_l);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);


        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(
                std::static_pointer_cast<hl_definition_node>(results[0])->get_scalar_initializer());

        EXPECT_EQ(*res, *gs_1);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(gs_1)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, assignmentExpressions) {

        std::istringstream test_content(R""""(
            int main(){
                test = c^5;
                test += c^5;
                test -= c^5;
                test *= c^5;
                test /= c^5;
                test %= c^5;
                test &= c^5;
                test |= c^5;
                test ^= c^5;
                test <<= c^5;
                test >>= c^5;
            }
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        //std::vector<std::shared_ptr<hl_ast_node>> results = parser.visitor.block_content;

        std::vector<std::shared_ptr<hl_ast_node>> func_body;

        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        var = std::make_shared<variable>("test");
        std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> assignment = std::make_shared<hl_expression_node>(expr_assign);
        assignment->set_lhs(op_3);
        assignment->set_rhs(gs_1);

        func_body.push_back(assignment);

        std::vector<assignment_type_t> assignment_types = {addition_assignment, subtraction_assignment, multiplication_assignment, division_assignment, modulo_assignment, and_assignment, or_assignment, xor_assignment, lsh_assignment, rsh_assignment};
        for(auto item:assignment_types){
            assignment = std::make_shared<hl_expression_node>(expr_assign);
            assignment->set_assignment_type(item);
            assignment->set_lhs(op_3);
            assignment->set_rhs(gs_1);
            func_body.push_back(assignment);
        }

        std::shared_ptr<hl_function_def_node> gold_standard = std::make_shared<hl_function_def_node>();

        std::vector<std::shared_ptr<hl_ast_node>> res_body;

        gold_standard->set_body(func_body);
        std::string f_name = "main";
        gold_standard->set_name(f_name);
        gold_standard->set_return_type(c_type_int);


        std::shared_ptr<hl_function_def_node> result = std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0]);
        EXPECT_EQ(*result, *gold_standard);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_function_def_node>(result)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_function_def_node>(gold_standard)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, function_def) {

        std::istringstream test_content(R""""(
            int main(){
                test = c^5;
            }
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::shared_ptr<hl_function_def_node> results = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);



        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);


        var = std::make_shared<variable>("test");
        std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(var);

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

        std::istringstream test_content(R""""(
            int main(){
                test(c+4, 5);
            }
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::shared_ptr<hl_function_def_node> result = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);

        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

        var = std::make_shared<variable>("constant", 4);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_add);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(var);

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

        std::istringstream test_content(R""""(
            int test = c^5;
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        var = std::make_shared<variable>("test");
        std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("test",c_type_int, var);
        def->set_scalar_initializer(gs_1);
        std::shared_ptr<hl_definition_node> res = std::static_pointer_cast<hl_definition_node>(parser.visitor.ext_decl[0]);

        EXPECT_EQ(*res, *def);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_definition_node>(res)->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_definition_node>(def)->pretty_print()<< std::endl;
        }
    }

    TEST( cTreeVisitor, returnTest) {

        std::istringstream test_content(R""""(
        int main(){
            return test = c^5;
        }
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);


        std::shared_ptr<hl_function_def_node> func_def = std::static_pointer_cast<hl_function_def_node>(parser.visitor.functions[0]);
        std::shared_ptr<hl_expression_node> res = std::static_pointer_cast<hl_expression_node>(func_def->get_return());

        std::shared_ptr<variable> var = std::make_shared<variable>("c");
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(var);

        std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_xor_b);
        gs_1->set_lhs(op_1);
        gs_1->set_rhs(op_2);

        var = std::make_shared<variable>("test");
        std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(var);

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

        std::istringstream test_content(R""""(
            int main(){
                if( i == 0){
                    int a = 2;
                } else{
                    int a = 3;
                }
            }
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::shared_ptr<hl_ast_conditional_node> result = std::static_pointer_cast<hl_ast_conditional_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[0]);

        std::shared_ptr<hl_ast_conditional_node> gold_standard = std::make_shared<hl_ast_conditional_node>();
        std::shared_ptr<variable> var = std::make_shared<variable>("a");
        std::shared_ptr<hl_definition_node> def_node = std::make_shared<hl_definition_node>("a", c_type_int, var);

        var = std::make_shared<variable>("constant",2);
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

        def_node->set_scalar_initializer(op_1);
        gold_standard->set_if_block({def_node});
        var = std::make_shared<variable>("a");
        def_node = std::make_shared<hl_definition_node>("a", c_type_int, var);

        var = std::make_shared<variable>("constant",3);
        op_1 = std::make_shared<hl_ast_operand>(var);

        def_node->set_scalar_initializer(op_1);
        gold_standard->set_else_block({def_node});


        var = std::make_shared<variable>("i");
        std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant",0);
        op_1 = std::make_shared<hl_ast_operand>(var);

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

        std::istringstream test_content(R""""(
            int main(){

                int h;
                int a;
                int j;

                for(int i = 0; i<4; ++i){
                   j = a + h;
                }

            }
        )"""");

        std::unordered_map<std::string, variable_class_t> io_spec;
        io_spec["a"] = variable_input_type;
        io_spec["h"] = variable_input_type;
        io_spec["j"] = variable_output_type;

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
        C_language_parser parser(test_content, result_def);
        parser.pre_process({});
        parser.parse(io_spec);

        std::shared_ptr<hl_ast_loop_node> result = std::static_pointer_cast<hl_ast_loop_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[3]);


        std::shared_ptr<hl_ast_loop_node> gold_standard = std::make_shared<hl_ast_loop_node>();

        // LOOP BODY
        std::shared_ptr<hl_expression_node> loop_body = std::make_shared<hl_expression_node>(expr_assign);

        std::shared_ptr<variable> var = std::make_shared<variable>("j");
        var->set_variable_class(variable_output_type);
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

        loop_body->set_lhs(op_1);
        std::shared_ptr<hl_expression_node> body_add_expr = std::make_shared<hl_expression_node>(expr_add);

        var = std::make_shared<variable>( "a");
        var->set_variable_class(variable_input_type);
        op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("h");
        var->set_variable_class(variable_input_type);
        std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

        body_add_expr->set_lhs(op_1);
        body_add_expr->set_rhs(op_2);
        loop_body->set_rhs(body_add_expr);
        gold_standard->set_loop_content({loop_body});
        // LOOP INIT CONDITION
        var = std::make_shared<variable>( "i");
        std::shared_ptr<hl_definition_node> init_def = std::make_shared<hl_definition_node>("i", c_type_int, var);

        var = std::make_shared<variable>("constant",0);
        std::shared_ptr<hl_ast_operand> def_val = std::make_shared<hl_ast_operand>(var);

        init_def->set_scalar_initializer(def_val);
        gold_standard->set_init_statement(init_def);
        // LOOP CONDITION
        std::shared_ptr<hl_expression_node> loop_cond = std::make_shared<hl_expression_node>(expr_lt);

        var = std::make_shared<variable>("i");
        op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant",4);
        op_2 = std::make_shared<hl_ast_operand>(var);

        loop_cond->set_rhs(op_2);
        loop_cond->set_lhs(op_1);
        gold_standard->set_condition(loop_cond);
        // LOOP ITERATION EXPR
        std::shared_ptr<hl_expression_node> loop_iter = std::make_shared<hl_expression_node>(expr_incr_pre);

        var = std::make_shared<variable>("i");
        op_1 = std::make_shared<hl_ast_operand>(var);

        loop_iter->set_rhs(op_1);
        gold_standard->set_iteration_expr(loop_iter);

        EXPECT_EQ(*result, *gold_standard);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << result->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << gold_standard->pretty_print()<< std::endl;
        }

    }

    TEST( cTreeVisitor, nestedLoopTest) {

        std::istringstream test_content(R""""(
        int main(){

            int h;
            int a;
            int j;

            for(int i = 0; i<4; ++i){
                j = a + h;
                for(int k = 0; k<4; ++k ){
                    j = a + h;
                }
                j = a + h;
            }

        }
        )"""");

        std::unordered_map<std::string, variable_class_t> io_spec;
        io_spec["a"] = variable_input_type;
        io_spec["h"] = variable_input_type;
        io_spec["j"] = variable_output_type;

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
        C_language_parser parser(test_content, result_def);
        parser.pre_process({});
        parser.parse(io_spec);
        std::shared_ptr<hl_ast_loop_node> result = std::static_pointer_cast<hl_ast_loop_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[3]);


        // CONTENT EXPRESSION

        std::shared_ptr<hl_expression_node> content_expr = std::make_shared<hl_expression_node>(expr_assign);

        std::shared_ptr<variable> var = std::make_shared<variable>("j");
        var->set_variable_class(variable_output_type);
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);

        content_expr->set_lhs(op_1);
        std::shared_ptr<hl_expression_node> body_add_expr = std::make_shared<hl_expression_node>(expr_add);

        var = std::make_shared<variable>( "a");
        var->set_variable_class(variable_input_type);
        op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("h");
        var->set_variable_class(variable_input_type);
        std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);

        body_add_expr->set_lhs(op_1);
        body_add_expr->set_rhs(op_2);
        content_expr->set_rhs(body_add_expr);


        // INNER LOOP
        std::shared_ptr<hl_ast_loop_node> inner_loop = std::make_shared<hl_ast_loop_node>();

        inner_loop->set_loop_content({content_expr});

        //      LOOP INIT

        var = std::make_shared<variable>( "k");
        std::shared_ptr<hl_definition_node> init_def = std::make_shared<hl_definition_node>("k", c_type_int, var);

        var = std::make_shared<variable>("constant",0);
        std::shared_ptr<hl_ast_operand> def_val = std::make_shared<hl_ast_operand>(var);

        init_def->set_scalar_initializer(def_val);
        inner_loop->set_init_statement(init_def);

        //       LOOP CONDITION

        std::shared_ptr<hl_expression_node> loop_cond = std::make_shared<hl_expression_node>(expr_lt);

        var = std::make_shared<variable>("k");
        op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant",4);
        op_2 = std::make_shared<hl_ast_operand>(var);

        loop_cond->set_rhs(op_2);
        loop_cond->set_lhs(op_1);
        inner_loop->set_condition(loop_cond);

        //       LOOP ITERATION EXPR

        std::shared_ptr<hl_expression_node> loop_iter = std::make_shared<hl_expression_node>(expr_incr_pre);

        var = std::make_shared<variable>("k");
        op_1 = std::make_shared<hl_ast_operand>(var);

        loop_iter->set_rhs(op_1);
        inner_loop->set_iteration_expr(loop_iter);

        std::shared_ptr<hl_ast_loop_node> outer_loop = std::make_shared<hl_ast_loop_node>();

        // LOOP BODY

        outer_loop->set_loop_content({content_expr, inner_loop, content_expr});

        // LOOP INIT CONDITION
        var = std::make_shared<variable>( "i");
        init_def = std::make_shared<hl_definition_node>("i", c_type_int, var);

        var = std::make_shared<variable>("constant",0);
        def_val = std::make_shared<hl_ast_operand>(var);

        init_def->set_scalar_initializer(def_val);
        outer_loop->set_init_statement(init_def);

        // LOOP CONDITION
        loop_cond = std::make_shared<hl_expression_node>(expr_lt);

        var = std::make_shared<variable>("i");
        op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant",4);
        op_2 = std::make_shared<hl_ast_operand>(var);

        loop_cond->set_rhs(op_2);
        loop_cond->set_lhs(op_1);
        outer_loop->set_condition(loop_cond);
        // LOOP ITERATION EXPR
        loop_iter = std::make_shared<hl_expression_node>(expr_incr_pre);

        var = std::make_shared<variable>("i");
        op_1 = std::make_shared<hl_ast_operand>(var);

        loop_iter->set_rhs(op_1);
        outer_loop->set_iteration_expr(loop_iter);

        EXPECT_EQ(*result, *outer_loop);
        if(Test::HasFailure()){
            std::cout << "TEST RESULT: " << result->pretty_print()<< std::endl;
            std::cout << "GOLD STANDARD: " << outer_loop->pretty_print()<< std::endl;
        }

    }

    TEST( cTreeVisitor, array_test){

        std::istringstream test_content(R""""(
        int main(){
            int array_test[5];

            int test_matrix[2][2];

            int b = array_test[0] + test_matrix[1];
        }
        )"""");

        std::unordered_map<std::string, variable_class_t> io_spec;
        io_spec["b"] = variable_output_type;

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
        C_language_parser parser(test_content, result_def);
        parser.pre_process({});
        parser.parse(io_spec);
        std::vector<std::shared_ptr<hl_ast_node>> result = std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body();

        std::vector<std::shared_ptr<hl_ast_node>> gold_standard;
        std::shared_ptr<variable> var = std::make_shared<variable>("array_test");
        var->set_type(var_type_array);
        std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("array_test", c_type_int, var);


        var = std::make_shared<variable>("constant", 5);
        std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(var);
        std::vector<int> shape = {5};
        def_1->set_array_shape(shape);
        def_1->set_array_index({op_1});
        var = std::make_shared<variable>("test_matrix");
        var->set_type(var_type_array);
        std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("test_matrix", c_type_int, var);

        var = std::make_shared<variable>("constant",2);
        op_1 = std::make_shared<hl_ast_operand>(var);

        def_2->set_array_index({op_1, op_1});
        shape = {2,2};
        def_2->set_array_shape(shape);
        var = std::make_shared<variable>( "b");
        var->set_variable_class(variable_output_type);
        std::shared_ptr<hl_definition_node> def_3 = std::make_shared<hl_definition_node>("b", c_type_int, var);

        std::shared_ptr<hl_expression_node> ex = std::make_shared<hl_expression_node>(expr_add);

        var = std::make_shared<variable>( "array_test");
        var->set_type(var_type_array);
        var->set_array_shape({5});
        op_1 = std::make_shared<hl_ast_operand>(var);

        //lhs

        var = std::make_shared<variable>("constant",0);
        std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(var);
        op_1->set_array_index({op_2});
        ex->set_lhs(op_1);
        //rhs

        var = std::make_shared<variable>( "test_matrix");
        var->set_type(var_type_array);
        var->set_array_shape({2,2});
        op_1 = std::make_shared<hl_ast_operand>(var);


        var = std::make_shared<variable>("constant", 1);
        op_2 = std::make_shared<hl_ast_operand>(var);

        op_1->set_array_index({op_2});
        ex->set_rhs(op_1);
        def_3->set_scalar_initializer(ex);

        gold_standard.push_back(def_1);
        gold_standard.push_back(def_2);
        gold_standard.push_back(def_3);

        ASSERT_TRUE(hl_ast_node::compare_vectors(result, gold_standard));

    }

    TEST( cTreeVisitor, array_init){

        std::istringstream test_content(R""""(
        int main(){
            int array_test[5] = {1,2,3,4,5};

            int test_matrix[2][2] = {{1,2}, {3,4}};

        }
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::vector<std::shared_ptr<hl_ast_node>> result = std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body();

        std::vector<std::shared_ptr<hl_ast_node>> gold_standard;


        std::vector<std::shared_ptr<hl_ast_node>> init;
        std::shared_ptr<variable> var;
        std::shared_ptr<hl_ast_operand> op;
        for(int i = 1; i<6;++i){
            var = std::make_shared<variable>("constant", i);
            op = std::make_shared<hl_ast_operand>(var);
            init.push_back(op);
        }

        var = std::make_shared<variable>("array_test");
        var->set_type(var_type_array);
        std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("array_test", c_type_int, var);
        var = std::make_shared<variable>("constant", 5);
        op = std::make_shared<hl_ast_operand>(var);
        def->set_array_index({op});

        std::vector<int> shape = {5};
        def->set_array_shape(shape);

        def->set_array_initializer(init);
        gold_standard.push_back(def);

        init.clear();

        for(int i = 1; i<5;++i){
            var = std::make_shared<variable>("constant", i);
            op = std::make_shared<hl_ast_operand>(var);
            init.push_back(op);
        }

        var = std::make_shared<variable>("test_matrix");
        var->set_type(var_type_array);
        def = std::make_shared<hl_definition_node>("test_matrix", c_type_int, var);

        def->set_array_initializer(init);

        shape = {2,2};
        def->set_array_shape(shape);

        var = std::make_shared<variable>("constant", 2);
        op = std::make_shared<hl_ast_operand>(var);
        def->set_array_index({op, op});

        gold_standard.push_back(def);

        ASSERT_TRUE(hl_ast_node::compare_vectors(result, gold_standard));

    }

    TEST( cTreeVisitor, float_const){

        std::istringstream test_content(R""""(
        void main(){
            float test = 20.47;
        }
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);

        std::shared_ptr<hl_definition_node> def = std::static_pointer_cast<hl_definition_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[0]);
        std::shared_ptr<hl_ast_operand> result = std::static_pointer_cast<hl_ast_operand>(def->get_scalar_initializer());


        std::shared_ptr<variable> var = std::make_shared<variable>("constant", 20.47f);
        std::shared_ptr<hl_ast_operand> gold_standard = std::make_shared<hl_ast_operand>(var);

        ASSERT_EQ(*result,*gold_standard);

    }

    TEST( cTreeVisitor, ternary_operation){
        std::istringstream test_content(R""""(
        int main(){
            int b = a>0 ? 100: 200;
        }
        )"""");

        std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

        C_language_parser parser(test_content, result_def);
        parser.pre_process({});

        std::unordered_map<std::string, variable_class_t> io_spec;
        parser.parse(io_spec);
        auto fun = parser.AST->get_content()[0];
        auto result = std::static_pointer_cast<hl_function_def_node>(fun)->get_body()[0];

        auto cond =  std::make_shared<hl_ast_conditional_node>();

        auto var = std::make_shared<variable>( "a");
        std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);

        auto expr = std::make_shared<hl_expression_node>(expr_gt);
        expr->set_lhs(op);

        var = std::make_shared<variable>("constant", 0);
        op = std::make_shared<hl_ast_operand>(var);
        expr->set_rhs(op);

        cond->set_condition(expr);

        var = std::make_shared<variable>("constant", 100);
        op = std::make_shared<hl_ast_operand>(var);
        cond->set_if_block({op});

        var = std::make_shared<variable>("constant", 200);
        op = std::make_shared<hl_ast_operand>(var);
        cond->set_if_block({op});
        cond->set_ternary(true);

         var = std::make_shared<variable>("b");
        auto gold_standard = std::make_shared<hl_definition_node>("b", c_type_int, var);
        gold_standard->set_scalar_initializer(cond);



        ASSERT_EQ(*result,*gold_standard);

    }

}