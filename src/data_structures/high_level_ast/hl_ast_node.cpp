// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.30/06/2021.
//

#include "data_structures/high_level_ast/hl_ast_node.hpp"

#include "data_structures/high_level_ast/hl_ast_operand.hpp"
#include "data_structures/high_level_ast/hl_definition_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "data_structures/high_level_ast/hl_function_call_node.hpp"
#include "data_structures/high_level_ast/hl_function_def_node.hpp"
#include "data_structures/high_level_ast/hl_ast_conditional_node.hpp"
#include "data_structures/high_level_ast/hl_ast_root.hpp"
#include "data_structures/high_level_ast/hl_ast_loop_node.h"
#include "data_structures/high_level_ast/hl_code_block.hpp"

namespace fcore{

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

    bool
    hl_ast_node::compare_content_by_type(const std::shared_ptr<hl_ast_node> &lhs, const std::shared_ptr<hl_ast_node> &rhs) {
        if(lhs->node_type != rhs->node_type) return false;

        switch (lhs->node_type) {
            case hl_ast_node_type_program_root:
                return *std::static_pointer_cast<hl_ast_root>(lhs) == *std::static_pointer_cast<hl_ast_root>(rhs);
            case hl_ast_node_type_code_block:
                return *std::static_pointer_cast<hl_code_block>(lhs) == *std::static_pointer_cast<hl_code_block>(rhs);
            case hl_ast_node_type_loop:
                return *std::static_pointer_cast<hl_ast_loop_node>(lhs) == *std::static_pointer_cast<hl_ast_loop_node>(rhs);
            case hl_ast_node_type_conditional:
                return *std::static_pointer_cast<hl_ast_conditional_node>(lhs) == *std::static_pointer_cast<hl_ast_conditional_node>(rhs);
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
            return hl_expression_node::deep_copy(std::static_pointer_cast<hl_expression_node>(node));
        } else if(node->node_type == hl_ast_node_type_definition){
            return hl_definition_node::deep_copy(std::static_pointer_cast<hl_definition_node>(node));
        } else if(node->node_type == hl_ast_node_type_conditional){
            return hl_ast_conditional_node::deep_copy(std::static_pointer_cast<hl_ast_conditional_node>(node));
        } else if(node->node_type == hl_ast_node_type_loop){
            return hl_ast_loop_node::deep_copy(std::static_pointer_cast<hl_ast_loop_node>(node));
        } else if(node->node_type == hl_ast_node_type_function_def){
            return hl_function_def_node::deep_copy(std::static_pointer_cast<hl_function_def_node>(node));
        } else if(node->node_type == hl_ast_node_type_operand){
            return hl_ast_operand::deep_copy(std::static_pointer_cast<hl_ast_operand>(node));
        } else if(node->node_type == hl_ast_node_type_function_call){
            return hl_function_call_node::deep_copy(std::static_pointer_cast<hl_function_call_node>(node));
        } else if(node->node_type == hl_ast_node_type_program_root) {
            return hl_ast_root::deep_copy(std::static_pointer_cast<hl_ast_root>(node));
        } else if(node->node_type == hl_ast_node_type_code_block){
            return hl_code_block::deep_copy(std::static_pointer_cast<hl_code_block>(node));
        } else {
            throw std::runtime_error("HL ast node with unknown type");
        }

    }



    bool hl_ast_node::compare_vectors(const std::vector<std::shared_ptr<hl_ast_node>> &lhs,
                                             const std::vector<std::shared_ptr<hl_ast_node>> &rhs) {
        bool ret_val = true;
        if(lhs.empty() && rhs.empty()){
            ret_val &= true;
        } else if(lhs.empty() || rhs.empty()){
            ret_val = false;
        } else{
            bool body_equal = true;
            if(lhs.size() != rhs.size()) return false;

            for(uint32_t i = 0; i<lhs.size(); i++){
                body_equal &= hl_ast_node::compare_content_by_type( lhs[i], rhs[i]);
            }
            ret_val &= body_equal;
        }
        return ret_val;
    }

    std::string hl_ast_node::pretty_print(const std::shared_ptr<hl_ast_node> &node) {
        if(node->node_type == hl_ast_node_type_expr){
            return std::static_pointer_cast<hl_expression_node>(node)->pretty_print();
        } else if(node->node_type == hl_ast_node_type_definition){
            return std::static_pointer_cast<hl_definition_node>(node)->pretty_print();
        } else if(node->node_type == hl_ast_node_type_conditional){
            return std::static_pointer_cast<hl_ast_conditional_node>(node)->pretty_print();
        } else if(node->node_type == hl_ast_node_type_loop){
            return std::static_pointer_cast<hl_ast_loop_node>(node)->pretty_print();
        } else if(node->node_type == hl_ast_node_type_function_def){
            return std::static_pointer_cast<hl_function_def_node>(node)->pretty_print();
        } else if(node->node_type == hl_ast_node_type_operand){
            return std::static_pointer_cast<hl_ast_operand>(node)->pretty_print();
        } else if(node->node_type == hl_ast_node_type_function_call){
            return std::static_pointer_cast<hl_function_call_node>(node)->pretty_print();
        } else if(node->node_type == hl_ast_node_type_program_root) {
            return std::static_pointer_cast<hl_ast_root>(node)->pretty_print();
        } else if(node->node_type == hl_ast_node_type_code_block){
            return std::static_pointer_cast<hl_code_block>(node)->pretty_print();
        } else {
            throw std::runtime_error("HL ast node with unknown type");
        }
    }


}
