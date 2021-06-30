// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#include "code_elements/ll_ast/ll_loop.hpp"

ll_loop::ll_loop() {
 loop_start = {"", 0};
 loop_advance = {true, 1};
 end_condition = {0, ">"};
}

void ll_loop::set_loop_start(loop_start_t start) {
    loop_start = start;
}

void ll_loop::set_loop_end(loop_end_t end) {
    end_condition = end;
}

void ll_loop::set_advance(loop_advance_t adv) {
    loop_advance = adv;
}

loop_start_t ll_loop::get_loop_start() {
    return loop_start;
}

loop_end_t ll_loop::get_loop_end() {
    return end_condition;
}

loop_advance_t ll_loop::get_advance() {
    return loop_advance;
}

