// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_FUCTION_MANGLING_PASS_H
#define FCORE_TOOLCHAIN_FUCTION_MANGLING_PASS_H


#include "passes/high_level/infrastructure/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{
    class fuction_mangling_pass  : public pass_base{
    public:
        fuction_mangling_pass();
        std::shared_ptr<ast_code_block> process_global(std::shared_ptr<ast_code_block> element,const std::vector<std::shared_ptr<ast_definition>> &globals) override;
    private:
        std::shared_ptr<ast_node> mangle_node(const std::shared_ptr<ast_node>& node, const std::string &function);
        std::shared_ptr<ast_expression> mangle_node(std::shared_ptr<ast_expression> node, const std::string& function);
        std::shared_ptr<ast_conditional> mangle_node(std::shared_ptr<ast_conditional> node, const std::string& function);
        std::shared_ptr<ast_call> mangle_node(const std::shared_ptr<ast_call>& node, const std::string& function);
        std::shared_ptr<ast_definition> mangle_node(const std::shared_ptr<ast_definition>& node, const std::string& function);
        std::shared_ptr<ast_loop> mangle_node(std::shared_ptr<ast_loop> node, const std::string& function);
        std::shared_ptr<ast_operand> mangle_node(const std::shared_ptr<ast_operand>& node, const std::string& function);
        std::vector<std::shared_ptr<ast_node>> mangle_vector(const std::vector<std::shared_ptr<ast_node>> &v, const std::string& function);
        std::shared_ptr<variable> mangle_variable(const std::shared_ptr<variable> &v, const std::string &function);
        std::string mangle_string(const std::string& s, const std::string& function);
    };
}



#endif //FCORE_TOOLCHAIN_FUCTION_MANGLING_PASS_H
