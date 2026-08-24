//  Copyright  2026 University of Nottingham
//  Author: Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
#include "fuzzer/fuzzer.hpp"


namespace fcore {
    fuzzer::fuzzer(const fuzzer_config& config) : rng(config.rng_seed, config.rng_float_params), config(config){
        if (config.max_inputs > config.active_regs){
            throw std::runtime_error("There needs to be enough registers active to fit all the possible inputs");
        }
    }

    fuzzing_package fuzzer::generate_binary() {
        fuzzing_package result;
        std::vector<uint32_t> active_registers;
        instruction_stream program;
        uint8_t n_inputs = rng.generate_int({config.min_inputs, config.max_inputs});
        for (int i = 0; i < n_inputs; i++){
            int reg_n = 0;
            do {
                reg_n =  rng.generate_int({1, config.active_regs});
            } while (result.inputs.contains(reg_n));
            active_registers.push_back(reg_n);
            result.inputs[reg_n] = rng.generate_float();
        }
        auto size = rng.generate_int({config.min_program_size, config.max_program_size});

        for (int i = 0; i < size; i++) {
            auto reg_n =  rng.generate_int({1, config.active_regs});
            program.push_back(generate_instruction(reg_n, active_registers));
            if (!std::ranges::contains(active_registers, reg_n)) active_registers.push_back(reg_n);
        }
        program.push_back(instruction_variant(independent_instruction(opcode_stop)));
        result.binary = compile_binary(program);
        return result;
    }

    std::vector<uint32_t> fuzzer::compile_binary(const instruction_stream& s){

        std::shared_ptr<instrumentation_core> ic = nullptr;

        std::vector<int> io_res;
        stream_pass_manager sman(io_res, ic, stream_pass_manager::asm_language);


        instruction_stream program_stream = sman.process_stream(s);

        auto amap = std::make_shared<std::map<std::string, std::vector<io_map_entry>>>();

        std::map<std::string, std::vector<uint32_t>> dma_map;

        for(auto &item:dma_map){
            io_map_entry e(-1,item.second[0],"m");
            amap->insert({item.first, {e}});
        }
        binary_generator writer;
        writer.process_stream(program_stream, dma_map, amap, false);
        return writer.generate_hex(false);
    }

    instruction_variant fuzzer::generate_instruction(uint32_t dest,std::vector<uint32_t>& active_registers) {
        auto max_opcode = opcode_inputs_bounds[std::min<size_t>(3, active_registers.size())];
        auto idx = rng.generate_int({0, max_opcode-1});
        auto opcode = opcodes[idx];
        switch (fcore_op_types[opcode]) {
            case isa_conversion_instruction:
                return instruction_variant(generate_conversion_instruction(opcode, dest, active_registers));
            case isa_register_instruction:
                return instruction_variant(generate_register_instruction(opcode, dest, active_registers));
            case isa_load_constant_instruction:
                return instruction_variant(generate_constant_instruction(opcode, dest, active_registers));
            case isa_ternary_instruction:
                return instruction_variant(generate_ternary_instruction(opcode, dest, active_registers));
            case isa_independent_instruction:
            case isa_pseudo_instruction:
            default:
                throw std::runtime_error("attempted generation of an instruction type unsuitable for fuzzing");
        }
    }
    conversion_instruction fuzzer::generate_conversion_instruction(opcode_table_t op, uint32_t dest, std::vector<unsigned int>& available_inputs){
        std::string dst = "r" + std::to_string(dest);
        return {op,
            std::make_shared<variable>(generate_register(available_inputs)),
            std::make_shared<variable>(dst)
        };
    }

    register_instruction fuzzer::generate_register_instruction(opcode_table_t op, uint32_t dest, std::vector<unsigned int>& available_inputs){
        std::string dst = "r" + std::to_string(dest);
        return {
            op,
            std::make_shared<variable>(generate_register(available_inputs)),
            std::make_shared<variable>(generate_register(available_inputs)),
            std::make_shared<variable>(dst)
        };
    }

    load_constant_instruction fuzzer::generate_constant_instruction(opcode_table_t op, uint32_t dest, std::vector<unsigned int>& available_inputs){
        std::string dst = "r" + std::to_string(dest);
        auto c_val = rng.generate_float();
        auto c = std::make_shared<variable>("constant" + std::to_string(c_val), c_val);
        return {
            op,
            std::make_shared<variable>(dst),
            c
        };
    }

    ternary_instruction fuzzer::generate_ternary_instruction(opcode_table_t op, uint32_t dest, std::vector<unsigned int>& available_inputs){
        std::string dst = "r" + std::to_string(dest);
        return {
            op,
            std::make_shared<variable>(dst),
            std::make_shared<variable>(generate_register(available_inputs)),
            std::make_shared<variable>(generate_register(available_inputs)),
            std::make_shared<variable>(dst)
        };
    }

    std::string fuzzer::generate_register(std::vector<unsigned int>& available_inputs) {
        auto reg = available_inputs[rng.generate_int({0, available_inputs.size()-1})];
        if (!std::ranges::contains(available_inputs, reg)) available_inputs.push_back(reg);
        return "r" + std::to_string(reg);
    }
}
