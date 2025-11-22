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
        external_input = 2,
        random_input = 3,
        waveform_input = 4
    } source_type_t;

    struct square_wave_parameters {
        std::vector<double> v_on;
        std::vector<double> v_off;
        std::vector<double> period;
        std::vector<double> t_delay;
        std::vector<double> t_on;
    };

    struct sine_wave_parameters {
        std::vector<double> dc_offset;
        std::vector<double> amplitude;
        std::vector<double> frequency;
        std::vector<double> phase;
    };

    struct triangle_wave_parameters {
        std::vector<double> dc_offset;
        std::vector<double> amplitude;
        std::vector<double> frequency;
        std::vector<double> phase;
        std::vector<double> duty;
    };


    typedef enum {
        type_float=0,
        type_uint=1
    } register_data_type;

    struct iom_metadata {
        friend bool operator==(const iom_metadata &lhs, const iom_metadata &rhs) {
            return lhs.io_address == rhs.io_address
                   && lhs.width == rhs.width
                   && lhs.is_signed == rhs.is_signed
                   && lhs.is_common_io == rhs.is_common_io;
        }

        friend bool operator!=(const iom_metadata &lhs, const iom_metadata &rhs) {
            return !(lhs == rhs);
        }

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
        std::variant<square_wave_parameters, sine_wave_parameters, triangle_wave_parameters> waveform_parameters;
    };

    struct deployer_interconnect_slot {
        friend bool operator==(const deployer_interconnect_slot &lhs, const deployer_interconnect_slot &rhs) {
            bool ret = true;
            ret &= lhs.source_io_address == rhs.source_io_address;
            ret &= lhs.destination_bus_address == rhs.destination_bus_address;
            ret &= lhs.source_channel == rhs.source_channel;
            ret &= lhs.destination_channel == rhs.destination_channel;
            ret &= lhs.source_id == rhs.source_id;
            ret &= lhs.source_name == rhs.source_name;
            ret &= lhs.type == rhs.type;
            ret &= lhs.metadata == rhs.metadata;

            ret &= lhs.destination_id == rhs.destination_id;
            ret &= lhs.destination_name == rhs.destination_name;
            return ret;
        }

        friend bool operator!=(const deployer_interconnect_slot &lhs, const deployer_interconnect_slot &rhs) {
            return !(lhs == rhs);
        }

        uint16_t source_io_address;
        uint16_t destination_bus_address;
        uint16_t source_channel;
        uint16_t destination_channel;
        std::string source_id;
        std::string source_name;
        std::string destination_id;
        std::string destination_name;
        std::string type;
        iom_metadata metadata;
    };

    struct memory_init_value {
        friend bool operator==(const memory_init_value &lhs, const memory_init_value &rhs) {
            bool ret = true;
            if(std::holds_alternative<std::vector<float>>(lhs.value) && std::holds_alternative<std::vector<uint32_t>>(rhs.value) ) return false;
            if(std::holds_alternative<std::vector<float>>(rhs.value) && std::holds_alternative<std::vector<uint32_t>>(lhs.value) ) return false;
            ret &= lhs.address== rhs.address;
            if(std::holds_alternative<std::vector<float>>(lhs.value)) {
                ret &= std::get<std::vector<float>>(lhs.value) == std::get<std::vector<float>>(rhs.value);
            } else {
                ret &= std::get<std::vector<uint32_t>>(lhs.value) == std::get<std::vector<uint32_t>>(rhs.value);
            }
            return ret;
        }

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
        uint32_t n_outputs;
    };

    struct deployment_options {
        uint64_t rom_address;
        uint64_t control_address;
        bool has_reciprocal;
    };

    static std::map<std::string, source_type_t > source_type_map = {
        {"constant", constant_input},
        {"file", time_series_input},
        {"series", time_series_input},
        {"external", external_input},
        {"random", random_input},
        {"waveform", waveform_input}
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
        std::map<std::string, uint32_t> inputs;


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
