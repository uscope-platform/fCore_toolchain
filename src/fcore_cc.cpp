//
// Created by fils on 28/06/2021.
//

#include "fcore_cc.h"


fcore_cc::fcore_cc(std::istream &input, std::vector<std::string> &includes) {
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    std::shared_ptr<define_map> defines_map = std::make_shared<define_map>();

    C_language_parser target_parser(input, variables_map, defines_map);
    target_parser.pre_process({}, {});
    target_parser.parse();
    AST = target_parser.AST;

    manager = create_hl_pass_manager(variables_map);
    manager.run_morphing_passes(AST);
    
}


fcore_cc::~fcore_cc() {

}

std::vector<uint32_t> fcore_cc::get_hexfile(bool endian_swap) {
    return writer->generate_hex(endian_swap);
}

std::string fcore_cc::get_errors() {
    return error_code;
}

std::vector<std::string> fcore_cc::get_verilog_memfile() {
    return writer->generate_mem();
}

void fcore_cc::write_hexfile(const std::string &ouput_file) {
    writer->write_hex_file(ouput_file);
}

void fcore_cc::write_verilog_memfile(const std::string &ouput_file) {
    writer->write_mem_file(ouput_file);
}

uint32_t fcore_cc::get_program_size() {
    return writer->get_program_size();
}

uint32_t fcore_cc::get_inst_count() {
    int program_lenght = manager.analysis_passes["instruction_counting"]->get_analysis_result()[0];
    float program_runtime = (float) program_lenght*0.01f;
    std::cout << "The compiled program is " << program_lenght << "instructions long"<< std::endl;
    std::cout << "Runtime at the standard frequency of 100 MHz will be of " << program_runtime << " µS"<< std::endl;
    return 0;
}
