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
#include <vector>
#include <filesystem>


#include "../third_party/CLI11.hpp"
#include "fcore_cc.hpp"

int main(int argc, char **argv) {
    CLI::App app{"fCore C compiler"};

    bool output_hex = false;
    bool output_mem = false;
    bool output_json = false;
    bool output_force = false;;
    std::string input_file;
    std::string output_file;
    app.add_option("input_file", input_file, "Input file path")->required()->check(CLI::ExistingFile);
    app.add_flag("--mem", output_mem, "produce binary output file");
    app.add_flag("--hex", output_hex, "produce verilog memory initialization output file");
    app.add_flag("--json", output_json, "produce a json file for output");
    app.add_flag("--f", output_force, "force the rewriting of an existing product file");
    app.add_option("--o", output_file, "Output file path");
    CLI11_PARSE(app, argc, argv);

    if(!output_file.empty() & !output_force){
        if(std::filesystem::exists(output_file)){
            std::cout<< "ERROR: The Specified output file already exists, to force the file to be rewritten use the --f flag"<<std::endl;
            exit(-1);
        }
    }

    std::vector<std::string> include_files = {""};
    fcore_cc cc_engine(input_file, include_files, false);

    if(output_hex){
        cc_engine.write_hexfile(output_file);
    }

    if(output_mem){
        cc_engine.write_verilog_memfile(output_file);
    }

    if(output_json){
        cc_engine.write_json(output_file);
    }

    return 0;
}

