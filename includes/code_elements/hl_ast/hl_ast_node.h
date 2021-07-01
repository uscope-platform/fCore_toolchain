//
// Created by fils on 30/06/2021.
//

#ifndef FCORE_HAS_HL_AST_NODE_H
#define FCORE_HAS_HL_AST_NODE_H

#include <map>
#include <string>

#include "code_elements/ast_node_base.h"

typedef enum {
    type_expr = 1,
    type_identifier = 2,
    type_conditional = 3,
    type_loop = 4,
    type_function = 5
} hl_ast_node_type_t;

typedef enum {
    c_type_void = 1,
    c_type_char = 2,
    c_type_short = 3,
    c_type_int = 4,
    c_type_long = 5,
    c_type_float = 6
} c_types_t;

class hl_ast_node : public ast_node_base<hl_ast_node>{

public:
    explicit hl_ast_node(hl_ast_node_type_t t);
    static c_types_t string_to_type(const std::string& t);

    bool is_terminal();



private:
    hl_ast_node_type_t type;

};


#endif //FCORE_HAS_HL_AST_NODE_H
