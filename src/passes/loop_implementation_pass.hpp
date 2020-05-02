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
    std::shared_ptr<code_element> process_element_enter( std::shared_ptr<code_element> ) override;
    std::shared_ptr<code_element> process_element_exit(std::shared_ptr<code_element> ) override;
    std::shared_ptr<code_element> deep_copy_element(std::shared_ptr<code_element>);

};


#endif //FCORE_HAS_LOOP_IMPLEMENTATION_PASS_HPP
