//
// Created by fils on 30/04/20.
//

#include "output_writer.hpp"

output_writer::output_writer(const std::shared_ptr<code_element> & AST) {
    program = AST;
    emit_program(program);
}

void output_writer::write_hex(const std::string& filename) {
    std::ofstream output(filename + ".hex",std::ios::binary | std::ios::out);
    for(auto &it:raw_program){
        uint32_t reverse = Reverse32(it);
        output.write(reinterpret_cast<const char *>(&reverse),4);
    }
}

void output_writer::write_mem(const std::string& filename) {
    std::ofstream output(filename + ".mem");
    for(auto &it:raw_program){
        output<<std::hex<<it<<std::endl;
    }
}

void output_writer::emit_program(std::shared_ptr<code_element> &sub_program) {
    std::vector<std::shared_ptr<code_element>> content = sub_program->get_content();
    for(auto &item:content){
        if(item->type == type_instr){
            raw_program.push_back(item->inst.emit());
            item->inst.print();
        }
    }
}

std::vector<uint32_t> output_writer::get_raw_program() {
    return raw_program;
}
