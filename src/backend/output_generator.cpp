//
// Created by fils on 30/04/20.
//

#include "output_generator.hpp"

output_generator::output_generator(const ast_t &AST, bool debug_print) {
    program = AST;
    progress_counter = 0;
    emit_program(program, debug_print);
}

void output_generator::write_hex_file(const std::string& filename) {
    std::ofstream output(filename, std::ios::binary | std::ios::out);
    for(auto &it:raw_program){
        uint32_t reverse = Reverse32(it);
        output.write(reinterpret_cast<const char *>(&reverse),4);
    }
}

void output_generator::write_mem_file(const std::string& filename) {
    std::ofstream output(filename);
    for(auto &it:raw_program){
        output<<std::hex<<it<<std::endl;
    }
}


std::vector<uint32_t> output_generator::generate_hex(bool endian_swap) {
    std::vector<uint32_t> ret;
    for(auto &it:raw_program){
        if(endian_swap) ret.push_back(Reverse32(it));
        else ret.push_back(it);
    }
    return ret;
}

std::vector<std::string> output_generator::generate_mem() {
    std::vector<std::string> ret;
    for(auto &it:raw_program){
        std::stringstream stream;
        stream << std::hex << it;
        ret.push_back(stream.str());
    }
    return ret;
}


void output_generator::emit_program(ast_t &sub_program, bool debug_print) {
    std::vector<ast_t> content = sub_program->get_content();
    for(auto &item:content){
        if(item->type == type_instr){
            raw_program.push_back(item->inst.emit());
            progress_counter++;
            if(debug_print) {
                std::cout << progress_counter << std::endl;
                item->inst.print();
            }
        }
        if(item->type == type_code_block){
            emit_program(item, debug_print);
        }
    }
}

std::vector<uint32_t> output_generator::get_raw_program() {
    return raw_program;
}

int output_generator::get_program_size() {
    return raw_program.size();
}
