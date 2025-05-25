//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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
// limitations under the License.05/07/2021.


#include "emulator/backend/gp_executor.hpp"
namespace fcore::emulator{

    uint32_t gp_executor::execute_add(uint32_t a, uint32_t b) {
        auto op_a = uint32_to_float(a);
        auto op_b = uint32_to_float(b);
        auto res = op_a + op_b;
        return float_to_uint32(res);
    }

    uint32_t gp_executor::execute_sub(uint32_t a, uint32_t b) {
        auto op_a = uint32_to_float(a);
        auto op_b = uint32_to_float(b);
        auto res = op_a - op_b;
        return float_to_uint32(res);
    }

    uint32_t gp_executor::execute_mul(uint32_t a, uint32_t b) {
        auto op_a = uint32_to_float(a);
        auto op_b = uint32_to_float(b);
        auto res = op_a * op_b;
        return float_to_uint32(res);
    }

    uint32_t gp_executor::execute_rec(uint32_t a) {
        auto op_a = uint32_to_float(a);
        auto res = 1.0f/op_a;
        return float_to_uint32(res);
    }

    uint32_t gp_executor::execute_fti(uint32_t a) {
        auto op_a = uint32_to_float(a);
        return op_a;
    }

    uint32_t gp_executor::execute_itf(uint32_t a) {
        int32_t singed_a;
        if (a > INT32_MAX) {
            singed_a = static_cast<int32_t>(a - UINT32_MAX - 1);
        } else {
            singed_a = static_cast<int32_t>(a);
        }
        float op_a = singed_a;

        return float_to_uint32(op_a);
    }

    uint32_t gp_executor::float_to_uint32(float f) {
        uint32_t ret;
        memcpy(&ret, &f, sizeof(f));
        return ret;
    }

    float gp_executor::uint32_to_float(uint32_t u) {
        float ret;
        memcpy(&ret, &u, sizeof(u));
        return ret;
    }
}
