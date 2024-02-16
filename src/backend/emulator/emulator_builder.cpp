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

#include "backend/emulator/emulator_builder.hpp"


emulator_metadata emulator_builder::load_json_program(const nlohmann::json &core_info,
                                                      const std::vector<nlohmann::json> &input_connections,
                                                      const std::vector<nlohmann::json> &output_connections,
                                                      std::set<io_map_entry> &am
                             ) {
    emulator_metadata metadata;


    std::shared_ptr<ll_ast_node> ast;
    if(core_info["program"].contains("filename")){
        auto p = core_info["program"];
        std::ifstream stream;

        bin_loader_input_type_t in_type;
        std::string file_path = p["filename"];
        if(!std::filesystem::is_regular_file(file_path)){
            std::string core_id = core_info["id"];
            throw std::runtime_error("Invalid program file for core: " + core_id);
        }
        if(p["type"] == "mem") {
            stream.open(file_path);
            in_type = bin_loader_mem_input;
        } else if(p["type"] == "hex") {
            stream.open(file_path, std::ifstream::binary);
            in_type = bin_loader_hex_input;
        } else{
            throw std::runtime_error("Unknown program type for core: " + nlohmann::to_string(core_info["id"]));
        }
        binary_loader dis = binary_loader(stream, in_type);
        metadata.io_map = dis.get_io_mapping();
        metadata.io_remapping_active = dis.is_io_mapped();
        ast = dis.get_ast();

    } else {
        auto program = compile_programs(core_info, input_connections, output_connections, am);

        binary_loader dis(program);
        metadata.io_map = dis.get_io_mapping();
        metadata.io_remapping_active = dis.is_io_mapped();
        ast = dis.get_ast();
    }

    instruction_stream program_stream = instruction_stream_builder::build_stream(ast);

    std::vector<int> io_res;
    stream_pass_manager sman(io_res,0);
    sman.set_enabled_passes({false, false, true, true, true,false, true});
    program_stream = sman.process_stream(program_stream);

    auto ch = core_info["channels"];
    metadata.active_channels = ch;

    metadata.emu = std::make_shared<emulator>(program_stream, ch, core_info["id"]);
    if(core_info.contains("options")){
        auto opt = core_info["options"];
        metadata.efi_implementation = opt["efi_implementation"];
        metadata.comparator_type = opt["comparators"];
        metadata.emu->set_comparator_type(metadata.comparator_type);
    }

    if(core_info.contains("order")){
        if(ordering_style==implicit_ordering){
            throw std::runtime_error("Mixing of explicit and implicit cores ordering is not allowed");
        }
        cores_ordering[core_info["order"]] = core_info["id"];
        ordering_style = explicit_ordering;
    } else {
        if(ordering_style==explicit_ordering){
            throw std::runtime_error("Mixing of explicit and implicit cores ordering is not allowed");
        }
        ordering_style = implicit_ordering;

        cores_ordering[implicit_order_idx] =  core_info["id"];
        implicit_order_idx++;
    }

    clear_dma_io();
    return metadata;
}

void emulator_builder::process_interconnects(
        const std::vector<nlohmann::json> &input_connections,
        const std::vector<nlohmann::json> &output_connections,
        std::set<std::string> memories
) {
    for(auto  &conn:input_connections){
        if(conn.contains("channels")){
            for(auto &item:conn["channels"]){
                std::string  dma_name = item["destination_input"];
                nlohmann::json spec;
                spec["type"] = "input";
                std::vector<uint32_t> addrs;
                int transfer_length = 1;
                if(item.contains("length")){
                    std::string transfer_type = item["type"];
                    if(transfer_type == "2d_vector_transfer"){
                        transfer_length = item["stride"];
                    } else if(transfer_type == "scatter_transfer"){
                        transfer_length = item["length"];
                    }
                }

                uint32_t addr_base = item["destination"]["register"];
                for(int i = 0; i< transfer_length; i++){
                    assigned_inputs.insert(addr_base+i);
                    addrs.push_back(addr_base+i);
                }
                spec["address"]  = addrs;
                dma_io[item["destination_input"]] = spec;
            }
        }
    }

    for(auto &conn:output_connections){
        if(conn.contains("channels")){
            for(auto &item:conn["channels"]){
                nlohmann::json spec;
                std::string output_name = item["source_output"];
                if(memories.contains(output_name)){
                    spec["type"] = "memory";
                    memory_names.insert(output_name);
                } else {
                    spec["type"] = "output";
                }
                std::vector<uint32_t> addrs;
                int transfer_length = 1;
                if(item.contains("length")){
                    std::string transfer_type = item["type"];
                    if(transfer_type == "2d_vector_transfer"){
                        transfer_length = item["stride"];
                    } else if(transfer_type == "gather_transfer"){
                        transfer_length = item["length"];
                    }
                }
                uint32_t addr_base = item["source"]["register"];
                for(int i = 0; i< transfer_length; i++){
                    assigned_outputs.insert(addr_base+i);
                    addrs.push_back(addr_base+i);
                }
                spec["address"]  = addrs;
                dma_io[output_name] = spec;
            }
        }
    }

}

