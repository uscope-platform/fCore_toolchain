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

#include "code_elements/ll_ast/ll_ast_node.hpp"

#include <utility>

ll_ast_node::ll_ast_node() {

}

ll_ast_node::ll_ast_node(element_type_t block_type) {
    type = block_type;
}

ll_ast_node::ll_ast_node(element_type_t block_type, ll_instruction block_spec) {
    type = block_type;
    inst = std::move(block_spec);
}

ll_ast_node::ll_ast_node(element_type_t block_type, ll_loop block_spec) {
    type = block_type;
    loop = std::move(block_spec);
}

ll_ast_node::ll_ast_node(element_type_t block_type, pragma block_spec) {
    type = block_type;
    directive = std::move(block_spec);
}


ll_ast_node::ll_ast_node(element_type_t block_type, variable var_in) {
    type = block_type;
    var = var_in;
}


void ll_ast_node::add_content(const std::shared_ptr<ll_ast_node>& element) {
    content.push_back(element);
}

bool ll_ast_node::has_content() {
    return !content.empty();
}

std::vector<std::shared_ptr<ll_ast_node>> ll_ast_node::get_content() {
    return content;
}

void ll_ast_node::set_content(const std::vector<std::shared_ptr<ll_ast_node>>& c) {
    content = c;
}

bool ll_ast_node::is_terminal() {

    return  type == type_instr || type == type_pragma;
}

void ll_ast_node::prepend_content(const std::vector<std::shared_ptr<ll_ast_node>> &c) {
    content.insert(content.begin(), c.begin(), c.end());
}

void ll_ast_node::append_content(const std::vector<std::shared_ptr<ll_ast_node>> &c) {
    content.insert(content.end(), c.begin(), c.end());
}


pragma::pragma() = default;

pragma::pragma(std::string str) {
    directive = std::move(str);
}

void pragma::print() {
    std::cout<<"PRAGMA -> " + directive;
}

std::string pragma::get_directive() {
    return directive;
}



