

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

#ifndef FCORE_TOOLCHAIN_EMULATOR_INTERCONNECT_HPP
#define FCORE_TOOLCHAIN_EMULATOR_INTERCONNECT_HPP

#include <vector>
#include <cstdint>
#include <nlohmann/json.hpp>


namespace fcore::emulator {


    typedef enum {
        dma_link_scalar=0,
        dma_link_scatter=1,
        dma_link_gather=2,
        dma_link_vector=3,
        dma_link_2d_vector=4
    }dma_channel_type;

    static std::unordered_map<std::string, dma_channel_type > interconnect_type_map = {
            {"scalar_transfer", dma_link_scalar},
            {"scatter_transfer", dma_link_scatter},
            {"gather_transfer", dma_link_gather},
            {"vector_transfer", dma_link_vector},
            {"2d_vector_transfer", dma_link_2d_vector},
    };

    struct endpoint_specs{
        std::string io_name;
        std::vector<uint16_t> channel;
        std::vector<uint16_t> address;
    };

    struct dma_channel{
        endpoint_specs source;
        endpoint_specs destination;
        uint32_t length=1;
        uint32_t stride=0;
        dma_channel_type type = dma_link_scalar;
    };

    struct emulator_interconnect {
        std::string source_core_id;
        std::string destination_core_id;
        std::vector<dma_channel> channels;
    };

} // fcore

#endif //FCORE_TOOLCHAIN_EMULATOR_INTERCONNECT_HPP
