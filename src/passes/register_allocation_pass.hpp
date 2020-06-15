//
// Created by fils on 13/06/20.
//

#ifndef FCORE_HAS_REGISTER_ALLOCATION_PASS_HPP
#define FCORE_HAS_REGISTER_ALLOCATION_PASS_HPP

#include <memory>
#include <unordered_map>
#include "../frontend/variable_map.hpp"
#include "../code_elements/code_element.hpp"
#include "pass_manager.hpp"
#include "../../include/fCore_isa.hpp"


class register_allocation_pass: public pass_base {
    public:
        explicit register_allocation_pass(std::shared_ptr<variable_map> varmap);
        ast_t process_leaf(ast_t element) override ;

        std::vector<ast_t>process_node(ast_t element) override{
            std::vector<ast_t> elem;
            elem.push_back(element);
            return elem;
        };

        std::vector<int> get_analysis_result() override {return std::vector<int>();};
        void analyze_element(ast_t element) override {};

        int get_pass_type() override { return LEAF_PASS;};
private:
    bool used[16] = {false};
    std::unordered_map<std::shared_ptr<variable>, std::shared_ptr<variable>> register_mapping;
    std::shared_ptr<variable_map> var_map;
};


#endif //FCORE_HAS_REGISTER_ALLOCATION_PASS_HPP
