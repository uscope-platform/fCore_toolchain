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

    std::shared_ptr<ast_code_block> intrinsics_implementation_pass::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_function_call = process_function_call;
        return visitor.visit(ops, element);

    }


    std::vector<std::shared_ptr<ast_node>>
    intrinsics_implementation_pass::process_function_call(const std::shared_ptr<ast_call> &element) {


        static std::map<std::string, ast_expression::expression_type> substitutions= {
                std::make_pair("itf", ast_expression::ITF),
                std::make_pair("fti", ast_expression::FTI),
                std::make_pair("satp", ast_expression::SATP),
                std::make_pair("satn", ast_expression::SATN),
                std::make_pair("abs", ast_expression::ABS),
                std::make_pair("popcnt", ast_expression::POPCNT),
                std::make_pair("efi", ast_expression::EFI),
                std::make_pair("bset", ast_expression::BSET),
                std::make_pair("bsel", ast_expression::BSEL),
                std::make_pair("nop", ast_expression::NOP)
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

        std::shared_ptr<ast_expression> retval = std::make_shared<ast_expression>(substitutions[element->get_name()]);

        if(n_arguments[element->get_name()]== 3){
            retval = std::make_shared<ast_expression>(ast_expression::ASSIGN);
            retval->set_lhs(element->get_arguments()[2]);
            std::shared_ptr<ast_expression> rhs = std::make_shared<ast_expression>(substitutions[element->get_name()]);
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