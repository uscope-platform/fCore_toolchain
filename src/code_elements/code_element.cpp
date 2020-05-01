//
// Created by fils on 30/04/20.
//

#include "code_element.hpp"

#include <utility>


code_element::code_element(element_type_t block_type, std::shared_ptr<code_element> parent_element) {
    type = block_type;
    parent = std::move(parent_element);
}

code_element::code_element() {
    type = type_indep_instr;
    parent = nullptr;
}

std::shared_ptr<code_element> code_element::get_parent() {
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

uint32_t code_element::emit() {
    return 0;
}

void code_element::print() {
    if(type==type_pragma){
        std::cout<<"PRAGMA -> " + directive;
    }
}

void code_element::set_directive(std::string str) {
    directive = std::move(str);
}

std::string code_element::get_directive() {
    return directive;
}

void code_element::set_content(std::vector<std::shared_ptr<code_element>> c) {
    content = std::move(c);
}
