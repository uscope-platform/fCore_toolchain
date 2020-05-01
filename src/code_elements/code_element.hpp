//
// Created by fils on 30/04/20.
//

#ifndef FCORE_HAS_CODE_ELEMENT_HPP
#define FCORE_HAS_CODE_ELEMENT_HPP

#include <vector>
#include <cstdint>
#include <memory>
#include <iostream>

typedef enum {
    type_reg_instr = 1,
    type_imm_instr = 2,
    type_indep_instr = 3,
    type_for_block = 4,
    type_program_head = 5,
    type_pragma = 6
} element_type_t;

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

class code_element {

public:
    code_element();
    code_element(element_type_t block_type, std::shared_ptr<code_element>parent_element);
    std::shared_ptr<code_element> get_parent();

    void add_content(const std::shared_ptr<code_element>& element);
    void set_directive(std::string str);
    std::string get_directive();
    bool has_content();

    std::vector<std::shared_ptr<code_element>> get_content();
    void set_content(std::vector<std::shared_ptr<code_element>> c);
    virtual bool is_terminal(){ return false;};
    virtual uint32_t emit();
    virtual void print();
    virtual void set_loop_start(loop_start_t variable) {};
    virtual void set_loop_end(loop_end_t end) {};
    virtual void set_advance(loop_advance_t adv){};
    virtual loop_start_t get_loop_start(){ loop_start_t start = loop_start_t(); return start; };
    virtual loop_end_t get_loop_end(){ loop_end_t end = loop_end_t(); return end;};
    virtual loop_advance_t get_advance(){ loop_advance_t adv = loop_advance_t(); return adv;};
    element_type_t type;

private:
    std::string directive;
    uint32_t order{};
    std::vector<std::shared_ptr<code_element>> content;
    //std::vector<std::shared_ptr<instruction>> content {};
    std::shared_ptr<code_element> parent;



};


#endif //FCORE_HAS_CODE_ELEMENT_HPP
