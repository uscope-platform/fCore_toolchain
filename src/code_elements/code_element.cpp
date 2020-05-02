//
// Created by fils on 30/04/20.
//

#include "code_element.hpp"

#include <utility>

code_element::code_element() {

}

code_element::code_element(element_type_t block_type, std::shared_ptr<code_element> parent_element) {
    type = block_type;
    parent = std::move(parent_element);
}



code_element::code_element(element_type_t block_type, std::shared_ptr<code_element>parent_element, instruction block_spec) {
    type = block_type;
    parent = std::move(parent_element);
    inst = block_spec;
}

code_element::code_element(element_type_t block_type, std::shared_ptr<code_element>parent_element, for_loop block_spec) {
    type = block_type;
    parent = std::move(parent_element);
    loop = std::move(block_spec);
}

code_element::code_element(element_type_t block_type, std::shared_ptr<code_element>parent_element, pragma block_spec) {
    type = block_type;
    parent = std::move(parent_element);
    directive = std::move(block_spec);
}

std::weak_ptr<code_element> code_element::get_parent() {
    return parent;
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

void code_element::set_parent(std::weak_ptr<code_element> new_parent) {
    parent = new_parent;
}

pragma::pragma() = default;

pragma::pragma(std::string str) {
    directive = std::move(str);
}

void pragma::print() {
    std::cout<<"PRAGMA -> " + directive;
}

void pragma::set_directive(std::string str) {
    directive = std::move(str);
}

std::string pragma::get_directive() {
    return directive;
}



