//
// Created by fils on 01/07/2021.
//

#ifndef FCORE_HAS_HL_IDENTIFIER_NODE_H
#define FCORE_HAS_HL_IDENTIFIER_NODE_H

#include "hl_ast_node.h"


#include <string>

class hl_identifier_node : public hl_ast_node{
public:
    hl_identifier_node(hl_ast_node_type_t nt, std::string n, c_types_t ct);
private:
    std::string name;
    c_types_t type;
};


#endif //FCORE_HAS_HL_IDENTIFIER_NODE_H
