//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "passes/high_level/optimizations/dead_load_elimination.hpp"

namespace fcore{

    dead_load_elimination::dead_load_elimination() : pass_base("dead_load_elimination") {
        efi_mode = false;
    }

    std::shared_ptr<ast_code_block> dead_load_elimination::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {
        auto retval = std::make_shared<ast_code_block>();

        std::vector<std::shared_ptr<ast_node>> new_content;

        idx = 0;
        for(auto &item:element->get_content()){
            search_constants(item);
            search_usages(item);
            idx++;
        }

        idx = 0;
        for(auto &item:element->get_content()){
            std::shared_ptr<ast_node> node = purge_dead_loads(item);
            if(node != nullptr) new_content.push_back(node);
            idx++;
        }
        retval->set_content(new_content);
        return retval;
    }


    void dead_load_elimination::search_constants(std::shared_ptr<ast_node> element) {
        if(element->node_type == hl_ast_node_type_definition) {
            std::shared_ptr<ast_definition> node = std::static_pointer_cast<ast_definition>(element);
            if(last_loads_map.contains(node->get_name())){
                last_loads_map[node->get_name()].last_assignment = idx;
            } else{
                last_loads_map[node->get_name()] = load_t({idx, -1});
            }

        } else if(element->node_type == hl_ast_node_type_expr){
            std::shared_ptr<ast_expression> node = std::static_pointer_cast<ast_expression>(element);
            if(node->get_type() == ast_expression::ASSIGN){
                std::shared_ptr<ast_operand> op = std::static_pointer_cast<ast_operand>(node->get_lhs().value());
                if(last_loads_map.contains(op->get_identifier())){
                    last_loads_map[op->get_identifier()].last_assignment = idx;
                } else{
                    last_loads_map[op->get_identifier()] = load_t({idx, -1});
                }
            }
        }
    }

    void dead_load_elimination::search_usages(std::shared_ptr<ast_node> element) {
        if(element->node_type == hl_ast_node_type_definition) {
            std::shared_ptr<ast_definition> node = std::static_pointer_cast<ast_definition>(element);
            search_usages(node);
        } else if(element->node_type == hl_ast_node_type_expr){
            std::shared_ptr<ast_expression> node = std::static_pointer_cast<ast_expression>(element);
            search_usages(node);
        } else{
            throw std::runtime_error("unexpected node type in dead load elimination pass");
        }
    }

    void dead_load_elimination::search_usages(std::shared_ptr<ast_definition> element) {
        if(element->is_initialized()){
            if(element->get_scalar_initializer()->node_type == hl_ast_node_type_expr){
                search_usages(std::static_pointer_cast<ast_expression>(element->get_scalar_initializer()));
            } else if(element->get_scalar_initializer()->node_type == hl_ast_node_type_operand){
                search_usages(std::static_pointer_cast<ast_operand>(element->get_scalar_initializer()));
            } else {
                throw std::runtime_error("unexpected definition initializer type in dead load elimination pass");
            }
        }
    }

    void dead_load_elimination::search_usages(std::shared_ptr<ast_expression> element) {
        if(element->is_immediate()){
            return;
        }

        if(auto lhs = element->get_lhs()){
            if(element->get_type() != ast_expression::ASSIGN){
                if(lhs.value()->node_type == hl_ast_node_type_operand){
                    search_usages(std::static_pointer_cast<ast_operand>(lhs.value()));
                }
            }
        }

        if(element->get_rhs()->node_type == hl_ast_node_type_operand){
            search_usages(std::static_pointer_cast<ast_operand>(element->get_rhs()));
        } else if(element->get_rhs()->node_type == hl_ast_node_type_expr){
            auto rhs_expr = std::static_pointer_cast<ast_expression>(element->get_rhs());
            if(rhs_expr->get_type() == ast_expression::EFI){
                efi_mode = true;
                search_usages(rhs_expr);
                efi_mode = false;
            }
        }
    }


    void dead_load_elimination::search_usages(std::shared_ptr<ast_operand> element) {
        if(efi_mode){
            for(auto &item:last_loads_map){
                if(item.first.starts_with(element->get_name()+"_")){
                    if(item.second.first_usage == -1){
                        item.second.first_usage = idx;
                    }
                }
            }
        } else {
            if(last_loads_map.contains(element->get_identifier()) && !element->get_variable()->is_constant()){
                if(last_loads_map[element->get_identifier()].first_usage == -1){
                    last_loads_map[element->get_identifier()].first_usage = idx;
                }
            }
        }

    }

    std::shared_ptr<ast_node> dead_load_elimination::purge_dead_loads(std::shared_ptr<ast_node> element) {
        if(element->node_type == hl_ast_node_type_definition) {
            std::shared_ptr<ast_definition> node = std::static_pointer_cast<ast_definition>(element);
            if(node->is_initialized()){
                if(node->get_scalar_initializer()->node_type != hl_ast_node_type_operand){
                    return element;
                }
            } else{
                return nullptr;
            }

            auto l = last_loads_map[node->get_name()];
            if(l.last_assignment==idx || (l.first_usage != -1 && (l.first_usage<l.last_assignment))){
                return element;
            }
        } else if(element->node_type == hl_ast_node_type_expr){
            std::shared_ptr<ast_expression> node = std::static_pointer_cast<ast_expression>(element);
            if(node->get_type() == ast_expression::ASSIGN){
                if(node->get_rhs()->node_type != hl_ast_node_type_operand){
                    return element;
                }
                std::string name = std::static_pointer_cast<ast_operand>(node->get_lhs().value())->get_identifier();

                auto l = last_loads_map[name];
                if(l.last_assignment == idx || (l.first_usage != -1 && (l.first_usage < l.last_assignment))){
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


}