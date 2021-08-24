// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.07/07/2021.
//

float add_first(float mem_1[2][2][3], float mem_2[7], int i){
    return mem_1[0][0][i] + mem_2[i];
}


int main(){
    int a[2][2][3] = {{{0, 1, 2}, {3, 4, 5}},{{6, 7, 8}, {9, 10, 11}}};
    int b[7] = {2, 2, 2, 2, 2, 2, 2};

    #pragma output(c, r18)
    float c = add_first(a, b, 1);
}
