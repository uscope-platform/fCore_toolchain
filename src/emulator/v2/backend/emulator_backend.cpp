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

#include "emulator/v2/backend/emulator_backend.hpp"

namespace fcore::emulator_v2{


    void emulator_backend::setup_memory(
            std::shared_ptr<std::vector<uint32_t>> channel_mem,
            const std::shared_ptr<std::vector<uint32_t>> &common_mem
    ) {
        spdlog::trace("Setup memory");
        working_memory = std::move(channel_mem);
        common_io = common_mem;

    }

    void emulator_backend::run_round(
            int init_point
    ) {


        for(current_instruction = init_point; current_instruction<prog.size(); current_instruction++){

            bool skip_breakpoint = current_instruction == init_point;
            auto opcode = get_opcode(prog[current_instruction].instruction);
            auto operands  = get_operands(prog[current_instruction].instruction);
            auto io_flags =get_common_io_flags(prog[current_instruction].instruction);

            if(breakpoints.contains(current_instruction) & !skip_breakpoint & debugging_enabled){
                spdlog::trace("Breakpoint Hit at line {0}",  current_instruction);
                throw BreakpointException(produce_checkpoint(false));
            }

            spdlog::trace("Running instruction {0}: opcode = {1}", current_instruction, fcore_opcodes_reverse[opcode]);

            if(opcode == fcore_opcodes["ldc"]){
                run_load_constant_instruction(operands[0], prog[current_instruction].load_constant);
            } else{
                run_instruction_by_type(opcode, operands, io_flags);
            }
            if(stop_requested){
                break;
            }
        }
        current_instruction = -1;
        stop_requested = false;

    }

    debug_checkpoint emulator_backend::step_over() {
        if(current_instruction == -1) {
            reset_instruction_pointer();
        };
        auto opcode = get_opcode(prog[current_instruction].instruction);
        auto operands  = get_operands(prog[current_instruction].instruction);
        auto io_flags =get_common_io_flags(prog[current_instruction].instruction);
        if(opcode == fcore_opcodes["ldc"]){
            run_load_constant_instruction(operands[0], prog[current_instruction].load_constant);
        } else{
            run_instruction_by_type(opcode, operands, io_flags);
        }

        debug_checkpoint res;


        if(stop_requested){
            current_instruction = 0;
            res =  produce_checkpoint(true);
            stop_requested = false;
        } else {
            current_instruction++;
            res =  produce_checkpoint(false);
        }

        return res;
    }

    void emulator_backend::run_instruction_by_type(const uint32_t& raw_opcode, std::array<uint32_t, 3> operands, std::array<bool, 3> io_flags) {
        auto opcode = static_cast<opcode_table_t>(raw_opcode);
        switch (fcore_op_types[fcore_opcodes_reverse[opcode]]) {
            case isa_independent_instruction:
                run_independent_instruction(opcode, operands);
                break;
            case isa_register_instruction:
                run_register_instruction(opcode,operands, io_flags);
                break;
            case isa_conversion_instruction:
                run_conversion_instruction(opcode, operands, io_flags);
                break;
            case isa_ternary_instruction:
                run_ternary_instruction(opcode,operands, io_flags);
                break;
            default:
                break;
        }
    }

