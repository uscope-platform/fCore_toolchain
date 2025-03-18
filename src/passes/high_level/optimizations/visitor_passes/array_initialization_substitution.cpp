//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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


#include "passes/high_level/optimizations/visitor_passes/array_initialization_substitution.h"

namespace fcore{

    array_initialization_substitution::array_initialization_substitution() : pass_base("array_initialization_substitution"){

    }

    std::shared_ptr<hl_code_block> array_initialization_substitution::process_global(std::shared_ptr<hl_code_block> element, const std::vector<std::shared_ptr<hl_definition_node>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_definition = process_definition;

        return visitor.visit(ops, element);
    }



    std::shared_ptr<hl_expression_node> array_initialization_substitution::build_initialization_expr(const std::shared_ptr<hl_definition_node>& def, int index) {
        std::shared_ptr<hl_expression_node> init_expr = std::make_shared<hl_expression_node>(expr_assign);
        init_expr->set_rhs(def->get_array_initializer()[index]);
        std::shared_ptr<variable> var = std::make_shared<variable>(def->get_name());
        std::shared_ptr<hl_ast_operand> op = std::make_shared<hl_ast_operand>(var);


        auto array_shape = def->get_array_shape();
        std::vector<int> indices;
        if(array_shape.size()>1){
            indices = array_delinearize(def->get_array_shape(), index);
        } else{
            indices = {index};
        }

        std::vector<std::shared_ptr<hl_ast_node>> index_operands;
        for(auto &i:indices){
            var = std::make_shared<variable>("index", i);
            index_operands.push_back(std::make_shared<hl_ast_operand>(var));
        }

        op->set_array_index(index_operands);
        init_expr->set_lhs(op);
        return init_expr;
    }

    std::vector<std::shared_ptr<hl_ast_node>>
    array_initialization_substitution::process_definition(const std::shared_ptr<hl_definition_node> &def) {
        if(!def->is_scalar()){
            if(def->is_initialized()){
                std::vector<std::shared_ptr<hl_ast_node>> ret;
                for(uint32_t i = 0; i<def->get_array_initializer().size(); ++i){

                    auto init_expr = build_initialization_expr(def, i);

                    auto lhs = std::static_pointer_cast<hl_ast_operand>(init_expr->get_lhs().value());
                    lhs->get_variable()->set_array_shape(def->get_variable()->get_array_shape());
                    lhs->get_variable()->set_bound_reg_array(def->get_variable()->get_bound_reg_array());
                    lhs->get_variable()->set_variable_class(def->get_variable()->get_variable_class());
                    lhs->get_variable()->set_type(def->get_variable()->get_type());
                    ret.push_back(init_expr);
                }
                def->set_array_initializer({});
                ret.insert(ret.begin(), def);
                return ret;
            } else {
                return {def};
            }
        } else return {def};
    }
}

