//
// Created by fils on 30/04/20.
//

#include "output_writer.hpp"

output_writer::output_writer(const ast_t &AST, bool debug_print) {
    program = AST;
    emit_program(program, debug_print);
}

void output_writer::write_hex(const std::string& filename) {
    std::ofstream output(filename, std::ios::binary | std::ios::out);
    for(auto &it:raw_program){
        uint32_t reverse = Reverse32(it);
        output.write(reinterpret_cast<const char *>(&reverse),4);
    }
}

void output_writer::write_mem(const std::string& filename) {
    std::ofstream output(filename);
    for(auto &it:raw_program){
        output<<std::hex<<it<<std::endl;
    }
}

void output_writer::emit_program(ast_t &sub_program, bool debug_print) {
    std::vector<ast_t> content = sub_program->get_content();
    for(auto &item:content){
        if(item->type == type_instr){
            raw_program.push_back(item->inst.emit());
            if(debug_print) item->inst.print();
        }
        if(item->type == type_code_block){
            emit_program(item, debug_print);
        }
    }
}

std::vector<uint32_t> output_writer::get_raw_program() {
    return raw_program;
}

int output_writer::get_program_size() {
    return raw_program.size();
}
