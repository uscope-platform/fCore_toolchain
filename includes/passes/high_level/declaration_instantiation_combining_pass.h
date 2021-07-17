//
// Created by fils on 17/07/2021.
//

#ifndef FCORE_TOOLCHAIN_DECLARATION_INSTANTIATION_COMBINING_PASS_H
#define FCORE_TOOLCHAIN_DECLARATION_INSTANTIATION_COMBINING_PASS_H

#include "passes/pass_base.hpp"
#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "ast/high_level/hl_expression_node.hpp"

class declaration_instantiation_combining_pass : public pass_base<hl_ast_node> {
public:
    declaration_instantiation_combining_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};
};


#endif //FCORE_TOOLCHAIN_DECLARATION_INSTANTIATION_COMBINING_PASS_H
