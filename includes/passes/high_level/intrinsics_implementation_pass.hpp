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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_INTRINSICS_IMPLEMENTATION_PASS_HPP
#define FCORE_TOOLCHAIN_INTRINSICS_IMPLEMENTATION_PASS_HPP

#include <map>
#include <string>

#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "passes/pass_base.hpp"

class intrinsics_implementation_pass : public  pass_base<hl_ast_node> {
public:
    intrinsics_implementation_pass();
    std::shared_ptr<hl_ast_node> process_leaf(std::shared_ptr<hl_ast_node> element) override;
    std::shared_ptr<hl_ast_node> process_node_by_type(const std::shared_ptr<hl_ast_node>& element);
    std::shared_ptr<hl_ast_node> process_function_call(const std::shared_ptr<hl_function_call_node>& element);
    int get_pass_type() override { return LEAF_PASS;};
private:
    std::map<std::string, expression_type_t> substitutions;
    std::map<std::string, int> n_arguments;
};


#endif //FCORE_TOOLCHAIN_INTRINSICS_IMPLEMENTATION_PASS_HPP
