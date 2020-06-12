//
// Created by fils on 11/05/20.
//

#include "instruction_counting_pass.hpp"

void instruction_counting_pass::analyze_element(ast_t element) {
    if(element->type==type_instr){
        int count = element->inst.instruction_count();
        if(count==1)
            instruction_count += count;
        else
            throw std::runtime_error("Instruction counting in brancing code is not supported");
    }

}

std::vector<int> instruction_counting_pass::get_analysis_result() {
    std::vector<int> result_count = {instruction_count};
    return result_count;
}
