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

#include "includes/catch.hpp"
#include "fcore_has/code_elements/code_element.hpp"
#include "fcore_has/backend/output_generator.hpp"
#include "fcore_has/passes/passes.hpp"

#include "fcore_has/fcore_has.hpp"

static inline uint32_t Reverse32(uint32_t value)
{
    return (((value & 0x000000FFu) << 24u) |
            ((value & 0x0000FF00u) <<  8u) |
            ((value & 0x00FF0000u) >>  8u) |
            ((value & 0xFF000000u) >> 24u));
}

TEST_CASE( "simple assembly file", "[simple_file]" ) {
    std::string input_file = "test_add.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};
    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> gold_standard = {0xc887, 0x190A7, 0xCA81,0xc};

    SECTION("file parsing and processing") {

        std::vector<uint32_t> result = uut.get_hexfile(false);

        REQUIRE( result == gold_standard);
    }
    SECTION("verilog memfile generation") {

        uut.write_verilog_memfile(input_file+".mem");

        std::ifstream infile(input_file+".mem");
        std::string a;
        std::vector<uint32_t> result;
        while (infile >> a)
        {
            result.push_back(std::stoi(a, nullptr, 16));
        }
        REQUIRE(result == gold_standard);
    }
    SECTION("hex file generation"){

        uut.write_hexfile(input_file+".hex");

        std::string filename = input_file+".hex";
        FILE *fptr = fopen(filename.c_str(),"rb");

        int program_size = uut.get_program_size();
        uint32_t res[1000];
        fread(res,sizeof(uint32_t), program_size, fptr);
        std::vector<uint32_t> result;
        for(int i = 0; i < program_size; i++){
            result.push_back(Reverse32(res[i]));
        }
        REQUIRE(result == gold_standard);//result == gold_standard);
    }


}

TEST_CASE( "for block file", "[for_file]" ) {
    std::string input_file = "test_for.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0xC887, 0x190a7, 0xca81, 0xC887, 0xca81, 0x0000, 0x0000, 0xC887, 0xca81, 0x0000, 0x0000, 0xc};
    REQUIRE( result == gold_standard);
}

TEST_CASE( "branch file", "[branch_file]" ) {
    std::string input_file = "test_branch.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);

     std::vector<uint32_t> gold_standard = {0xC887, 0xca81, 0x8061, 0xa00648, 0xa00649, 0xa0064a, 0xa0064b, 0xC};
    REQUIRE( result == gold_standard);
}

TEST_CASE( "variables file") {
    std::string input_file = "test_variables.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);
    std::vector<uint32_t> gold_standard = {0xc827, 0x19047, 0x190a7, 0xca81, 0xf221,0xf241,0xc827,0xf221, 0xc};
    REQUIRE( result == gold_standard);
}

TEST_CASE( "load constant file") {
    std::string input_file = "test_ldc.s";

    std::string include_dir = "";
    std::vector<std::string> include_files = {"register_defs.s"};

    std::ifstream stream(input_file);
    fcore_has uut(stream,include_files,include_dir);

    std::vector<uint32_t> result = uut.get_hexfile(false);

    std::vector<uint32_t> gold_standard = {0xc887, 0x190a7, 0x86, 0x4048f5c3, 0xc};
    REQUIRE( result == gold_standard);
}

TEST_CASE( "Embeddable C wrapper pass") {
    std::string input_file = "test_ldc.s";
    int hex_size;
    uint32_t *hex_result = (uint32_t*) malloc(4096*sizeof(uint32_t));

    fCore_has_embeddable_f(input_file.c_str(),hex_result, &hex_size);

    std::vector<uint32_t> result;
    for(int i = 0; i<hex_size;i++){
        result.push_back(hex_result[i]);
    }
    free(hex_result);
    std::vector<uint32_t> gold_standard = {0xc887, 0x190a7, 0x86, 0x4048f5c3, 0xc};
    REQUIRE( result == gold_standard);
}


TEST_CASE( "Embeddable C wrapper fail") {
    std::string input_file = "test_ldc_fail.s";

    std::ifstream ifs(input_file);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );

    int hex_size;
    uint32_t *hex_result = (uint32_t*) malloc(4096*sizeof(uint32_t));
    std::string gold_standard = "mismatched input '<EOF>' expecting {'ldc', 'stop', 'nop', 'add', 'sub', 'mul', 'itf', 'fti', 'ldr', 'ble', 'bgt', 'beq', 'bne', 'mov', 'for(', '#pragma ', 'let', 'const', 'input', 'output'}";
    REQUIRE_THROWS_WITH(fCore_has_embeddable_s(content.c_str(),hex_result, &hex_size), gold_standard);
}