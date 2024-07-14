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

std::unordered_map<std::string, fcore::core_iom> fcore::emulator_builder::process_interconnects(
        const std::vector<emulator::emulator_interconnect> &input_connections,
        const std::vector<emulator::emulator_interconnect> &output_connections,
        std::set<std::string> memories
) {
    std::unordered_map<std::string, core_iom> result;

    for(auto  &conn:input_connections){
        for(auto &item:conn.channels){
            std::string  dma_name = item.destination.io_name;
            core_iom spec;
            spec.type = core_iom_input;
            std::vector<uint32_t> addrs;
            uint32_t transfer_length = item.length;

            if(item.type == emulator::dma_link_scatter){
                transfer_length = 1;
            } else if(item.type == emulator::dma_link_2d_vector){
                transfer_length = item.stride;
            }

            uint32_t addr_base = item.destination.address[0];
            for(int i = 0; i< transfer_length; i++){
                assigned_inputs.insert(addr_base+i);
                addrs.push_back(addr_base+i);
            }
            spec.address  = addrs;
            result[item.destination.io_name] = spec;
        }
    }

    for(auto &conn:output_connections){
        for(auto &item:conn.channels){
            core_iom spec;
            std::string output_name = item.source.io_name;
            if(memories.contains(output_name)){
                spec.type = core_iom_memory;
                memory_names.insert(output_name);
            } else {
                spec.type = core_iom_output;
            }
            std::vector<uint32_t> addrs;
            uint32_t transfer_length = item.length;

            if(item.type == emulator::dma_link_gather){
                transfer_length = 1;
            } else if(item.type == emulator::dma_link_2d_vector){
                transfer_length = item.stride;
            }

            uint32_t addr_base = item.source.address[0];
            for(int i = 0; i< transfer_length; i++){
                assigned_outputs.insert(addr_base+i);
                addrs.push_back(addr_base+i);
            }
            spec.address  = addrs;
            result[output_name] = spec;
        }
    }
    return result;
}

std::unordered_map<std::string, fcore::core_iom> fcore::emulator_builder::process_ioms(
        const std::unordered_map<std::string, fcore::core_iom> &interconnect_io,
        std::vector<emulator::emulator_input_specs> inputs,
        std::vector<emulator::emulator_output_specs> outputs,
        std::vector<emulator::emulator_memory_specs> memory_init_specs,
        std::set<std::string> memories
        ) {

    std::unordered_map<std::string, fcore::core_iom> result = interconnect_io;
    for(auto &item: inputs){
        core_iom spec;
        spec.type = core_iom_input;
        spec.address  = item.address;
        assigned_inputs.insert(item.address.begin(), item.address.end());
        result[item.name] = spec;
    }


    for(auto &item: memory_init_specs){
        if(!result.contains(item.name)){
            core_iom spec;
            spec.type = core_iom_memory;
            spec.address  = item.address;
            memory_names.insert(item.name);
            assigned_inputs.insert(item.address.begin(), item.address.end());
            result[item.name] = spec;
        }
    }


    uint32_t mem_progressive = 63;
    while(assigned_outputs.contains(mem_progressive)|| assigned_inputs.contains(mem_progressive)) mem_progressive--;

    for(auto &item:memories){
        if(!result.contains(item)){
            core_iom spec;
            spec.type = core_iom_memory;
            std::vector<uint32_t> addrs = {mem_progressive};
            assigned_outputs.insert(mem_progressive);
            spec.address  = addrs;
            result[item] = spec;
            memory_names.insert(item);
            while(assigned_outputs.contains(mem_progressive)|| assigned_inputs.contains(mem_progressive)) mem_progressive--;
        }
    }

    for(auto &item:outputs){
        core_iom spec;
        spec.type = core_iom_output;
        // TODO: ass support for vector outputs on different addresses?
        if(!assigned_outputs.contains(item.address[0])){
            spec.address  = item.address;
            if(!memory_names.contains(item.name)){
                result[item.name] = spec;
            } else{
                result[item.name].address = item.address;
            }
        }
    }

    return result;
}


std::vector<uint32_t> fcore::emulator_builder::compile_program(
        const emulator::emulator_core& core_spec,
        const std::vector<emulator::emulator_interconnect> &input_connections,
        const std::vector<emulator::emulator_interconnect> &output_connections,
        std::set<io_map_entry> &am
) {

    std::set<std::string> memories = core_spec.program.io.memories;

    auto interconnect_io = process_interconnects(input_connections, output_connections, memories);

    std::unordered_map<std::string, core_iom> dma_io = process_ioms(interconnect_io, core_spec.inputs, core_spec.outputs,core_spec.memories, memories);

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
        ofs << fcore_cc::dump_iom_map(dma_io);

        std::ofstream ofs2("autogen/" + core_name + "_src.c");
        ofs2<<program_content;

        compiler.write_verilog_memfile("autogen/"+core_name+ ".mem");

        fcore_dis dis_engine(compiler.get_executable());
        dis_engine.write_disassembled_program("autogen/"+core_name+ ".s");
    }

    assigned_inputs.clear();
    assigned_outputs.clear();
    memory_names.clear();
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
