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

#ifndef FCORE_HAS_LOOP_IMPLEMENTATION_PASS_HPP
#define FCORE_HAS_LOOP_IMPLEMENTATION_PASS_HPP

#include <memory>
#include "code_elements/ll_ast/ll_ast_node.hpp"
#include "pass_manager.hpp"

class loop_implementation_pass : public pass_base {

public:
    std::vector<ast_t>process_node(ast_t element) override;
    int get_pass_type() override { return NODE_PASS;};
};


#endif //FCORE_HAS_LOOP_IMPLEMENTATION_PASS_HPP