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


#ifndef FCORE_TOOLCHAIN_INVARIANTS_HPP
#define FCORE_TOOLCHAIN_INVARIANTS_HPP

#include <cstdio>
#include <cstdlib>
#include <source_location>
#include <string_view>

namespace fcore {

    /// Reports a broken internal invariant and aborts. For states that only a bug of the toolchain can produce,
    /// anything that bad user input can cause must be returned as an fcore::error instead.
    [[noreturn]] inline void invariant_violated(
            std::string_view message,
            std::source_location loc = std::source_location::current()) {
        std::fprintf(stderr,
                     "internal error: %.*s\n  at %s:%u in %s\n  this is a bug in the fCore toolchain, please report it\n",
                     static_cast<int>(message.size()), message.data(),
                     loc.file_name(), static_cast<unsigned>(loc.line()), loc.function_name());
        std::abort();
    }

    /// Aborts through invariant_violated if the condition does not hold.
    inline void ensure(
            bool condition,
            std::string_view message,
            std::source_location loc = std::source_location::current()) {
        if (!condition) [[unlikely]] invariant_violated(message, loc);
    }

}

#endif //FCORE_TOOLCHAIN_INVARIANTS_HPP
