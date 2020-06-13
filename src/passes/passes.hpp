//
// Created by fils on 01/05/20.
//

#ifndef FCORE_HAS_PASSES_HPP
#define FCORE_HAS_PASSES_HPP

#include "pass_manager.hpp"
#include "loop_implementation_pass.hpp"
#include "pseudo_instructions_pass.hpp"
#include "instruction_counting_pass.hpp"
#include "register_allocation_pass.hpp"
static pass_manager create_pass_manager(){
    pass_manager manager;
    manager.add_pass(std::make_shared<loop_implementation_pass>());
    manager.add_pass(std::make_shared<pseudo_instructions_pass>());
    manager.add_pass(std::make_shared<register_allocation_pass>());
    //pass = std::make_shared<instruction_counting_pass>();
    //manager.add_pass(pass);
    return manager;
}

#endif //FCORE_HAS_PASSES_HPP
