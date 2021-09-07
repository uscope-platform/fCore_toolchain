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

#include <fstream>
#include <gtest/gtest.h>
#include <filesystem>
#include <cstdlib>

#include "fcore_dis.hpp"

TEST( Disassembler, disassembler_mem) {
    std::string input_file = "dis/test_add.mem";
    std::ifstream ifs(input_file);

    fcore_dis disassembler(ifs, bin_loader_mem_input);

    std::string result = disassembler.get_disassenbled_program();

    std::string gold_standard = "ldc r4, 100.000000\nldc r5, 200.000000\nadd r24, r5, r6\nstop\n";

    ASSERT_EQ(result, gold_standard);
}

TEST( Disassembler, disassembler_hex) {
    std::string input_file = "dis/test_add.hex";
    std::ifstream ifs(input_file);

    fcore_dis disassembler(ifs, bin_loader_hex_input);

    std::string result = disassembler.get_disassenbled_program();

    std::string gold_standard = "ldc r4, 100.000000\nldc r5, 200.000000\nadd r24, r5, r6\nstop\n";

    ASSERT_EQ(result, gold_standard);
}


TEST( Disassembler, disassembler_json) {
    std::string input_file = "dis/test_add.hex";
    std::ifstream ifs(input_file);

    fcore_dis disassembler(ifs, bin_loader_hex_input);


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