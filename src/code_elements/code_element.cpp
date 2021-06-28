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

#include "code_elements/code_element.hpp"

#include <utility>

code_element::code_element() {

}

code_element::code_element(element_type_t block_type) {
    type = block_type;
}

code_element::code_element(element_type_t block_type, instruction block_spec) {
    type = block_type;
    inst = std::move(block_spec);
}

code_element::code_element(element_type_t block_type, for_loop block_spec) {
    type = block_type;
    loop = std::move(block_spec);
}

code_element::code_element(element_type_t block_type, pragma block_spec) {
    type = block_type;
    directive = std::move(block_spec);
}


code_element::code_element(element_type_t block_type, variable var_in) {
    type = block_type;
    var = var_in;
}


void code_element::add_content(const std::shared_ptr<code_element>& element) {
    content.push_back(element);
}

bool code_element::has_content() {
    return !content.empty();
}

std::vector<std::shared_ptr<code_element>> code_element::get_content() {
    return content;
}

void code_element::set_content(const std::vector<std::shared_ptr<code_element>>& c) {
    content = c;
}

bool code_element::is_terminal() {

    return  type == type_instr || type == type_pragma;
}

void code_element::prepend_content(const std::vector<std::shared_ptr<code_element>> &c) {
    content.insert(content.begin(), c.begin(), c.end());
}

void code_element::append_content(const std::vector<std::shared_ptr<code_element>> &c) {
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



