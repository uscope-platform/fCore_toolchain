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


#include "emulator/ba_executor.hpp"


fcore::ba_executor::ba_executor() {
    xip_fpo_init2(xil_a, 8, 24);
    xip_fpo_init2(xil_b, 8, 24);
    xip_fpo_init2(xil_res, 8, 24);
    xip_fpo_fix_init2(xil_a_fixed_point, 32, 0);
}

uint32_t fcore::ba_executor::execute_add(uint32_t a, uint32_t b) {
    if(b==0){ // I must be doing something wrong... investigate why these are necessary
        return a;
    } else if(a==0){
        return b;
    }
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    xip_fpo_exc_t exc = xip_fpo_add(xil_res, xil_a, xil_b);
    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the addition of"+ std::to_string(a) + " and " + std::to_string(b));
    }

    auto fv = xip_fpo_get_flt(xil_res);
    return float_to_uint32(fv);
}

uint32_t fcore::ba_executor::execute_sub(uint32_t a, uint32_t b) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    xip_fpo_exc_t exc = xip_fpo_sub(xil_res, xil_a, xil_b);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the subtraction of"+ std::to_string(a) + " and " + std::to_string(b));
    }

    return float_to_uint32(xip_fpo_get_flt(xil_res));
}

uint32_t fcore::ba_executor::execute_mul(uint32_t a, uint32_t b) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));
    xip_fpo_set_flt(xil_b, uint32_to_float(b));

    xip_fpo_exc_t exc = xip_fpo_mul(xil_res, xil_a, xil_b);
    if ( exc != 0) {
        throw std::runtime_error("An exception occurred in the multiplication of"+ std::to_string(a) + " and " + std::to_string(b));
    }

    return float_to_uint32(xip_fpo_get_flt(xil_res));
}

uint32_t fcore::ba_executor::execute_rec(uint32_t a) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));

    xip_fpo_exc_t exc = xip_fpo_rec(xil_res, xil_a);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the calculation of the reciprocal of"+ std::to_string(a));
    }

    auto res = xip_fpo_get_flt(xil_res);
    return float_to_uint32(res);
}

uint32_t fcore::ba_executor::execute_fti(uint32_t a) {
    xip_fpo_set_flt(xil_a, uint32_to_float(a));

    xip_fpo_exc_t exc = xip_fpo_flttofix(xil_a_fixed_point, xil_a);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the conversion of "+ std::to_string(a) + "to float from integer");
    }
    return (uint32_t) xip_fpo_fix_get_si(xil_a_fixed_point);
}


uint32_t fcore::ba_executor::execute_itf(uint32_t a) {
    xip_fpo_fix_set_si(xil_a_fixed_point, (int32_t)a);
    xip_fpo_exc_t exc = xip_fpo_fixtoflt(xil_res, xil_a_fixed_point);

    if ( exc != 0) {
        throw std::runtime_error("An exception occurred during the conversion of "+ std::to_string(a) + "to integer from float");
    }
    auto fv = xip_fpo_get_flt(xil_res);
    return float_to_uint32(fv);
}


uint32_t fcore::ba_executor::float_to_uint32(float f) {
    uint32_t ret;
    memcpy(&ret, &f, sizeof(f));
    return ret;
}

float fcore::ba_executor::uint32_to_float(uint32_t u) {
    float ret;
    memcpy(&ret, &u, sizeof(u));
    return ret;
}


