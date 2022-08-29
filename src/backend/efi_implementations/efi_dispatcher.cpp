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
// limitations under the License.05/07/2021.
//

#include "backend/efi_implementations/efi_dispatcher.h"


void efi_dispatcher::emulate_efi(const std::string& function, uint32_t op_a, uint32_t op_b, uint32_t dest) {
    if(function == "efi_sort"){
        efi_sort(op_a, op_b, dest);
    }
}

void efi_dispatcher::efi_sort(uint32_t op_a, uint32_t op_b, uint32_t dest) {
    std::vector<float> in;
    for(int i = 0; i<op_b; i++){
        in.push_back(uint32_to_float(memory->at(op_a+i)));
    }

    bool descending_order  = memory->at(op_a) != 1;
    std::vector<cell> cells;
    std::vector<uint32_t> idx;
    idx.reserve(in.size());
    cells.reserve(in.size());

    for (int i = 1; i < in.size(); i++) {
        cells.emplace_back(in[i], i, descending_order);
    }

    std::sort(cells.begin(), cells.end());

    for (int i = 0; i < cells.size(); ++i) {
        memory->at(dest+i) = (uint32_t)cells[i].idx-1;
    }
}



uint32_t efi_dispatcher::float_to_uint32(float f) {
    uint32_t ret;
    std::memcpy(&ret, &f, sizeof(f));
    return ret;
}

float efi_dispatcher::uint32_to_float(uint32_t u) {
    float ret;
    std::memcpy(&ret, &u, sizeof(u));
    return ret;
}


void efi_dispatcher::efi_trig(uint32_t op_a, uint32_t op_b, uint32_t dest) {

}

