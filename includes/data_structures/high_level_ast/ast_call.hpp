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

#ifndef FCORE_TOOLCHAIN_AST_CALL_HPP
#define FCORE_TOOLCHAIN_AST_CALL_HPP

#include "data_structures/high_level_ast/ast_node.hpp"
#include "data_structures/high_level_ast/ast_expression.hpp"
#include "data_structures/high_level_ast/ast_operand.hpp"

#include <string>
#include <sstream>
#include <utility>

namespace fcore{

    class ast_call : public ast_node {
    public:
        ast_call(std::string n, std::vector<std::shared_ptr<ast_node>> a);
        std::string get_name() {return name;};
        std::string pretty_print();
        std::vector<std::shared_ptr<ast_node>> get_arguments() { return arguments;};
        void set_arguments(std::vector<std::shared_ptr<ast_node>> args) {arguments = std::move(args);};

        friend bool operator==(const ast_call& lhs, const ast_call& rhs){
            bool ret_val = true;

            ret_val &= lhs.name == rhs.name;

            ret_val &= compare_vectors(lhs.arguments, rhs.arguments);

            return ret_val;
        };


        static std::shared_ptr<ast_call> deep_copy(const std::shared_ptr<ast_call> &node);

    protected:
        std::string name;
        std::vector<std::shared_ptr<ast_node>> arguments;
    };
}


#endif //FCORE_TOOLCHAIN_AST_CALL_HPP
