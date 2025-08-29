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
// limitations under the License.

#include <fstream>
#include <gtest/gtest.h>

#include "emulator/input_waveform_generator.hpp"

using namespace fcore::emulator_v2;


TEST(waveform_generator, generate_square) {

    input_waveform_generator gen;
    gen.set_sampling_frequency(1e6);

    fcore::square_wave_parameters p{};
    p.period = 1e-3;
    p.t_on = 850e-6;
    p.v_on = 50;
    p.v_off = -30;
    p.t_delay = 124e-6;
    gen.add_waveform("test_square", p);

    std::ifstream file("in_gen/square.txt");
    for(int i = 0; i < 2300; i++){
        auto sample = gen.get_value("test_square");
        double val;
        file >> val;
        EXPECT_NEAR(sample, val, 1e-6);
    }
}



TEST(waveform_generator, generate_sine) {

    input_waveform_generator gen;
    gen.set_sampling_frequency(1e6);

    fcore::sine_wave_parameters p{};
    p.amplitude = 25;
    p.dc_offset = 25;
    p.frequency = 1e3;
    p.phase = 2.0*M_PI/3;
    gen.add_waveform("test_sine", p);

    std::ifstream file("in_gen/sine.txt");
    for(int i = 0; i < 2300; i++){
        auto sample = gen.get_value("test_sine");
        double val;
        file >> val;
        EXPECT_NEAR(sample, val, 1e-6);
    }
}


TEST(waveform_generator, generate_triangle) {

    input_waveform_generator gen;
    gen.set_sampling_frequency(1e6);

    fcore::triangle_wave_parameters p{};
    p.amplitude = 25;
    p.dc_offset = 25;
    p.frequency = 1e3;
    p.phase = M_PI;
    p.duty = 0.5;
    gen.add_waveform("test_triangle", p);

    std::ifstream file("in_gen/triangle.txt");
    for(int i = 0; i < 2300; i++){
        auto sample = gen.get_value("test_triangle");
        double val;
        file >> val;
        EXPECT_NEAR(sample, val, 1e-4);
    }
}



