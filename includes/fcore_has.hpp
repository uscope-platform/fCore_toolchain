// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_FCORE_HAS_HPP
#define FCORE_TOOLCHAIN_FCORE_HAS_HPP

#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

#include "tools/variable_map.hpp"
#include "frontend/asm/asm_language_parser.hpp"
#include "backend/binary_generator.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"

#define REGISTER_DEFINITION_STRING "const r0\nlet r1\nlet r2\nlet r3\nlet r4\nlet r5\nlet r6\nlet r7\nlet r8\nlet r9\nlet r10\nlet r11\nlet r12\nlet r13\nlet r14\nlet r15"

extern "C"{
    std::tuple<std::vector<uint32_t>, int> fCore_has_embeddable_s(const std::string& content);
    void fCore_has_embeddable_f(const char * filename, uint32_t *hex, int *hex_size, bool print_debug);
};

namespace fcore{
    class fcore_has {
    public:
        fcore_has(std::istream &input, int dump_ast_level, bool print_debug);
        void construct_assembler(std::istream &input, int dump_ast_level, bool print_debug);

        static std::vector<std::istream*> process_includes(const std::vector<std::string>& include_files, const std::string& include_directory);

        std::vector<uint32_t> get_hexfile(bool endian_swap);
        std::vector<uint32_t> get_executable();
        std::vector<uint32_t> get_raw_code();
        std::string get_errors();
        void write_hexfile(const std::string& ouput_file);
        void write_verilog_memfile(const std::string& ouput_file);
        void write_json(const std::string& output_file);
        uint32_t get_program_size();
        uint32_t get_inst_count();
        nlohmann::json get_dump() {return dump;};
    private:
        binary_generator writer;
        std::string error_code;
        nlohmann::json dump;
    };
}



#endif //FCORE_TOOLCHAIN_FCORE_HAS_HPP
