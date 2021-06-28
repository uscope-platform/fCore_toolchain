// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#include <fstream>

#include <gtest/gtest.h>
#include "fcore_has/fcore_has.hpp"


TEST( EndToEnd, simple_file ) {#include "fcore_has/code_elements/code_element.hpp"
    std::string input_file = "test_add.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};
    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> gold_standard = {0x32087, 0x640A7, 0xc2b01, 0xc};

    // file parsing and processing

    std::vector<uint32_t> result = uut.get_hexfile(false);
    ASSERT_EQ(result, gold_standard);

    //verilog memfile generation

    uut.write_verilog_memfile(input_file+".mem");

    std::ifstream infile(input_file+".mem");
    std::string a;
    result.clear();
    while (infile >> a)
    {
        result.push_back(std::stoi(a, nullptr, 16));
    }
    ASSERT_EQ(result, gold_standard);

    // hex file generation

    uut.write_hexfile(input_file+".hex");

    std::string filename = input_file+".hex";
    FILE *fptr = fopen(filename.c_str(),"rb");

    int program_size = uut.get_program_size();
    uint32_t res[1000];
    fread(res,sizeof(uint32_t), program_size, fptr);
    result.clear();
    for(int i = 0; i < program_size; i++){
        result.push_back(Reverse32(res[i]));
    }
    ASSERT_EQ(result, gold_standard);//result == gold_standard);


}