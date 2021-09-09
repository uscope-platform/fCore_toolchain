
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


int main(){
    #pragma input(a, {r4,r7});
    #pragma output(b, r3);
    #pragma output(c, {r8,r9});
    #pragma memory(d, {r10,r11});
    float a[2];
    float b = a[0] + a[1];
    float c[2];
    c[0] = a[0] + a[1];
    c[1] = a[0] - a[1];
    float d[2];
    d[0] = a[0] * a[1];
    d[1] = a[0] * b;
}