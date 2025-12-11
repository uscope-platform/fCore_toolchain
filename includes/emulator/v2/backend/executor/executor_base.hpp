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

#ifndef FCORE_TOOLCHAIN_EXECUTOR_BASE_HPP
#define FCORE_TOOLCHAIN_EXECUTOR_BASE_HPP


#include <cstdint>
#include <cstring>
#include <bitset>

#include "data_structures/emulation/v2/emulator_metadata.hpp"

namespace fcore::emulator_v2 {
    class executor_base{
    public:
        virtual uint32_t execute_add(uint32_t a, uint32_t b){ return 0;}
        virtual uint32_t execute_sub(uint32_t a, uint32_t b){ return 0;}
        virtual uint32_t execute_mul(uint32_t a, uint32_t b){ return 0;}
        virtual uint32_t execute_rec(uint32_t a){ return 0;}
        virtual uint32_t execute_fti(uint32_t a){ return 0;}
        virtual uint32_t execute_itf(uint32_t a){ return 0;}

        uint32_t execute_not(uint32_t a);
        uint32_t execute_and(uint32_t a, uint32_t b);
        uint32_t execute_abs(uint32_t a);
        uint32_t execute_popcnt(uint32_t a);
        uint32_t execute_satp(uint32_t a, uint32_t b);
        uint32_t execute_satn(uint32_t a, uint32_t b);
        uint32_t execute_bset(uint32_t a, uint32_t b, uint32_t c);
        uint32_t execute_bsel(uint32_t a, uint32_t b);
        uint32_t execute_csel(uint32_t a, uint32_t b, uint32_t c);
        uint32_t execute_or(uint32_t a, uint32_t b);
        uint32_t execute_xor(uint32_t a, uint32_t b);
        uint32_t execute_compare_gt(uint32_t a, uint32_t b, comparator_type_t comparator_type);
        uint32_t execute_compare_le(uint32_t a, uint32_t b, comparator_type_t comparator_type);
        uint32_t execute_compare_eq(uint32_t a, uint32_t b, comparator_type_t comparator_type);
        uint32_t execute_compare_ne(uint32_t a, uint32_t b, comparator_type_t comparator_type);

        static uint32_t float_to_uint32(float f);
        static float uint32_to_float(uint32_t u);
    private:

        uint32_t process_comparison_output(bool val, comparator_type_t comparator_type);
    };
}


#endif //FCORE_TOOLCHAIN_EXECUTOR_BASE_HPP