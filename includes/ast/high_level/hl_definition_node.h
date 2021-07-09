//
// Created by fils on 01/07/2021.
//

#ifndef FCORE_HAS_HL_DEFINITION_NODE_H
#define FCORE_HAS_HL_DEFINITION_NODE_H

#include "ast/high_level/hl_ast_node.h"
#include "ast/high_level/hl_expression_node.h"

#include <utility>
#include <string>

class hl_definition_node : public hl_ast_node{
public:
    hl_definition_node(std::string n, c_types_t ct);
    void set_name(std::string name);
    std::string get_name(){ return name;};
    c_types_t get_type(){ return type;};
    bool is_initialized();
    void set_constant(bool c);
    bool is_constant();
    std::shared_ptr<hl_expression_node> get_initializer();
    void set_initializer(std::shared_ptr<hl_expression_node> init);
    std::string pretty_print();
    bool is_terminal() override {
        return true;
    }

    friend bool operator==(const hl_definition_node& lhs, const hl_definition_node& rhs);

protected:
    bool constant;
    std::string name;
    c_types_t type;
    std::shared_ptr<hl_expression_node> initializer;

};


#endif //FCORE_HAS_HL_DEFINITION_NODE_H
