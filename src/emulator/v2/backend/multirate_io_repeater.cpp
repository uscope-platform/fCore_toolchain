

//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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

#include "emulator/v2/backend/multirate_io_repeater.hpp"

void fcore::emulator_v2::multirate_io_repeater::add_output(const endpoint_descriptor &source, uint32_t addr,
    uint32_t channel, uint32_t value) {
    initialized_endpoints[source.core_name][source.port_name] = true;
    working_map[source.core_name][channel][addr] = value;
}

uint32_t fcore::emulator_v2::multirate_io_repeater::
get_output(const endpoint_descriptor &source, const endpoint_descriptor &dest,  uint32_t addr, uint32_t channel) {
    if(!initialized_endpoints[source.core_name][source.port_name]) {
        auto val =  initial_input_values[dest.core_name][dest.port_name];
        return val;
    } else {
        return working_map[source.core_name][channel][addr];
    }

}