void emulator_builder::process_ioms(
        const nlohmann::json &inputs,
        const nlohmann::json &outputs,
        const nlohmann::json &memory_init_specs,
        std::set<std::string> memories
        ) {

    for(auto &item: inputs){
        nlohmann::json spec;
        spec["type"] = "input";
        std::vector<uint32_t> addrs;
        if(item["register_type"] == "explicit_vector"){
            int base_addr = item["reg_n"];
            for(uint32_t i = 0; i<item["vector_labels"].size(); i++){
                addrs.push_back(base_addr + i);
            }
        } else {
            addrs.push_back(item["reg_n"]);
        }

        spec["address"]  = addrs;

        assigned_inputs.insert(addrs.begin(), addrs.end());
        dma_io[item["name"]] = spec;
    }


    for(auto &item: memory_init_specs){
        std::string memory_name= item["name"];
        if(!dma_io.contains(memory_name)){
            nlohmann::json spec;
            spec["type"] = "memory";
            std::vector<uint32_t> addrs;
            if(item["reg_n"].is_array()) {
                for(const auto &r_a:item["reg_n"]) addrs.push_back(r_a);
            } else {
                addrs.push_back(item["reg_n"]);
            }
            spec["address"]  = addrs;
            assigned_inputs.insert(addrs.begin(), addrs.end());
            dma_io[item["name"]] = spec;
        }
    }


    uint32_t mem_progressive = 63;
    while(assigned_outputs.contains(mem_progressive)|| assigned_inputs.contains(mem_progressive)) mem_progressive--;

    for(auto &item:memories){
        if(!dma_io.contains(item)){
            nlohmann::json spec;
            spec["type"] = "memory";
            std::vector<uint32_t> addrs = {mem_progressive};
            assigned_outputs.insert(mem_progressive);
            spec["address"]  = addrs;
            dma_io[item] = spec;
            memory_names.insert(item);
            while(assigned_outputs.contains(mem_progressive)|| assigned_inputs.contains(mem_progressive)) mem_progressive--;
        }
    }

    for(auto &item:outputs){
        nlohmann::json spec;
        spec["type"] = "output";
        std::vector<uint32_t> addrs;
        if(item["reg_n"].is_array()){
            for(const auto &val:item["reg_n"]) addrs.push_back(val);
        } else {
            addrs = {item["reg_n"]};
        }

        if(!assigned_outputs.contains(addrs[0])){
            spec["address"]  = addrs;
            if(!memory_names.contains(item["name"])){
                dma_io[item["name"]] = spec;
            } else{
                dma_io[item["name"]]["address"] = addrs;
            }
        }
    }

}


std::vector<uint32_t> emulator_builder::compile_programs(const nlohmann::json &core_info,
                                        const std::vector<nlohmann::json> &input_connections,
                                        const std::vector<nlohmann::json> &output_connections,
                                        std::set<io_map_entry> &am
) {

    std::set<std::string> memories = core_info["program"]["build_settings"]["io"]["memories"];

    process_interconnects(input_connections, output_connections, memories);
    process_ioms(core_info["inputs"], core_info["outputs"],core_info["memory_init"], memories);

    std::vector<std::string> content = {core_info["program"]["content"]};
    fcore_cc compiler(content);
    compiler.set_dma_map(dma_io);
    compiler.compile();

    auto program = compiler.get_executable();

    if(debug_autogen){
        if(!std::filesystem::exists("autogen")) std::filesystem::create_directories("autogen");

        std::string program_content = core_info["program"]["content"];
        std::string core_name = core_info["id"];
        std::ofstream ofs("autogen/" + core_name + "_dma_io.json");
        ofs<<dma_io;

        std::ofstream ofs2("autogen/" + core_name + "_src.c");
        ofs2<<program_content;

        compiler.write_verilog_memfile("autogen/"+core_name+ ".mem");

        fcore_dis dis_engine(compiler.get_executable());
        dis_engine.write_disassembled_program("autogen/"+core_name+ ".s");
    }


    am = compiler.get_io_map();

    return program;
}

emulator_builder::emulator_builder(bool dbg) {
    debug_autogen = dbg;
}
