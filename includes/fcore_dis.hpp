//
// Created by fils on 18/08/2021.
//

#ifndef FCORE_TOOLCHAIN_FCORE_DIS_H
#define FCORE_TOOLCHAIN_FCORE_DIS_H

#include <string>
#include <vector>

#include "data_structures/low_level_ast/ll_ast_node.hpp"
#include "frontend/binary_loader.hpp"
#include "data_structures/instruction_stream.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "backend/assembly_generator.hpp"

#include "../third_party/json.hpp"

class fcore_dis {
public:
    fcore_dis(std::istream &input, bin_loader_input_type_t in_type);
    std::string get_errors();
    void write_json(const std::string& output_file);
    std::string get_disassenbled_program();
    void write_disassembled_program(const std::string& output_file);
private:
    std::shared_ptr<ll_ast_node> ll_ast;
    std::unique_ptr<assembly_generator> gen;
    std::string error_code;
};

#endif //FCORE_TOOLCHAIN_FCORE_DIS_H
