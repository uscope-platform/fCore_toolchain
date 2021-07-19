//
// Created by fils on 18/07/2021.
//

#ifndef FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP
#define FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP

#include <unordered_map>

#include "passes/pass_base.hpp"
#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "frontend/variable_map.hpp"

class constant_propagation :public pass_base<hl_ast_node> {
public:
    explicit constant_propagation(std::shared_ptr<variable_map>  &v);
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    std::shared_ptr<hl_ast_node> substitute_constant(std::shared_ptr<hl_ast_node> element);
    std::shared_ptr<hl_ast_operand> process_operand(std::shared_ptr<hl_ast_operand> element);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::unordered_map<std::string, std::shared_ptr<hl_ast_operand>> constants_map;
    std::shared_ptr<variable_map> var_map;
};


#endif //FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP
