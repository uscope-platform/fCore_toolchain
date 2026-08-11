//  Copyright  2026 University of Nottingham
//  Author: Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
#include "fuzzer/fuzzer.hpp"

void fuzzer::fuzz() {
}

std::vector<uint32_t> fuzzer::generate_binary() {
    // 1: select the number of inputs to generate
    // 2: select the program size
    // 3: generate instructions in a loop until the size goal is met
    // 4: compile injecting the instruction stream post register allocation
}
