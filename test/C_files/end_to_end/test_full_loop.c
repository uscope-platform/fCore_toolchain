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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.02/07/2021.
//

int add (int a, int b){
    return a+b;
}



int main(){
#pragma input(h, r1);
    int h[6];

#pragma input(k, r2)
    int k[4];

#pragma output(j, r15);
    int j;

    for(int i = 0+5; i+1<8; ++i){
        if(3<5){
            j = k[i] + h[i];
            b[i] = add(h[i], k[i]);
        }
    }
}