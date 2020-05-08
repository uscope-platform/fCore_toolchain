#include <iostream>
#include <string>
#include <vector>

#include "frontend/file_parser.h"
#include "code_elements/code_element.hpp"
#include "backend/output_writer.hpp"
#include "../include/CLI11.hpp"
#include "passes/passes.hpp"


int main(int argc, char **argv) {
    CLI::App app{"fCore High level assembler"};

    bool output_hex;
    bool output_mem;
    std::string input_file;
    std::string output_file;
    app.add_option("input_file", input_file, "Input file path")->required()->check(CLI::ExistingFile);
    app.add_flag("--mem", output_mem, "produce binary output file");
    app.add_flag("--hex", output_hex, "produce verilog memory initialization output file");
    app.add_option("--o", output_file, "Output file path")->check(CLI::NonexistentPath);
    CLI11_PARSE(app, argc, argv);

    std::shared_ptr<code_element> AST = parse(input_file);
    pass_manager manager = create_pass_manager();
    manager.run_passes(AST);

    output_writer writer(AST, false);
    if(output_hex){
        writer.write_hex(output_file);
    }

    if(output_mem){
        writer.write_mem(output_file);
    }

    return 0;
}

