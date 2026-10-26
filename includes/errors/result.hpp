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

#ifndef FCORE_TOOLCHAIN_RESULT_HPP
#define FCORE_TOOLCHAIN_RESULT_HPP

#include <exception>
#include <expected>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "errors/error.hpp"

namespace fcore {

    template<typename T>
    using result = std::expected<T, error>;

    /// Builds the failure side of a result: `return fail(error_code::parse_error, "unexpected token");`
    [[nodiscard]] inline std::unexpected<error> fail(
            error_code c, std::string msg,
            std::source_location loc = std::source_location::current()) {
        return std::unexpected<error>(error(c, std::move(msg), loc));
    }

    /// Failure from an already built error, to be used when the position/context were attached first.
    [[nodiscard]] inline std::unexpected<error> fail(error e) {
        return std::unexpected<error>(std::move(e));
    }

    /// Adds context to the error of a failed result, leaves successes untouched.
    template<typename T>
    result<T> with_context(result<T> r, std::string ctx) {
        if (!r) r.error().with_context(std::move(ctx));
        return r;
    }

    // ---- boundary with code that throws ---------------------------------------------------------
    // The toolchain does not throw. The standard library and the third party libraries still do (std::stoi on a
    // literal that does not fit, nlohmann::json on a value of the wrong type, failed allocations...), catching() is the
    // place where those are turned into errors, at the entry points that can meet them.

    template<typename T>
    inline constexpr bool is_result_v = false;
    template<typename T>
    inline constexpr bool is_result_v<result<T>> = true;

    namespace detail {
        /// Translates the exception being handled into a failure, to be called from inside a catch block.
        inline std::unexpected<error> from_current_exception() {
            try {
                throw;
            } catch (const std::invalid_argument &e) {
                return fail(error_code::invalid_argument, e.what());
            } catch (const std::exception &e) {
                return fail(error_code::unknown, e.what());
            } catch (...) {
                return fail(error_code::unknown, "unknown exception");
            }
        }
    }

    /// Runs a callable that may throw an exception of the standard or of a third party library and returns its outcome.
    template<typename F>
    auto catching(F &&f) -> result<std::invoke_result_t<F>> {
        try {
            if constexpr (std::is_void_v<std::invoke_result_t<F>>) {
                std::forward<F>(f)();
                return {};
            } else {
                return std::forward<F>(f)();
            }
        } catch (...) {
            return detail::from_current_exception();
        }
    }

    /// Same for callables that already return a result, which is handed back as it is instead of being nested.
    template<typename F>
        requires is_result_v<std::invoke_result_t<F>>
    auto catching(F &&f) -> std::invoke_result_t<F> {
        try {
            return std::forward<F>(f)();
        } catch (...) {
            return detail::from_current_exception();
        }
    }

}

#endif //FCORE_TOOLCHAIN_RESULT_HPP
