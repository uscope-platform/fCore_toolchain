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

#ifndef FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP
#define FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP

#include <unordered_map>

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "tools/variable_map.hpp"

class constant_propagation :public pass_base<hl_ast_node> {
public:
    explicit constant_propagation();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    std::shared_ptr<hl_ast_node> substitute_constant(std::shared_ptr<hl_ast_node> element);
    std::shared_ptr<hl_ast_operand> process_operand(std::shared_ptr<hl_ast_operand> element);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::unordered_map<std::string, std::shared_ptr<hl_ast_operand>> constants_map;
};


#endif //FCORE_TOOLCHAIN_CONSTANT_PROPAGATION_HPP
