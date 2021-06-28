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

#include "fcore_has/frontend/C/Tree_visitor.hpp"


Tree_visitor::Tree_visitor(std::shared_ptr<variable_map> map) {
    varmap = std::move(map);
}


ast_t Tree_visitor::get_program() {
    return program_head;
}

std::shared_ptr<variable> Tree_visitor::get_variable(const std::string &variable_name, bool is_const) const {
    std::shared_ptr<variable> var;
    if(!varmap->count(variable_name))
        var = std::make_shared<variable>(is_const, variable_name);
    else
        var = varmap->at(variable_name);
    return var;
}
