//
// Created by fils on 29/06/2021.
//

#include "frontend/C/C_language_parser.h"
#include <gtest/gtest.h>

TEST( cFrontend, preprocessor_decomment) {
    std::string input_file = "test_preproc_comments.c";
    std::ifstream ifs(input_file);

    C_language_parser parser(ifs);
    std::string result = parser.preprocessed_content;
    std::string gold_standard = "#define  TEST 15\n#define TESTT 1 \n #define TESTQ 5\n";

    ASSERT_EQ(result, gold_standard);
}

TEST( cFrontend, preprocessor_pragma) {
    std::string input_file = "test_preproc_pragmas.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result = std::make_shared<variable_map>();

    C_language_parser parser(ifs, result);

    std::shared_ptr<variable_map> gold_standard = std::make_shared<variable_map>();
    std::string type = "output";
    std::string var_name = "test";
    std::string reg = "10";
    std::shared_ptr<variable> v = std::make_shared<variable>(false, var_name);
    v->type = type == "output" ? TYPE_OUTPUT : TYPE_INPUT;
    v->set_bound_reg(std::stoul(reg));
    gold_standard->insert(var_name, v);

    ASSERT_EQ(*result->at("test"), *gold_standard->at("test"));
}