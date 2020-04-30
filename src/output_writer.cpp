//
// Created by fils on 30/04/20.
//

#include "output_writer.hpp"





output_writer::output_writer(const std::vector<uint32_t>& in_program) {
    program = in_program;
}

void output_writer::write_hex(const std::string& filename) {
    std::ofstream output(filename + ".hex",std::ios::binary | std::ios::out);
    for(auto &it:program){
        uint32_t reverse = Reverse32(it);
        output.write(reinterpret_cast<const char *>(&reverse),4);
    }
}

void output_writer::write_mem(const std::string& filename) {
    std::ofstream output(filename + ".mem");
    for(auto &it:program){
        output<<std::hex<<it<<std::endl;
    }
}
