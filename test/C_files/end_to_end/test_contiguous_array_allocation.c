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
    float out_1;
    #pragma output(out_1, r2)
    float out_2;
    #pragma output(out_2, r6)


    float index[2];

    int a[2];
    a = efi(index, 11);
    out_1 = a[0] + 4;
    out_2 = a[1] + 2;
}

