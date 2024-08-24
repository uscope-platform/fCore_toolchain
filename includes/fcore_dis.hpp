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

#ifndef FCORE_TOOLCHAIN_FCORE_DIS_H
#define FCORE_TOOLCHAIN_FCORE_DIS_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "frontend/binary_loader.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "backend/assembly_generator.hpp"

namespace fcore{
    class fcore_dis {
    public:
        fcore_dis(std::istream &input, bin_loader_input_type_t in_type);
        explicit fcore_dis(const std::vector<uint32_t> &mem);
        std::string get_errors();
        void write_json(const std::string& output_file);
        std::string get_disassenbled_program();
        void write_disassembled_program(const std::string& output_file);
    private:
        void process_stream(instruction_stream program_stream);
        std::unordered_map<uint16_t, uint16_t> io_map;
        std::unique_ptr<assembly_generator> gen;
        std::string error_code;
    };
}


#endif //FCORE_TOOLCHAIN_FCORE_DIS_H
