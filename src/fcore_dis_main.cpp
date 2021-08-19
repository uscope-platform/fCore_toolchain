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

#include <iostream>
#include <string>
#include <filesystem>

#include "../third_party/CLI11.hpp"
#include "fcore_dis.hpp"

int main(int argc, char **argv) {
    CLI::App app{"fCore High level assembler"};

    bool input_hex = false;
    bool input_mem = false;
    bool output_json = false;
    bool output_force = false;;
    std::string input_file;
    std::string output_file;
    app.add_option("input_file", input_file, "Input file path")->required()->check(CLI::ExistingFile);
    app.add_flag("--mem", input_mem, "the input is a verilog mem file");
    app.add_flag("--hex", input_hex, "the input is a binary file");
    app.add_flag("--json", output_json, "produce a json file for output");
    app.add_flag("--f", output_force, "force the rewriting of an existing product file");
    app.add_option("--o", output_file, "Output file path");
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
        stream.open(input_file);
        in_type = bin_loader_mem_input;
    } else {
        stream.open(input_file, std::ifstream::binary);
        in_type = bin_loader_hex_input;
    }

    fcore_dis dis_engine(stream, in_type);
    if(output_json){
        dis_engine.write_json(output_file);
    } else {
        dis_engine.write_disassembled_program(output_file);
    }

    return 0;
}

