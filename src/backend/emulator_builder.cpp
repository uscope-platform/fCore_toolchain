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
    emulator_metadata metadata;

    nlohmann::json dma_io;
    if(input_connections.contains("channels")){
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
    }

    for(auto &item: core_info["inputs"]){
        nlohmann::json spec;
        spec["type"] = "input";
        std::vector<uint32_t> addrs = {item["reg_n"]};
        spec["address"]  = addrs;
        dma_io[item["name"]] = spec;
    }
    for(auto &item:core_info["outputs"]){
        nlohmann::json spec;
        spec["type"] = "output";
        std::vector<uint32_t> addrs = {item["reg_n"]};
        spec["address"]  = addrs;
        dma_io[item["name"]] = spec;
    }

    std::vector<std::string> content = {core_info["program"]["content"]};
    fcore_cc compiler(content);
    compiler.set_dma_map(dma_io);
    compiler.compile();

    auto program = compiler.get_executable();
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

    if(core_info.contains("options")){
        metadata.efi_implementation = core_info["options"]["efi_implementation"];
        metadata.comparator_type = core_info["options"]["comparators"];
        metadata.emu->set_comparator_type(metadata.comparator_type);
    }

    if(core_info.contains("order")){
        if(ordering_style==implicit_ordering){
            spdlog::critical("Mixing of explicit and implicit cores ordering is not allowed");
            exit(-1);
        }
        cores_ordering[core_info["order"]] = core_info["id"];
        ordering_style = explicit_ordering;
    } else {
        if(ordering_style==explicit_ordering){
            spdlog::critical("Mixing of explicit and implicit cores ordering is not allowed");
            exit(-1);
        }
        ordering_style = implicit_ordering;

        cores_ordering[implicit_order_idx] =  core_info["id"];
        implicit_order_idx++;
    }
    return metadata;
}
