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
// limitations under the License.05/07/2021.

#include "backend/emulator_builder.hpp"


emulator_metadata emulator_builder::load_program(const nlohmann::json &core_info, const nlohmann::json &input_connections,
                             const nlohmann::json &output_connections) {
    emulator_metadata ret;

    nlohmann::json dma_io;
    for(auto &item:input_connections["channels"]){
        nlohmann::json spec;
        spec["type"] = "input";
        std::vector<uint32_t> addrs;
        for(int i = 0; i< item["length"]; i++){
            uint32_t addr_base = item["destination"]["register"];
            addrs.push_back(addr_base+i);
        }
        spec["address"]  = addrs;
        dma_io[item["destination_input"]] = spec;
    }

    for(auto &item:output_connections["channels"]){
        nlohmann::json spec;
        spec["type"] = "output";
        std::vector<uint32_t> addrs;
        for(int i = 0; i< item["length"]; i++){
            uint32_t addr_base = item["source"]["register"];
            addrs.push_back(addr_base+i);
        }
        spec["address"]  = addrs;
        dma_io[item["destination_input"]] = spec;
    }


    // TODO: build program

    emulator_metadata metadata;
    std::vector<uint32_t> program;

    binary_loader dis(program);
    metadata.io_map = dis.get_io_mapping();
    metadata.io_remapping_active = dis.is_io_mapped();
    std::shared_ptr<ll_ast_node> ast = dis.get_ast();
    instruction_stream program_stream = instruction_stream_builder::build_stream(ast);


    std::vector<int> io_res;
    stream_pass_manager sman(io_res,0);
    sman.set_enabled_passes({false, false, true, true, true,false, true});
    program_stream = sman.process_stream(program_stream);

    auto ch = core_info["channels"];
    metadata.active_channels = core_info["channels"];

    metadata.emu = std::make_shared<emulator>(program_stream, ch, core_info["id"]);

    return metadata;
}
