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


    nlohmann::json instruction::dump() {
        nlohmann::json retval;
        retval["instruction_type"] = isa_instr_type_to_string(instruction_type);
        return retval;
    }

}

