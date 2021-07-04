//
// Created by fils on 01/07/2021.
//

#ifndef FCORE_HAS_HL_FUNCTION_CALL_NODE_H
#define FCORE_HAS_HL_FUNCTION_CALL_NODE_H

#include "hl_ast_node.h"
#include "hl_expression_node.h"
#include "hl_ast_operand.h"

#include <string>
#include <utility>
#include <sstream>

class hl_function_call_node : public hl_ast_node{
public:
    hl_function_call_node(std::string n, std::vector<std::shared_ptr<hl_ast_node>> a);
    std::string pretty_print();
    friend bool operator==(const hl_function_call_node& lhs, const hl_function_call_node& rhs);

protected:
    std::string name;
    std::vector<std::shared_ptr<hl_ast_node>> arguments;

};

#endif //FCORE_HAS_HL_FUNCTION_CALL_NODE_H
