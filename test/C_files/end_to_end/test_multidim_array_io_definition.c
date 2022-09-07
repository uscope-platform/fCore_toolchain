
// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
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
// limitations under the License.07/07/2021.
//

int main(){
    #pragma input(a, {r4,r7});
    #pragma output(c, {r8, r9, r10, r11});
    #pragma memory(d, {r12, r13, r16, r18});
    float a[2];
    float b = a[0] + a[1];
    float c[2][2];
    c[0][0] = a[0] + a[1];
    c[1][0] = a[0] - a[1];
    c[0][1] =  a[0] + a[1];
    c[1][1] = a[0] - a[1];
    float d[2][2];
    d[0][0] = a[0] * a[1];
    d[1][0] = a[0] * b;
    d[0][1] = a[0] * a[1];
    d[1][1] = a[0] * b;
}