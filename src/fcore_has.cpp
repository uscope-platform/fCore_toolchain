// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#include "fcore_has.hpp"



std::tuple<std::vector<uint32_t>, int> fCore_has_embeddable_s(const std::string& content){
    std::string ret_val;
    std::istringstream stream(content);
    std::vector<std::string> include_files;
    auto *iss = new std::istringstream(REGISTER_DEFINITION_STRING);
    std::vector<std::istream*> includes = {iss};

    fcore_has assembler(stream,includes);
    std::vector<uint32_t> hex = assembler.get_hexfile(false);
    unsigned int int_size = assembler.get_program_size();
    std::cout<<int_size<<std::endl;
    std::tuple<std::vector<uint32_t>, int> ret(hex, int_size);
    return ret;
}

void fCore_has_embeddable_f(const char * path, uint32_t *hex, int *hex_size){
    std::string ret_val;
    std::ifstream stream;
    stream.open(path);
    std::vector<std::string> include_files;
    auto *iss = new std::istringstream(REGISTER_DEFINITION_STRING);
    std::vector<std::istream*> includes = {iss};
    // parse target file

    fcore_has assembler(stream,includes);
    std::vector<uint32_t> data = assembler.get_hexfile(false);
    unsigned int int_size = assembler.get_program_size();
    memcpy(hex_size, &int_size, sizeof(int));
    for(int i = 0; i < assembler.get_program_size(); i++){
        hex[i] = data[i];
    }

}


fcore_has::fcore_has(std::istream &input, std::vector<std::istream *> &includes) {
    construct_assembler(input, includes);
}

fcore_has::fcore_has(std::istream &input, const std::vector<std::string>& include_files, const std::string& include_directory) {

    std::vector<std::istream*> includes = process_includes(include_files, include_directory);

    construct_assembler(input, includes);
}


void fcore_has::construct_assembler(std::istream &input, std::vector<std::istream*> &includes) {
    variable_map tmp_map;
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>(tmp_map);
    // Parse includes files
    std::shared_ptr<ll_ast_node> includes_ast;

    for(auto &item:includes){
        asm_language_parser include_parser(*item, variables_map);
        std::shared_ptr<ll_ast_node> tmp_ast = include_parser.AST;
        if(includes_ast != nullptr){
            includes_ast->append_content(tmp_ast->get_content());
        } else{
            includes_ast = tmp_ast;
        }
        delete item;
    }

    try{
        asm_language_parser target_parser(input, variables_map);
        AST = target_parser.AST;
        //merge the two together (right now just concatenate them)
        if(includes_ast != nullptr)
            AST->prepend_content(includes_ast->get_content());


        manager = create_ll_pass_manager();
        manager.run_morphing_passes(AST);

        instruction_stream program_stream = instruction_stream_builder::build_stream(AST);

        stream_pass_manager sman;
        program_stream = sman.process_stream(program_stream);

        writer.process_stream(program_stream, true);



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

std::vector<std::string> fcore_has::get_verilog_memfile() {
    return writer.generate_mem();
}

uint32_t fcore_has::get_inst_count() {
    int program_lenght = manager.analysis_passes["instruction_counting"]->get_analysis_result()[0];
    float program_runtime = (float) program_lenght*0.01f;
    std::cout << "The compiled program is " << program_lenght << "instructions long"<< std::endl;
    std::cout << "Runtime at the standard frequency of 100 MHz will be of " << program_runtime << " µS"<< std::endl;
    return 0;
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
