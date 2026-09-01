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
        cfg.max_program_size = 35;
        cfg.active_regs = 9;
        fuzzer f(cfg);
        auto res = f.generate_binary();
        EXPECT_FALSE(res.binary.empty());
        ASSERT_GT(res.binary.size(), 1);
        EXPECT_LE(res.binary.size()-1, cfg.max_program_size);
        EXPECT_LE(res.inputs.size(), cfg.active_regs);

        std::vector<uint32_t> check_binary= {
            2097153,
            12,
            12,
            12,
            397456,
            10387,
            1054989,
            2324,
            4367,
            6245,
            528651,
            788758,
            8467,
            14612,
            923930,
            14386,
            800802,
            669819,
            788762,
            276681,
            10436,
            262,
            1124831561,
            526491,
            2322,
            4325,
            1050875,
            16531,
            665744,
            921819,
            929899,
            14450,
            14597,
            2117,
            1059041,
            12
        };
        EXPECT_EQ(res.binary,check_binary);

        std::unordered_map<uint32_t, float> check_inputs = {
            {2, 153.097794},
            {4, 124.245865},
            {5, 115.314125},
            {8, 110.39316},
        };
        EXPECT_EQ(check_inputs.size(), res.inputs.size());
        for (auto &k : check_inputs | std::views::keys) {
            ASSERT_TRUE(res.inputs.contains(k));
            ASSERT_FLOAT_EQ(res.inputs[k], check_inputs[k]);
        }

    }

    TEST( fuzzer, program_execution) {
        fuzzer_config cfg;
        cfg.rng_seed = 1523;
        cfg.rng_float_params = {125, 20};
        cfg.max_program_size = 35;
        cfg.active_regs = 9;
        fuzzer f(cfg);

        std::istringstream stream(R"(
            ldc r6, 2.0
            add r2, r1, r5
            mul r5, r6, r3
            stop
        )");

        std::map<std::string, std::vector<uint32_t>> io_map = {{"r2", {2}}, {"r1", {1}}, {"r3", {3}}};

        fcore_has has(stream, false, io_map);

        std::vector<uint32_t> test_exec = has.get_executable();
        test_exec.erase(test_exec.begin()+2, test_exec.begin()+5);
        fuzzing_package pkg;
        pkg.binary = test_exec;
        pkg.inputs = {
                {2, 153.097794},
                {1, 124.245865},
        };
        auto mem = f.emulate(pkg);
        std::vector<float> result(mem.size());
        std::transform(mem.begin(), mem.end(), result.begin(),
                       [](uint32_t val) { return std::bit_cast<float>(val); });

        std::vector<float> expected_result(mem.size());
        expected_result[1] = 124.245865;
        expected_result[2] = 153.097794;
        expected_result[5] = expected_result[1] + expected_result[2];
        expected_result[6] = 2.0;
        expected_result[3] = (expected_result[1] + expected_result[2])*2    ;

        for (int i = 0; i<result.size(); i++){
            EXPECT_FLOAT_EQ(result[i], expected_result[i]);
        }
    }



    TEST( fuzzer, emu_fuzzer_e2e) {
        fuzzer_config cfg;
        cfg.rng_seed = 324;
        cfg.rng_float_params = {125, 20};
        cfg.max_program_size = 35;
        cfg.active_regs = 9;
        fuzzer f(cfg);


        auto pkg = f.generate_binary();
        auto mem = f.emulate(pkg);
        std::vector<float> result(mem.size());
        std::transform(mem.begin(), mem.end(), result.begin(),
                       [](uint32_t val) { return std::bit_cast<float>(val); });

        int i = 0;
    }


}