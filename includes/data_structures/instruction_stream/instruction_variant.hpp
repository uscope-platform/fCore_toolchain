

//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_INSTRUCTION_VARIANT_HPP
#define FCORE_TOOLCHAIN_INSTRUCTION_VARIANT_HPP

#include <vector>
#include <variant>

#include "conversion_instruction.hpp"
#include "independent_instruction.hpp"
#include "load_constant_instruction.hpp"
#include "pseudo_instruction.hpp"
#include "register_instruction.hpp"
#include "ternary_instruction.hpp"


namespace fcore{
    class instruction_variant {
    public:
        explicit instruction_variant(const independent_instruction &t): content(t){};
        explicit instruction_variant(const load_constant_instruction &t): content(t){};
        explicit instruction_variant(const conversion_instruction &t): content(t){};
        explicit instruction_variant(const pseudo_instruction &t): content(t){};
        explicit instruction_variant(const register_instruction &t): content(t){};
        explicit instruction_variant(const ternary_instruction &t): content(t){};
        instruction_variant(const instruction_variant& other) = default;
        instruction_variant(instruction_variant&& other) noexcept = default;
        instruction_variant& operator=(const instruction_variant& other) = default;
        instruction_variant& operator=(instruction_variant&& other) noexcept = default;

        friend bool operator==(const instruction_variant& lhs, const instruction_variant& rhs){
            return lhs.content == rhs.content;
        };

        [[nodiscard]] bool is_pseudo() const { return std::holds_alternative<pseudo_instruction>(content);};


        std::vector<uint32_t> emit()const;
        std::string to_string()const;
        void print() const;
        std::string disassemble()const;
        int instruction_count()const;


        std::vector<std::shared_ptr<variable>> get_arguments();
        std::vector<std::shared_ptr<variable>> get_arguments() const;

        opcode_table_t get_opcode();

        std::variant<
                conversion_instruction,
                independent_instruction,
                load_constant_instruction,
                pseudo_instruction,
                register_instruction,
                ternary_instruction
        > get_content() const {return content;};

    private:
        std::variant<
                conversion_instruction,
                independent_instruction,
                load_constant_instruction,
                pseudo_instruction,
                register_instruction,
                ternary_instruction
        > content;
    };

}


#endif //FCORE_TOOLCHAIN_INSTRUCTION_VARIANT_HPP
