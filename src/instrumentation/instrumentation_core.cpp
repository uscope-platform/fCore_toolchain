

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

#include "instrumentation/instrumentation_core.hpp"

namespace fcore{
    void  instrumentation_core::start_event(std::string point_name, bool g) {
        instrumentation_point point;
        point.start_time = std::chrono::high_resolution_clock::now();
        point.point_name = std::move(point_name);
        point.order = order;
        point.global = g;
        point.phase = phase;
        events_log[active_program].push_back(point);
        order++;
    }

    void instrumentation_core::end_event(const std::string& point_name) {

        for(auto &e:events_log[active_program]){
            if(e.point_name == point_name) e.end_time = std::chrono::high_resolution_clock::now();
        }
        events_log[active_program];
    }

    void instrumentation_core::set_active_program(const std::string &s) {
        active_program = s;
        order = 0;
    }

    nlohmann::json instrumentation_core::dump() {
        nlohmann::json ret_val;
        for(auto &item:events_log){
            nlohmann::json program_obj;
            for(auto &event:item.second){
                if(event.global){
                    if(!ret_val.contains(event.phase)) ret_val[event.phase] = nlohmann::json();
                    ret_val[event.phase][event.point_name] = nlohmann::json();
                    ret_val[event.phase][event.point_name]["order"] = event.order;
                    ret_val[event.phase][event.point_name]["duration"] = std::chrono::duration_cast<std::chrono::microseconds>(event.end_time-event.start_time).count()*1e-6;
                } else {
                    if(!program_obj.contains(event.phase)) program_obj[event.phase] = nlohmann::json();
                    program_obj[event.phase][event.point_name] = nlohmann::json();
                    program_obj[event.phase][event.point_name]["order"] = event.order;
                    program_obj[event.phase][event.point_name]["duration"] = std::chrono::duration_cast<std::chrono::microseconds>(event.end_time-event.start_time).count()*1e-6;
                }

            }
            ret_val[item.first] = program_obj;
        }
        return ret_val;
    }
}

