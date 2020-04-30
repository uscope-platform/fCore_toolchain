#include <iostream>
#include <string>
#include <vector>

#include "file_parser.h"
#include "output_writer.hpp"
#include "../include/CLI11.hpp"



int main(int argc, char **argv) {
    CLI::App app{"fCore High level assembler"};

    bool output_hex;
    bool output_mem;
    std::string input_file;
    app.add_option("input_file", input_file, "Input file path")->required()->check(CLI::ExistingFile);
    app.add_flag("--mem", output_hex, "produce binary output file");
    app.add_flag("--hex", output_mem, "produce verilog memory initialization output file");

    CLI11_PARSE(app, argc, argv);

    std::vector<uint32_t> program = parse(input_file);

    output_writer writer(program);
    if(output_hex){
        writer.write_hex(input_file);
    }

    if(output_mem){
        writer.write_mem(input_file);
    }

    return 0;
}

