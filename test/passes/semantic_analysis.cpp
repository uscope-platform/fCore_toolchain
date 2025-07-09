//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <fcore_cc.hpp>
#include <gtest/gtest.h>
#include "tools/variable_map.hpp"
#include "frontend/C/C_language_parser.hpp"
#include <sstream>


#include "passes/high_level/infrastructure/type_checking_engine.hpp"

#include <memory>

using namespace fcore;

TEST(semantic_analysis, simple_undefined_variable) {
    std::vector<std::string> input =  {R"(
        float add(float a, float b){
            return a+b;
        };

        void main(){
            float a = 1.0;
            float c = add(a, b);
        }
    )"};
    auto includes = std::vector<std::string>();


    auto engine = create_type_checking_engine();

    fcore_cc compiler(input, includes);
    auto [ast, globals] = compiler.get_hl_ast();

    try {
        engine.run_semantic_analysis(ast, globals);
        EXPECT_TRUE(false);
    } catch(const std::runtime_error &err) {
        std::string msg = err.what();
        EXPECT_EQ(msg, "Undefined variable: b");
    }

}

TEST(semantic_analysis, undefined_variable_in_else) {
    std::vector<std::string> input =  {R"(
        float add(float a, float b){
            return a+b;
        };

        void main(){
            float a = 1.0;
            if(a>3.0){
                float b = 5;
                float c = add(a, b);
            } else {
                float c = add(a, b);
            }
        }
    )"};

    auto includes = std::vector<std::string>();
    auto engine = create_type_checking_engine();

    fcore_cc compiler(input, includes);
    auto [ast, globals] = compiler.get_hl_ast();

    try {
        engine.run_semantic_analysis(ast, globals);
        EXPECT_TRUE(false);
    } catch(const std::runtime_error &err) {
        std::string msg = err.what();
        EXPECT_EQ(msg, "Undefined variable: b");
    }

}

TEST(semantic_analysis, for_loop_variable) {
    std::vector<std::string> input =  {R"(

        void main(){
            float a[4];
            for(int i = 0; i<5; ++i){
                a[i] = 1.0;
            }
        }
    )"};

    auto includes = std::vector<std::string>();
    auto engine = create_type_checking_engine();

    fcore_cc compiler(input, includes);
    auto [ast, globals] = compiler.get_hl_ast();

    try {
        engine.run_semantic_analysis(ast, globals);
    } catch(const std::runtime_error &err) {
        spdlog::critical("unexpected error: {}", err.what());
        EXPECT_TRUE(false);
    }

}

TEST(semantic_analysis, undefined_for_loop_variable) {
    std::vector<std::string> input =  {R"(

        void main(){
            float a[4];
            for(int i = 0; i<5; ++i){
                a[j] = 1.0;
            }
        }
    )"};

    auto includes = std::vector<std::string>();
    auto engine = create_type_checking_engine();

    fcore_cc compiler(input, includes);
    auto [ast, globals] = compiler.get_hl_ast();

    try {
        engine.run_semantic_analysis(ast, globals);
        spdlog::critical("The undefined variable j was not caught");
        EXPECT_TRUE(false);
    } catch(const std::runtime_error &err) {
        std::string msg = err.what();
        EXPECT_EQ(msg, "Undefined variable: j");
    }

}

TEST(semantic_analysis, undefined_variable_in_expression) {
    std::vector<std::string> input =  {R"(

        void main(){
            float a = 3.0;
            float b = 2.0;

            float c = a + ba;
        }
    )"};

    auto includes = std::vector<std::string>();
    auto engine = create_type_checking_engine();

    fcore_cc compiler(input, includes);
    auto [ast, globals] = compiler.get_hl_ast();

    try {
        engine.run_semantic_analysis(ast, globals);
        spdlog::critical("The undefined variable ba was not caught");
        EXPECT_TRUE(false);
    } catch(const std::runtime_error &err) {
        std::string msg = err.what();
        EXPECT_EQ(msg, "Undefined variable: ba");
    }

}


