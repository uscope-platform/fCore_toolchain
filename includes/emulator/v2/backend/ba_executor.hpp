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


#ifndef FCORE_TOOLCHAIN_BA_EXECUTOR_V2_HPP
#define FCORE_TOOLCHAIN_BA_EXECUTOR_V2_HPP

#include <cstdint>
#include <stdexcept>
#include <cstring>


#include "floating_point_v7_1_bitacc_cmodel.h"

namespace fcore::emulator_v2{
    class ba_executor {
    public:
        ba_executor();
        uint32_t execute_add(uint32_t a, uint32_t b);
        uint32_t execute_sub(uint32_t a, uint32_t b);
        uint32_t execute_mul(uint32_t a, uint32_t b);
        uint32_t execute_rec(uint32_t a);
        uint32_t execute_fti(uint32_t a);
        uint32_t execute_itf(uint32_t a);
    private:
        xip_fpo_t xil_a, xil_b, xil_res;
        xip_fpo_fix_t xil_a_fixed_point;

        static uint32_t float_to_uint32(float f);
        static float uint32_to_float(uint32_t u);
    };

}

#endif //FCORE_TOOLCHAIN_BA_EXECUTOR_V2_HPP
