//
// Created by fils on 11/05/20.
//

#ifndef FCORE_HAS_INSTRUCTION_COUNTING_PASS_HPP
#define FCORE_HAS_INSTRUCTION_COUNTING_PASS_HPP

#include "pass_manager.hpp"

class instruction_counting_pass : public pass_base {

    void analyze_element(ast_t element) override;
    int get_pass_type() override { return ANALYSIS_PASS;};
    std::vector<int> get_analysis_result() override;
    int instruction_count{0};
};


#endif //FCORE_HAS_INSTRUCTION_COUNTING_PASS_HPP
