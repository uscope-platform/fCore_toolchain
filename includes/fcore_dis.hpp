//
// Created by fils on 18/08/2021.
//

#ifndef FCORE_TOOLCHAIN_FCORE_DIS_H
#define FCORE_TOOLCHAIN_FCORE_DIS_H

#include <string>
#include <vector>

#include "data_structures/low_level_ast/ll_ast_node.hpp"
#include "frontend/disassembler_testing.hpp"

class fcore_dis {
public:
    fcore_dis(std::istream &input, disassembler_input_type_t in_type);
    std::string get_errors();
    void write_json(const std::string& output_file);
private:
    std::shared_ptr<ll_ast_node> ll_ast;

    std::string error_code;
};

#endif //FCORE_TOOLCHAIN_FCORE_DIS_H
