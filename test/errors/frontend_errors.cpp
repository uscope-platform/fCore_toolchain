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
#include <sstream>

#include "frontend/C/C_language_parser.hpp"
#include "frontend/asm/asm_language_parser.hpp"
#include "frontend/binary_loader.hpp"

using namespace fcore;

namespace {
    result<void> parse_c(const std::string &code) {
        std::istringstream content(code);
        C_language_parser parser(content, std::make_shared<define_map>());
        if (auto processed = parser.pre_process({}); !processed) return processed;
        return parser.parse({});
    }
}

TEST(frontend_errors, c_syntax_error_has_code_and_position) {
    auto r = parse_c("int main() {\n  int a = ;\n}\n");
    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, error_code::parse_error);
    ASSERT_TRUE(r.error().position.has_value());
    EXPECT_EQ(r.error().position->line, 2u);
}

TEST(frontend_errors, c_unsupported_construct_stops_the_walk) {
    auto r = parse_c("float main() {\n  float a = \"text\";\n  return a;\n}\n");
    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, error_code::not_supported);
    ASSERT_TRUE(r.error().position.has_value());
    EXPECT_EQ(r.error().position->line, 2u);
}

TEST(frontend_errors, c_valid_program_parses) {
    EXPECT_TRUE(parse_c("float main() {\n  float a = 1.0;\n  return a;\n}\n"));
}

TEST(frontend_errors, asm_syntax_error) {
    std::istringstream content("this is not assembly @@@\n");
    asm_language_parser parser;
    auto r = parser.parse(content);
    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, error_code::parse_error);
}

TEST(frontend_errors, binary_loader_rejects_empty_program) {
    binary_loader loader;
    auto r = loader.load_program({});
    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, error_code::binary_format_error);
}

TEST(frontend_errors, binary_loader_rejects_malformed_mem_file) {
    std::istringstream content("00000001\nnot_hex\n");
    binary_loader loader;
    auto r = loader.load_stream(content, bin_loader_mem_input);
    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, error_code::binary_format_error);
    ASSERT_TRUE(r.error().position.has_value());
    EXPECT_EQ(r.error().position->line, 2u);
}
