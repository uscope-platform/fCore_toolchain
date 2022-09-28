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

#include "passes/high_level/contiguous_array_identification.hpp"

contiguous_array_identification::contiguous_array_identification() : pass_base<hl_ast_node>("contiguous_array_identification"){
}

std::shared_ptr<hl_ast_node> contiguous_array_identification::process_element(std::shared_ptr<hl_function_call_node> element) {
    return std::shared_ptr<hl_ast_node>();
}

std::shared_ptr<hl_ast_node> contiguous_array_identification::process_global(std::shared_ptr<hl_ast_node> element) {
    switch (element->node_type) {
        case hl_ast_node_type_function_call:
            return process_element(std::static_pointer_cast<hl_function_call_node>(element));
        case hl_ast_node_type_expr:
            return process_element(std::static_pointer_cast<hl_expression_node>(element));
        case hl_ast_node_type_definition:
            return process_element(std::static_pointer_cast<hl_definition_node>(element));
        case hl_ast_node_type_conditional:
            return process_element(std::static_pointer_cast<hl_ast_conditional_node>(element));
        case hl_ast_node_type_loop:
            return process_element(std::static_pointer_cast<hl_ast_loop_node>(element));
        case hl_ast_node_type_function_def:
            return process_element(std::static_pointer_cast<hl_function_def_node>(element));
        case hl_ast_node_type_operand:
            return process_element(std::static_pointer_cast<hl_ast_operand>(element));
        case hl_ast_node_type_code_block:
            throw std::runtime_error("unexpected code block in contiguous array identification pass");
    }
    return element;
}

std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_expression_node> element) {
    return element;
}

std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_definition_node> element) {
    return element;
}

std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_ast_loop_node> element) {
    return element;
}

std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_ast_conditional_node> element) {
    return element;
}

std::shared_ptr<hl_ast_node>
contiguous_array_identification::process_element(std::shared_ptr<hl_function_def_node> element) {
    return element;
}

std::shared_ptr<hl_ast_node> contiguous_array_identification::process_element(std::shared_ptr<hl_ast_operand> element) {
    return element;
}
