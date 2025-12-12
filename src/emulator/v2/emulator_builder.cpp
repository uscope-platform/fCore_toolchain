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

#include "emulator/v2/emulator_builder.hpp"

namespace fcore::emulator_v2{

    emulator_builder::emulator_builder(bool dbg, const std::shared_ptr<bus_allocator> &bus_engine)  {
        debug_autogen = dbg;
        engine = bus_engine;
    }

    std::map<std::string, core_iom> emulator_builder::process_ioms(
            const std::vector<emulator_interconnect> &input_connections,
            const std::vector<emulator_interconnect> &output_connections,
            std::vector<emulator_input_specs> inputs,
            std::vector<emulator_output_specs> outputs,
            std::vector<emulator_memory_specs> memory_init_specs,
            const std::set<std::string>& memories
    ) {


        std::map<std::string, core_iom> result;

        std::set<uint32_t> assigned_inputs;
        std::set<uint32_t> assigned_outputs;
        std::set<std::string> memory_names;

        //////////////////////////////////////////////////////////////
        //                        PROCESS INPUTS
        /////////////////////////////////////////////////////////////

        for(auto &item: inputs){
            core_iom spec;
            spec.type = core_iom_input;
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
                memory_names.insert(item.name);
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

        }

        return result;
    }


    fcore_program emulator_builder::compile_program(
            const emulator_core& core_spec,
            std::set<io_map_entry> &am
    ) {

        std::map<std::string, core_iom> dma_io = engine->get_dma_io(core_spec.id);
        std::vector<std::string> content = {core_spec.program.content};


        auto headers = core_spec.program.headers;

        fcore_program ret_val;
        if(core_spec.program.type==  prog_type_asm){
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
            if(instr == fcore_opcodes[opcode_stop]){
                section++;
            }
        }
        return program;
    }

    std::pair<fcore_program,std::set<io_map_entry>>  emulator_builder::compile_program_c(
            std::vector<std::string> &content,
            std::vector<std::string> &headers,
            std::map<std::string, core_iom> &dma_io,
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
            std::map<std::string, core_iom> &map,
            std::string core_name
    ) {
        std::map<std::string, std::vector<uint32_t>> io_map;

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
