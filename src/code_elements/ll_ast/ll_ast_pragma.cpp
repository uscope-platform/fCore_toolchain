//
// Created by fils on 05/07/2021.
//

#include "code_elements/ll_ast/ll_ast_pragma.h"



ll_ast_pragma::ll_ast_pragma() : ll_ast_node(ll_type_pragma){

}

ll_ast_pragma::ll_ast_pragma(std::string str): ll_ast_node(ll_type_pragma) {
    directive = std::move(str);
}

void ll_ast_pragma::print() {
    std::cout<<"PRAGMA -> " + directive;
}

std::string ll_ast_pragma::get_directive() {
    return directive;
}

bool ll_ast_pragma::is_terminal() {
    return true;
}
