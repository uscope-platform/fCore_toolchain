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

#include "data_structures/instruction_stream/intercalated_constant.hpp"

namespace fcore {
    intercalated_constant::intercalated_constant(float constant) {
        float_const = constant;
        int_const = 0;
        is_float = true;
    }


    intercalated_constant::intercalated_constant(uint32_t constant) {
        int_const = constant;
        float_const = 0;
        is_float = false;
    }


    uint32_t intercalated_constant::emit()const {
        uint32_t  raw_instr = 0;
        if(is_float){
            memcpy(&raw_instr, &float_const, sizeof(raw_instr));
        } else {
            raw_instr = int_const;
        }
        return raw_instr;
    }

    void intercalated_constant::print() const{
    }

    int intercalated_constant::instruction_count()const {
        return 1;
    }


    nlohmann::json intercalated_constant::dump()const {
        nlohmann::json retval;
        retval["instruction_type"] = "isa_intercalated_constant";
        retval["intercalated_constant"] = float_const;
        return retval;
    }

    std::string intercalated_constant::disassemble()const {
        if(is_float) return std::to_string(float_const);
        else return  std::to_string(int_const);
    }


}
