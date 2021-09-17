// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "backend/binary_generator.hpp"


void binary_generator::process_stream(const instruction_stream& stream, bool debug_print) {
    for(const auto& item:stream){
        raw_program.push_back(item->emit());
        progress_counter++;
        if(debug_print) {
            std::cout << progress_counter << std::endl;
            item->print();
        }
    }

}

void binary_generator::write_hex_file(const std::string& filename) {
    std::ofstream output(filename, std::ios::binary | std::ios::out);
    for(auto &it:raw_program){
        uint32_t reverse = Reverse32(it);
        output.write(reinterpret_cast<const char *>(&reverse),4);
    }
}

void binary_generator::write_mem_file(const std::string& filename) {
    std::ofstream output(filename);
    for(auto &it:raw_program){
        output<<std::hex<<it<<std::endl;
    }
}


std::vector<uint32_t> binary_generator::generate_hex(bool endian_swap) {
    std::vector<uint32_t> ret;
    for(auto &it:raw_program){
        if(endian_swap) ret.push_back(Reverse32(it));
        else ret.push_back(it);
    }
    return ret;
}

std::vector<std::string> binary_generator::generate_mem() {
    std::vector<std::string> ret;
    for(auto &it:raw_program){
        std::stringstream stream;
        stream << std::hex << it;
        ret.push_back(stream.str());
    }
    return ret;
}

std::vector<uint32_t> binary_generator::get_raw_program() {
    return raw_program;
}

int binary_generator::get_program_size() {
    return raw_program.size();
}
