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
        EXPECT_EQ(msg, "Undefined variable: ba");
    }

}

