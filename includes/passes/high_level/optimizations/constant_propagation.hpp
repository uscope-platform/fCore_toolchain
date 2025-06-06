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
//

#ifndef FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP
#define FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP


#include "data_structures/constants_tracker.h"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/pass_base.hpp"
#include "tools/variable_map.hpp"

namespace fcore{
    class constant_propagation :public pass_base {
    public:
        explicit constant_propagation();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;

    private:
        std::shared_ptr<ast_node> propagate_constant(std::shared_ptr<ast_node> element, int instr_idx);
        std::shared_ptr<ast_node> propagate_constant(std::shared_ptr<ast_expression> element, int instr_idx);
        std::shared_ptr<ast_node> propagate_constant(std::shared_ptr<ast_definition> element, int instr_idx);
        std::shared_ptr<ast_operand> propagate_constant(std::shared_ptr<ast_operand> element, int instr_idx);

        bool map_constants(const std::shared_ptr<ast_node>& element, int instr_idx);
        bool map_constants(const std::shared_ptr<ast_expression>& element, int instr_idx);
        bool map_constants(const std::shared_ptr<ast_definition>& element, int instr_idx);
        bool map_constants(const std::shared_ptr<ast_operand>& element, const std::shared_ptr<ast_operand> &target, int instr_idx);

        std::vector<uint32_t> get_index_array(const std::shared_ptr<ast_operand> &target);

        void analyze_assignment(const std::shared_ptr<ast_expression> &element, int instr_idx);
        bool needs_termination(const std::shared_ptr<ast_expression> &element, int instr_idx);
        constants_tracker tracker;

        std::shared_ptr<ast_node> purge_definition(std::shared_ptr<ast_node> element);

    };
}



#endif //FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP
