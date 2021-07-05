//
// Created by fils on 05/07/2021.
//

#include "code_elements/ll_ast/ll_loop_node.h"

#include <utility>



ll_loop_node::ll_loop_node() : ll_ast_node(ll_type_for_block) {
    loop_start = {"", 0};
    loop_advance = {true, 1};
    end_condition = {0, ">"};
}

void ll_loop_node::set_loop_start(loop_start_t start) {
    loop_start = std::move(start);
}

void ll_loop_node::set_loop_end(loop_end_t end) {
    end_condition = std::move(end);
}

void ll_loop_node::set_advance(loop_advance_t adv) {
    loop_advance = adv;
}

loop_start_t ll_loop_node::get_loop_start() {
    return loop_start;
}

loop_end_t ll_loop_node::get_loop_end() {
    return end_condition;
}

loop_advance_t ll_loop_node::get_advance() {
    return loop_advance;
}

