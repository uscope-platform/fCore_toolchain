//
// Created by fils on 29/06/2021.
//

#include "frontend/C/C_language_parser.h"
#include <gtest/gtest.h>

TEST( cFrontend, preprocessor_decomment) {
    std::string input_file = "test_preproc.c";
    std::ifstream ifs(input_file);

    C_language_parser parser(ifs);
    std::string result = parser.preprocessed_content;
    std::string gold_standard = "#define  TEST 15\n#define TESTT 1 \n #define TESTQ 5\n";

    ASSERT_EQ(result, gold_standard);
}