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

#ifndef FCORE_TOOLCHAIN_HL_FUNCTION_DEF_NODE_HPP
#define FCORE_TOOLCHAIN_HL_FUNCTION_DEF_NODE_HPP

#include <map>
#include <string>
#include <utility>

#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_definition_node.hpp"
#include "ast/high_level/hl_expression_node.hpp"

class hl_function_def_node : public hl_ast_node{
public:
    hl_function_def_node();
    void set_return_type(c_types_t ret_val);
    c_types_t get_return_type() {return return_type;};
    void set_name(std::string n);
    void set_parameters_list(std::vector<std::shared_ptr<hl_definition_node>> list);
    std::vector<std::shared_ptr<hl_definition_node>> get_parameters_list() { return parameters_list;};
    void set_body(std::vector<std::shared_ptr<hl_ast_node>> b);
    void set_return(std::shared_ptr<hl_ast_node> r);
    std::string get_name();
    std::shared_ptr<hl_ast_node> get_return();
    std::vector<std::shared_ptr<hl_ast_node>> get_body();
    std::string pretty_print() override;
    friend bool operator==(const hl_function_def_node& lhs, const hl_function_def_node& rhs);
    bool is_terminal() override {
        return false;
    }
protected:
    c_types_t return_type;
    std::string name;
    std::vector<std::shared_ptr<hl_definition_node>> parameters_list;
    std::vector<std::shared_ptr<hl_ast_node>> function_body;
    std::shared_ptr<hl_ast_node> return_expression;
};


#endif //FCORE_TOOLCHAIN_HL_FUNCTION_DEF_NODE_HPP
