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
// limitations under the License.05/07/2021.
//

#include "passes/high_level/dead_load_elimination.hpp"

dead_load_elimination::dead_load_elimination() : pass_base<hl_ast_node>("dead_load_elimination") {

}

std::shared_ptr<hl_ast_node> dead_load_elimination::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::vector<std::shared_ptr<hl_ast_node>> new_content;

    idx = 0;
    for(auto &item:element->get_content()){
        search_constants(item);
        search_usages(item);
        idx++;
    }

    idx = 0;
    for(auto &item:element->get_content()){
        std::shared_ptr<hl_ast_node> node = purge_dead_loads(item);
        if(node != nullptr) new_content.push_back(node);
        idx++;
    }
    retval->set_content(new_content);
    return retval;
}


// ORA COME ORA TENGO SEMPLICEMENTE L'ULTIMO ASSEGNAMENTO, GLI ALTRI VENGONO TOLTI, TUTTAVIA BISOGNA ANCHE GUARDARE SE
// TRA IL PRIMO E L'ULTIMO ASSEGNAMENTO IL REGISTRO E' STATO USATO O NO
void dead_load_elimination::search_constants(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type == hl_ast_node_type_definition) {
        std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(element);
        if(last_loads_map.contains(node->get_name())){
            last_loads_map[node->get_name()].last_assignment = idx;
        } else{
            last_loads_map[node->get_name()] = load_t({idx, -1});
        }

    } else if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        if(node->get_type() == expr_assign){
            std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(node->get_lhs());
            if(last_loads_map.contains(op->get_name())){
                last_loads_map[op->get_name()].last_assignment = idx;
            } else{
                last_loads_map[op->get_name()] = load_t({idx, -1});
            }
        }
    }
}

void dead_load_elimination::search_usages(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type == hl_ast_node_type_definition) {
        std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(element);
        search_usages(node);
    } else if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        search_usages(node);
    } else{
        throw std::runtime_error("ERROR: unexpected node type in dead load elimination pass");
    }
}

void dead_load_elimination::search_usages(std::shared_ptr<hl_definition_node> element) {
    if(element->is_initialized()){
        if(element->get_scalar_initializer()->node_type == hl_ast_node_type_expr){
            search_usages(std::static_pointer_cast<hl_expression_node>(element->get_scalar_initializer()));
        } else if(element->get_scalar_initializer()->node_type == hl_ast_node_type_operand){
            search_usages(std::static_pointer_cast<hl_ast_operand>(element->get_scalar_initializer()));
        } else {
            throw std::runtime_error("ERROR: unexpected definition initializer type in dead load elimination pass");
        }
    }
}

void dead_load_elimination::search_usages(std::shared_ptr<hl_expression_node> element) {
    if(element->is_immediate()){
        return;
    }
    if(!element->is_unary()){
        search_usages(std::static_pointer_cast<hl_ast_operand>(element->get_lhs()));
    }
    search_usages(std::static_pointer_cast<hl_ast_operand>(element->get_rhs()));
}


void dead_load_elimination::search_usages(std::shared_ptr<hl_ast_operand> element) {
    if(last_loads_map.contains(element->get_name())){
        if(last_loads_map[element->get_name()].first_usage == -1){
            last_loads_map[element->get_name()].first_usage = idx;
        }
    }
}

std::shared_ptr<hl_ast_node> dead_load_elimination::purge_dead_loads(std::shared_ptr<hl_ast_node> element) {
    if(element->node_type == hl_ast_node_type_definition) {
        std::shared_ptr<hl_definition_node> node = std::static_pointer_cast<hl_definition_node>(element);
        if(node->is_initialized()){
            if(node->get_scalar_initializer()->node_type != hl_ast_node_type_operand){
                return element;
            }
        } else{
            return nullptr;
        }

        auto l = last_loads_map[node->get_name()];
        if(l.last_assignment==idx || l.first_usage != -1 && (l.first_usage<l.last_assignment)){
            return element;
        }
    } else if(element->node_type == hl_ast_node_type_expr){
        std::shared_ptr<hl_expression_node> node = std::static_pointer_cast<hl_expression_node>(element);
        if(node->get_type() == expr_assign){
            if(node->get_rhs()->node_type != hl_ast_node_type_operand){
                return element;
            }
            std::string name = std::static_pointer_cast<hl_ast_operand>(node->get_lhs())->get_name();

            auto l = last_loads_map[name];
            if(l.last_assignment==idx || l.first_usage != -1 && (l.first_usage<l.last_assignment)){
                return element;
            }
        } else {
            return element;
        }
    } else{
        return element;
    }
    return nullptr;
}


