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
// limitations under the License.05/07/2021.
//

#ifndef FCORE_TOOLCHAIN_ARRAY_INITIALIZATION_PROPAGATION_H
#define FCORE_TOOLCHAIN_ARRAY_INITIALIZATION_PROPAGATION_H

#include "passes/pass_base.hpp"
#include "tools/array_linearizer.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

class array_initialization_propagation_pass : public pass_base<hl_ast_node>{
public:
    array_initialization_propagation_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};

private:
    std::vector<std::shared_ptr<hl_ast_node>> process_node_by_type(const std::shared_ptr<hl_ast_node>& node);
    std::shared_ptr<hl_expression_node> process_expression(std::shared_ptr<hl_expression_node> node);
    std::shared_ptr<hl_ast_operand> process_operand(std::shared_ptr<hl_ast_operand> node);
    std::vector<std::shared_ptr<hl_ast_node>> process_definition(std::shared_ptr<hl_definition_node> node);
    std::shared_ptr<hl_function_def_node> process_function_definition(std::shared_ptr<hl_function_def_node> node);
    std::shared_ptr<hl_function_call_node> process_function_call(std::shared_ptr<hl_function_call_node> node);
    std::shared_ptr<hl_ast_conditional_node> process_conditional(std::shared_ptr<hl_ast_conditional_node>node);
    std::shared_ptr<hl_ast_loop_node> process_loop(std::shared_ptr<hl_ast_loop_node> node);

    std::unordered_map<std::string, std::shared_ptr<hl_definition_node>> def_map;
    std::unordered_map<std::string, std::vector<std::vector<int>>> dirty_elements_idx;
    unsigned int n_init_iom = 0;
};


#endif //FCORE_TOOLCHAIN_ARRAY_INITIALIZATION_PROPAGATION_H
