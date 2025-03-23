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

#include "data_structures/high_level_ast/ast_node.hpp"

#include "data_structures/high_level_ast/ast_operand.hpp"
#include "data_structures/high_level_ast/ast_definition.hpp"
#include "data_structures/high_level_ast/ast_expression.hpp"
#include "data_structures/high_level_ast/ast_call.hpp"
#include "data_structures/high_level_ast/ast_function_def.hpp"
#include "data_structures/high_level_ast/ast_conditional.hpp"
#include "data_structures/high_level_ast/ast_loop.hpp"
#include "data_structures/high_level_ast/ast_code_block.hpp"
#include "data_structures/high_level_ast/ast_struct.hpp"


namespace fcore{

    ast_node::ast_node(hl_ast_node_type_t t) {
        node_type = t;
    }

    c_types_t ast_node::string_to_type(const std::string &t) {
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
    ast_node::compare_content_by_type(const std::shared_ptr<ast_node> &lhs, const std::shared_ptr<ast_node> &rhs) {
        if(lhs->node_type != rhs->node_type) return false;

        switch (lhs->node_type) {
           case hl_ast_node_type_code_block:
                return *std::static_pointer_cast<ast_code_block>(lhs) == *std::static_pointer_cast<ast_code_block>(rhs);
            case hl_ast_node_type_loop:
                return *std::static_pointer_cast<ast_loop>(lhs) == *std::static_pointer_cast<ast_loop>(rhs);
            case hl_ast_node_type_conditional:
                return *std::static_pointer_cast<ast_conditional>(lhs) == *std::static_pointer_cast<ast_conditional>(rhs);
            case hl_ast_node_type_operand:
                return *std::static_pointer_cast<ast_operand>(lhs) == *std::static_pointer_cast<ast_operand>(rhs);
            case hl_ast_node_type_expr:
                return *std::static_pointer_cast<ast_expression>(lhs) == *std::static_pointer_cast<ast_expression>(rhs);
            case hl_ast_node_type_definition:
                return *std::static_pointer_cast<ast_definition>(lhs) == *std::static_pointer_cast<ast_definition>(rhs);
            case hl_ast_node_type_function_def:
                return *std::static_pointer_cast<ast_function_def>(lhs) == *std::static_pointer_cast<ast_function_def>(rhs);
            case hl_ast_node_type_function_call:
                return *std::static_pointer_cast<ast_call>(lhs) == *std::static_pointer_cast<ast_call>(rhs);
            case hl_ast_node_type_struct:
                return *std::static_pointer_cast<ast_struct>(lhs) == *std::static_pointer_cast<ast_struct>(rhs);
            default:
                return false;
        }
    }

    std::shared_ptr<ast_node> ast_node::deep_copy(const std::shared_ptr<ast_node> &node) {
        if(node == nullptr){
            return nullptr;
        }
        if(node->node_type == hl_ast_node_type_expr){
            return ast_expression::deep_copy(std::static_pointer_cast<ast_expression>(node));
        }
        if(node->node_type == hl_ast_node_type_definition){
            return ast_definition::deep_copy(std::static_pointer_cast<ast_definition>(node));
        }
        if(node->node_type == hl_ast_node_type_conditional){
            return ast_conditional::deep_copy(std::static_pointer_cast<ast_conditional>(node));
        }
        if(node->node_type == hl_ast_node_type_loop){
            return ast_loop::deep_copy(std::static_pointer_cast<ast_loop>(node));
        }
        if(node->node_type == hl_ast_node_type_function_def){
            return ast_function_def::deep_copy(std::static_pointer_cast<ast_function_def>(node));
        }
        if(node->node_type == hl_ast_node_type_operand){
            return ast_operand::deep_copy(std::static_pointer_cast<ast_operand>(node));
        }
        if(node->node_type == hl_ast_node_type_function_call){
            return ast_call::deep_copy(std::static_pointer_cast<ast_call>(node));
        }
        if(node->node_type == hl_ast_node_type_code_block){
            return ast_code_block::deep_copy(std::static_pointer_cast<ast_code_block>(node));
        }
        if(node->node_type == hl_ast_node_type_struct) {
            return ast_struct::deep_copy(std::static_pointer_cast<ast_struct>(node));
        }
        throw std::runtime_error("HL ast node with unknown type");

    }



    bool ast_node::compare_vectors(const std::vector<std::shared_ptr<ast_node>> &lhs,
                                             const std::vector<std::shared_ptr<ast_node>> &rhs) {
        bool ret_val = true;
        if(lhs.empty() && rhs.empty()){
            ret_val &= true;
        } else if(lhs.empty() || rhs.empty()){
            ret_val = false;
        } else{
            bool body_equal = true;
            if(lhs.size() != rhs.size()) return false;

            for(uint32_t i = 0; i<lhs.size(); i++){
                body_equal &= compare_content_by_type( lhs[i], rhs[i]);
            }
            ret_val &= body_equal;
        }
        return ret_val;
    }

    std::string ast_node::pretty_print(const std::shared_ptr<ast_node> &node) {
        if(node->node_type == hl_ast_node_type_expr){
            return std::static_pointer_cast<ast_expression>(node)->pretty_print();
        }
        if(node->node_type == hl_ast_node_type_definition){
            return std::static_pointer_cast<ast_definition>(node)->pretty_print();
        }
        if(node->node_type == hl_ast_node_type_conditional){
            return std::static_pointer_cast<ast_conditional>(node)->pretty_print();
        }
        if(node->node_type == hl_ast_node_type_loop){
            return std::static_pointer_cast<ast_loop>(node)->pretty_print();
        }
        if(node->node_type == hl_ast_node_type_function_def){
            return std::static_pointer_cast<ast_function_def>(node)->pretty_print();
        }
        if(node->node_type == hl_ast_node_type_operand){
            return std::static_pointer_cast<ast_operand>(node)->pretty_print();
        }
        if(node->node_type == hl_ast_node_type_function_call){
            return std::static_pointer_cast<ast_call>(node)->pretty_print();
        }
        if(node->node_type == hl_ast_node_type_code_block){
            return std::static_pointer_cast<ast_code_block>(node)->pretty_print();
        }
        if(node->node_type == hl_ast_node_type_struct) {
            return std::static_pointer_cast<ast_struct>(node)->pretty_print();
        }
        throw std::runtime_error("HL ast node with unknown type");
    }


}
