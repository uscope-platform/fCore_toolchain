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


#include "emulator/v2/backend/executor/executor_base.hpp"

namespace fcore::emulator_v2 {

    uint32_t executor_base::execute_not(uint32_t a){
        return ~a;
    }

    uint32_t executor_base::execute_and(uint32_t a, uint32_t b){
        return a & b;
    }

    uint32_t executor_base::execute_abs(uint32_t a){
        return a&0x7fffffff;
    }

    uint32_t executor_base::execute_popcnt(uint32_t a){
        return std::bitset<32>(a).count();
    }

    uint32_t executor_base::execute_satp(uint32_t a, uint32_t b) {
        float raw_a = uint32_to_float(a);
        float raw_b = uint32_to_float(b);

        float raw_res;

        if(raw_a>raw_b){
            raw_res = raw_b;
        } else {
            raw_res = raw_a;
        }

        return float_to_uint32(raw_res);
    }

    uint32_t executor_base::execute_satn(uint32_t a, uint32_t b) {
        float raw_a = uint32_to_float(a);
        float raw_b = uint32_to_float(b);

        float raw_res;
        if(raw_a<raw_b){
            raw_res = raw_b;
        } else {
            raw_res = raw_a;
        }

        return float_to_uint32(raw_res);
    }

    uint32_t executor_base::execute_bset(uint32_t a, uint32_t b, uint32_t c){
        std::bitset<32> bits(a);
        bits[b] = c;
        return bits.to_ulong();
    }

    uint32_t executor_base::execute_bsel(uint32_t a, uint32_t b){
        return (a & (1<<b))>>b;
    }

    uint32_t executor_base::execute_csel(uint32_t a, uint32_t b, uint32_t c){
        if(a & 0x1){
            return b;
        } else {
            return c;
        }
    }

    uint32_t executor_base::execute_or(uint32_t a, uint32_t b){
        return a | b;
    }

    uint32_t executor_base::execute_xor(uint32_t a, uint32_t b){
        return a ^ b;
    }

    uint32_t executor_base::execute_compare_gt(uint32_t a, uint32_t b, comparator_type_t comparator_type) {
        bool sign_a = (1<<31) & a;
        bool sign_b = (1<<31) & b;

        bool res;

        if(sign_a & sign_b) {
            res = a < b;
        }else if(sign_a & !sign_b){
            res = false;
        } else if(!sign_a & sign_b){
            res = true;
        } else {
            res = a>b;
        }

        return process_comparison_output(res, comparator_type);
    }

    uint32_t executor_base::execute_compare_le(uint32_t a, uint32_t b, comparator_type_t comparator_type){
        bool sign_a = (1<<31) & a;
        bool sign_b = (1<<31) & b;

        bool res;
        if(a == b){
            res = true;
        } else if(sign_a & sign_b) {
            res = a>b;
        }else if(sign_a & !sign_b){
            res = true;
        } else if(!sign_a & sign_b){
            res = false;
        }else {
            res = a<=b;
        }
        return process_comparison_output(res, comparator_type);
    }

    uint32_t executor_base::execute_compare_eq(uint32_t a, uint32_t b, comparator_type_t comparator_type){
        return process_comparison_output(a==b, comparator_type);
    }

    uint32_t executor_base::execute_compare_ne(uint32_t a, uint32_t b, comparator_type_t comparator_type){
        return process_comparison_output(a!=b, comparator_type);
    }

    uint32_t executor_base::float_to_uint32(float f){
        uint32_t ret;
        memcpy(&ret, &f, sizeof(f));
        return ret;
    }

    float executor_base::uint32_to_float(uint32_t u){
        float ret;
        memcpy(&ret, &u, sizeof(u));
        return ret;
    }


    uint32_t executor_base::process_comparison_output(bool val, comparator_type_t comparator_type) {

        if(comparator_type== comparator_full) {
            if(val){
                return 0xffffffff;
            } else {
                return 0;
            }
        } else if(comparator_type==comparator_reducing){
            return val;
        } else if(comparator_type == comparator_none) {
            throw std::runtime_error("The emulator has encountered a comparison instruction on core which does not have comparators.");
        } else{
            throw std::runtime_error("The emulator has encountered a comparison instruction, however an unknown type was selected in the spec file");
        }
    }

}
