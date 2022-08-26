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


int main(){

    int test_in;
    #pragma input(test_in, r25)

    float test_out;
    #pragma output(test_out, r5)

    float test_var = 1.0;
    #pragma output(test_var, r7)

    int factor_1 = test_var <= test_in;
    #pragma output(factor_1, r6)
    test_var=test_var+test_in;

    test_out = test_var;
    return 0;
}
