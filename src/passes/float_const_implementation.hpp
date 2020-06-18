//
// Created by fils on 15/06/20.
//

#ifndef FCORE_HAS_FLOAT_CONST_IMPLEMENTATION_HPP
#define FCORE_HAS_FLOAT_CONST_IMPLEMENTATION_HPP

#include "../code_elements/code_element.hpp"
#include "../frontend/variable_map.hpp"
#include "pass_manager.hpp"
#define MAX_ALLOWABLE_SHIFT 8

#include <cmath>
#include <iomanip>
#include <memory>
#include <cstdlib>


class float_const_implementation: public pass_base {
public:
    explicit float_const_implementation(std::shared_ptr<variable_map> var_map);
    ast_t process_leaf(ast_t element) override ;
    int get_pass_type() override { return LEAF_PASS;};
private:
    static std::vector<int> rationalize_constant(double constant);
    std::shared_ptr<code_element> create_block(std::vector<int> frac, std::vector<std::shared_ptr<variable>> op_args);
    std::shared_ptr<variable_map> vmap;
};



#endif //FCORE_HAS_FLOAT_CONST_IMPLEMENTATION_HPP
