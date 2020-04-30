//
// Created by fils on 30/04/20.
//

#ifndef FCORE_HAS_CODE_ELEMENT_HPP
#define FCORE_HAS_CODE_ELEMENT_HPP

#include <vector>
#include <cstdint>
#include <memory>

typedef enum {
    type_reg_instr = 1,
    type_imm_instr = 2,
    type_indep_instr = 3,
    type_for_block = 4,
    type_program_head = 5
} element_type_t;

class code_element {

public:
    code_element();
    code_element(element_type_t block_type, std::shared_ptr<code_element>parent_element);
    std::shared_ptr<code_element> get_parent();

    void add_content(const std::shared_ptr<code_element>& element);
    bool has_content();
    std::vector<std::shared_ptr<code_element>> get_content();

    virtual bool is_terminal(){ return false;};
    virtual uint32_t emit();
    virtual void print();
private:
    uint32_t order{};
    element_type_t type;
    std::vector<std::shared_ptr<code_element>> content;
    //std::vector<std::shared_ptr<instruction>> content {};
    std::shared_ptr<code_element> parent;



};


#endif //FCORE_HAS_CODE_ELEMENT_HPP
