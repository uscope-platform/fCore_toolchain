//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_INPUT_WAVEFORM_GENERATOR_HPP
#define FCORE_TOOLCHAIN_INPUT_WAVEFORM_GENERATOR_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <variant>
#include <algorithm>

#include "emulator/emulator_metadata_common.hpp"


namespace fcore::emulator_v2 {
    class input_waveform_generator {
    public:
        void set_sampling_frequency(const double f){sampling_period = 1/f;}
        void add_waveform(const std::string& in, std::variant<square_wave_parameters, sine_wave_parameters, triangle_wave_parameters> p, uint32_t channels);
        double peek_value(const std::string &in, uint32_t channel);
        double get_value(const std::string &in, uint32_t channel);
        void reset() {current_sample.clear();}
        void advance();
    private:
        double produce_waveform(const square_wave_parameters &p, double time, uint32_t channel);
        double produce_waveform(const triangle_wave_parameters &p, double time, uint32_t channel);
        double produce_waveform(const sine_wave_parameters &p, double time, uint32_t channel);
        std::unordered_map<std::string, std::variant<square_wave_parameters, sine_wave_parameters, triangle_wave_parameters>> parameters;
        double sampling_period = 0;
        std::unordered_map<std::string, std::vector<uint64_t>> current_sample;
    };
}



#endif //FCORE_TOOLCHAIN_INPUT_WAVEFORM_GENERATOR_HPP