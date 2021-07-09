//
// Created by fils on 01/07/2021.
//

#ifndef FCORE_HAS_HL_FUNCTION_CALL_NODE_H
#define FCORE_HAS_HL_FUNCTION_CALL_NODE_H

#include "ast/high_level/hl_ast_node.h"
#include "ast/high_level/hl_expression_node.h"
#include "ast/high_level/hl_ast_operand.h"

#include <string>
#include <utility>
#include <sstream>

class hl_function_call_node : public hl_ast_node {
public:
    hl_function_call_node(std::string n, std::vector<std::shared_ptr<hl_ast_node>> a);
    std::string get_name() {return name;};
    std::string pretty_print();
    std::vector<std::shared_ptr<hl_ast_node>> get_arguments() { return arguments;};
    void set_body(std::vector<std::shared_ptr<hl_ast_node>> i);
    std::vector<std::shared_ptr<hl_ast_node>> get_body() { return function_body;};
    void set_return(std::shared_ptr<hl_ast_node> r);
    std::shared_ptr<hl_ast_node> get_return() { return function_return;};
    friend bool operator==(const hl_function_call_node& lhs, const hl_function_call_node& rhs);
    bool is_terminal() override {
        return true;
    }
protected:
    std::string name;
    std::vector<std::shared_ptr<hl_ast_node>> arguments;
    std::vector<std::shared_ptr<hl_ast_node>> function_body;
    std::shared_ptr<hl_ast_node> function_return;
};

#endif //FCORE_HAS_HL_FUNCTION_CALL_NODE_H
