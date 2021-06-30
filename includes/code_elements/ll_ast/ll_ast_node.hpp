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

#ifndef FCORE_HAS_LL_AST_NODE_HPP
#define FCORE_HAS_LL_AST_NODE_HPP

#include <vector>
#include <cstdint>
#include <memory>
#include <iostream>
#include <utility>

#include "ll_instruction.h"
#include "ll_loop.hpp"
#include "code_elements/variable.hpp"


typedef enum {
    type_instr = 1,
    type_for_block = 4,
    type_program_head = 5,
    type_pragma = 6,
    type_code_block = 7,

} element_type_t;


class pragma {
public:
    pragma();
    explicit pragma(std::string directive);
    std::string get_directive();
    void print();
private:
    std::string directive;
};

class ll_ast_node {

public:
    ll_ast_node();
    explicit ll_ast_node(element_type_t block_type);
    ll_ast_node(element_type_t block_type, ll_instruction block_spec);
    ll_ast_node(element_type_t block_type, ll_loop block_spec);
    ll_ast_node(element_type_t block_type, pragma block_spec);
    ll_ast_node(element_type_t block_type, variable);
    bool is_terminal();
    void add_content(const std::shared_ptr<ll_ast_node>& element);
    bool has_content();
    std::vector<std::shared_ptr<ll_ast_node>> get_content();
    void set_content(const std::vector<std::shared_ptr<ll_ast_node>>& c);
    void prepend_content(const std::vector<std::shared_ptr<ll_ast_node>>& c);
    void append_content(const std::vector<std::shared_ptr<ll_ast_node>>& c);

    element_type_t type;
    ll_loop loop;
    ll_instruction inst;
    pragma directive;
    variable var;
private:
    std::vector<std::shared_ptr<ll_ast_node>> content;

};

typedef  std::shared_ptr<ll_ast_node> ast_t;


static ast_t deep_copy_element(const ast_t& element) {
    ll_ast_node copied_elem;
    ast_t result = std::make_shared<ll_ast_node>(copied_elem);
    if(element->has_content()){
        std::vector<ast_t> children;
        for(auto &item:element->get_content()){
            ast_t child = deep_copy_element(item);
            children.push_back(child);
        }
        result->set_content(children);
    }
    result->type = element->type;
    result->loop = element->loop;
    result->inst = element->inst;
    result->directive = element->directive;
    return result;
}





#endif //FCORE_HAS_LL_AST_NODE_HPP
