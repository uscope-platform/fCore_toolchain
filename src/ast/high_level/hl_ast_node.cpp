// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.30/06/2021.
//

#include "ast/high_level/hl_ast_node.hpp"

#include "ast/high_level/hl_ast_operand.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "ast/high_level/hl_expression_node.hpp"
#include "ast/high_level/hl_function_call_node.hpp"
#include "ast/high_level/hl_function_def_node.hpp"

bool hl_ast_node::is_terminal() {
    return false;
}

hl_ast_node::hl_ast_node(hl_ast_node_type_t t) {
    node_type = t;
}

c_types_t hl_ast_node::string_to_type(const std::string &t) {
    std::map <std::string, c_types_t>  translator {
            {"void", c_type_void},
            {"char", c_type_char},
            {"short", c_type_short},
            {"int", c_type_int},
            {"long", c_type_long},
            {"float", c_type_float}
    };


    return translator[t];
}



bool operator==(const hl_ast_node &lhs, const hl_ast_node &rhs) {
    bool ret_val = true;
    ret_val &= lhs.node_type == rhs.node_type;

    if(lhs.content.empty() && rhs.content.empty()){
        ret_val &= true;
    } else if(lhs.content.empty() || rhs.content.empty()){
        ret_val = false;
    } else{
        bool body_equal = true;
        body_equal &= lhs.content.size() == rhs.content.size();

        for(int i = 0; i<lhs.content.size(); i++){

            body_equal &=  hl_ast_node::compare_content_by_type(lhs.content[i], rhs.content[i]);
        }
        ret_val &= body_equal;
    }

    return ret_val;
}

bool
hl_ast_node::compare_content_by_type(const std::shared_ptr<hl_ast_node> &lhs, const std::shared_ptr<hl_ast_node> &rhs) {
    if(lhs->node_type != rhs->node_type) return false;

    switch (lhs->node_type) {
        case hl_ast_node_type_loop:
        case hl_ast_node_type_conditional:
        case hl_ast_node_type_program_root:
            return *lhs == *rhs;
        case hl_ast_node_type_operand:
            return *std::static_pointer_cast<hl_ast_operand>(lhs) == *std::static_pointer_cast<hl_ast_operand>(rhs);
        case hl_ast_node_type_expr:
            return *std::static_pointer_cast<hl_expression_node>(lhs) == *std::static_pointer_cast<hl_expression_node>(rhs);
        case hl_ast_node_type_definition:
            return *std::static_pointer_cast<hl_definition_node>(lhs) == *std::static_pointer_cast<hl_definition_node>(rhs);
        case hl_ast_node_type_function_def:
            return *std::static_pointer_cast<hl_function_def_node>(lhs) == *std::static_pointer_cast<hl_function_def_node>(rhs);
        case hl_ast_node_type_function_call:
            return *std::static_pointer_cast<hl_function_call_node>(lhs) == *std::static_pointer_cast<hl_function_call_node>(rhs);
        default:
            return false;
    }
    return false;
}

