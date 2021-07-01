//
// Created by fils on 01/07/2021.
//

#ifndef FCORE_HAS_HL_FUNCTION_NODE_H
#define FCORE_HAS_HL_FUNCTION_NODE_H

#include <map>
#include <string>

#include "hl_ast_node.h"
#include "hl_identifier_node.h"


class hl_function_node : public hl_ast_node{
public:
    hl_function_node(hl_ast_node_type_t t, c_types_t ret_val, std::string &n);
    void set_parameters_list(std::vector<std::shared_ptr<hl_identifier_node>> list);

private:
    c_types_t return_type;
    std::string name;
    std::vector<std::shared_ptr<hl_identifier_node>> parameters_list;
};


#endif //FCORE_HAS_HL_FUNCTION_NODE_H
