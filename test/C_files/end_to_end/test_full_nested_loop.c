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
// limitations under the License.02/07/2021.
//

int add (int a, int b){
    return a+b;
}



int main(){
    int h[4];

#pragma input(a, r2)
    int a[4];
    int b[4];

    for(int i = 2; i<4; ++i)
        for(int x = 0; x<2; ++x){
            b[i] = h[i] + a[x];
        }
}
