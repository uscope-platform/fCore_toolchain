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

#include "emulator/v1/emulator_builder.hpp"

namespace fcore::emulator{

    emulator_builder::emulator_builder(bool dbg) {
        debug_autogen = dbg;
    }

    std::unordered_map<std::string, core_iom> emulator_builder::process_ioms(
            const std::vector<emulator::emulator_interconnect> &input_connections,
            const std::vector<emulator::emulator_interconnect> &output_connections,
            std::vector<emulator::emulator_input_specs> inputs,
            std::vector<emulator::emulator_output_specs> outputs,
            std::vector<emulator::emulator_memory_specs> memory_init_specs,
            const std::set<std::string>& memories
    ) {


        std::unordered_map<std::string, core_iom> result;

        std::set<uint32_t> assigned_inputs;
        std::set<uint32_t> assigned_outputs;
        std::set<std::string> memory_names;


        //////////////////////////////////////////////////////////////
        //                        PROCESS INTERCONNECTS
        /////////////////////////////////////////////////////////////
        for(auto  &conn:input_connections){
            for(auto &item:conn.channels){
                std::string  dma_name = item.destination.io_name;
                core_iom spec;
                spec.type = core_iom_input;
                std::vector<uint32_t> addrs;
                uint32_t transfer_length = item.length;

                if(item.type == emulator::dma_link_scatter || item.type == emulator::dma_link_vector){
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
                spec.common_io = false;
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

                if(item.type == emulator::dma_link_gather || item.type == emulator::dma_link_vector){
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
                spec.common_io = false;
                result[output_name] = spec;
            }
        }


        //////////////////////////////////////////////////////////////
        //                        PROCESS INPUTS
        /////////////////////////////////////////////////////////////

        for(auto &item: inputs){
            core_iom spec;
            spec.type = core_iom_input;
            spec.address  = item.address;
            assigned_inputs.insert(item.address.begin(), item.address.end());
            spec.common_io = false;
            result[item.name] = spec;
        }


        //////////////////////////////////////////////////////////////
        //                        PROCESS MEMORIES
        /////////////////////////////////////////////////////////////

        for(auto &item: memory_init_specs){
            if(!result.contains(item.name)){
                core_iom spec;
                spec.type = core_iom_memory;
                spec.address  = item.address;
                memory_names.insert(item.name);
                assigned_inputs.insert(item.address.begin(), item.address.end());
                spec.common_io = false;
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
                spec.common_io = false;
                result[item] = spec;
                memory_names.insert(item);
                while(assigned_outputs.contains(mem_progressive)|| assigned_inputs.contains(mem_progressive)) mem_progressive--;
            }
        }

        //////////////////////////////////////////////////////////////
        //                        PROCESS OUTPUTS
        /////////////////////////////////////////////////////////////

        for(auto &item:outputs){
            core_iom spec;
            spec.type = core_iom_output;
            // TODO: ass support for vector outputs on different addresses?
            if(!assigned_outputs.contains(item.address[0])){
                spec.address  = item.address;
                spec.common_io = false;
                if(!memory_names.contains(item.name)){
                    result[item.name] = spec;
                } else{
                    result[item.name].address = item.address;
                }
            }
        }

        return result;
    }


    fcore_program emulator_builder::compile_program(
            const emulator::emulator_core& core_spec,
            const std::vector<emulator::emulator_interconnect>& interconnect_spec,
            std::set<io_map_entry> &am
    ) {

        std::vector<emulator::emulator_interconnect> src = {};
        std::vector<emulator::emulator_interconnect> dst = {};
        for(const auto &ic:interconnect_spec){
            if(core_spec.id == ic.source_core_id) src.push_back(ic);
            if(core_spec.id == ic.destination_core_id) dst.push_back(ic);
        }

        std::set<std::string> memories = core_spec.program.io.memories;

        std::unordered_map<std::string, core_iom> dma_io = process_ioms(
                dst,
                src,
                core_spec.inputs,
                core_spec.outputs,
                core_spec.memories,
                memories
        );

        std::vector<std::string> content = {core_spec.program.content};


        auto headers = core_spec.program.headers;

        fcore_program ret_val;
        if(core_spec.program.type==  emulator::prog_type_asm){
            auto [prog, io_map] = compile_program_asm(content, headers, dma_io,  core_spec.id);
            am = io_map;
            ret_val = prog;
        } else {
            auto [prog, io_map] = compile_program_c(content, headers, dma_io,  core_spec.id);
            am = io_map;
            ret_val = prog;
        }

        if(debug_autogen){
            if(!std::filesystem::exists("autogen")) std::filesystem::create_directories("autogen");

            std::string program_content = core_spec.program.content;
            std::string core_name = core_spec.id;
            std::ofstream ofs("autogen/" + core_name + "_dma_io.json");
            ofs << fcore_cc::dump_iom_map(dma_io);

            std::ofstream ofs2("autogen/" + core_name + "_src.c");
            ofs2<<program_content;
        }


        return ret_val;
    }


    efi_implementation_t emulator_builder::get_efi_implementation(const std::string &s) {
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

    comparator_type_t emulator_builder::get_comparator_type(const std::string &s) {
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

    std::vector<uint32_t> emulator_builder::sanitize_program(const std::vector<uint32_t>&  raw_prog) {
        std::vector<uint32_t> program;
        int section = 0;

        for(auto &instr:raw_prog){
            if(section == code_section_index){
                program.push_back(instr);
            }
            if(instr == fcore_opcodes["stop"]){
                section++;
            }
        }
        return program;
    }

    std::pair<fcore_program,std::set<io_map_entry>>  emulator_builder::compile_program_c(
            std::vector<std::string> &content,
            std::vector<std::string> &headers,
            std::unordered_map<std::string, core_iom> &dma_io,
            std::string core_name
    ) {

        fcore_cc compiler(content, headers);
        compiler.set_profiler(profiler);
        compiler.set_dma_map(dma_io);
        bool result = compiler.compile();


        if(!result){
            throw std::runtime_error(compiler.get_errors());
        }

        if(debug_autogen){

            compiler.write_verilog_memfile("autogen/"+core_name+ ".mem");

            fcore_dis dis_engine(compiler.get_executable());
            dis_engine.write_disassembled_program("autogen/"+core_name+ ".s");
            std::ofstream ofs3("autogen/" + core_name + "_profiling.json");
            ofs3<<profiler->dump();
        }

        fcore_program ret_val;
        ret_val.binary = compiler.get_executable();
        ret_val.program_length = compiler.get_program_info();
        return {ret_val, compiler.get_io_map()};
    }

    std::pair<fcore_program,std::set<io_map_entry>>  emulator_builder::compile_program_asm(
            std::vector<std::string> &contents,
            std::vector<std::string> &inc,
            std::unordered_map<std::string, core_iom> &map,
            std::string core_name
    ) {
        std::unordered_map<std::string, std::vector<uint32_t>> io_map;

        std::set<io_map_entry> io_map_out;
        for(int i = 1; i<64; i++){
            auto var_name = "r" + std::to_string(i);
            io_map[var_name] = {};
            io_map[var_name].push_back(i);
            io_map_out.emplace(i, i, "o");
        }

        std::stringstream iss(contents[0]);
        fcore_has assembler(iss, false, io_map);

        fcore_program ret_val;
        ret_val.binary = assembler.get_executable();
        ret_val.program_length = assembler.get_program_info();

        return {ret_val, io_map_out};
    }
}
