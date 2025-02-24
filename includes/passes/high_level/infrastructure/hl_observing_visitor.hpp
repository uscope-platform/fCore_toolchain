

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

#ifndef HL_OBSERVING_VISITOR_HPP
#define HL_OBSERVING_VISITOR_HPP

#include <memory>

#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore {

    struct hl_observing_visitor_operations{
        std::function<void (const std::shared_ptr<hl_ast_conditional_node> &cond)> visit_conditional;
        std::function<void (const std::shared_ptr<hl_ast_loop_node> &cond)> visit_loop;
        std::function<void (const std::shared_ptr<hl_ast_operand> &cond)> visit_operand;
        std::function<void (const std::shared_ptr<hl_definition_node> & def)> visit_definition;
        std::function<void (const std::shared_ptr<hl_expression_node> &cond)> visit_expression;
        std::function<void (const std::shared_ptr<hl_function_def_node> &cond)> visit_function_def;
        std::function<void (const std::shared_ptr<hl_function_call_node> &cond)> visit_function_call;
    };
    class hl_observing_visitor {
    public:
        void visit(const hl_observing_visitor_operations &operations,const std::shared_ptr<hl_code_block> &node);
    private:
        void process_node_by_type(const std::shared_ptr<hl_ast_node> &node);
        void process_nodes_vector(const std::vector<std::shared_ptr<hl_ast_node>> &node);
        void process_node(const std::shared_ptr<hl_ast_conditional_node> &cond);
        void process_node(const std::shared_ptr<hl_ast_loop_node> &loop);
        void process_node(const std::shared_ptr<hl_ast_operand> &op);
        void process_node(const std::shared_ptr<hl_definition_node> &def);
        void process_node(const std::shared_ptr<hl_expression_node> &cond);
        void process_node(const std::shared_ptr<hl_function_call_node> &cond);
        void process_node(const std::shared_ptr<hl_function_def_node> &def);
        void process_node(const std::shared_ptr<hl_code_block> &block);
        hl_observing_visitor_operations ops;

    };


}

#endif //HL_OBSERVING_VISITOR_HPP
