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

#include "frontend/binary_loader.hpp"

fcore::binary_loader::binary_loader(std::istream &stream, bin_loader_input_type_t in_type) {
    std::string line;
    std::vector<uint32_t> file_content;

    if(in_type == bin_loader_hex_input){
        uint32_t instr = 0;
        while(stream.read(reinterpret_cast<char*>(&instr), sizeof(uint32_t))){
            file_content.push_back(to_littleEndian(instr));
        }
    } else if(in_type == bin_loader_mem_input){
        while (std::getline(stream, line)) {
            uint32_t instr = std::stoul(line, nullptr, 16);
            file_content.push_back(instr);
        }
    }

    load_program(file_content);
}

fcore::binary_loader::binary_loader(const std::vector<uint32_t> &file_content) {
    load_program(file_content);
}

void fcore::binary_loader::load_program(const std::vector<uint32_t> &file_content) {

    executable exec(file_content);
    construct_ast(exec.get_code());
    io_mapping = exec.get_io_mapping();
}


void fcore::binary_loader::construct_ast(const std::vector<uint32_t> &program) {
    ast_root = std::make_shared<ll_ast_node>(ll_type_program_head);

    for(auto it = std::begin(program); it != std::end(program); it++){
        uint32_t instruction = *it;
        uint32_t opcode = instruction & (1<<fcore_opcode_width)-1;
        if (fcore_opcodes_reverse.count(opcode)==0){
            throw std::runtime_error("unknown opcode: " + std::to_string(opcode));
        }
        switch (fcore_op_types[fcore_opcodes_reverse[opcode]]) {
            case isa_independent_instruction:
                ast_root->add_content(process_independent_instruction(instruction));
                break;
            case isa_register_instruction:
                ast_root->add_content(process_register_instr(instruction));
                break;
            case isa_conversion_instruction:
                ast_root->add_content(process_conversion_instr(instruction));
                break;
            case isa_load_constant_instruction:{
                ast_root->add_content(process_load_constant(instruction,*(it + 1)));
                ++it;
                break;
            }
            case isa_ternary_instruction:{
                ast_root->add_content(process_ternary_instr(instruction));
                break;
            }
            // Pseudo instructions and intercalated constants are either not present in the stream, or dont have an opcode
            case isa_pseudo_instruction:
            case isa_intercalated_constant:
                throw std::runtime_error("something went wront during binary program loading.");
                break;
        }

    }
}

std::shared_ptr<fcore::ll_ast_node> fcore::binary_loader::process_register_instr(uint32_t instruction) {
    uint32_t opcode = instruction & (1<<fcore_opcode_width)-1;

    uint32_t operand_a = (instruction >> fcore_opcode_width) & (1<<fcore_register_address_width)-1;
    uint32_t operand_b = (instruction >> (fcore_opcode_width+fcore_register_address_width)) & (1<<fcore_register_address_width)-1;
    uint32_t destination = (instruction >> (fcore_opcode_width+2*fcore_register_address_width)) & (1<<fcore_register_address_width)-1;

    std::shared_ptr<variable> op_a_var = std::make_shared<variable>("r" + std::to_string(operand_a));
    std::shared_ptr<variable> op_b_var  = std::make_shared<variable>("r" + std::to_string(operand_b));
    std::shared_ptr<variable> dest_var  = std::make_shared<variable>("r" + std::to_string(destination));

    return std::make_shared<ll_register_instr_node>(fcore_opcodes_reverse[opcode], op_a_var, op_b_var, dest_var);
}

