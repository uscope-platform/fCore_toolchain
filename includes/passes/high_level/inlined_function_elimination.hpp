// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_HAS_INLINED_FUNCTION_ELIMINATION_HPP
#define FCORE_HAS_INLINED_FUNCTION_ELIMINATION_HPP

#include <utility>

#include "ast/high_level/hl_ast_node.hpp"
#include "ast/high_level/hl_function_def_node.hpp"
#include "passes/pass_base.hpp"

class inlined_function_elimination : public  pass_base<hl_ast_node>{
public:
    explicit inlined_function_elimination(std::string entry_point_name);
    std::vector<std::shared_ptr<hl_ast_node>> process_node(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return NODE_PASS;};
private:
    std::string entry_point;
};



#endif //FCORE_HAS_INLINED_FUNCTION_ELIMINATION_HPP
