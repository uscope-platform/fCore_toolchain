

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

#ifndef FCORE_TOOLCHAIN_LITERAL_COERCION_PASS_HPP
#define FCORE_TOOLCHAIN_LITERAL_COERCION_PASS_HPP

#include <map>
#include <string>

#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/high_level/infrastructure/hl_observing_visitor.hpp"
#include "passes/high_level/infrastructure/hl_acting_visitor.hpp"

namespace fcore {

    /// Turns decimal integer literals into float literals wherever a float is expected, as C does implicitly:
    /// `float a = 1024;`, `a = 3;`, `a * 2`, `return 1;` in a float function, arguments of user functions.
    /// \`raw(1)\` marks an integer literal as a bit pattern that is left alone, which is how a float variable or array
    /// element is made to carry raw integer bits (the operation selector of an efi input for example).
    class literal_coercion_pass : public pass_base {
    public:
        literal_coercion_pass();
        pass_result process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) override;
    private:
        std::vector<std::shared_ptr<ast_node>> resolve_raw(const std::shared_ptr<ast_call> &call);
        void process_definition(const std::shared_ptr<ast_definition> &def);
        void process_function_def(const std::shared_ptr<ast_function_def> &def);
        void process_expression(const std::shared_ptr<ast_expression> &exp);
        void process_call(const std::shared_ptr<ast_call> &call);

        static bool is_int_literal(const std::shared_ptr<ast_node> &node);
        bool is_float(const std::shared_ptr<ast_node> &node);
        static std::shared_ptr<ast_node> to_float(const std::shared_ptr<ast_node> &node);

        std::map<std::string, c_types_t> scope;
        std::map<std::string, c_types_t> global_scope;
        std::map<std::string, std::vector<c_types_t>> signatures;
    };

}

#endif //FCORE_TOOLCHAIN_LITERAL_COERCION_PASS_HPP
