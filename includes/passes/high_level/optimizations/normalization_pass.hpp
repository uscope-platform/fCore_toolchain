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

#ifndef FCORE_TOOLCHAIN_NORMALIZATION_PASS_HPP
#define FCORE_TOOLCHAIN_NORMALIZATION_PASS_HPP

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/pass_base.hpp"

namespace fcore{


    typedef std::pair<std::shared_ptr<ast_node>, std::vector<std::shared_ptr<ast_node>>> norm_pair_t;

    class normalization_pass : public pass_base {
    public:
        normalization_pass();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;
        bool is_normal(const std::shared_ptr<ast_node>& element);

        norm_pair_t process_node_by_type(std::shared_ptr<ast_node> n);
        norm_pair_t process_node_def(const std::shared_ptr<ast_definition>& n);
        norm_pair_t process_node_exp(const std::shared_ptr<ast_expression>& n);

        c_types_t get_expression_type(std::shared_ptr<ast_expression> expr);
    private:
        int intermediate_ordinal = 0;
    };
}


#endif //FCORE_TOOLCHAIN_NORMALIZATION_PASS_HPP
