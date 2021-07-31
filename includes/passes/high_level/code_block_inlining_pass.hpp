//
// Created by fils on 31/07/2021.
//

#ifndef FCORE_TOOLCHAIN_CODE_BLOCK_INLINING_PASS_HPP
#define FCORE_TOOLCHAIN_CODE_BLOCK_INLINING_PASS_HPP

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

class code_block_inlining_pass : public pass_base<hl_ast_node>{
public:
    code_block_inlining_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    std::vector<std::shared_ptr<hl_ast_node>> process_element_by_type(std::shared_ptr<hl_ast_node> element);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::vector<std::shared_ptr<hl_ast_node>> process_vector(const std::vector<std::shared_ptr<hl_ast_node>>& elements);
    std::shared_ptr<hl_ast_node> process_loop(std::shared_ptr<hl_ast_loop_node> element);
    std::shared_ptr<hl_ast_node> process_definition(std::shared_ptr<hl_definition_node> element);
    std::shared_ptr<hl_ast_node> process_conditional(std::shared_ptr<hl_ast_conditional_node> element);
};


#endif //FCORE_TOOLCHAIN_CODE_BLOCK_INLINING_PASS_HPP
