//
// Created by fils on 05/07/2021.
//

#ifndef FCORE_HAS_LL_LOOP_NODE_H
#define FCORE_HAS_LL_LOOP_NODE_H

#include "ll_ast_node.hpp"

class ll_loop_node: public ll_ast_node{

public:
    ll_loop_node();

    bool is_terminal() { return false;};
    void set_loop_start(loop_start_t start);
    void set_loop_end(loop_end_t end);
    void set_advance(loop_advance_t adv);
    loop_start_t get_loop_start();
    loop_end_t get_loop_end();
    loop_advance_t get_advance();
private:
    loop_start_t loop_start;
    loop_end_t end_condition;
    loop_advance_t loop_advance{};
};


#endif //FCORE_HAS_LL_LOOP_NODE_H
