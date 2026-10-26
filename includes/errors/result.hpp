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

    // ---- transitional bridges between exceptions and results -----------------------------------
    // Removed once the last throw is gone, they let migrated and unmigrated code coexist.

    /// Exception carrying a full error, derives from runtime_error so existing catch blocks keep working.
    class error_exception : public std::runtime_error {
    public:
        explicit error_exception(error e) : std::runtime_error(e.what()), err(std::move(e)) {}
        [[nodiscard]] const error &get() const { return err; }
    private:
        error err;
    };

    /// result -> exception, for migrated callees called from not yet migrated callers.
    template<typename T>
    T value_or_throw(result<T> &&r) {
        if (!r) throw error_exception(std::move(r).error());
        if constexpr (!std::is_void_v<T>) return std::move(r).value();
    }

    /// exception -> result, for not yet migrated callees called from migrated callers.
    template<typename F>
    auto catching(F &&f) -> result<std::invoke_result_t<F>> {
        try {
            if constexpr (std::is_void_v<std::invoke_result_t<F>>) {
                std::forward<F>(f)();
                return {};
            } else {
                return std::forward<F>(f)();
            }
        } catch (const error_exception &e) {
            return std::unexpected<error>(e.get());
        } catch (const std::invalid_argument &e) {
            return fail(error_code::invalid_argument, e.what());
        } catch (const std::exception &e) {
            return fail(error_code::unknown, e.what());
        }
    }

}

#endif //FCORE_TOOLCHAIN_RESULT_HPP
