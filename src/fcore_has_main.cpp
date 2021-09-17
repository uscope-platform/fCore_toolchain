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
#include <vector>
#include <filesystem>

#include "../third_party/CLI11.hpp"
#include "fcore_has.hpp"

int main(int argc, char **argv) {
    CLI::App app{"fCore High level assembler"};

    bool output_hex = false;
    bool output_mem = false;
    bool output_json = false;
    bool output_force = false;
    std::string input_file;
    std::string output_file;
    app.add_option("input_file", input_file, "Input file path")->required()->check(CLI::ExistingFile);
    app.add_flag("--mem", output_mem, "produce binary output file");
    app.add_flag("--json", output_json, "produce a json file for output");
    app.add_flag("--hex", output_hex, "produce verilog memory initialization output file");
    app.add_flag("--f", output_force, "force the rewriting of an existing product file");
    app.add_option("--o", output_file, "Output file path");
    CLI11_PARSE(app, argc, argv);



    if(!output_file.empty() & !output_force){
        if(std::filesystem::exists(output_file)){
            std::cout<< "ERROR: The Specified output file already exists, to force the file to be rewritten use the --f flag"<<std::endl;
            exit(-1);
        }
    }

    std::string include_dir = "/home/fils/git/fCore_has/";
    std::vector<std::string> include_files = {};

    std::ifstream stream;
    stream.open(input_file);

    fcore_has has_engine(stream,include_files, include_dir);

    if(output_hex){
        has_engine.write_hexfile(output_file);
    }

    if(output_mem){
        has_engine.write_verilog_memfile(output_file);
    }

    if(output_json){
        has_engine.write_json(output_file);
    }

    return 0;
}

