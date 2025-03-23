

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

#ifndef TYPE_PROPAGATION_HPP
#define TYPE_PROPAGATION_HPP

#include <stack>

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/hl_acting_visitor.hpp"

namespace fcore {
    class type_propagation :public pass_base{
    public:
        type_propagation();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;

        std::vector<std::shared_ptr<ast_node>> process_definition(const std::shared_ptr<ast_definition> &node);
        std::shared_ptr<ast_node> process_operand(const std::shared_ptr<ast_operand> &node);


        void enter_loop(const std::shared_ptr<ast_loop> &node);
        std::shared_ptr<ast_node> exit_loop(const std::shared_ptr<ast_loop> &node);

        void enter_function_def(const std::shared_ptr<ast_function_def> &node);
        std::vector<std::shared_ptr<ast_node>> exit_function_def(const std::shared_ptr<ast_function_def> &node);

        void enter_conditional(const std::shared_ptr<ast_conditional> &node);
        void after_else_conditional(const std::shared_ptr<ast_conditional> &node);
        std::shared_ptr<ast_node> exit_conditional(const std::shared_ptr<ast_conditional> &node);

    private:

        std::stack<std::unordered_map<std::string, c_types_t>> scopes_stack;
        std::unordered_map<std::string, c_types_t> current_scope;

        void setup_frame();
        void teardown_frame();
    };



};



#endif //TYPE_PROPAGATION_HPP
