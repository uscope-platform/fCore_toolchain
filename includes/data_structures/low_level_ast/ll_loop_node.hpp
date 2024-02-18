// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_LL_LOOP_NODE_HPP
#define FCORE_TOOLCHAIN_LL_LOOP_NODE_HPP

#include <utility>

#include "ll_ast_node.hpp"
namespace fcore{

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


    class ll_loop_node: public ll_ast_node{

    public:
        ll_loop_node();

        bool is_terminal() override { return false;};
        void set_loop_start(loop_start_t start);
        void set_loop_end(loop_end_t end);
        void set_advance(loop_advance_t adv);
        loop_start_t get_loop_start();
        loop_end_t get_loop_end();
        loop_advance_t get_advance();

        nlohmann::json dump() override;

        friend bool operator==(const ll_loop_node& lhs, const ll_loop_node& rhs){
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

        };
    private:
        loop_start_t loop_start;
        loop_end_t end_condition;
        loop_advance_t loop_advance{};
    };
}


#endif //FCORE_TOOLCHAIN_LL_LOOP_NODE_HPP
