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

    std::vector<uint32_t> gold_standard = {0xc88b, 0x190Ab, 0xCA81, 0x632a ,0x3e8e91,0x10};

    SECTION("file parsing and processing") {

        parser p(input_file);
        ast_t ast = p.AST;
        output_writer writer(ast, false);
        std::vector<uint32_t> result = writer.get_raw_program();

        REQUIRE( result == gold_standard);
    }
    SECTION("verilog memfile generation") {
        parser p(input_file);
        ast_t ast = p.AST;
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
        parser p(input_file);
        ast_t ast = p.AST;
        output_writer writer(ast, false);
        writer.write_hex(input_file+".hex");
        std::string filename = input_file+".hex";
        FILE *fptr = fopen(filename.c_str(),"rb");

        int program_size = writer.get_program_size();
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

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    parser p1("register_defs.s", map);
    parser p2(input_file, map);
    ast_t ast = p2.AST;

    pass_manager manager = create_pass_manager(map);
    manager.run_morphing_passes(ast);

    output_writer writer(ast, false);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0xC88B, 0x190ab, 0xca81, 0xC88b, 0xca81, 0x0000, 0x0000, 0xC88b, 0xca81, 0x0000, 0x0000, 0x10};
    REQUIRE( result == gold_standard);
}

TEST_CASE( "branch file", "[for_file]" ) {
    std::string input_file = "test_branch.s";

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    parser p1("register_defs.s", map);
    parser p2(input_file, map);
    ast_t ast = p2.AST;


    pass_manager manager = create_pass_manager(map);
    manager.run_morphing_passes(ast);

    output_writer writer(ast, true);
    std::vector<uint32_t> result = writer.get_raw_program();
     std::vector<uint32_t> gold_standard = {0xC88B, 0xca81, 0x8061, 0xa0064c, 0xa0064d, 0xa0064e, 0xa0064f, 0x10};
    REQUIRE( result == gold_standard);
}

TEST_CASE( "variables file") {
    std::string input_file = "test_variables.s";

    std::shared_ptr<variable_map> map = std::make_shared<variable_map>();
    parser p1("register_defs.s", map);
    parser p2(input_file, map);
    ast_t ast = p2.AST;


    pass_manager manager = create_pass_manager(map);
    manager.run_morphing_passes(ast);

    output_writer writer(ast, true);
    std::vector<uint32_t> result = writer.get_raw_program();
    std::vector<uint32_t> gold_standard = {0xc82b, 0x1904b, 0x190ab, 0xca81, 0x28e31,0x28e51,0xc82b,0x28e31, 0x10};
    REQUIRE( result == gold_standard);
}