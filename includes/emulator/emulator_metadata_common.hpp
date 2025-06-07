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


#ifndef EMULATOR_METADATA_COMMON_HPP
#define EMULATOR_METADATA_COMMON_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>


#include "data_structures/common/program_metadata.hpp"

namespace fcore {

    typedef enum {
        constant_input = 0,
        time_series_input = 1,
        external_input = 2
    } source_type_t;

    typedef enum {
        type_float=0,
        type_uint=1
    } register_data_type;

    struct iom_metadata {
        std::vector<uint32_t> io_address = {0};
        register_data_type type;
        uint16_t width;
        bool is_signed;
        bool is_common_io = false;
    };

    struct deployed_core_inputs {
        std::string name;
        iom_metadata metadata;
        source_type_t source_type;
        std::vector<std::variant<std::vector<uint32_t>, std::vector<float>>> data;
        std::vector<uint32_t> address;
        std::vector<uint32_t> channel;
    };

    struct deployer_interconnect_slot {
        uint16_t source_io_address;
        uint16_t destination_bus_address;
        uint16_t source_channel;
        uint16_t destination_channel;
        std::string source_id;
        std::string type;
        iom_metadata metadata;
    };

    struct memory_init_value {
        std::vector<uint32_t>  address;
        std::variant<std::vector<float>, std::vector<uint32_t>> value;
    };

    struct deployed_program {
        std::string name;
        uint16_t index;
        uint32_t sampling_frequency;
        uint32_t n_channels;
        uint32_t order;
        fcore_program program;
        std::vector<deployed_core_inputs> inputs;
    };

    struct deployment_options {
        uint64_t rom_address;
        uint64_t control_address;
        bool has_reciprocal;
    };

    static std::unordered_map<std::string, source_type_t > source_type_map = {
        {"constant", constant_input},
        {"file", time_series_input},
        {"series", time_series_input},
        {"external", external_input},
    };


    class debug_checkpoint{
    public:
        std::string status;
        std::string core_name;
        uint32_t breakpoint;
        emulation_progress_stat progress;
        std::vector<uint32_t> memory_view;
        bool completed_round;
        std::string next_program;
        std::unordered_map<std::string, uint32_t> inputs;


    };


    inline bool operator==(const debug_checkpoint& lhs, const debug_checkpoint& rhs) {
        bool ret = true;

        ret &= lhs.core_name == rhs.core_name;
        ret &= lhs.breakpoint == rhs.breakpoint;
        ret &= lhs.memory_view == rhs.memory_view;
        ret &= lhs.inputs == rhs.inputs;
        ret &= lhs.completed_round == rhs.completed_round;
        ret &= lhs.next_program == rhs.next_program;
        ret &= lhs.progress.period == rhs.progress.period;
        ret &= lhs.progress.channel == rhs.progress.channel;
        ret &= lhs.progress.total_steps == rhs.progress.total_steps;
        ret &= lhs.progress.current == rhs.progress.current;
        ret &= lhs.status == rhs.status;

        return ret;
    }

    inline std::ostream& operator<<(std::ostream& os, const debug_checkpoint& cp){
        os <<"\n\tcore name: " << cp.core_name<< std::endl;
        os <<"\tstatus: " << cp.status<< std::endl;
        os <<"\tline: " << cp.breakpoint<< std::endl;

        os <<"\tcompleted round: " << (cp.completed_round ? "true" : "false")<< std::endl;
        os <<"\tnext program: " << cp.next_program<< std::endl;
        os <<"\tmemory view: ";
        for(auto &v:cp.memory_view){
            os << std::hex<< std::to_string(v);
            if(&v != &cp.memory_view.back()) os  << ", ";
        }

        os <<"\n\tinputs: ";
        for(auto &v:cp.inputs){
            os << v.first << " = " << v.second << "        ";
        }

        os <<"\n\tprogress" << std::endl;
        os << "\t\t period: " << cp.progress.period << std::endl;
        os << "\t\t channel: " << cp.progress.channel << std::endl;
        os << "\t\t total steps: " << cp.progress.total_steps << std::endl;
        os << "\t\t current: " << cp.progress.current << std::endl;

        return os;
    }
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(debug_checkpoint, status, core_name, breakpoint, progress, memory_view, completed_round, next_program, inputs )



}


#endif //EMULATOR_METADATA_COMMON_HPP
