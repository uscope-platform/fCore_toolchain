// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
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


#include "data_structures/instruction_stream/ll_instruction_node.hpp"

#include "data_structures/instruction_stream/register_instruction.hpp"
#include "data_structures/instruction_stream/conversion_instruction.hpp"
#include "data_structures/instruction_stream/independent_instruction.hpp"
#include "data_structures/instruction_stream/load_constant_instruction.hpp"
#include "data_structures/instruction_stream/pseudo_instruction.hpp"
#include "data_structures/instruction_stream/intercalated_constant.hpp"


namespace fcore{

    instruction::instruction(isa_instruction_type t)  {
        instruction_type = t;
    }

    instruction::instruction(const instruction &old_obj) {

        instruction_type = old_obj.instruction_type;
    }

    isa_instruction_type instruction::get_type() {
        return instruction_type;
    }

    bool instruction::is_terminal() {
        return true;
    }

    bool
    instruction::compare_content_by_type(const std::shared_ptr<instruction> &lhs, const std::shared_ptr<instruction> &rhs) {
        if(lhs->get_type() != rhs->get_type()) return false;

        switch (lhs->instruction_type) {
            case isa_register_instruction:
                return *std::static_pointer_cast<register_instruction>(lhs) == *std::static_pointer_cast<register_instruction>(rhs);
            case isa_independent_instruction:
                return *std::static_pointer_cast<independent_instruction>(lhs) == *std::static_pointer_cast<independent_instruction>(rhs);
            case isa_pseudo_instruction:
                return *std::static_pointer_cast<pseudo_instruction>(lhs) == *std::static_pointer_cast<pseudo_instruction>(rhs);
            case isa_conversion_instruction:
                return *std::static_pointer_cast<conversion_instruction>(lhs) == *std::static_pointer_cast<conversion_instruction>(rhs);
            case isa_load_constant_instruction:
                return *std::static_pointer_cast<load_constant_instruction>(lhs) == *std::static_pointer_cast<load_constant_instruction>(rhs);
            case isa_intercalated_constant:
                return *std::static_pointer_cast<intercalated_constant>(lhs) == *std::static_pointer_cast<intercalated_constant>(rhs);
        }
        return false;
    }

    nlohmann::json instruction::dump() {
        nlohmann::json retval;
        retval["instruction_type"] = isa_instr_type_to_string(instruction_type);
        return retval;
    }

    nlohmann::json instruction::dump_instruction_by_type(const std::shared_ptr<instruction> &node) {
        switch (node->get_type()) {
            case isa_independent_instruction: return std::static_pointer_cast<independent_instruction>(node)->dump();
            case isa_register_instruction: return std::static_pointer_cast<register_instruction>(node)->dump();
            case isa_pseudo_instruction: return std::static_pointer_cast<pseudo_instruction>(node)->dump();
            case isa_conversion_instruction: return std::static_pointer_cast<conversion_instruction>(node)->dump();
            case isa_load_constant_instruction: return std::static_pointer_cast<load_constant_instruction>(node)->dump();
            case isa_intercalated_constant: return std::static_pointer_cast<intercalated_constant>(node)->dump();
            default:
                throw std::runtime_error("Unknown instruction node type has been dumped");
        }
    }

}

