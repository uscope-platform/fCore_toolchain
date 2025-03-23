

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
        struct operations {
            std::function<void (const std::shared_ptr<ast_conditional> &cond)> visit_conditional;
            std::function<void ()> before_else;
            std::function<void (const std::shared_ptr<ast_loop> &cond)> visit_loop;
            std::function<void (const std::shared_ptr<ast_operand> &cond)> visit_operand;
            std::function<void (const std::shared_ptr<ast_definition> & def)> visit_definition;
            std::function<void (const std::shared_ptr<ast_expression> &cond)> visit_expression;
            std::function<void (const std::shared_ptr<ast_function_def> &cond)> visit_function_def;
            std::function<void (const std::shared_ptr<ast_call> &cond)> visit_function_call;
        };

        operations pre;
        operations post;
    };
    class hl_observing_visitor {
    public:
        void visit(const hl_observing_visitor_operations &operations,const std::shared_ptr<ast_code_block> &node);
    private:
        void process_node_by_type(const std::shared_ptr<ast_node> &node);
        void process_nodes_vector(const std::vector<std::shared_ptr<ast_node>> &node);
        void process_node(const std::shared_ptr<ast_conditional> &cond);
        void process_node(const std::shared_ptr<ast_loop> &loop);
        void process_node(const std::shared_ptr<ast_operand> &op);
        void process_node(const std::shared_ptr<ast_definition> &def);
        void process_node(const std::shared_ptr<ast_expression> &cond);
        void process_node(const std::shared_ptr<ast_call> &cond);
        void process_node(const std::shared_ptr<ast_function_def> &def);
        void process_node(const std::shared_ptr<ast_code_block> &block);
        hl_observing_visitor_operations ops;

    };


}

#endif //HL_OBSERVING_VISITOR_HPP
