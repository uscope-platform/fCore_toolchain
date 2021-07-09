//
// Created by fils on 01/07/2021.
//

#ifndef FCORE_HAS_HL_EXPRESSION_NODE_H
#define FCORE_HAS_HL_EXPRESSION_NODE_H


#include "hl_ast_operand.h"
#include "hl_ast_node.h"
#include "hl_function_call_node.h"

#include <iostream>
#include <sstream>

typedef enum {
expr_add = 0,
expr_sub = 1,
expr_mult = 2,
expr_div = 3,
expr_incr_pre= 4,
expr_incr_post= 5,
expr_decr_pre= 6,
expr_decr_post= 7,
expr_modulo =8,
expr_and_l = 9,
expr_and_b = 10,
expr_or_l = 11,
expr_or_b = 12,
expr_not_l = 13,
expr_not_b = 14,
expr_xor_b = 15,
expr_lsh = 16,
expr_rsh = 17,
expr_eq = 18,
expr_neq = 19,
expr_neg = 20,
expr_lt = 21,
expr_gt = 22,
expr_lte = 23,
expr_gte = 24,
expr_assign = 25,
expr_call = 26,
expr_reciprocal = 27
} expression_type_t;

class hl_expression_node : public hl_ast_node{
public:
    hl_expression_node( expression_type_t et);
    void set_lhs(const std::shared_ptr<hl_ast_node> &node);
    void set_rhs(const std::shared_ptr<hl_ast_node> &node);
    std::shared_ptr<hl_ast_node> get_lhs();
    std::shared_ptr<hl_ast_node> get_rhs();
    expression_type_t get_type();
    std::string pretty_print();
    bool is_unary();
    static bool is_hardware_compatible(expression_type_t et);
    bool is_terminal() override {
        return true;
    }
    friend bool operator==(const hl_expression_node& lhs, const hl_expression_node& rhs);

private:
    expression_type_t expr_type;
    std::shared_ptr<hl_ast_node> lhs;
    std::shared_ptr<hl_ast_node> rhs;
    std::map<expression_type_t, std::string> type_print;
};

#endif //FCORE_HAS_HL_EXPRESSION_NODE_H
