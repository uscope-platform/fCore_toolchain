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

#ifndef FCORE_HAS_FOR_LOOP_HPP
#define FCORE_HAS_FOR_LOOP_HPP


#include <string>

typedef struct {
    std::string variable;
    int starting_value;
}loop_start_t;


typedef struct {
    int end_count;
    std::basic_string<char> condition;
}loop_end_t;

typedef struct {
    bool direction;
    int loop_increment;
}loop_advance_t;


class for_loop{

public:
    for_loop();

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
    loop_advance_t loop_advance;
};


#endif //FCORE_HAS_FOR_LOOP_HPP
