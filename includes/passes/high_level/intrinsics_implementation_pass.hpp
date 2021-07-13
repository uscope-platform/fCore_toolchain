//
// Created by fils on 12/07/2021.
//

#ifndef FCORE_TOOLCHAIN_INTRINSICS_IMPLEMENTATION_PASS_HPP
#define FCORE_TOOLCHAIN_INTRINSICS_IMPLEMENTATION_PASS_HPP

#include <map>
#include <string>

#include "ast/high_level/hl_expression_node.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "passes/pass_base.hpp"
#include "ast/high_level/hl_ast_node.hpp"

class intrinsics_implementation_pass : public  pass_base<hl_ast_node> {
public:
    intrinsics_implementation_pass();
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;
    std::shared_ptr<hl_ast_node> process_node_by_type(const std::shared_ptr<hl_ast_node>& element);
    std::shared_ptr<hl_ast_node> process_function_call(const std::shared_ptr<hl_function_call_node>& element);
    int get_pass_type() override { return LEAF_PASS;};
private:
    std::map<std::string, expression_type_t> substitutions;
    std::map<std::string, int> n_arguments;
};


#endif //FCORE_TOOLCHAIN_INTRINSICS_IMPLEMENTATION_PASS_HPP
