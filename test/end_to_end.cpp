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
#include "fcore_has/code_elements/code_element.hpp"


#include "fcore_has/fcore_has.hpp"

static inline uint32_t Reverse32(uint32_t value)
{
    return (((value & 0x000000FFu) << 24u) |
            ((value & 0x0000FF00u) <<  8u) |
            ((value & 0x00FF0000u) >>  8u) |
            ((value & 0xFF000000u) >> 24u));
}

TEST( EndToEnd, simple_file ) {
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

TEST( EndToEnd, for_file ) {
    std::string input_file = "test_for.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0x32087, 0x640A7, 0xc2881, 0x32087, 0xc2881, 0x0000, 0x0000, 0x32087, 0xc2881, 0x0000, 0x0000, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST( EndToEnd, branch_file ) {
    std::string input_file = "test_branch.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);

     std::vector<uint32_t> gold_standard = {0x32087, 0xc2881, 0x80061, 0x21848, 0x21849, 0x2184a, 0x2184b, 0xC};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEnd, variables_file) {
    std::string input_file = "test_variables.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);
    std::vector<uint32_t> gold_standard = {0x32027, 0x64047, 0x640A7, 0xc2881, 0xe4821,0xe4841,0x32027,0xe4821, 0x50B2, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEnd, load_constant_file) {
    std::string input_file = "test_ldc.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0x32087, 0x640A7, 0x86, 0x4048f5c3, 0xc};
    ASSERT_EQ( result, gold_standard);
}

TEST(EndToEnd, embeddable_wrapper_pass) {
    std::string input_file = "test_ldc.s";
    int hex_size;
    uint32_t *hex_result = (uint32_t*) malloc(4096*sizeof(uint32_t));

    fCore_has_embeddable_f(input_file.c_str(),hex_result, &hex_size);

    std::vector<uint32_t> result;
    for(int i = 0; i<hex_size;i++){
        result.push_back(hex_result[i]);
    }
    free(hex_result);
    std::vector<uint32_t> gold_standard = {0x32087, 0x640A7, 0x86, 0x4048f5c3, 0xc};
    ASSERT_EQ( result, gold_standard);
}

/*
TEST_CASE( "Embeddable C wrapper fail") {
    std::string input_file = "test_ldc_fail.s";

    std::ifstream ifs(input_file);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()) );

    std::string gold_standard = "mismatched input '<EOF>' expecting {'ldc', 'stop', 'nop', 'add', 'sub', 'mul', 'itf', 'fti', 'ldr', 'ble', 'bgt', 'beq', 'bne', 'mov', 'for(', '#pragma ', 'let', 'const', 'input', 'output'}";
    REQUIRE_THROWS_WITH( fCore_has_embeddable_s(content), gold_standard);
}*/


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}