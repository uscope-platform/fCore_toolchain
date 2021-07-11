//
// Created by fils on 09/07/2021.
//

#ifndef FCORE_HAS_HIGH_LEVEL_AST_LOWERING_H
#define FCORE_HAS_HIGH_LEVEL_AST_LOWERING_H


#include <utility>
#include <stdexcept>

#include "frontend/variable_map.hpp"
#include "ast/high_level/hl_ast_node.h"
#include "ast/high_level/hl_expression_node.h"
#include "ast/high_level/hl_definition_node.h"
#include "ast/low_level/ll_ast_node.hpp"
#include "ast/low_level/ll_instruction_node.h"

class high_level_ast_lowering {
public:
    explicit high_level_ast_lowering(std::shared_ptr<variable_map> &m);
    void set_input_ast(std::shared_ptr<hl_ast_node> i) {input_ast = std::move(i);};
    void translate();
    std::shared_ptr<ll_ast_node> get_output_ast() {return output_ast;};
private:
    std::shared_ptr<ll_ast_node> translate_node(const std::shared_ptr<hl_ast_node>& input);
    std::shared_ptr<ll_ast_node> translate_node(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest);
    std::shared_ptr<ll_ast_node> translate_node(std::shared_ptr<hl_definition_node> input, std::shared_ptr<variable> dest);
    std::shared_ptr<ll_ast_node> process_unary_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest);
    std::shared_ptr<ll_ast_node> process_regular_expression(std::shared_ptr<hl_expression_node> input, std::shared_ptr<variable> dest);
    std::shared_ptr<hl_ast_node> input_ast;
    std::shared_ptr<ll_ast_node> output_ast;
    std::map<expression_type_t, std::string> expr_instruction_mapping;
    std::shared_ptr<variable_map> var_map;
};


#endif //FCORE_HAS_HIGH_LEVEL_AST_LOWERING_H