std::string hl_ast_node::type_to_string(const c_types_t &t) {
    std::map <c_types_t,std::string>  translator {
            {c_type_void, "void"},
            {c_type_char, "char"},
            {c_type_short, "short"},
            {c_type_int, "int"},
            {c_type_long, "long"},
            {c_type_float, "float"}
    };

    return translator[t];
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy(const std::shared_ptr<hl_ast_node> &node) {
    if(node == nullptr){
        return nullptr;
    } else if(node->node_type == hl_ast_node_type_expr){
        return deep_copy_expr(node);
    } else if(node->node_type == hl_ast_node_type_definition){
        return deep_copy_def(node);
    } else if(node->node_type == hl_ast_node_type_conditional){
        return deep_copy_conditional(node);
    } else if(node->node_type == hl_ast_node_type_loop){
        return deep_copy_loop(node);
    } else if(node->node_type == hl_ast_node_type_function_def){
        return deep_copy_function_def(node);
    } else if(node->node_type == hl_ast_node_type_operand){
        return deep_copy_operands(node);
    } else if(node->node_type == hl_ast_node_type_function_call){
        return deep_copy_function_call(node);
    } else if(node->node_type == hl_ast_node_type_program_root){
        return deep_copy_program_root(node);
    } else {
        throw std::runtime_error("HL ast node with unknown type");
    }

}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_expr(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_expression_node> orig = std::static_pointer_cast<hl_expression_node>(node);
    std::shared_ptr<hl_expression_node> copied_obj = std::make_shared<hl_expression_node>(orig->get_type());

    std::shared_ptr<hl_ast_node> lhs = deep_copy(orig->get_lhs());
    std::shared_ptr<hl_ast_node> rhs = deep_copy(orig->get_rhs());

    copied_obj->set_lhs(lhs);
    copied_obj->set_rhs(rhs);

    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_def(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_definition_node> orig = std::static_pointer_cast<hl_definition_node>(node);
    std::shared_ptr<hl_definition_node> copied_obj = std::make_shared<hl_definition_node>(orig->get_name(), orig->get_type());
    copied_obj->set_constant(orig->is_constant());
    std::shared_ptr<hl_expression_node> initializer = std::static_pointer_cast<hl_expression_node>(deep_copy_expr(orig->get_initializer()));
    copied_obj->set_initializer(initializer);
    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_conditional(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_ast_node> orig = std::static_pointer_cast<hl_ast_node>(node);
    std::shared_ptr<hl_ast_node> copied_obj = std::make_shared<hl_ast_node>(node->node_type);

    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_loop(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_ast_node> orig = std::static_pointer_cast<hl_ast_node>(node);
    std::shared_ptr<hl_ast_node> copied_obj = std::make_shared<hl_ast_node>(node->node_type);

    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_function_def(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_function_def_node> orig = std::static_pointer_cast<hl_function_def_node>(node);
    std::shared_ptr<hl_function_def_node> copied_obj = std::make_shared<hl_function_def_node>();

    copied_obj->set_return_type(orig->get_return_type());
    copied_obj->set_name(orig->get_name());
    std::shared_ptr<hl_ast_node> ret_expr = deep_copy(orig->get_return());
    copied_obj->set_return(ret_expr);

    std::vector<std::shared_ptr<hl_definition_node>> params;
    for(const auto& i:orig->get_parameters_list()){
        params.push_back(std::static_pointer_cast<hl_definition_node>(deep_copy_def(i)));
    }

    std::vector<std::shared_ptr<hl_ast_node>> body;
    for(const auto& i:orig->get_body()){
        body.push_back(deep_copy(i));
    }

    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_operands(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_ast_operand> orig = std::static_pointer_cast<hl_ast_operand>(node);
    std::shared_ptr<hl_ast_operand> copied_obj = std::make_shared<hl_ast_operand>(orig->get_type());
    copied_obj->set_name(orig->get_name());
    copied_obj->set_immediate(orig->get_int_value());
    copied_obj->set_immediate(orig->get_float_val());
    copied_obj->set_string(orig->get_string());
    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_function_call(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_function_call_node> orig = std::static_pointer_cast<hl_function_call_node>(node);
    std::vector<std::shared_ptr<hl_ast_node>> args;
    for(const auto &i :orig->get_arguments()){
        args.push_back(deep_copy(i));
    }
    std::vector<std::shared_ptr<hl_ast_node>> impl;
    for(const auto &i :orig->get_body()){
        impl.push_back(deep_copy(i));
    }

    std::shared_ptr<hl_function_call_node> copied_obj = std::make_shared<hl_function_call_node>(orig->get_name(), args);
    copied_obj->set_body(impl);
    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

std::shared_ptr<hl_ast_node> hl_ast_node::deep_copy_program_root(const std::shared_ptr<hl_ast_node> &node) {
    std::shared_ptr<hl_ast_node> orig = std::static_pointer_cast<hl_function_def_node>(node);
    std::shared_ptr<hl_ast_node> copied_obj = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    copied_obj->set_content(orig->get_content());
    return copied_obj;
}

