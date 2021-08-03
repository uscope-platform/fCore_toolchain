// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.05/07/2021.
//

#ifndef FCORE_TOOLCHAIN_ARRAY_SCALARIZATION_PASS_HPP
#define FCORE_TOOLCHAIN_ARRAY_SCALARIZATION_PASS_HPP

#include <unordered_map>

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"

class array_scalarization_pass : public pass_base<hl_ast_node> {
public:
    array_scalarization_pass();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};
private:

    std::shared_ptr<hl_ast_node> process_element(std::shared_ptr<hl_ast_node> node);
    std::shared_ptr<hl_expression_node> process_expression(std::shared_ptr<hl_expression_node> node);
    std::shared_ptr<hl_ast_operand> process_operand(std::shared_ptr<hl_ast_operand> node);
    std::shared_ptr<hl_definition_node> process_definition(std::shared_ptr<hl_definition_node> node);
    int loop_variable_counter;
    std::unordered_map<std::string, int> var_index_map;
};


#endif //FCORE_TOOLCHAIN_ARRAY_SCALARIZATION_PASS_HPP
