//
// Created by fils on 30/06/2021.
//

#ifndef FCORE_HAS_HL_AST_NODE_H
#define FCORE_HAS_HL_AST_NODE_H

#include "code_elements/ast_node_base.h"

class hl_ast_node : public ast_node_base<hl_ast_node>{

public:
    explicit hl_ast_node(int t);

    bool is_terminal();



private:
    int type;

};


#endif //FCORE_HAS_HL_AST_NODE_H
