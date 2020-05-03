//
// Created by fils on 30/04/20.
//

#ifndef FCORE_HAS_CODE_ELEMENT_HPP
#define FCORE_HAS_CODE_ELEMENT_HPP

#include <vector>
#include <cstdint>
#include <memory>
#include <iostream>
#include <utility>

#include "instruction.h"
#include "for_loop.hpp"

typedef enum {
    type_instr = 1,
    type_for_block = 4,
    type_program_head = 5,
    type_pragma = 6
} element_type_t;


class pragma {
public:
    pragma();
    pragma(std::string directive);
    void set_directive(std::string str);
    std::string get_directive();
    void print();
private:
    std::string directive;
};

class code_element {

public:
    code_element();
    code_element(element_type_t block_type);
    code_element(element_type_t block_type, instruction block_spec);
    code_element(element_type_t block_type, for_loop block_spec);
    code_element(element_type_t block_type, pragma block_spec);
    bool is_terminal();
    void add_content(const std::shared_ptr<code_element>& element);
    bool has_content();
    std::vector<std::shared_ptr<code_element>> get_content();
    void set_content(const std::vector<std::shared_ptr<code_element>>& c);

    element_type_t type;
    for_loop loop;
    instruction inst;
    pragma directive;
private:
    std::vector<std::shared_ptr<code_element>> content;

};



static std::shared_ptr<code_element> deep_copy_element(std::shared_ptr<code_element> element) {
    code_element copied_elem;
    std::shared_ptr<code_element> result = std::make_shared<code_element>(copied_elem);
    if(element->has_content()){
        std::vector<std::shared_ptr<code_element>> children;
        for(auto &item:element->get_content()){
            std::shared_ptr<code_element> child = deep_copy_element(item);
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





#endif //FCORE_HAS_CODE_ELEMENT_HPP
