//
// Created by fils on 30/04/20.
//

#include "code_element.hpp"

#include <utility>


code_element::code_element(element_type_t block_type, std::shared_ptr<code_element> parent_element) {
    type = block_type;
    children = {};
    parent = std::move(parent_element);
}

code_element::code_element() {
    type = type_indep_instr;
    children = {};
    parent = nullptr;
}

std::shared_ptr<code_element> code_element::get_parent() {
    return parent;
}

void code_element::add_children(std::shared_ptr<code_element> child) {
    children.push_back(child);
}

void code_element::add_content(const std::shared_ptr<instruction>& instr) {
    content.push_back(instr);
}

bool code_element::has_content() {
    return !content.empty();
}

std::vector<std::shared_ptr<instruction>> code_element::get_content() {
    return content;
}

bool code_element::has_children() {
    return !children.empty();
}

std::vector<std::shared_ptr<code_element>> code_element::get_children() {
    return children;
}
