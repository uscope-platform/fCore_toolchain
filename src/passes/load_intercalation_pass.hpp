//
// Created by fils on 26/06/2020.
//

#ifndef FCORE_HAS_LOAD_INTERCALATION_PASS_HPP
#define FCORE_HAS_LOAD_INTERCALATION_PASS_HPP

#include "../code_elements/code_element.hpp"
#include "../frontend/variable_map.hpp"
#include "pass_manager.hpp"


class load_intercalation_pass: public pass_base {
public:
    ast_t process_leaf(ast_t element) override ;
    int get_pass_type() override { return LEAF_PASS;};
};

#endif //FCORE_HAS_LOAD_INTERCALATION_PASS_HPP
