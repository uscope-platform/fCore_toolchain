//
// Created by fils on 12/07/2021.
//

#ifndef FCORE_HAS_INTRINSICS_IMPLEMENTATION_PASS_HPP
#define FCORE_HAS_INTRINSICS_IMPLEMENTATION_PASS_HPP

#include "passes/pass_base.hpp"
#include "ast/high_level/hl_ast_node.hpp"

class intrinsics_implementation_pass : public  pass_base<hl_ast_node> {
public:
    intrinsics_implementation_pass();
    std::vector<std::shared_ptr<hl_ast_node>> process_node(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return NODE_PASS;};
};


#endif //FCORE_HAS_INTRINSICS_IMPLEMENTATION_PASS_HPP
