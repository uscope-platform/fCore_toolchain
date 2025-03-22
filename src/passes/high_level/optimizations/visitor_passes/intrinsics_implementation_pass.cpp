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
// limitations under the License.

#include "passes/high_level/optimizations/visitor_passes/intrinsics_implementation_pass.hpp"

namespace fcore {

    intrinsics_implementation_pass::intrinsics_implementation_pass() : pass_base(
            "intrinsics implementation pass") {
    }

    std::shared_ptr<hl_code_block> intrinsics_implementation_pass::process_global(std::shared_ptr<hl_code_block> element, const std::vector<std::shared_ptr<hl_definition_node>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_function_call = process_function_call;
        return visitor.visit(ops, element);

    }


    std::vector<std::shared_ptr<hl_ast_node>>
    intrinsics_implementation_pass::process_function_call(const std::shared_ptr<hl_function_call_node> &element) {


        static std::map<std::string, hl_expression_node::expression_type> substitutions= {
                std::make_pair("itf", hl_expression_node::ITF),
                std::make_pair("fti", hl_expression_node::FTI),
                std::make_pair("satp", hl_expression_node::SATP),
                std::make_pair("satn", hl_expression_node::SATN),
                std::make_pair("abs", hl_expression_node::ABS),
                std::make_pair("popcnt", hl_expression_node::POPCNT),
                std::make_pair("efi", hl_expression_node::EFI),
                std::make_pair("bset", hl_expression_node::BSET),
                std::make_pair("bsel", hl_expression_node::BSEL),
                std::make_pair("nop", hl_expression_node::NOP)
        };
        static std::map<std::string, int> n_arguments= {
                std::make_pair("itf", 1),
                std::make_pair("fti", 1),
                std::make_pair("satp", 2),
                std::make_pair("satn", 2),
                std::make_pair("abs", 1),
                std::make_pair("popcnt", 1),
                std::make_pair("efi", 2),
                std::make_pair("binv", 2),
                std::make_pair("bset", 3),
                std::make_pair("bsel", 2),
                std::make_pair("bclr", 2),
                std::make_pair("nop", 0)
        };

        unsigned int matches = substitutions.count(element->get_name());
        if(matches == 0) {
            return {element};
        }

        std::shared_ptr<hl_expression_node> retval = std::make_shared<hl_expression_node>(substitutions[element->get_name()]);

        if(n_arguments[element->get_name()]== 3){
            retval = std::make_shared<hl_expression_node>(hl_expression_node::ASSIGN);
            retval->set_lhs(element->get_arguments()[2]);
            std::shared_ptr<hl_expression_node> rhs = std::make_shared<hl_expression_node>(substitutions[element->get_name()]);
            rhs->set_lhs(element->get_arguments()[0]);
            rhs->set_rhs(element->get_arguments()[1]);
            retval->set_rhs(rhs);
        } else if(n_arguments[element->get_name()]==2){
            retval->set_lhs(element->get_arguments()[0]);
            retval->set_rhs(element->get_arguments()[1]);
        }else if(n_arguments[element->get_name()]==1){
            retval->set_rhs(element->get_arguments()[0]);
        }

        return {retval};
    }
}