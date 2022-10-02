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
// limitations under the License.05/07/2021.
//

#ifndef FCORE_TOOLCHAIN_EARLY_REGISTGER_ALLOCATION_PASS_HPP
#define FCORE_TOOLCHAIN_EARLY_REGISTGER_ALLOCATION_PASS_HPP


#include <utility>

#include "fCore_isa.hpp"
#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "data_structures/common/memory_tracker.hpp"

class early_register_allocation_pass : public pass_base<hl_ast_node> {
public:
    early_register_allocation_pass(std::unordered_map<std::string, std::shared_ptr<variable>> iom);
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::shared_ptr<hl_ast_node> process_element(std::shared_ptr<hl_ast_node> element);
    std::shared_ptr<hl_ast_node> process_element(std::shared_ptr<hl_ast_conditional_node> element);
    std::shared_ptr<hl_ast_node> process_element(std::shared_ptr<hl_definition_node> element);
    std::shared_ptr<hl_ast_node> process_element(std::shared_ptr<hl_ast_operand> element);
    std::shared_ptr<hl_ast_node> process_element(std::shared_ptr<hl_expression_node> element);

    std::shared_ptr<variable> allocate_contiguous_array(std::shared_ptr<variable> v, uint32_t size);

    std::unordered_map<std::string, std::vector<int>> bindings_map;

    memory_tracker mem_tracker;
};


#endif //FCORE_TOOLCHAIN_EARLY_REGISTGER_ALLOCATION_PASS_HPP
