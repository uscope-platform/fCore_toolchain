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

#ifndef FCORE_TOOLCHAIN_HL_FUNCTION_CALL_NODE_HPP
#define FCORE_TOOLCHAIN_HL_FUNCTION_CALL_NODE_HPP

#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "data_structures/high_level_ast/hl_ast_operand.hpp"

#include <string>
#include <utility>
#include <sstream>

class hl_function_call_node : public hl_ast_node {
public:
    hl_function_call_node(std::string n, std::vector<std::shared_ptr<hl_ast_node>> a);
    std::string get_name() {return name;};
    std::string pretty_print();
    std::vector<std::shared_ptr<hl_ast_node>> get_arguments() { return arguments;};
    void set_arguments(std::vector<std::shared_ptr<hl_ast_node>> args) {arguments = args;};
    friend bool operator==(const hl_function_call_node& lhs, const hl_function_call_node& rhs);
    bool is_terminal() override {
        return true;
    }
protected:
    std::string name;
    std::vector<std::shared_ptr<hl_ast_node>> arguments;
};

#endif //FCORE_TOOLCHAIN_HL_FUNCTION_CALL_NODE_HPP
