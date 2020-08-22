#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "../include/CLI11.hpp"
#include "fcore_has.hpp"

int main(int argc, char **argv) {
    CLI::App app{"fCore High level assembler"};

    bool output_hex;
    bool output_mem;
    bool output_force;
    std::string input_file;
    std::string output_file;
    app.add_option("input_file", input_file, "Input file path")->required()->check(CLI::ExistingFile);
    app.add_flag("--mem", output_mem, "produce binary output file");
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
    std::vector<std::string> include_files = {"include/registers_definitions.s"};

    std::ifstream stream;
    stream.open(input_file);

    fcore_has has_engine(stream,include_files, include_dir);

    if(output_hex){
        has_engine.write_hexfile(output_file);
    }

    if(output_mem){
        has_engine.write_verilog_memfile(output_file);
    }

    return 0;
}

