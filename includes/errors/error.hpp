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

#ifndef FCORE_TOOLCHAIN_ERROR_HPP
#define FCORE_TOOLCHAIN_ERROR_HPP

#include <cstdint>
#include <optional>
#include <source_location>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace fcore {

    /// Machine readable error category. Tests and tools should match on this instead of on the message text.
    enum class error_code : uint16_t {
        unknown = 0,

        // generic
        io_error,               ///< a file could not be opened, read or written
        invalid_argument,       ///< a caller supplied value is out of range or malformed
        not_supported,          ///< the requested feature/version is not supported
        internal_error,         ///< a toolchain bug, something that should have been impossible

        // frontend
        parse_error,            ///< lexer/parser failure in the C or assembly frontends
        preprocessor_error,     ///< #include/#define related failure
        schema_validation,      ///< json spec does not conform to the schema
        binary_format_error,    ///< malformed binary program

        // compiler passes
        semantic_error,         ///< generic semantic analysis failure
        undefined_variable,
        type_error,             ///< type checking failure, mixed type operations
        lowering_error,         ///< failure lowering the HL AST (inlining, unrolling, mangling...)
        register_allocation,
        pipeline_hazard,        ///< failure inserting stalls/deconflicting results

        // emulator
        spec_error,             ///< emulator/compiler spec is semantically invalid (not just schema invalid)
        bus_allocation,         ///< interconnect/bus allocation failure
        emulation_error,        ///< failure while running a program
    };

    constexpr std::string_view to_string(error_code c) {
        switch (c) {
            case error_code::unknown:              return "unknown";
            case error_code::io_error:             return "io_error";
            case error_code::invalid_argument:     return "invalid_argument";
            case error_code::not_supported:        return "not_supported";
            case error_code::internal_error:       return "internal_error";
            case error_code::parse_error:          return "parse_error";
            case error_code::preprocessor_error:   return "preprocessor_error";
            case error_code::schema_validation:    return "schema_validation";
            case error_code::binary_format_error:  return "binary_format_error";
            case error_code::semantic_error:       return "semantic_error";
            case error_code::undefined_variable:   return "undefined_variable";
            case error_code::type_error:           return "type_error";
            case error_code::lowering_error:       return "lowering_error";
            case error_code::register_allocation:  return "register_allocation";
            case error_code::pipeline_hazard:      return "pipeline_hazard";
            case error_code::spec_error:           return "spec_error";
            case error_code::bus_allocation:       return "bus_allocation";
            case error_code::emulation_error:      return "emulation_error";
        }
        return "unknown";
    }

    /// Position inside a user supplied input (C source, assembly, json spec...)
    struct source_position {
        std::string file;       ///< may be empty if the input is not a file
        uint32_t line = 0;      ///< 1 based, 0 if unknown
        uint32_t column = 0;    ///< 0 if unknown
    };

    struct error {
        error_code code = error_code::unknown;
        std::string message;
        std::optional<source_position> position;    ///< where in the user input the problem is
        std::vector<std::string> context;           ///< innermost first, e.g. "while running pass X"
        std::source_location raised_at;             ///< where in the toolchain the error was created, for debugging

        error() = default;

        error(error_code c, std::string msg,
              std::source_location loc = std::source_location::current())
            : code(c), message(std::move(msg)), raised_at(loc) {}

        error &at(source_position p) & { position = std::move(p); return *this; }
        error &&at(source_position p) && { position = std::move(p); return std::move(*this); }
        error &at(uint32_t line, uint32_t column = 0, std::string file = {}) & {
            position = source_position{std::move(file), line, column};
            return *this;
        }
        error &&at(uint32_t line, uint32_t column = 0, std::string file = {}) && {
            position = source_position{std::move(file), line, column};
            return std::move(*this);
        }

        /// Records what was going on when the error was propagated through a layer.
        error &with_context(std::string ctx) & { context.push_back(std::move(ctx)); return *this; }
        error &&with_context(std::string ctx) && { context.push_back(std::move(ctx)); return std::move(*this); }

        /// Human readable message: "[file:line:col] message (while ctx1, ctx2)". Does not include the code or raise location.
        [[nodiscard]] std::string what() const {
            std::string out;
            if (position && (position->line != 0 || !position->file.empty())) {
                out += "[";
                if (!position->file.empty()) out += position->file;
                if (position->line != 0) {
                    if (!position->file.empty()) out += ":";
                    out += std::to_string(position->line);
                    if (position->column != 0) out += ":" + std::to_string(position->column);
                }
                out += "] ";
            }
            out += message;
            for (const auto &c: context) out += "\n  while " + c;
            return out;
        }

        /// Like what() but prefixed with the code and suffixed with the raise location, for logs.
        [[nodiscard]] std::string verbose() const {
            std::string out = "(" + std::string(to_string(code)) + ") " + what();
            out += "\n  raised at " + std::string(raised_at.file_name()) + ":" + std::to_string(raised_at.line());
            return out;
        }
    };

}

#endif //FCORE_TOOLCHAIN_ERROR_HPP
