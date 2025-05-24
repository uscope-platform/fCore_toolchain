//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_EMULATOR_OUTPUT_HPP
#define FCORE_TOOLCHAIN_EMULATOR_OUTPUT_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <map>
#include <spdlog/spdlog.h>

#include "specs/v1/emulator_specs.hpp"
#include "emulator/backend/emulator_backend.hpp"


namespace fcore{


    class emulator_output {
    public:
        emulator_output() = default;
        emulator_output(const emulator::emulator_output_specs &s, uint32_t n_channels);
        void set_sampling_period(double per){sampling_period = per;};
        void add_data_point(const std::vector<uint32_t>& dp, uint32_t channel);
        void add_data_point(uint32_t dp, uint32_t channel);
        void repeat_last_data_point();
        std::map<std::string, std::vector<std::vector<uint32_t>>> get_integer_data();
        std::map<std::string, std::vector<std::vector<float>>> get_float_data();
        uint64_t get_data_length(){return data[0].size();};
        double get_sampling_period() const{return sampling_period;};

    private:
        std::map<uint32_t, std::vector<std::string>> id;
        double sampling_period;
        uint32_t vector_size;
        std::map<uint32_t, std::vector<std::vector<uint32_t>>> data;

    };
}



#endif //FCORE_TOOLCHAIN_EMULATOR_OUTPUT_HPP
