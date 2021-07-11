//
// Created by fils on 05/07/2021.
//

#include "ast/low_level/ll_loop_node.h"



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

bool operator==(const ll_loop_node &lhs, const ll_loop_node &rhs) {
    bool retval = true;

    retval &= lhs.loop_start.variable == rhs.loop_start.variable;
    retval &= lhs.loop_start.starting_value == rhs.loop_start.starting_value;

    retval &= lhs.loop_advance.direction == rhs.loop_advance.direction;
    retval &= lhs.loop_advance.loop_increment == rhs.loop_advance.loop_increment;

    retval &= lhs.end_condition.condition == rhs.end_condition.condition;
    retval &= lhs.end_condition.end_count == rhs.end_condition.end_count;

    if(lhs.content.empty() && rhs.content.empty()){
        retval &= true;
    } else if(lhs.content.empty() || rhs.content.empty()){
        retval = false;
    } else {
        bool args_equal = true;
        args_equal &= lhs.content.size() == rhs.content.size();
        for (int i = 0; i < lhs.content.size(); i++) {
            args_equal &= *lhs.content[i] == *rhs.content[i];
        }
        retval &= args_equal;
    }
    return retval;

}

