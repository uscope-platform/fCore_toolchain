

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

#ifndef FCORE_TOOLCHAIN_HL_AST_VISITOR_HPP
#define FCORE_TOOLCHAIN_HL_AST_VISITOR_HPP

#include <memory>
#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{

    struct hl_ast_visitor_operations{
        std::function<std::shared_ptr<hl_ast_node>(const std::shared_ptr<hl_ast_conditional_node> &cond)> visit_conditional;
        std::function<std::shared_ptr<hl_ast_node>(const std::shared_ptr<hl_ast_loop_node> &cond)> visit_loop;
        std::function<std::shared_ptr<hl_ast_node>(const std::shared_ptr<hl_ast_operand> &cond)> visit_operand;
        std::function<std::shared_ptr<hl_ast_node>(const std::shared_ptr<hl_definition_node> &cond)> visit_definition;
        std::function<std::shared_ptr<hl_ast_node>(const std::shared_ptr<hl_expression_node> &cond)> visit_expression;
        std::function<std::shared_ptr<hl_ast_node>(const std::shared_ptr<hl_function_def_node> &cond)> visit_function_def;
        std::function<std::shared_ptr<hl_ast_node>(const std::shared_ptr<hl_function_call_node> &cond)> visit_function_call;
    };

    class hl_ast_visitor {
    public:
        std::shared_ptr<hl_ast_node> visit(const hl_ast_visitor_operations &operations,const std::shared_ptr<hl_code_block> &node);
    private:
        std::shared_ptr<hl_ast_node> process_node_by_type(const std::shared_ptr<hl_ast_node> &node);
        std::shared_ptr<hl_ast_node> process_node(const std::shared_ptr<hl_ast_conditional_node> &cond);
        std::shared_ptr<hl_ast_node> process_node(const std::shared_ptr<hl_ast_loop_node> &loop);
        std::shared_ptr<hl_ast_node> process_node(const std::shared_ptr<hl_ast_operand> &op);
        std::shared_ptr<hl_ast_node> process_node(const std::shared_ptr<hl_definition_node> &def);
        std::shared_ptr<hl_ast_node> process_node(const std::shared_ptr<hl_expression_node> &cond);
        std::shared_ptr<hl_ast_node> process_node(const std::shared_ptr<hl_function_call_node> &cond);
        std::shared_ptr<hl_ast_node> process_node(const std::shared_ptr<hl_function_def_node> &def);
        hl_ast_visitor_operations ops;

    };

}


#endif //FCORE_TOOLCHAIN_HL_AST_VISITOR_HPP
