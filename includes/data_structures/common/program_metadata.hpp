

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

#ifndef PROGRAM_METADATA_HPP
#define PROGRAM_METADATA_HPP

#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <nlohmann/json.hpp>


namespace fcore {

    class emulation_progress_stat {
    public:
        uint32_t current;
        uint32_t channel;
        uint32_t total_steps;
        float period;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(emulation_progress_stat, current, total_steps, period, channel);

    struct core_info {
        uint32_t n_channels = 11;
        uint32_t efi_lenght = 13;
        uint32_t load_overhead = 2;
        uint32_t stop_duration = 1;
        uint32_t fixed_core_overhead = 4;
    };

    struct program_info {
        uint32_t fixed_portion;
        uint32_t per_channel_portion;
    };

    typedef enum {
        core_iom_input = 0,
        core_iom_output = 1,
        core_iom_memory = 2
    } core_iom_type;

    static std::map<std::string, core_iom_type> core_iom_type_translator = {
        {"input", core_iom_input},
        {"output", core_iom_output},
        {"memory", core_iom_memory}
    };

    struct core_iom {
        core_iom_type type;
        std::vector<uint32_t> address;
        bool common_io;
    };

    struct fcore_program{
        std::vector<uint32_t> binary;
        program_info program_length;
    };
}


#endif //PROGRAM_METADATA_HPP
