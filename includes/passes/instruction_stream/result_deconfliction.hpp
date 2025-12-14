//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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


#ifndef FCORE_TOOLCHAIN_RESULT_DECONFLICTION_HPP
#define FCORE_TOOLCHAIN_RESULT_DECONFLICTION_HPP

#include "fCore_isa.hpp"
#include "stream_pass_base.hpp"
#include <bitset>
#include <set>

namespace fcore {
    class result_deconfliction :public stream_pass_base{
    public:
        result_deconfliction(uint8_t ac);
        std::vector<instruction_variant> apply_vector_mutable_pass(instruction_variant &element,
            uint32_t n_pass, uint32_t n_instuction) override;
    private:
        std::bitset<fcore_max_binary_size+150> allocated_writeback_slots;
        uint8_t active_channels;
        std::set<uint32_t> delay_slot_addresses;
    };
}



#endif //FCORE_TOOLCHAIN_RESULT_DECONFLICTION_HPP