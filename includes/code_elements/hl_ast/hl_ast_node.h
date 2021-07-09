//
// Created by fils on 30/06/2021.
//

#ifndef FCORE_HAS_HL_AST_NODE_H
#define FCORE_HAS_HL_AST_NODE_H

#include <map>
#include <string>
#include <stdexcept>

#include "code_elements/ast_node_base.h"



typedef enum {
    hl_ast_node_type_expr = 1,
    hl_ast_node_type_definition = 2,
    hl_ast_node_type_conditional = 3,
    hl_ast_node_type_loop = 4,
    hl_ast_node_type_function_def = 5,
    hl_ast_node_type_operand = 6,
    hl_ast_node_type_function_call = 7,
    hl_ast_node_type_program_root = 8
} hl_ast_node_type_t;

typedef enum {
    c_type_void = 1,
    c_type_char = 2,
    c_type_short = 3,
    c_type_int = 4,
    c_type_long = 5,
    c_type_float = 6
} c_types_t;

class hl_ast_node : public ast_node_base<hl_ast_node>{

public:
    explicit hl_ast_node(hl_ast_node_type_t t);
    static c_types_t string_to_type(const std::string& t);
    static std::string  type_to_string(const c_types_t &t);

    virtual bool is_terminal();

    friend bool operator==(const hl_ast_node& lhs, const hl_ast_node& rhs);

    static  bool compare_content_by_type(const std::shared_ptr<hl_ast_node>& lhs, const std::shared_ptr<hl_ast_node>& rhs);

    static std::shared_ptr<hl_ast_node> deep_copy(const std::shared_ptr<hl_ast_node> &node);
    hl_ast_node_type_t node_type;
private:
    static std::shared_ptr<hl_ast_node> deep_copy_expr(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_def(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_conditional(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_loop(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_function_def(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_operands(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_function_call(const std::shared_ptr<hl_ast_node> &node);
    static std::shared_ptr<hl_ast_node> deep_copy_program_root(const std::shared_ptr<hl_ast_node> &node);
};


#endif //FCORE_HAS_HL_AST_NODE_H
