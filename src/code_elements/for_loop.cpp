//
// Created by fils on 01/05/20.
//

#include "for_loop.hpp"

#include <utility>

for_loop::for_loop(element_type_t block_type, std::shared_ptr<code_element> parent_element)
                : code_element(block_type, std::move(parent_element)) {
    }

void for_loop::set_loop_start(loop_start_t start) {
    loop_start = start;
}

void for_loop::set_loop_end(loop_end_t end) {
    end_condition = end;
}

void for_loop::set_advance(loop_advance_t adv) {
    loop_advance = adv;
}

loop_start_t for_loop::get_loop_start() {
    return loop_start;
}

loop_end_t for_loop::get_loop_end() {
    return end_condition;
}

loop_advance_t for_loop::get_advance() {
    return loop_advance;
}
