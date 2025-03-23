//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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


#include "passes/high_level/optimizations/visitor_passes/dead_variable_elimination.hpp"
namespace fcore{

    dead_variable_elimination::dead_variable_elimination() : pass_base("dead variable elimination"){

    }

    std::shared_ptr<ast_code_block> dead_variable_elimination::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.post.visit_definition = [this](auto && arg) { return detect_definition(std::forward<decltype(arg)>(arg));};
        ops.post.visit_expression = [this](auto && arg) { return detect_expression(std::forward<decltype(arg)>(arg));};
        visitor.visit(ops, element);

        hl_acting_visitor_operations ops2;
        ops2.post.visit_definition = [this](auto && arg) { return process_definition(std::forward<decltype(arg)>(arg));};

        return  visitor.visit(ops2, element);
    }


    std::vector<std::shared_ptr<ast_node>>
    dead_variable_elimination::process_definition(const std::shared_ptr<ast_definition> &def) {
        if(defined_variables.count(def->get_name())>0){
            return {ast_node::deep_copy(def)};
        }
        return {};
    }

    std::vector<std::shared_ptr<ast_node>>
    dead_variable_elimination::detect_definition(const std::shared_ptr<ast_definition> &def) {
        if(def->is_initialized())
            defined_variables.insert(std::make_pair(def->get_name(), true));
        return {def};
    }

    std::vector<std::shared_ptr<ast_node>>
    dead_variable_elimination::detect_expression(const std::shared_ptr<ast_expression> &expr) {
        if(expr->get_type() == ast_expression::ASSIGN){
            std::shared_ptr<ast_operand> lhs = std::static_pointer_cast<ast_operand>(expr->get_lhs().value());
            defined_variables.insert(std::make_pair(lhs->get_name(), true));
        }
        return {expr};
    }

}