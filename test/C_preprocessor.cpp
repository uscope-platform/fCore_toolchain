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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.29/06/2021.
//

#include "frontend/C/C_language_parser.hpp"
#include <gtest/gtest.h>

#include <stdexcept>

TEST( cFrontend, preprocessor_decomment) {
    std::string input_file = "test_preproc_comments.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs,result_def);
    parser.pre_process({}, {});

    define def_1(0, "TEST", "15");
    define def_2(0, "TESTT", "1 ");
    define def_3(0, "TESTQ", "5");
    define res_1 = *result_def->at("TEST");
    define res_2 = *result_def->at("TESTT");
    define res_3 = *result_def->at("TESTQ");


    ASSERT_EQ(def_1, res_1);
    ASSERT_EQ(def_2, res_2);
    ASSERT_EQ(def_3, res_3);
}

TEST( cFrontend, preprocessor_pragma) {
    std::string input_file = "test_preproc_pragmas.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_def);
    parser.pre_process({}, {});
    std::unordered_map<std::string, std::shared_ptr<variable>> iom_map = parser.preproc->get_iom_map();

    std::shared_ptr<variable_map> gold_standard = std::make_shared<variable_map>();

    std::shared_ptr<variable> v = std::make_shared<variable>( "test");

    v->set_variable_class(variable_output_type);
    v->set_bound_reg(10);

    ASSERT_EQ(*iom_map["test"], *v);
    v = std::make_shared<variable>( "test_array");
    v->set_variable_class(variable_output_type);
    v->set_bound_reg_array({10, 15, 27});
    ASSERT_EQ(*iom_map["test_array"], *v);
}

TEST( cFrontend, preprocessor_define) {
    std::string input_file = "test_preproc_define.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs,result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::shared_ptr<hl_definition_node> result = std::static_pointer_cast<hl_definition_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[0]);

    std::shared_ptr<variable> var = std::make_shared<variable>("a");
    var->set_bound_reg(19);
    var->set_variable_class(variable_input_type);
    std::shared_ptr<hl_definition_node> gold_standard = std::make_shared<hl_definition_node>("a", c_type_int, var);
    var = std::make_shared<variable>("constant", 15);
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
    gold_standard->set_scalar_initializer(op);

    ASSERT_EQ(*result, *gold_standard);
}

TEST( cFrontend, preprocessor_include) {
    std::string input_file = "test_preproc_include.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();


    C_language_parser parser(ifs,result_def);
    parser.pre_process({}, {"include_test.h"});
    parser.parse();

    std::shared_ptr<hl_definition_node> result = std::static_pointer_cast<hl_definition_node>(std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0])->get_body()[0]);

    std::shared_ptr<variable> var = std::make_shared<variable>("a");
    var->set_bound_reg(19);
    var->set_variable_class(variable_input_type);
    std::shared_ptr<hl_definition_node> gold_standard = std::make_shared<hl_definition_node>("a", c_type_int, var);
    var = std::make_shared<variable>("constant", 42);
    std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);
    gold_standard->set_scalar_initializer(op);


    EXPECT_EQ(*gold_standard, *result);
}

TEST( cFrontend, preprocessor_include_fail) {
    std::string input_file = "test_preproc_include_fail.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
    C_language_parser parser(ifs,result_def);
    EXPECT_THROW(parser.pre_process({}, {}), std::runtime_error);

}
