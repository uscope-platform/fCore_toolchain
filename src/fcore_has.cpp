// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fcore_has.hpp"


void fCore_has_embeddable_f(const char * path, uint32_t *hex, int *hex_size, bool print_debug){
    std::string ret_val;
    std::ifstream stream;
    stream.open(path);
    std::vector<std::string> include_files;
    // parse target file

    fcore::fcore_has assembler(stream, 0, print_debug);
    std::vector<uint32_t> data = assembler.get_hexfile(false);
    unsigned int int_size = assembler.get_program_size();
    memcpy(hex_size, &int_size, sizeof(int));
    for(int i = 0; i < assembler.get_program_size(); i++){
        hex[i] = data[i];
    }
}

namespace fcore{

    fcore_has::fcore_has(std::istream &input, int dump_ast_level,bool print_debug) {
        construct_assembler(input, dump_ast_level,print_debug);
    }


    void fcore_has::construct_assembler(std::istream &input, int dump_ast_level, bool print_debug) {
        variable_map tmp_map;
        std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>(tmp_map);

        try{
            asm_language_parser target_parser(input, variables_map);

            std::shared_ptr<instrumentation_core> ic = nullptr;

            std::vector<int> io_res;
            stream_pass_manager sman(io_res, dump_ast_level, ic);
            sman.set_enabled_passes({true, false, false, false, true, true, true, false ,false}); // do not mess with constants in assembly

            instruction_stream program_stream = sman.process_stream(target_parser.program);

            if(dump_ast_level>0) dump["stream"] = sman.get_dump();

            writer.process_stream(program_stream, print_debug);

        } catch(std::runtime_error &e){
            error_code = e.what();
        }

    }


    std::vector<std::istream*>
    fcore_has::process_includes(const std::vector<std::string> &include_files, const std::string &include_directory) {
        std::vector<std::istream*> input_streams;

        for(auto const &item:include_files){
            std::string name = include_directory;
            name += item;
            auto *ifstr = new std::ifstream(name);
            input_streams.push_back(ifstr);
        }

        return input_streams;
    }

    std::vector<uint32_t> fcore_has::get_hexfile(bool endian_swap) {
        return writer.generate_hex(endian_swap);
    }

    void fcore_has::write_hexfile(const std::string& ouput_file) {
        writer.write_hex_file(ouput_file);
    }

    void fcore_has::write_verilog_memfile(const std::string& ouput_file) {
        writer.write_mem_file(ouput_file);
    }


    uint32_t fcore_has::get_program_size() {
        return writer.get_program_size();
    }

    std::string fcore_has::get_errors() {
        return  error_code;
    }

    void fcore_has::write_json(const std::string &output_file) {
        nlohmann::json j;
        j["error_code"] = error_code;
        if(error_code.empty()){
            j["compiled_program"] = writer.generate_hex(false);
        } else{
            j["compiled_program"] = {};
        }
        std::string str = j.dump();
        std::ofstream ss(output_file);
        ss<<str;
        ss.close();
    }

    std::vector<uint32_t> fcore_has::get_raw_code() {
        return writer.get_code();
    }

    std::vector<uint32_t> fcore_has::get_executable() {
        return writer.get_executable();
    }

}