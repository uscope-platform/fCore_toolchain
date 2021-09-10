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

#define MAX_MATRIX 3

void matrix_matrix_mult(float mat_1[MAX_MATRIX][MAX_MATRIX], float mat_2[MAX_MATRIX][MAX_MATRIX], float mat_3[MAX_MATRIX][MAX_MATRIX], int M, int N){
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            mat_3[i][j] = mat_1[i][j]+ mat_2[i][j];
        }
    }

}

int main(){


#pragma input(test_in, r25)

    float a[2][2] = {{1.0, 2.0}, {4.0, 5.0}};
    float b[2][2] = {{1.0, 2.0}, {4.0, 5.0}};
    #pragma output(c, {r12, r13, r14, r15})
    float c[2][2];
    matrix_matrix_mult(a, b, c, 2, 2);

    return 0;
}