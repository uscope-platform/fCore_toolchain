// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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
//

#include "emulator/backend/efi_dispatcher.h"


void fcore::efi_dispatcher::emulate_efi(efi_implementation_t function, uint32_t op_a, uint32_t op_b, uint32_t dest, std::shared_ptr<std::vector<uint32_t>>m) {
    if(function == efi_sort){
        efi_sort_exec(op_a, op_b, dest, m);
    } else if(function ==efi_trig) {
        efi_trig_exec(op_a, dest, m);
    } else if(function ==efi_none) {
        throw std::runtime_error("The emulator has encountered an EFI instruction on core "+core_name+" which does not have an EFI interface.");
    } else{
        throw std::runtime_error("The emulator has encountered an EFI instruction, however an unknown implementation was selected in the spec file");
    }
}

void fcore::efi_dispatcher::efi_sort_exec(uint32_t op_a, uint32_t op_b, uint32_t dest, std::shared_ptr<std::vector<uint32_t>>m) {


    bool descending_order  = m->at(op_a) != 1;
    std::vector<cell> cells;
    std::vector<uint32_t> idx;
    idx.reserve(op_b-1);
    cells.reserve(op_b-1);

    for (uint32_t i = 1; i < op_b; i++) {
        cells.emplace_back(uint32_to_float(m->at(op_a+i)), i, descending_order);
    }

    std::sort(cells.begin(), cells.end());

    for (uint32_t i = 0; i < cells.size(); ++i) {
        m->at(dest+i) = (uint32_t)cells[i].idx-1;
    }
}



uint32_t fcore::efi_dispatcher::float_to_uint32(float f) {
    uint32_t ret;
    std::memcpy(&ret, &f, sizeof(f));
    return ret;
}

float fcore::efi_dispatcher::uint32_to_float(uint32_t u) {
    float ret;
    std::memcpy(&ret, &u, sizeof(u));
    return ret;
}



template <typename T, unsigned B>
inline T signextend(const T x)
{
    struct {T x:B;} s;
    return s.x = x;
}

void fcore::efi_dispatcher::efi_trig_exec(uint32_t op_a, uint32_t dest, std::shared_ptr<std::vector<uint32_t>>m) {

    int opcode  = m->at(op_a);

    uint32_t theta = m->at(op_a+1);

    double angle_deg = theta/65536.0*360.0;

    double angle_rad = angle_deg*(M_PI/180);
    double quant_angle = 1/512.0*(floor(angle_rad/(1/512.0))+0.5);
    float raw_result;
    if(opcode== 0){
        raw_result = (float)sin(quant_angle);
    } else{
        raw_result = (float)cos(quant_angle);
    }
    float scaled_res = raw_result*32768;
    int result = round(scaled_res);
    m->at(dest) = result;
}




