//
// Created by fils on 01/07/2021.
//

#ifndef FCORE_HAS_HL_FUNCTION_DEF_NODE_H
#define FCORE_HAS_HL_FUNCTION_DEF_NODE_H

#include <map>
#include <string>
#include <utility>

#include "ast/high_level/hl_ast_node.h"
#include "ast/high_level/hl_definition_node.h"
#include "ast/high_level/hl_expression_node.h"

class hl_function_def_node : public hl_ast_node{
public:
    hl_function_def_node();
    void set_return_type(c_types_t ret_val);
    c_types_t get_return_type() {return return_type;};
    void set_name(std::string n);
    void set_parameters_list(std::vector<std::shared_ptr<hl_definition_node>> list);
    std::vector<std::shared_ptr<hl_definition_node>> get_parameters_list() { return parameters_list;};
    void set_body(std::vector<std::shared_ptr<hl_ast_node>> b);
    void set_return(std::shared_ptr<hl_ast_node> r);
    std::string get_name();
    std::shared_ptr<hl_ast_node> get_return();
    std::vector<std::shared_ptr<hl_ast_node>> get_body();
    std::string pretty_print();
    friend bool operator==(const hl_function_def_node& lhs, const hl_function_def_node& rhs);
    bool is_terminal() override {
        return false;
    }
protected:
    c_types_t return_type;
    std::string name;
    std::vector<std::shared_ptr<hl_definition_node>> parameters_list;
    std::vector<std::shared_ptr<hl_ast_node>> function_body;
    std::shared_ptr<hl_ast_node> return_expression;
};


#endif //FCORE_HAS_HL_FUNCTION_DEF_NODE_H