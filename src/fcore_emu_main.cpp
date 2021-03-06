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



#include <iostream>
#include <string>
#include <filesystem>

#include "../third_party/CLI11.hpp"
#include "fcore_emu.hpp"

int main(int argc, char **argv) {
    CLI::App app{"fCore Emulator"};

    bool input_hex = false;
    bool input_mem = false;
    bool output_force = false;
    std::string input_program;
    std::string inputs_file;
    std::string output_file;
    app.add_option("input_program", input_program, "Input program path")->required()->check(CLI::ExistingFile);
    app.add_flag("--mem", input_mem, "the input is a verilog mem file");
    app.add_flag("--hex", input_hex, "the input is a binary file");
    app.add_flag("--f", output_force, "force the rewriting of an existing product file");
    app.add_option("--o", output_file, "Output file path");
    app.add_option("--inputs_csv", inputs_file, "Path of a csv file containing input vectors for the emulated core");
    CLI11_PARSE(app, argc, argv);

    if(!input_hex && !input_mem){
        std::cout<< "ERROR: the input file type should be specified (use either the --mem or --hex flags)"<<std::endl;
        exit(-1);
    } else if (input_hex && input_mem){
        std::cout<< "ERROR: Both input file type specifiers are present on the command line, only one should be used"<<std::endl;
        exit(-1);
    }

    if(!output_file.empty() & !output_force){
        if(std::filesystem::exists(output_file)){
            std::cout<< "ERROR: The Specified output file already exists, to force the file to be rewritten use the --f flag"<<std::endl;
            exit(-1);
        }
    }

    std::ifstream stream;


    bin_loader_input_type_t in_type;
    if(input_mem) {
        stream.open(input_program);
        in_type = bin_loader_mem_input;
    } else {
        stream.open(input_program, std::ifstream::binary);
        in_type = bin_loader_hex_input;
    }

    fcore_emu emu_engine(stream, in_type);

    if(!inputs_file.empty()){
        std::ifstream in_stream(inputs_file);
        emu_engine.set_inputs(in_stream);
    }
    emu_engine.emulate_program();

    emu_engine.write_json(output_file);

    return 0;
}