//
// Created by fils on 01/05/20.
//
#include <fstream>

#include "includes/catch.hpp"
#include "../src/code_elements/code_element.hpp"
#include "../src/backend/output_writer.hpp"
#include "../src/frontend/file_parser.h"
#include "../src/passes/passes.hpp"

static inline uint32_t Reverse32(uint32_t value)
{
    return (((value & 0x000000FFu) << 24u) |
            ((value & 0x0000FF00u) <<  8u) |
            ((value & 0x00FF0000u) >>  8u) |
            ((value & 0xFF000000u) >> 24u));
}

TEST_CASE( "simple assembly file", "[simple_file]" ) {
    std::string input_file = "test_add.s";

    std::vector<uint32_t> gold_standard = {0x6449, 0xc859, 0x6541,0xe};

    SECTION("file parsing and processing") {

        std::shared_ptr<code_element> ast = parse(input_file);
        output_writer writer(ast, false);
        std::vector<uint32_t> result = writer.get_raw_program();

        REQUIRE( result == gold_standard);
    }
    SECTION("verilog memfile generation") {
        std::shared_ptr<code_element> ast = parse(input_file);
        output_writer writer(ast,false);
        writer.write_mem(input_file+".mem");
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
        std::shared_ptr<code_element> ast = parse(input_file);
        output_writer writer(ast, false);
        writer.write_hex(input_file+".hex");
        std::string filename = input_file+".hex";
        FILE *fptr = fopen(filename.c_str(),"rb");

        uint32_t res[4];
        fread(res,sizeof(uint32_t), 4, fptr);
        std::vector<uint32_t> result;
        for(unsigned int re : res){
            result.push_back(Reverse32(re));
        }
        REQUIRE(result == gold_standard);//result == gold_standard);
    }


}

TEST_CASE( "for block file", "[for_file]" ) {
    std::string input_file = "test_for.s";

    std::shared_ptr<code_element> AST = parse(input_file);

    pass_manager manager = create_pass_manager();
    manager.run_passes(AST);

    output_writer writer(AST, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0x6449, 0xc859, 0x6541, 0x6449, 0x6541, 0x0000, 0x0000, 0x6449, 0x6541, 0x0000, 0x0000, 0xe};
    REQUIRE( result == gold_standard);
}

TEST_CASE( "branch file", "[for_file]" ) {
    std::string input_file = "test_branch.s";

    std::shared_ptr<code_element> AST = parse(input_file);

    pass_manager manager = create_pass_manager();
    manager.run_passes(AST);

    output_writer writer(AST, true);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0x6449, 0x6541, 0x431, 0x50032A, 0x50032B, 0x50032C, 0x50032D, 0xe};
    REQUIRE( result == gold_standard);
}