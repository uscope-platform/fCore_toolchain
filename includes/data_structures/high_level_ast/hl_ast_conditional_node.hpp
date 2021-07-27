//
// Created by fils on 17/07/2021.
//

#ifndef FCORE_TOOLCHAIN_HL_AST_CONDITIONAL_NODE_HPP
#define FCORE_TOOLCHAIN_HL_AST_CONDITIONAL_NODE_HPP

#include "data_structures/high_level_ast/hl_ast_node.hpp"

#include <utility>
#include <sstream>

class hl_ast_conditional_node : public hl_ast_node{
public:
    hl_ast_conditional_node();
    void set_if_block(std::vector<std::shared_ptr<hl_ast_node>> node);
    std::vector<std::shared_ptr<hl_ast_node>> get_if_block();
    void set_else_block(std::vector<std::shared_ptr<hl_ast_node>> node);
    std::vector<std::shared_ptr<hl_ast_node>> get_else_block();
    void set_condition(std::shared_ptr<hl_ast_node> node);
    std::shared_ptr<hl_ast_node> get_condition();
    std::string pretty_print() override;
    friend bool operator==(const hl_ast_conditional_node& lhs, const hl_ast_conditional_node& rhs);
    bool is_terminal() override {
        return false;
    }
    bool has_else() {return !else_block.empty();};
private:
    std::vector<std::shared_ptr<hl_ast_node>> if_block;
    std::vector<std::shared_ptr<hl_ast_node>> else_block;
    std::shared_ptr<hl_ast_node> condition;

};


#endif //FCORE_TOOLCHAIN_HL_AST_CONDITIONAL_NODE_HPP
