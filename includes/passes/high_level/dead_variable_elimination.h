//
// Created by fils on 16/07/2021.
//

#ifndef FCORE_TOOLCHAIN_DEAD_VARIABLE_ELIMINATION_H
#define FCORE_TOOLCHAIN_DEAD_VARIABLE_ELIMINATION_H

#include "passes/pass_base.hpp"
#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "frontend/variable_map.hpp"


class dead_variable_elimination : public pass_base<hl_ast_node>{
public:
    explicit dead_variable_elimination();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};


};


#endif //FCORE_TOOLCHAIN_DEAD_VARIABLE_ELIMINATION_H
