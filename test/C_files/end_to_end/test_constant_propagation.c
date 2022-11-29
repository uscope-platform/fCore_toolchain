//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.05/07/2021.



int main(){
    int a;
    #pragma input(a, r5)

    float switching_cell[2] = {1.0, 1.0};
    #pragma memory(switching_cell, {r17, r18})

    switching_cell[0]=switching_cell[0]+a;

    switching_cell[0] = 1.0;
    switching_cell[1] = 1.0;

    switching_cell[1]=switching_cell[1]+a;

}