    void emulator_backend::run_ternary_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands, std::array<bool, 3> io_flags) {

        uint32_t op_a = operands[0];
        uint32_t op_b = operands[1];
        uint32_t op_c = operands[2];

        uint32_t a,b,c;

        if(io_flags[0]){
            a = common_io->at(op_a);
        } else {
            a = working_memory->at(op_a);
        }

        if(io_flags[1]){
            b = common_io->at(op_b);
        } else {
            b = working_memory->at(op_b);
        }

        if(io_flags[2]){
            c = common_io->at(op_c);
        } else {
            c = working_memory->at(op_c);
        }

        uint32_t result;
        uint32_t writeback_address = op_a;
        switch (opcode) {
            case opcode_csel:
                result = execute_csel(a, b, c);
                break;
            default:
                throw std::runtime_error("Encountered the following unimplemented operation: " + fcore_opcodes_reverse[opcode]);
        }

        working_memory->at(writeback_address) = result;
    }

    void emulator_backend::run_register_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands, std::array<bool, 3> io_flags) {


        uint32_t dest = operands[2];
        uint32_t op_a = operands[0];
        uint32_t op_b = operands[1];


        uint32_t a, b;
        if(io_flags[0]){
            a = common_io->at(op_a);
        } else {
            a = working_memory->at(op_a);
        }

        if(io_flags[1]){
            b = common_io->at(op_b);
        } else {
            b = working_memory->at(op_b);
        }

        uint32_t result;
        uint32_t writeback_address = dest;
        switch (opcode) {
            case opcode_add:
                result = exec.execute_add(a, b);
                break;
            case opcode_sub:
                result = exec.execute_sub(a, b);
                break;
            case opcode_mul:
                result = exec.execute_mul(a, b);
                break;
            case opcode_and:
                result = exec.execute_and(a, b);
                break;
            case opcode_or:
                result = exec.execute_or(a, b);
                break;
            case opcode_xor:
                result = exec.execute_xor(a, b);
                break;
            case opcode_satp:
                result = exec.execute_satp(a, b);
                break;
            case opcode_satn:
                result  = exec.execute_satn(a, b);
                break;
            case opcode_beq:
                result = exec.execute_compare_eq(a, b, comparator_type);
                break;
            case opcode_bne:
                result = exec.execute_compare_ne(a, b, comparator_type);
                break;
            case opcode_bgt:
                result = exec.execute_compare_gt(a, b, comparator_type);
                break;
            case opcode_ble:
                result = exec.execute_compare_le(a, b, comparator_type);
                break;
            case opcode_efi:
                return execute_efi(op_a, op_b, dest);
            case opcode_bset:
                result = execute_bset(working_memory->at(op_a), working_memory->at(op_b), working_memory->at(dest));
                writeback_address = op_a;
                break;
            case opcode_bsel:
                result = execute_bsel(a, b);
                break;
            default:
                throw std::runtime_error("Encountered the following unimplemented operation: " + fcore_opcodes_reverse[opcode]);
        }

        working_memory->at(writeback_address) = result;
    }

    void emulator_backend::run_independent_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands) {

        switch (opcode) {
            case opcode_nop:
                break;
            case opcode_stop:
                stop_requested = true;
                break;
            default:
                throw std::runtime_error("Encountered the following unimplemented operation: " + fcore_opcodes_reverse[opcode]);
        }

    }

    void emulator_backend::run_conversion_instruction(opcode_table_t opcode, const std::array<uint32_t, 3> &operands, std::array<bool, 3> io_flags) {


        uint32_t src;
        if(io_flags[0]){
            src = common_io->at(operands[0]);
        } else {
            src = working_memory->at(operands[0]);
        }
        uint32_t dest = operands[1];

        uint32_t result;

        switch (opcode) {
            case opcode_rec:
                result = exec.execute_rec(src);
                break;
            case opcode_fti:
                result = exec.execute_fti(src);
                break;
            case opcode_itf:
                result = exec.execute_itf(src);
                break;
            case opcode_not:
                result = exec.execute_not(src);
                break;
            case opcode_abs:
                result = exec.execute_abs(src);
                break;
            case opcode_popcnt:
                result = exec.execute_popcnt(src);
                break;
            default:
                throw std::runtime_error("Encountered the following unimplemented operation: " + fcore_opcodes_reverse[opcode]);
        }

        working_memory->at(dest) = result;

    }

    void emulator_backend::run_load_constant_instruction(uint32_t dest, uint32_t val) {
        working_memory->at(dest) = val;
    }


    uint32_t emulator_backend::execute_or(uint32_t a, uint32_t b) {
        return exec.execute_or(a,b);
    }


    void emulator_backend::execute_efi(uint32_t op_a, uint32_t op_b, uint32_t dest) {
        efi_backend.emulate_efi(efi_selector, op_a, op_b, dest, working_memory);
    }


    uint32_t emulator_backend::float_to_uint32(float f) {
        return gp_executor::float_to_uint32(f);
    }

    float emulator_backend::uint32_to_float(uint32_t u) {
        return gp_executor::uint32_to_float(u);
    }

    uint32_t emulator_backend::execute_bset(uint32_t a, uint32_t b, uint32_t c){
        return exec.execute_bset(a,b,c);
    }

    uint32_t emulator_backend::execute_bsel(uint32_t a, uint32_t b) {
        return exec.execute_bsel(a, b);
    }

    uint32_t emulator_backend::execute_xor(uint32_t a, uint32_t b) {
        return exec.execute_xor(a, b);
    }


    uint32_t emulator_backend::execute_csel(uint32_t a, uint32_t b, uint32_t c) {
        return exec.execute_csel(a, b, c);
    }

    uint32_t emulator_backend::process_comparison_output(bool val) {

        if(comparator_type== comparator_full) {
            if(val){
                return 0xffffffff;
            } else {
                return 0;
            }
        } else if(comparator_type==comparator_reducing){
            return val;
        } else if(comparator_type == comparator_none) {
            throw std::runtime_error("The emulator has encountered a comparison instruction on core "+core_name+" which does not have comparators.");
        } else{
            throw std::runtime_error("The emulator has encountered a comparison instruction, however an unknown type was selected in the spec file");
        }
    }

    debug_checkpoint emulator_backend::produce_checkpoint(bool round_complete) {
        debug_checkpoint ret;
        ret.core_name = core_name;
        ret.completed_round = round_complete;
        ret.memory_view = *working_memory;
        ret.breakpoint = current_instruction;
        if(round_complete)
            ret.status = "complete";
        else
            ret.status = "in_progress";
        return ret;
    }

}