TEST(semantic_analysis, type_propagation) {
    std::vector<std::string> input =  {R"(
        float add(int a, float b){
            return itf(a) + b;
        }
        void main(){
            int a = 0;
            int b;
            if(2>3){
                float a = 21.0;
                float b;
                b = a + 24.0;
            } else {
                long a = 11;
                long b;
                b = a + 5;
            }
             b = a + 3;
        }
    )"};

    auto includes = std::vector<std::string>();
    auto engine = create_type_checking_engine();

    fcore_cc compiler(input, includes);
    auto [ast, globals] = compiler.get_hl_ast();


    engine.run_semantic_analysis(ast, globals);


    auto fcn = std::static_pointer_cast<ast_function_def>(ast->get_content()[0]);


    auto call = std::static_pointer_cast<ast_call>(
    std::static_pointer_cast<ast_expression>(fcn->get_return())->get_lhs().value());
    auto op = std::static_pointer_cast<ast_operand>(call->get_arguments()[0]);
    EXPECT_EQ(op->get_c_type(), c_type_int);

    op = std::static_pointer_cast<ast_operand>(
    std::static_pointer_cast<ast_expression>(fcn->get_return())->get_rhs());

    EXPECT_EQ(op->get_c_type(), c_type_float);

    fcn = std::static_pointer_cast<ast_function_def>(ast->get_content()[1]);

    auto conditional = std::static_pointer_cast<ast_conditional>(fcn->get_body()[2]);
    op= std::static_pointer_cast<ast_operand>(
            std::static_pointer_cast<ast_expression>(conditional->get_if_block()[2]
        )->get_lhs().value()
    );
    EXPECT_EQ(op->get_c_type(), c_type_float);

    op = std::static_pointer_cast<ast_operand>(
            std::static_pointer_cast<ast_expression>(conditional->get_else_block()[2]
        )->get_lhs().value()
    );
    EXPECT_EQ(op->get_c_type(), c_type_long);

    op = std::static_pointer_cast<ast_operand>(std::static_pointer_cast<ast_expression>(fcn->get_body()[3])->get_lhs().value());
    EXPECT_EQ(op->get_c_type(), c_type_int);


    int i = 0;
}

TEST(semantic_analysis, mixed_type_operation_warning) {
    std::vector<std::string> input =  {R"(

        void main(){
            float a;

            float c = a*3;
        }
    )"};

    auto includes = std::vector<std::string>();
    auto engine = create_type_checking_engine();

    fcore_cc compiler(input, includes);
    auto [ast, globals] = compiler.get_hl_ast();

    try {
        engine.run_semantic_analysis(ast, globals);
        spdlog::critical("The undefined variable ba was not caught");
        EXPECT_TRUE(false);
    } catch(const std::runtime_error &err) {
        std::string msg = err.what();
        EXPECT_EQ(msg, "Encountered expression with mixed types: a is float and constant is int");
    }

}



TEST(semantic_analysis, wrong_argument_for_builtin) {
    std::vector<std::string> input =  {R"(

        void main(){
            float c = itf(14);
        }
    )"};

    auto includes = std::vector<std::string>();
    auto engine = create_type_checking_engine();

    fcore_cc compiler(input, includes);
    auto [ast, globals] = compiler.get_hl_ast();

    try {
        engine.run_semantic_analysis(ast, globals);
        spdlog::critical("The undefined variable ba was not caught");
        EXPECT_TRUE(false);
    } catch(const std::runtime_error &err) {
        std::string msg = err.what();
        EXPECT_EQ(msg, "Argument #0 of a call to itf is of the wrong type");
    }

}


TEST(semantic_analysis, multiple_definitions) {
    std::vector<std::string> input =  {R"(

            void main(){
                float mem, out;

                mem += 1.0;
                out = mem*2;
            }
    )"};

    auto includes = std::vector<std::string>();
    auto engine = create_type_checking_engine();

    fcore_cc compiler(input, includes);
    auto [ast, globals] = compiler.get_hl_ast();


    try {
        engine.run_semantic_analysis(ast, globals);
        spdlog::critical("Mixed type operation not caught");
        EXPECT_TRUE(false);
    } catch(const std::runtime_error &err) {
        std::string msg = err.what();
        EXPECT_EQ(msg, "Encountered expression with mixed types: mem is float and constant is int");
    }

}
