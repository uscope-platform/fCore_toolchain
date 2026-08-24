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



#include <gtest/gtest.h>

#include "fuzzer/fuzzer.hpp"
namespace fcore {
    TEST( fuzzer, program_generation) {
        fuzzer_config cfg;
        cfg.rng_seed = 1523;
        cfg.rng_float_params = {125, 20};
        cfg.active_regs = 9;
        fuzzer f(cfg);
        auto res = f.generate_binary();
    }
}