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
#include <nlohmann/json.hpp>

#include "frontend/asm/asm_language_parser.hpp"
#include "data_structures/common/program_metadata.hpp"
#include "backend/binary_generator.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"

namespace fcore{
    class fcore_has {
    public:
        fcore_has(std::istream &input, bool print_debug, const std::map<std::string, std::vector<uint32_t>>& m);
        void construct_assembler(std::istream &input, bool print_debug);

        static std::vector<std::istream*> process_includes(const std::vector<std::string>& include_files, const std::string& include_directory);

        std::vector<uint32_t> get_hexfile(bool endian_swap);
        std::vector<uint32_t> get_executable();
        std::vector<uint32_t> get_raw_code();
        std::string get_errors();
        program_info get_program_info() { return length_info;}
        void write_hexfile(const std::string& ouput_file);
        void write_verilog_memfile(const std::string& ouput_file);
        void write_json(const std::string& output_file);
        uint32_t get_program_size();
        void set_io_map(const std::map<std::string, std::vector<uint32_t>>& m){dma_map = m;};
    private:
        std::map<std::string, std::vector<uint32_t>> dma_map;
        binary_generator writer;
        std::string error_code;
        program_info length_info;
        nlohmann::json dump;
    };
}



#endif //FCORE_TOOLCHAIN_FCORE_HAS_HPP
