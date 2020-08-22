//
// Created by fils on 22/08/2020.
//

#ifndef FCORE_HAS_FCORE_HAS_HPP
#define FCORE_HAS_FCORE_HAS_HPP

#include <string>
#include <vector>

#include "frontend/variable_map.hpp"
#include "frontend/file_parser.h"
#include "backend/output_generator.hpp"
#include "passes/passes.hpp"

class fcore_has {
public:
    fcore_has(std::istream &input,  const std::vector<std::string>& include_files, const std::string& include_directory);
    std::vector<uint32_t> get_hexfile(bool endian_swap);
    std::vector<std::string> get_verilog_memfile();
    void write_hexfile(const std::string& ouput_file);
    void write_verilog_memfile(const std::string& ouput_file);
    uint32_t get_program_size();
    uint32_t get_inst_count();
    ~fcore_has();
private:
    ast_t AST;
    output_generator *writer;
    pass_manager manager;
};


#endif //FCORE_HAS_FCORE_HAS_HPP
