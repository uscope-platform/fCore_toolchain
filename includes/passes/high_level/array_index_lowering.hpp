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


#ifndef FCORE_TOOLCHAIN_ARRAY_INDEX_LOWERING_HPP
#define FCORE_TOOLCHAIN_ARRAY_INDEX_LOWERING_HPP

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
namespace fcore{
    class array_index_lowering : public  pass_base<hl_ast_node> {
    public:
        array_index_lowering();
        std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    private:
        std::shared_ptr<hl_ast_node> process_node_by_type(std::shared_ptr<hl_ast_node> element);
        std::shared_ptr<hl_ast_node> process_terminal(std::shared_ptr<hl_ast_node> element);
        std::shared_ptr<hl_ast_node> process_expression(std::shared_ptr<hl_expression_node> exp);
        std::shared_ptr<hl_ast_node> process_operand(const std::shared_ptr<hl_ast_operand> &op);
        std::shared_ptr<hl_ast_node> process_definition(std::shared_ptr<hl_definition_node> exp);
        std::shared_ptr<hl_ast_node> process_f_call(std::shared_ptr<hl_function_call_node> f_call);
    };
}


#endif //FCORE_TOOLCHAIN_ARRAY_INDEX_LOWERING_HPP
