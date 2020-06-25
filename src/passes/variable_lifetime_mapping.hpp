//
// Created by fils on 17/06/20.
//

#ifndef FCORE_HAS_VARIABLE_LIFETIME_MAPPING_HPP
#define FCORE_HAS_VARIABLE_LIFETIME_MAPPING_HPP


#include "../code_elements/code_element.hpp"
#include "../frontend/variable_map.hpp"
#include "pass_manager.hpp"

#include <utility>

class variable_lifetime_mapping: public pass_base {
public:
    explicit variable_lifetime_mapping(std::shared_ptr<variable_map> var_map);
    ast_t process_leaf(ast_t element) override ;
    int get_pass_type() override { return LEAF_PASS;};
private:
    int variable_detection_ctr;
    std::shared_ptr<variable_map> vmap;
};



#endif //FCORE_HAS_VARIABLE_LIFETIME_MAPPING_HPP
