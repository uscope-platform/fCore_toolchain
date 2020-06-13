#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include "frontend/file_parser.h"
#include "code_elements/code_element.hpp"
#include "backend/output_writer.hpp"
#include "../include/CLI11.hpp"
#include "passes/passes.hpp"


int main(int argc, char **argv) {
    CLI::App app{"fCore High level assembler"};

    bool output_hex;
    bool output_mem;
    bool output_force;
    std::string input_file;
    std::string output_file;
    app.add_option("input_file", input_file, "Input file path")->required()->check(CLI::ExistingFile);
    app.add_flag("--mem", output_mem, "produce binary output file");
    app.add_flag("--hex", output_hex, "produce verilog memory initialization output file");
    app.add_flag("--f", output_force, "force the rewriting of an existing product file");
    app.add_option("--o", output_file, "Output file path");
    CLI11_PARSE(app, argc, argv);



    if(!output_file.empty() & !output_force){
        if(std::filesystem::exists(output_file)){
            std::cout<< "ERROR: The Specified output file already exists, to force the file to be rewritten use the --f flag"<<std::endl;
            exit(-1);
        }
    }

    std::string include_dir = "/home/fils/git/fCore_has/";
    std::vector<std::string> include_files = {"include/registers_definitions.s"};

    varmap_t variables_map;

    // Parse include files
    ast_t includes_ast;

    for(auto const &item:include_files){
        std::string name = include_dir;
        name += item;
        parser include_parser(name);
        ast_t tmp_ast = include_parser.AST;
        varmap_t tmp_varmap = include_parser.var_map;
        if(includes_ast != nullptr){
            includes_ast->append_content(tmp_ast->get_content());
            variables_map.insert(tmp_varmap.begin(), tmp_varmap.end());

        } else{
            includes_ast = tmp_ast;
            variables_map = include_parser.var_map;
        }
    }
    // parse target file
    parser target_parser(input_file, variables_map);

    ast_t AST = target_parser.AST;

    //merge the two together (right now just concatenate them)
    AST->prepend_content(includes_ast->get_content());

    pass_manager manager = create_pass_manager();
    manager.run_morphing_passes(AST);




    output_writer writer(AST, false);
    if(output_hex){
        writer.write_hex(output_file);
    }

    if(output_mem){
        writer.write_mem(output_file);
    }

    return 0;
}

