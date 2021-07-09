//
// Created by fils on 05/07/2021.
//

#ifndef FCORE_HAS_LL_AST_PRAGMA_H
#define FCORE_HAS_LL_AST_PRAGMA_H

#include <string>

#include "ll_ast_node.hpp"

class ll_ast_pragma :public ll_ast_node{
public:
    ll_ast_pragma();
    explicit ll_ast_pragma(std::string directive);
    std::string get_directive();
    bool is_terminal();
    void print();
private:
    std::string directive;
};


#endif //FCORE_HAS_LL_AST_PRAGMA_H
