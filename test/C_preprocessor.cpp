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
// limitations under the License.29/06/2021.
//

#include "frontend/C/C_language_parser.hpp"
#include <gtest/gtest.h>

#include <stdexcept>

using namespace fcore;


TEST( cFrontend, preprocessor_define) {

    std::istringstream test_content(R""""(
        #define TEST 15


        int main(){
            int a = TEST;
        }
    )"""");

    std::unordered_map<std::string, variable_class_t> io_spec;
    io_spec["a"] = {variable_input_type, false};

    auto dmap = std::make_shared<define_map>();
    C_language_parser parser(test_content, dmap);
    parser.pre_process({});

    parser.parse(io_spec);

    std::shared_ptr<ast_definition> result = std::static_pointer_cast<ast_definition>(std::static_pointer_cast<ast_function_def>(parser.AST->get_content()[0])->get_body()[0]);

    std::shared_ptr<variable> var = std::make_shared<variable>("a");
    var->set_variable_class({variable_input_type, false});
    std::shared_ptr<ast_definition> gold_standard = std::make_shared<ast_definition>("a", c_type_int, var);
    var = std::make_shared<variable>("constant", 15);
    std::shared_ptr<ast_operand> op = std::make_shared<ast_operand>(var);
    gold_standard->set_scalar_initializer(op);

    ASSERT_EQ(*result, *gold_standard);
}

TEST( cFrontend, preprocessor_include) {
    std::string input_file = "c_prep/test_include.c";

    std::unordered_map<std::string, variable_class_t> io_spec;
    io_spec["a"] = {variable_input_type, false};

    auto dmap = std::make_shared<define_map>();
    C_language_parser parser(input_file, dmap);
    parser.pre_process({});
    parser.parse(io_spec);

    std::shared_ptr<ast_definition> result = std::static_pointer_cast<ast_definition>(std::static_pointer_cast<ast_function_def>(parser.AST->get_content()[0])->get_body()[0]);

    std::shared_ptr<variable> var = std::make_shared<variable>("a");
    var->set_variable_class({variable_input_type, false});
    std::shared_ptr<ast_definition> gold_standard = std::make_shared<ast_definition>("a", c_type_int, var);
    var = std::make_shared<variable>("constant", 42);
    std::shared_ptr<ast_operand> op = std::make_shared<ast_operand>(var);
    gold_standard->set_scalar_initializer(op);


    EXPECT_EQ(*gold_standard, *result);
}

TEST( cFrontend, preprocessor_include_fail) {
    std::string input_file = "c_prep/test_include_fail.c";

    auto dmap = std::make_shared<define_map>();
    C_language_parser parser(input_file, dmap);
    EXPECT_THROW(parser.pre_process({}), std::runtime_error);

}
