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
// limitations under the License.02/07/2021.
//

#include "passes/instruction_stream/bound_register_mapping.hpp"

namespace fcore{

    bound_register_mapping_pass::bound_register_mapping_pass() : stream_pass_base("Bound register mapping" , 1){

    }

    std::shared_ptr<instruction>
    bound_register_mapping_pass::apply_pass(std::shared_ptr<instruction> element, uint32_t n) {

        switch (element->get_type()) {
            case isa_intercalated_constant:
            case isa_independent_instruction:
            case isa_pseudo_instruction:
                return element;
            case isa_register_instruction:
                return process_reg_instr(std::static_pointer_cast<register_instruction>(element));
            case isa_conversion_instruction:
                return process_conv_instr(std::static_pointer_cast<conversion_instruction>(element));
            case isa_load_constant_instruction:
                return process_load_instr(std::static_pointer_cast<load_constant_instruction>(element));
            case isa_ternary_instruction:
                return process_ternary_instr(std::static_pointer_cast<ternary_instruction>(element));
            default:
                throw std::runtime_error("ERROR: unknown instruction type");
        }

        return element;
    }

    std::shared_ptr<instruction>
    bound_register_mapping_pass::process_reg_instr(std::shared_ptr<register_instruction> node) {

        std::string raw_dest = node->get_destination()->get_name();
        int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
        node->get_destination()->set_bound_reg(dest);

        std::string raw_op_a = node->get_operand_a()->get_name();
        int op_a = std::stoi(raw_op_a.substr(1, raw_op_a.size()-1));
        node->get_operand_a()->set_bound_reg(op_a);

        std::string raw_op_b = node->get_operand_b()->get_name();
        int op_b = std::stoi(raw_op_b.substr(1, raw_op_b.size()-1));
        node->get_operand_b()->set_bound_reg(op_b);


        return node;
    }

    std::shared_ptr<instruction>
    bound_register_mapping_pass::process_conv_instr(std::shared_ptr<conversion_instruction> node) {
        std::string raw_dest = node->get_destination()->get_name();
        int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
        node->get_destination()->set_bound_reg(dest);

        std::string raw_src = node->get_source()->get_name();
        int src = std::stoi(raw_src.substr(1, raw_src.size()-1));
        node->get_source()->set_bound_reg(src);

        return node;
    }

    std::shared_ptr<instruction>
    bound_register_mapping_pass::process_load_instr(std::shared_ptr<load_constant_instruction> node) {

        std::string raw_dest = node->get_destination()->get_name();
        int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
        node->get_destination()->set_bound_reg(dest);

        return node;
    }

    std::shared_ptr<instruction>
    bound_register_mapping_pass::process_ternary_instr(const std::shared_ptr<ternary_instruction>& node) {

        std::string raw_dest = node->get_destination()->get_name();
        int dest = std::stoi(raw_dest.substr(1, raw_dest.size()-1));
        node->get_destination()->set_bound_reg(dest);

        std::string raw_op_a = node->get_operand_a()->get_name();
        int op_a = std::stoi(raw_op_a.substr(1, raw_op_a.size()-1));
        node->get_operand_a()->set_bound_reg(op_a);

        std::string raw_op_b = node->get_operand_b()->get_name();
        int op_b = std::stoi(raw_op_b.substr(1, raw_op_b.size()-1));
        node->get_operand_b()->set_bound_reg(op_b);


        std::string raw_op_c = node->get_operand_c()->get_name();
        int op_c = std::stoi(raw_op_c.substr(1, raw_op_c.size()-1));
        node->get_operand_c()->set_bound_reg(op_c);
        return node;
    }
}

