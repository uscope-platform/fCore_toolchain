// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.29/06/2021.
//

#include "frontend/C/C_language_parser.hpp"
#include <gtest/gtest.h>

#include <stdexcept>

TEST( cFrontend, preprocessor_decomment) {
    std::string input_file = "test_preproc_comments.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var,result_def);
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

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});

    std::shared_ptr<variable_map> gold_standard = std::make_shared<variable_map>();
    std::string type = "output";
    std::string var_name = "test";
    std::string reg = "10";
    std::shared_ptr<variable> v = std::make_shared<variable>(false, var_name);
    v->type = type == "output" ? TYPE_OUTPUT : TYPE_INPUT;
    v->set_bound_reg(std::stoul(reg));
    gold_standard->insert(var_name, v);

    ASSERT_EQ(*result_var->at("test"), *gold_standard->at("test"));
}

TEST( cFrontend, preprocessor_define) {
    std::string input_file = "test_preproc_define.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var,result_def);
    parser.pre_process({}, {});

    std::shared_ptr<define_map> gold_standard = std::make_shared<define_map>();
    std::shared_ptr<define> def_1 = std::make_shared<define>(0, "TEST", "15");
    std::shared_ptr<define> def_2 = std::make_shared<define>(0, "TEST2", "function(12,15)");
    gold_standard->insert("TEST", def_1);
    gold_standard->insert("TEST2", def_2);

    ASSERT_EQ(*result_def->at("TEST"), *gold_standard->at("TEST"));
    ASSERT_EQ(*result_def->at("TEST2"), *gold_standard->at("TEST2"));
}

TEST( cFrontend, preprocessor_include) {
    std::string input_file = "test_preproc_include.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();


    C_language_parser parser(ifs, result_var,result_def);
    parser.pre_process({}, {"include_test.h"});
    std::string result = parser.preproc->get_preprocessed_file();
    std::string gold_standard = "#define TEST\n#define test_include 42\n\n";
    EXPECT_EQ(gold_standard, result);
}

TEST( cFrontend, preprocessor_include_fail) {
    std::string input_file = "test_preproc_include_fail.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();
    C_language_parser parser(ifs, result_var,result_def);
    EXPECT_THROW(parser.pre_process({}, {}), std::runtime_error);

}
