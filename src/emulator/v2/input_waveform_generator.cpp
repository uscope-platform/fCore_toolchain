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

#include "emulator/v2/input_waveform_generator.hpp"


namespace  fcore::emulator_v2 {
    double input_waveform_generator::peek_value(const std::string &in) {
        auto p = parameters.at(in);
        if(!current_sample.contains(in)) current_sample.insert({in, 0});
        auto time = static_cast<double>(current_sample.at(in))*sampling_period;
        return std::visit([&](auto &&arg) { return produce_waveform(arg, time); }, p);

    }

    double input_waveform_generator::get_value(const std::string &in) {
        auto result = peek_value(in);
        current_sample[in]++;
        return result;
    }

    double input_waveform_generator::produce_waveform(const square_wave_parameters &p, double time) {
        double normalized_time = std::fmod(time-p.t_delay, p.period);
        if(normalized_time<(p.period-p.t_on)) return p.v_off;
        else return p.v_on;
    }

    double input_waveform_generator::produce_waveform(const triangle_wave_parameters &p, double time) {

        auto period = 1/p.frequency;
        auto t_peak = period*p.duty;
        auto time_shift = p.phase/(2*M_PI*p.frequency);

        double normalized_time = std::fmod(time-time_shift, period);
        if (normalized_time < 0) {
            normalized_time += period;
        }
        double slope;
        if(normalized_time<t_peak) {
            slope = 2.0/t_peak;
            return slope*normalized_time-1;
        } else {
            slope = -2.0/(period-t_peak);
            return 1 + slope*(normalized_time - t_peak);
        }
    }

    double input_waveform_generator::produce_waveform(const sine_wave_parameters &p, double time) {
        return p.amplitude * std::sin(2 * M_PI * p.frequency * time + p.phase) + p.dc_offset;
    }
}
