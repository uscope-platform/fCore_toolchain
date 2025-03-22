

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

#ifndef FUNCTION_CALLS_HPP
#define FUNCTION_CALLS_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/hl_observing_visitor.hpp"

#include <stack>
#include <unordered_map>

namespace fcore {

    class function_calls_checks : public pass_base{
    public:
        function_calls_checks();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;
    private:

        void push_stack();
        void pop_stack();
        void reset_conditional_stack();

        void map_definition(const std::shared_ptr<ast_function_def> &def);

        void process_definition(const std::shared_ptr<ast_definition> &def);
        void process_function_def(const std::shared_ptr<ast_function_def> &f_def);
        void process_function_call(const std::shared_ptr<ast_call> &call);

        std::stack<std::unordered_map<std::string, c_types_t>> scopes_stack;
        std::unordered_map<std::string, c_types_t> current_scope;

        std::unordered_map<std::string, std::vector<std::pair<std::string, c_types_t>>> definitions;
    };
}




#endif //FUNCTION_CALLS_HPP
