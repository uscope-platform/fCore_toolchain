//
// Created by fils on 07/07/2021.
//

#ifndef FCORE_HAS_NORMALIZATION_PASS_H
#define FCORE_HAS_NORMALIZATION_PASS_H



#include "code_elements/hl_ast/hl_ast_node.h"
#include "code_elements/hl_ast/hl_function_def_node.h"
#include "code_elements/hl_ast/hl_function_call_node.h"
#include "passes/pass_manager_base.hpp"

class normalization_pass : public pass_base<hl_ast_node> {
public:
    normalization_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    std::shared_ptr<hl_ast_node> process_node_by_type_top(std::shared_ptr<hl_ast_node> n);
    std::vector<std::pair<int, std::shared_ptr<hl_ast_node>>> process_node_expr_inner(std::shared_ptr<hl_expression_node> n);
    std::shared_ptr<hl_expression_node> produce_normalized_expression(std::shared_ptr<hl_expression_node> original_node, const std::vector<std::pair<int, std::shared_ptr<hl_ast_node>>>& extracted_intermediate);
    std::shared_ptr<hl_definition_node> process_node_def(std::shared_ptr<hl_definition_node> n);
    std::shared_ptr<hl_expression_node> process_node_exp(std::shared_ptr<hl_expression_node> n);
    std::shared_ptr<hl_ast_operand> extract_intermediate_expression(std::shared_ptr<hl_expression_node> n, int side);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    int intermediate_ordinal = 0;
    std::vector<std::shared_ptr<hl_definition_node>> additional_statements;
};


#endif //FCORE_HAS_NORMALIZATION_PASS_H
