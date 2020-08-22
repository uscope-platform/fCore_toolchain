//
// Created by fils on 22/08/2020.
//

#include "fcore_has.hpp"

fcore_has::fcore_has(std::istream &input,  const std::vector<std::string>& include_files, const std::string& include_directory) {
    variable_map tmp_map;
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>(tmp_map);
    // Parse include files
    ast_t includes_ast;
    std::ifstream stream;
    for(auto const &item:include_files){
        std::string name = include_directory;
        name += item;
        stream.open(name);
        parser include_parser(stream, variables_map);
        ast_t tmp_ast = include_parser.AST;
        if(includes_ast != nullptr){
            includes_ast->append_content(tmp_ast->get_content());
        } else{
            includes_ast = tmp_ast;
        }
    }

    // parse target file
    parser target_parser(input, variables_map);

    AST = target_parser.AST;

    //merge the two together (right now just concatenate them)
    AST->prepend_content(includes_ast->get_content());


    manager = create_pass_manager(variables_map);
    manager.run_morphing_passes(AST);

    //manager.run_analysis_passes(AST);
    writer = new output_generator(AST, false);

}

std::vector<uint32_t> fcore_has::get_hexfile(bool endian_swap) {
    return writer->generate_hex(endian_swap);
}

std::vector<std::string> fcore_has::get_verilog_memfile() {
    return writer->generate_mem();
}



fcore_has::~fcore_has() {
    delete writer;
}

uint32_t fcore_has::get_inst_count() {
    int program_lenght = manager.analysis_passes["instruction_counting"]->get_analysis_result()[0];
    float program_runtime = (float) program_lenght*0.01f;
    std::cout << "The compiled program is " << program_lenght << "instructions long"<< std::endl;
    std::cout << "Runtime at the standard frequency of 100 MHz will be of " << program_runtime << " µS"<< std::endl;
    return 0;
}

void fcore_has::write_hexfile(const std::string& ouput_file) {
    writer->write_hex_file(ouput_file);
}

void fcore_has::write_verilog_memfile(const std::string& ouput_file) {
    writer->write_mem_file(ouput_file);
}

uint32_t fcore_has::get_program_size() {
    return writer->get_program_size();
}
