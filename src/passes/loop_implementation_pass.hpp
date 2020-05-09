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
    std::vector<std::shared_ptr<code_element>>process_node(std::shared_ptr<code_element> element) override;
    std::shared_ptr<code_element> process_leaf(std::shared_ptr<code_element> element) override {
        return element;
    };
    int get_pass_type() override { return NODE_PASS;};
};


#endif //FCORE_HAS_LOOP_IMPLEMENTATION_PASS_HPP
