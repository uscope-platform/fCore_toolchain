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
#include <gtest/gtest.h>
#include <filesystem>
#include <cstdlib>

#include "fcore_dis.hpp"

using namespace fcore;

TEST( Disassembler, disassembler) {
    std::vector<uint32_t> program = {0x60001, 0xc, 0xc, 0x86, 0x42c80000, 0xa6, 0x43480000, 0xc2b01, 0xc};

    fcore_dis disassembler(program);

    std::string result = disassembler.get_disassenbled_program();

    std::string gold_standard = "ldc r4, 100.000000\nldc r5, 200.000000\nadd r24, r5, r6\nstop\n";

    ASSERT_EQ(result, gold_standard);
}


TEST( Disassembler, disassembler_file_out) {

    std::vector<uint32_t> program = {0x60001, 0xc, 0xc, 0x86, 0x42c80000, 0xa6, 0x43480000, 0xc2b01, 0xc};

    fcore_dis disassembler(program);

    unsigned int filename = rand();
    std::string outfile_name = std::filesystem::temp_directory_path().string() + "/" + std::to_string(filename);
    disassembler.write_disassembled_program(outfile_name);

    std::ifstream result_file(outfile_name);
    std::ostringstream sstr;
    sstr << result_file.rdbuf();

    std::string result_content = sstr.str();

    std::string gold_standard = "ldc r4, 100.000000\nldc r5, 200.000000\nadd r24, r5, r6\nstop\n";

    ASSERT_EQ(result_content, gold_standard);
}

TEST( Disassembler, disassembler_json) {

    std::vector<uint32_t> program = {0x60001, 0xc, 0xc, 0x86, 0x42c80000, 0xa6, 0x43480000, 0xc2b01, 0xc};
    fcore_dis disassembler(program);


    unsigned int filename = rand();
    std::string outfile_name = std::filesystem::temp_directory_path().string() + "/" + std::to_string(filename);
    disassembler.write_json(outfile_name);

    std::ifstream result_file(outfile_name);
    std::ostringstream sstr;
    sstr << result_file.rdbuf();

    auto result = nlohmann::json::parse(sstr.str());

    nlohmann::json gold_standard;
    gold_standard["error_code"] = "";
    gold_standard["disassembled_program"] = "ldc r4, 100.000000\nldc r5, 200.000000\nadd r24, r5, r6\nstop\n";

    ASSERT_EQ(result, gold_standard);
}


TEST( Disassembler, disassembler_error) {
    std::string input_file = "dis/test_error.mem";
    std::ifstream ifs(input_file);

    fcore_dis disassembler(ifs, bin_loader_mem_input);
    std::string exception = disassembler.get_errors();
    std::string gold_standard = "unknown opcode: 7";
    ASSERT_EQ(exception, gold_standard);


    unsigned int filename = rand();
    std::string outfile_name = std::filesystem::temp_directory_path().string() + "/" + std::to_string(filename);
    disassembler.write_json(outfile_name);

    std::ifstream result_file(outfile_name);
    std::ostringstream sstr;
    sstr << result_file.rdbuf();

    auto result = nlohmann::json::parse(sstr.str());

    nlohmann::json gold_standard_j;
    gold_standard_j["error_code"] = gold_standard;
    gold_standard_j["disassembled_program"] = "";

    ASSERT_EQ(result, gold_standard_j);
}