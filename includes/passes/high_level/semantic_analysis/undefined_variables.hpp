

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

#ifndef UNDEFINED_VARIABLES_HPP
#define UNDEFINED_VARIABLES_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "passes/high_level/infrastructure/hl_observing_visitor.hpp"

#include <stack>
#include <unordered_set>
#include <spdlog/spdlog.h>

namespace fcore {
    class undefined_variables : public pass_base{
    public:
        undefined_variables();
        std::shared_ptr<hl_code_block> process_global(std::shared_ptr<hl_code_block> element) override;
    private:

        void push_stack();
        void pop_stack();
        void reset_conditional_stack();

        void process_definition(const std::shared_ptr<hl_definition_node> &def);
        void process_function_def(const std::shared_ptr<hl_function_def_node> &def);
        void process_operand(const std::shared_ptr<hl_ast_operand> &op) const;

        std::stack<std::unordered_set<std::string>> definitions_stack;
        std::unordered_set<std::string> current_stack;

    };



}


#endif //UNDEFINED_VARIABLES_HPP
