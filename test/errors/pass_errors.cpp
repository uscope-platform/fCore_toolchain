// Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#include "fcore_cc.hpp"
#include "passes/high_level/infrastructure/hl_passes.hpp"
#include "passes/high_level/infrastructure/type_checking_engine.hpp"

using namespace fcore;

TEST(pass_errors, enabling_unknown_pass_fails) {
    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep);
    auto r = manager.enable_pass("There is no such pass");
    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, error_code::invalid_argument);
}

TEST(pass_errors, failing_pass_reports_code_and_pass_chain) {
    std::vector<std::string> input = {R"(
        void main(){
            float a = 1.0;
            float b = missing(a);
        }
    )"};
    std::vector<std::string> includes;

    fcore_cc compiler(input, includes);
    auto compilation = compiler.compile(1);
    ASSERT_FALSE(compilation);

    const auto &err = compilation.error();
    EXPECT_EQ(err.code, error_code::undefined_variable);
    EXPECT_EQ(err.message, "Function missing is not defined");
    ASSERT_FALSE(err.context.empty());
    EXPECT_NE(err.context.front().find("function inlining pass"), std::string::npos);
}

TEST(pass_errors, failed_pass_does_not_poison_the_next_run) {
    std::vector<std::string> bad_input = {"void main(){ float a = missing + 1.0; }"};
    std::vector<std::string> good_input = {"void main(){ float a = 1.0; float b = a + 2.0; }"};
    std::vector<std::string> includes;

    fcore_cc bad_compiler(bad_input, includes);
    auto bad_parsed = bad_compiler.get_hl_ast();
    ASSERT_TRUE(bad_parsed);
    auto [bad_ast, bad_globals] = bad_parsed.value();

    fcore_cc good_compiler(good_input, includes);
    auto good_parsed = good_compiler.get_hl_ast();
    ASSERT_TRUE(good_parsed);
    auto [good_ast, good_globals] = good_parsed.value();

    // the same engine, hence the same pass objects, runs a failing and then a passing program
    auto engine = create_type_checking_engine();
    EXPECT_FALSE(engine.run_semantic_analysis(bad_ast, bad_globals));
    EXPECT_TRUE(engine.run_semantic_analysis(good_ast, good_globals));
}
