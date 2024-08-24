

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
#include "intercalated_constant.hpp"
#include "load_constant_instruction.hpp"
#include "pseudo_instruction.hpp"
#include "register_instruction.hpp"
#include "ternary_instruction.hpp"


namespace fcore{
    class instruction_variant {
    public:

    private:

        std::vector<std::variant<
            conversion_instruction,
            independent_instruction,
            intercalated_constant,
            load_constant_instruction,
            pseudo_instruction,
            register_instruction,
            ternary_instruction
        >> content;
    };

}


#endif //FCORE_TOOLCHAIN_INSTRUCTION_VARIANT_HPP
