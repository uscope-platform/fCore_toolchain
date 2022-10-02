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

    float v_cells;
    #pragma input(v_cells, r59)

    float v_arms = 0;
    #pragma output(v_arms, {r60, r61})


    for(int i = 0; i<2; ++i){
        int idx_l = 10+i;
        v_arms += "v_cells[idx_l]";
    }
}
