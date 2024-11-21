

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

#ifndef FCORE_TOOLCHAIN_INSTRUMENTATION_CORE_HPP
#define FCORE_TOOLCHAIN_INSTRUMENTATION_CORE_HPP

#include <string>
#include <chrono>
#include <map>
#include <cstdint>
#include <nlohmann/json.hpp>


namespace fcore {

    struct instrumentation_point{
        std::string point_name;
        std::string phase;
        bool global;
        uint16_t order;
        std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> start_time;
        std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> end_time;

    };

    class instrumentation_core {

    public:
        void set_phase(std::string p) {phase = p;};
        void set_active_program(const std::string &s);
        void start_event(std::string point_name, bool global);
        void end_event(const std::string& point_name);
        nlohmann::json dump();
    private:
        std::string active_program;
        std::string phase;
        uint16_t order;
        std::map<std::string, std::vector<instrumentation_point>> events_log;
    };


}
#endif //FCORE_TOOLCHAIN_INSTRUMENTATION_CORE_HPP
