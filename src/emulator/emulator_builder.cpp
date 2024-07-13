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

#include "emulator/emulator_builder.hpp"

fcore::emulator_builder::emulator_builder(bool dbg) {
    debug_autogen = dbg;
}

nlohmann::json fcore::emulator_builder::process_interconnects(
        const std::vector<nlohmann::json> &input_connections,
        const std::vector<nlohmann::json> &output_connections,
        std::set<std::string> memories
) {
    nlohmann::json result;

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
                result[item["destination_input"]] = spec;
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
                result[output_name] = spec;
            }
        }
    }
    return result;
}

nlohmann::json fcore::emulator_builder::process_ioms(
        const nlohmann::json &interconnect_io,
        const nlohmann::json &inputs,
        const nlohmann::json &outputs,
        const nlohmann::json &memory_init_specs,
        std::set<std::string> memories
        ) {

    nlohmann::json result = interconnect_io;
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
        result[item["name"]] = spec;
    }


    for(auto &item: memory_init_specs){
        std::string memory_name= item["name"];
        if(!result.contains(memory_name)){
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
            result[item["name"]] = spec;
        }
    }


    uint32_t mem_progressive = 63;
    while(assigned_outputs.contains(mem_progressive)|| assigned_inputs.contains(mem_progressive)) mem_progressive--;

    for(auto &item:memories){
        if(!result.contains(item)){
            nlohmann::json spec;
            spec["type"] = "memory";
            std::vector<uint32_t> addrs = {mem_progressive};
            assigned_outputs.insert(mem_progressive);
            spec["address"]  = addrs;
            result[item] = spec;
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

        std::string dbg = item.dump();
        if(!assigned_outputs.contains(addrs[0])){
            spec["address"]  = addrs;
            if(!memory_names.contains(item["name"])){
                result[item["name"]] = spec;
            } else{
                result[item["name"]]["address"] = addrs;
            }
        }
    }

    auto dbg_res = result.dump();

    return result;
}


std::vector<uint32_t> fcore::emulator_builder::compile_program(
        const nlohmann::json &core_info,
        const emulator::emulator_core& core_spec,
        const std::vector<nlohmann::json> &input_connections,
        const std::vector<nlohmann::json> &output_connections,
        std::set<io_map_entry> &am
) {

    std::set<std::string> memories = core_spec.program.io.memories;

    auto interconnect_io = process_interconnects(input_connections, output_connections, memories);

    nlohmann::json dma_io = process_ioms(interconnect_io, core_info["inputs"], core_info["outputs"],core_info["memory_init"], memories);

    std::vector<std::string> content = {core_spec.program.content};

    auto headers = core_spec.program.headers;

    fcore_cc compiler(content, headers);
    compiler.set_dma_map(dma_io);
    bool result = compiler.compile();

    length_info = compiler.get_program_info();

    if(!result){
        throw std::runtime_error(compiler.get_errors());
    }
    auto program = compiler.get_executable();

    if(debug_autogen){
        if(!std::filesystem::exists("autogen")) std::filesystem::create_directories("autogen");

        std::string program_content = core_spec.program.content;
        std::string core_name = core_spec.id;
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


fcore::efi_implementation_t fcore::emulator_builder::get_efi_implementation(const std::string &s) {
    efi_implementation_t val;
    if(s=="efi_trig"){
        val = efi_trig;
    } else if(s=="efi_sort"){
        val = efi_sort;
    } else if(s=="efi_none"){
        val = efi_none;
    } else {
        val = efi_none;
    }
    return val;
}

fcore::comparator_type_t fcore::emulator_builder::get_comparator_type(const std::string &s) {
    comparator_type_t val;
    if(s=="full"){
        val = comparator_full;
    } else if(s=="reducing"){
        val = comparator_reducing;
    } else if(s=="none"){
        val = comparator_none;
    } else {
        val = comparator_none;
    }
    return val;
}

std::vector<uint32_t> fcore::emulator_builder::sanitize_program(const std::vector<uint32_t>&  raw_prog) {
    std::vector<uint32_t> program;
    int section = 0;

    for(auto &instr:raw_prog){
        if(section == 2){
            program.push_back(instr);
        }
        if(instr == fcore::fcore_opcodes["stop"]){
            section++;
        }
    }
    return program;
}

std::set<fcore::io_map_entry> fcore::emulator_builder::read_io_map(const std::vector<uint32_t> &raw_prog) {
    std::set<fcore::io_map_entry>ret;
    int section = 0;

    for(auto &instr:raw_prog){
        if(section == 1 && instr != fcore::fcore_opcodes["stop"]){
            auto io_addr = instr  & 0xFFFF;
            auto core_addr =( instr & 0xFFFF0000) >>16;
            ret.emplace(io_addr, core_addr, "");
        }
        if(instr == fcore::fcore_opcodes["stop"]){
            section++;
        }
        if(section==2) break;
    }
    return ret;
}
