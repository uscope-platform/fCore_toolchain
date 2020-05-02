//
// Created by fils on 01/05/20.
//

#include "for_loop.hpp"

for_loop::for_loop() {
 loop_start = {"", 0};
 loop_advance = {true, 1};
 end_condition = {0, ">"};
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

