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

#include "../../includes/emulator/v2/input_waveform_generator.hpp"

using namespace fcore::emulator_v2;


TEST(waveform_generator, generate_square) {

    input_waveform_generator gen;
    gen.set_sampling_frequency(1e6);

    fcore::square_wave_parameters p{};
    p.period = {1e-3};
    p.t_on = {850e-6};
    p.v_on = {50};
    p.v_off = {-30};
    p.t_delay = {124e-6};
    gen.add_waveform("test_square", p, 1);

    std::ifstream file("in_gen/square.txt");
    for(int i = 0; i < 2300; i++){
        auto sample = gen.get_value("test_square", 0);
        double val;
        file >> val;
        EXPECT_NEAR(sample, val, 1e-6);
    }
}



TEST(waveform_generator, generate_sine) {

    input_waveform_generator gen;
    gen.set_sampling_frequency(1e6);

    fcore::sine_wave_parameters p{};
    p.amplitude = {25};
    p.dc_offset = {25};
    p.frequency = {1e3};
    p.phase = {2.0*M_PI/3};
    gen.add_waveform("test_sine", p, 1);

    std::ifstream file("in_gen/sine.txt");
    for(int i = 0; i < 2300; i++){
        auto sample = gen.get_value("test_sine", 0);
        double val;
        file >> val;
        EXPECT_NEAR(sample, val, 1e-6);
    }
}


TEST(waveform_generator, generate_triangle) {

    input_waveform_generator gen;
    gen.set_sampling_frequency(1e6);

    fcore::triangle_wave_parameters p{};
    p.amplitude = {25};
    p.dc_offset = {25};
    p.frequency = {1e3};
    p.phase = {M_PI};
    p.duty = {0.5};
    gen.add_waveform("test_triangle", p, 1);

    std::ifstream file("in_gen/triangle.txt");
    for(int i = 0; i < 2300; i++){
        auto sample = gen.get_value("test_triangle", 0);
        double val;
        file >> val;
        EXPECT_NEAR(sample, val, 1e-4);
    }
}


TEST(waveform_generator, generate_sine_multichannel) {

    input_waveform_generator gen;
    gen.set_sampling_frequency(1e6);

    fcore::sine_wave_parameters p{};
    p.amplitude = {25, 50};
    p.dc_offset = {25, 50};
    p.frequency = {1e3, 1e3};
    p.phase = {M_PI, M_PI};
    gen.add_waveform("test_sine", p, 2);

    for(int i = 0; i < 2300; i++){
        auto sample_0 = gen.get_value("test_sine", 0);
        auto result_0 = 25*std::sin(2*M_PI*i*1e-3 + M_PI) + 25;
        auto sample_1 = gen.get_value("test_sine", 1);
        auto result_1 = 50*std::sin(2*M_PI*i*1e-3 + M_PI) + 50;
        EXPECT_FLOAT_EQ(sample_0, result_0);
        EXPECT_FLOAT_EQ(sample_1, result_1);
    }

}



TEST(waveform_generator, generate_sine_multirate) {

    input_waveform_generator gen, gen2;
    gen.set_sampling_frequency(1e6);
    gen2.set_sampling_frequency(1e6);

    fcore::sine_wave_parameters p{};
    p.amplitude = {25};
    p.dc_offset = {25};
    p.frequency = {1e3};
    p.phase = {M_PI, M_PI};
    gen.add_waveform("test_sine", p, 1);
    gen2.add_waveform("test_sine_slow", p, 1);

    for(int i = 0; i < 2300; i++){
        auto sample_0 = gen.get_value("test_sine", 0);
        auto result_0 = 25*std::sin(2*M_PI*i*1e-3 + M_PI) + 25;
        EXPECT_FLOAT_EQ(sample_0, result_0);

        if(i%2) {
            auto sample_1 = gen2.get_value("test_sine_slow", 0);
            auto result_1 = 25*std::sin(2*M_PI*i*1e-3 + M_PI) + 25;
            EXPECT_FLOAT_EQ(sample_1, result_1);
        } else {
            gen2.advance();
        }
    }

}
