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

#include "errors/result.hpp"

using namespace fcore;

namespace {
    result<int> parse_positive(int v) {
        if (v <= 0) return fail(error_code::invalid_argument, "value must be positive");
        return v;
    }
}

TEST(error, fields_and_formatting) {
    error e(error_code::parse_error, "unexpected token");
    e.at(12, 4, "main.c").with_context("parsing main.c");

    EXPECT_EQ(e.code, error_code::parse_error);
    EXPECT_EQ(e.what(), "[main.c:12:4] unexpected token\n  while parsing main.c");
    EXPECT_NE(e.verbose().find("(parse_error)"), std::string::npos);
    EXPECT_NE(e.verbose().find("error.cpp"), std::string::npos);
}

TEST(error, no_position) {
    error e(error_code::io_error, "cannot open file");
    EXPECT_EQ(e.what(), "cannot open file");
}

TEST(error, line_only_position) {
    error e(error_code::semantic_error, "bad");
    e.at(3);
    EXPECT_EQ(e.what(), "[3] bad");
}

TEST(result, fail_builds_error) {
    auto r = parse_positive(0);
    ASSERT_FALSE(r);
    EXPECT_EQ(r.error().code, error_code::invalid_argument);
    EXPECT_EQ(r.error().message, "value must be positive");
}

TEST(result, with_context_only_touches_failures) {
    auto bad = with_context(parse_positive(-1), "reading config");
    ASSERT_FALSE(bad);
    ASSERT_EQ(bad.error().context.size(), 1u);
    EXPECT_EQ(bad.error().context[0], "reading config");

    auto good = with_context(parse_positive(1), "reading config");
    EXPECT_TRUE(good);
}

TEST(result, bridge_result_to_exception) {
    EXPECT_EQ(value_or_throw(parse_positive(3)), 3);
    EXPECT_THROW(value_or_throw(parse_positive(-3)), std::runtime_error);
    try {
        value_or_throw(parse_positive(-3));
        FAIL();
    } catch (const error_exception &e) {
        EXPECT_EQ(e.get().code, error_code::invalid_argument);
    }
}

TEST(result, bridge_exception_to_result) {
    auto ok = catching([] { return 5; });
    ASSERT_TRUE(ok);
    EXPECT_EQ(*ok, 5);

    auto void_ok = catching([] {});
    EXPECT_TRUE(void_ok);

    auto bad = catching([]() -> int { throw std::runtime_error("boom"); });
    ASSERT_FALSE(bad);
    EXPECT_EQ(bad.error().message, "boom");

    auto inv = catching([]() -> int { throw std::invalid_argument("bad arg"); });
    EXPECT_EQ(inv.error().code, error_code::invalid_argument);

    // an error that went through value_or_throw keeps its code
    auto round_trip = catching([] { return value_or_throw(parse_positive(-1)); });
    ASSERT_FALSE(round_trip);
    EXPECT_EQ(round_trip.error().code, error_code::invalid_argument);
}
