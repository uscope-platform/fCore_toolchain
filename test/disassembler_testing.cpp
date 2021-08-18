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

#include "fcore_dis.hpp"


TEST( Disassembler, disassembler_mem) {
    std::string input_file = "test_add.mem";
    std::ifstream ifs(input_file);

    fcore_dis disassembler(ifs, disassembler_mem_input);

}

TEST( Disassembler, disassembler_hex) {
    std::string input_file = "test_add.hex";
    std::ifstream ifs(input_file);

    fcore_dis disassembler(ifs, disassembler_hex_input);
}