std::shared_ptr<fcore::ll_ast_node> fcore::binary_loader::process_ternary_instr(uint32_t instruction) {
    uint32_t opcode = instruction & (1<<fcore_opcode_width)-1;

    uint32_t operand_a = (instruction >> fcore_opcode_width) & (1<<fcore_register_address_width)-1;
    uint32_t operand_b = (instruction >> (fcore_opcode_width+fcore_register_address_width)) & (1<<fcore_register_address_width)-1;
    uint32_t operand_c = (instruction >> (fcore_opcode_width+2*fcore_register_address_width)) & (1<<fcore_register_address_width)-1;

    std::shared_ptr<variable> op_a_var = std::make_shared<variable>("r" + std::to_string(operand_a));
    std::shared_ptr<variable> op_b_var  = std::make_shared<variable>("r" + std::to_string(operand_b));
    std::shared_ptr<variable> op_c_var  = std::make_shared<variable>("r" + std::to_string(operand_c));
    std::shared_ptr<variable> dest_var  = std::make_shared<variable>("r" + std::to_string(operand_a));

    return std::make_shared<ll_ternary_instr_node>(fcore_opcodes_reverse[opcode], op_a_var, op_b_var, op_c_var, dest_var);
}


std::shared_ptr<fcore::ll_ast_node> fcore::binary_loader::process_independent_instruction(uint32_t instruction) {
    uint32_t opcode = instruction & (1<<fcore_opcode_width)-1;

    return std::make_shared<ll_independent_inst_node>(fcore_opcodes_reverse[opcode]);;
}

std::shared_ptr<fcore::ll_ast_node> fcore::binary_loader::process_load_constant(uint32_t instruction, uint32_t raw_constant) {
    float constant;
    std::memcpy(&constant, &raw_constant, sizeof(float));

    uint32_t opcode = instruction & (1<<fcore_opcode_width)-1;
    uint32_t destination = (instruction >> fcore_opcode_width) & (1<<fcore_register_address_width)-1;

    std::shared_ptr<variable> dest_var  = std::make_shared<variable>("r" + std::to_string(destination));
    std::shared_ptr<variable> f_const  = std::make_shared<variable>("constant", constant);

    return std::make_shared<ll_load_constant_instr_node>(fcore_opcodes_reverse[opcode],dest_var, f_const);
}

std::shared_ptr<fcore::ll_ast_node> fcore::binary_loader::process_conversion_instr(uint32_t instruction) {
    uint32_t opcode = instruction & (1<<fcore_opcode_width)-1;
    uint32_t source = (instruction >> fcore_opcode_width) & (1<<fcore_register_address_width)-1;
    uint32_t destination = (instruction >> (fcore_opcode_width+fcore_register_address_width)) & (1<<fcore_register_address_width)-1;

    std::shared_ptr<variable> source_var = std::make_shared<variable>("r" + std::to_string(source));
    std::shared_ptr<variable> dest_var  = std::make_shared<variable>("r" + std::to_string(destination));

    return std::make_shared<ll_conversion_instr_node>(fcore_opcodes_reverse[opcode], source_var, dest_var);
}

uint32_t fcore::binary_loader::to_littleEndian(uint32_t in_num) {
    uint8_t in_bytes[4];

    in_bytes[0] = (in_num & 0x000000ff);
    in_bytes[1] = (in_num & 0x0000ff00) >> 8;
    in_bytes[2] = (in_num & 0x00ff0000) >> 16;
    in_bytes[3] = (in_num & 0xff000000) >> 24;
    return (in_bytes[3]<<0) | (in_bytes[2]<<8) | (in_bytes[1]<<16) | (in_bytes[0]<<24);
}

std::unordered_map <uint16_t, uint16_t> fcore::binary_loader::get_io_mapping() {
    std::unordered_map<uint16_t, uint16_t> ret_val;
    for(auto &item:io_mapping){
        ret_val[item.first] = item.second;
    }
    return ret_val;
}

std::set<fcore::io_map_entry> fcore::binary_loader::get_io_mapping_set() {
    std::set<io_map_entry> ret_val = {};
    for(auto &item:io_mapping){
        io_map_entry e(item.first, item.second, "");
       ret_val.insert(e);
    }
    return ret_val;
}
