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

#include "data_structures/instruction_stream/pseudo_instruction.hpp"

#include "fCore_isa.hpp"


namespace fcore{
    pseudo_instruction::pseudo_instruction(opcode_table_t op, std::vector<std::shared_ptr<variable>> args){
            opcode = std::move(op);
            arguments = std::move(args);
    }

    int pseudo_instruction::instruction_count() const {
        return 1;
    }

}
