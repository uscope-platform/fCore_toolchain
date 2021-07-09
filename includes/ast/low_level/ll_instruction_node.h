//
// Created by fils on 05/07/2021.
//

#ifndef FCORE_HAS_LL_INSTRUCTION_NODE_H
#define FCORE_HAS_LL_INSTRUCTION_NODE_H

#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <cmath>
#include <iomanip>

#include "ast/low_level/ll_ast_node.hpp"
#include "ast/variable.hpp"
#include "fCore_isa.hpp"

typedef struct {
    std::string opcode;
    std::vector<std::shared_ptr<variable>> arguments;
    float intercalated_constant;
} instruction_t;


class ll_instruction_node : public ll_ast_node{

public:
    ll_instruction_node() = default;
    explicit ll_instruction_node(int inst_type);
    ll_instruction_node(int inst_type,std::string opcode, std::vector<std::shared_ptr<variable>> arguments);
    ll_instruction_node(int inst_type, float constant);
    int get_type();
    [[nodiscard]] uint32_t emit() const;
    [[nodiscard]] int instruction_count() const;
    bool is_terminal() override;
    void print();
    [[nodiscard]] bool is_pseudo() const { return type == PSEUDO_INSTRUCTION;};
    [[nodiscard]] const instruction_t &getStringInstr() const;
    void setStringInstr(const instruction_t &stringInstr);

private:
    [[nodiscard]] uint32_t emit_branch() const;
    [[nodiscard]] uint32_t emit_immediate() const;
    [[nodiscard]] uint32_t emit_independent() const;
    [[nodiscard]] uint32_t emit_register() const;
    [[nodiscard]] uint32_t emit_conversion() const;
    [[nodiscard]] uint32_t emit_load_const() const;
    [[nodiscard]] uint32_t emit_intercalated_const() const;
    void print_immediate() const;
    void print_independent() const;
    void print_register() const;
    void print_branch() const;
    void print_conversion() const;
    void print_load_const() const;

    int type;
    instruction_t string_instr;


};



#endif //FCORE_HAS_LL_INSTRUCTION_NODE_H
