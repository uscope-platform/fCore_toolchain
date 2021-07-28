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

#ifndef FCORE_TOOLCHAIN_FCORE_HAS_HPP
#define FCORE_TOOLCHAIN_FCORE_HAS_HPP

#include <string>
#include <vector>
#include <fstream>

#include "tools/variable_map.hpp"
#include "frontend/asm/asm_language_parser.hpp"
#include "backend/output_generator.hpp"
#include "passes/ll_passes.hpp"
#include "passes/low_level/ll_pass_manager.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "../third_party/json.hpp"
#include "data_structures/instruction_stream.hpp"
#include "tools/instruction_stream_builder.hpp"

#define REGISTER_DEFINITION_STRING "const r0\nlet r1\nlet r2\nlet r3\nlet r4\nlet r5\nlet r6\nlet r7\nlet r8\nlet r9\nlet r10\nlet r11\nlet r12\nlet r13\nlet r14\nlet r15"

extern "C"{
    std::tuple<std::vector<uint32_t>, int> fCore_has_embeddable_s(const std::string& content);
    void fCore_has_embeddable_f(const char * filename, uint32_t *hex, int *hex_size);
};

class fcore_has {
public:
    fcore_has(std::istream &input,   std::vector<std::istream*> &includes);
    fcore_has(std::istream &input,   const std::vector<std::string>& include_files,  const std::string& include_directory);
    void construct_assembler(std::istream &input, std::vector<std::istream*> &includes);

    static std::vector<std::istream*> process_includes(const std::vector<std::string>& include_files, const std::string& include_directory);

    std::vector<uint32_t> get_hexfile(bool endian_swap);
    std::string get_errors();
    std::vector<std::string> get_verilog_memfile();
    void write_hexfile(const std::string& ouput_file);
    void write_verilog_memfile(const std::string& ouput_file);
    void write_json(const std::string& output_file);
    uint32_t get_program_size();
    uint32_t get_inst_count();
private:
    std::shared_ptr<ll_ast_node> AST;
    output_generator writer;
    ll_pass_manager manager;
    std::string error_code;
};


#endif //FCORE_TOOLCHAIN_FCORE_HAS_HPP
