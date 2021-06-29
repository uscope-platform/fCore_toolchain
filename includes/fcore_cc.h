//
// Created by fils on 28/06/2021.
//

#ifndef FCORE_HAS_FCORE_CC_H
#define FCORE_HAS_FCORE_CC_H

#include <istream>
#include <vector>
#include <string>


#include "frontend/variable_map.hpp"
#include "frontend/C/c_language_parser.h"
#include "backend/output_generator.hpp"
#include "passes/passes.hpp"

class fcore_cc {
public:
    fcore_cc(std::istream &input, std::vector<std::string> &includes);

    std::vector<uint32_t> get_hexfile(bool endian_swap);
    std::string get_errors();
    std::vector<std::string> get_verilog_memfile();
    void write_hexfile(const std::string& ouput_file);
    void write_verilog_memfile(const std::string& ouput_file);
    uint32_t get_program_size();
    uint32_t get_inst_count();
    ~fcore_cc();
private:
    ast_t AST;
    output_generator *writer;
    pass_manager manager;
    std::string error_code;
};



#endif //FCORE_HAS_FCORE_CC_H
