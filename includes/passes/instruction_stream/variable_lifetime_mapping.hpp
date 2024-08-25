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

#ifndef FCORE_TOOLCHAIN_VARIABLE_LIFETIME_MAPPING_HPP
#define FCORE_TOOLCHAIN_VARIABLE_LIFETIME_MAPPING_HPP


#include <type_traits>
#include <variant>

#include "stream_pass_base.hpp"
#include "data_structures/common/variable.hpp"
#include "tools/variable_map.hpp"

namespace fcore{

    class variable_lifetime_mapping : public stream_pass_base{
    public:
        explicit variable_lifetime_mapping(std::shared_ptr<variable_map> &v);
        std::optional<instruction_variant> apply_pass(const instruction_variant &element, uint32_t n) override;

    private:

        unsigned int instr_cntr;
        std::shared_ptr<variable> update_variable_lifetime(const std::shared_ptr<variable>& var) const;
        void map_register_inst( register_instruction& instr);
        void map_conv_instr( conversion_instruction& instr);
        void map_load_const_instr( load_constant_instruction& instr);
        void map_ternary_instr( ternary_instruction& instr);

        std::shared_ptr<variable_map> vmap;

    };
}


#endif //FCORE_TOOLCHAIN_VARIABLE_LIFETIME_MAPPING_HPP
