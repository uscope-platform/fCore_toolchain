//
// Created by fils on 01/05/20.
//
#include "catch.hpp"
#include "../src/code_elements/code_element.hpp"
#include "../src/backend/output_writer.hpp"
#include "../src/frontend/file_parser.h"
#include "../src/passes/passes.hpp"
TEST_CASE( "simple assembly file", "[simple_file]" ) {
    std::string input_file = "test_add.s";

    std::shared_ptr<code_element> ast = parse(input_file);
    output_writer writer(ast);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0x6449, 0xc859, 0x6541,0xc};
REQUIRE( result == gold_standard);
}

TEST_CASE( "for block file", "[for_file]" ) {
    std::string input_file = "test_for.s";

    std::shared_ptr<code_element> AST = parse(input_file);

    pass_manager manager = create_pass_manager();
    manager.run_passes(AST);

    output_writer writer(AST);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0x6449, 0xc859, 0x6541, 0x6449, 0x6541, 0x0000, 0x0000, 0x6449, 0x6541, 0x0000, 0x0000, 0xc};
    REQUIRE( result == gold_standard);
}