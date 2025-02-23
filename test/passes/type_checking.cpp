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


#include "passes/semantic_analysis/infrastructure/type_checking_engine.hpp"

#include <memory>

using namespace fcore;

TEST(type_checking, wrong_call_arguments) {
    std::vector<std::string> input =  {R"(
        float add(float a, float b){
            return a+b;
        };

        void main(){
            float a = 1.0;
            int b_int = 2;
            float c = add(a, b_int);
        }
    )"};
    auto includes = std::vector<std::string>();
    fcore_cc compiler(input, includes);
    auto ast = compiler.get_hl_ast();
    auto engine = create_type_checking_engine();
    engine.check(ast);
    EXPECT_TRUE(false);
}

