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


#ifndef FCORE_TOOLCHAIN_TEST_RESULT_HELPERS_HPP
#define FCORE_TOOLCHAIN_TEST_RESULT_HELPERS_HPP

#include <gtest/gtest.h>
#include <utility>

#include "errors/result.hpp"

/// The value of a result that is expected to succeed. A failure is reported as a test failure, with the error text,
/// and a default constructed value is returned so that the rest of the test can still run.
template<typename T>
T expect_value(fcore::result<T> &&outcome) {
    if(outcome) return std::move(outcome).value();
    ADD_FAILURE() << outcome.error().what();
    return T{};
}

#endif //FCORE_TOOLCHAIN_TEST_RESULT_HELPERS_HPP
