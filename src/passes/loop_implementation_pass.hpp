//
// Created by fils on 01/05/20.
//

#ifndef FCORE_HAS_LOOP_IMPLEMENTATION_PASS_HPP
#define FCORE_HAS_LOOP_IMPLEMENTATION_PASS_HPP

#include <memory>
#include "../code_elements/code_element.hpp"
#include "pass_manager.hpp"

class loop_implementation_pass : public pass_base {

public:
    std::vector<ast_t>process_node(ast_t element) override;
    ast_t process_leaf(ast_t element) override {
        return element;
    };
    void analyze_element(ast_t element) override {};
    std::vector<int> get_analysis_result() override {return std::vector<int>();};
    int get_pass_type() override { return NODE_PASS;};
};


#endif //FCORE_HAS_LOOP_IMPLEMENTATION_PASS_HPP
