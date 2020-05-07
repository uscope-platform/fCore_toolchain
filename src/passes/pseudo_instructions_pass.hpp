//
// Created by fils on 06/05/20.
//

#ifndef FCORE_HAS_PSEUDO_INSTRUCTIONS_PASS_HPP
#define FCORE_HAS_PSEUDO_INSTRUCTIONS_PASS_HPP

#include <memory>
#include "../code_elements/code_element.hpp"
#include "pass_manager.hpp"
#include "../../include/fCore_isa.hpp"
class pseudo_instructions_pass: public pass_base {

public:
    //std::vector<std::shared_ptr<code_element>> process_element( std::shared_ptr<code_element> ) override;
    std::vector<std::shared_ptr<code_element>> process_node(std::shared_ptr<code_element> element) override;
    std::shared_ptr<code_element> process_leaf(std::shared_ptr<code_element> element) override ;
    int get_pass_type() override { return LEAF_PASS;};
};


#endif //FCORE_HAS_PSEUDO_INSTRUCTIONS_PASS_HPP
