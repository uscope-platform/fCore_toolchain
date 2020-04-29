#include <iostream>
#include <string>
#include <vector>

#include "file_parser.h"
#include "../include/CLI11.hpp"



int main(int argc, char **argv) {
    CLI::App app{"fCore High level assembler"};

    std::string input_file;
    app.add_option("input_file", input_file, "Input file path")->required()->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    std::vector<uint32_t> program = parse(input_file);

    return 0;
}

