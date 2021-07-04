//
// Created by fils on 01/07/2021.
//

#ifndef FCORE_HAS_HL_FUNCTION_NODE_H
#define FCORE_HAS_HL_FUNCTION_NODE_H

#include <map>
#include <string>

#include "hl_ast_node.h"
#include "hl_definition_node.h"
#include "hl_expression_node.h"

class hl_function_node : public hl_ast_node{
public:
    hl_function_node();
    void set_type( c_types_t ret_val);
    void set_name(std::string &n);
    void set_parameters_list(std::vector<std::shared_ptr<hl_definition_node>> list);
    void set_body(std::vector<std::shared_ptr<hl_ast_node>> b);
    void set_return(std::shared_ptr<hl_expression_node> r);
private:
    c_types_t return_type;
    std::string name;
    std::vector<std::shared_ptr<hl_definition_node>> parameters_list;
    std::vector<std::shared_ptr<hl_ast_node>> function_body;
    std::shared_ptr<hl_expression_node> return_expression;
};


#endif //FCORE_HAS_HL_FUNCTION_NODE_H
