//
// Created by fils on 05/07/2021.
//

#ifndef FCORE_HAS_FUNCTION_INLINING_PASS_H
#define FCORE_HAS_FUNCTION_INLINING_PASS_H

#include "ast/high_level/hl_ast_node.h"
#include "ast/high_level/hl_function_def_node.h"
#include "passes/pass_base.hpp"

#include <utility>

class function_inlining_pass :public pass_base<hl_ast_node>{
public:
    function_inlining_pass();
    void set_functions_map(std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> map);
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;

    std::shared_ptr<hl_ast_node> substitute_arguments(const std::shared_ptr<hl_ast_node> &statement, std::unordered_map<std::string, std::shared_ptr<hl_ast_node>>& parameters);
    int get_pass_type() override { return LEAF_PASS;};
private:
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> functions_map;
};


#endif //FCORE_HAS_FUNCTION_INLINING_PASS_H
