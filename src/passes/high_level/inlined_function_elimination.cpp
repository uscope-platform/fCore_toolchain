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
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.08/07/2021.
//

#include "passes/high_level/inlined_function_elimination.hpp"


inlined_function_elimination::inlined_function_elimination(std::string entry_point_name) : pass_base("inlined function elimination pass") {
    entry_point = std::move(entry_point_name);
}

std::vector<std::shared_ptr<hl_ast_node>>
inlined_function_elimination::process_node(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;

    if(element->node_type == hl_ast_node_type_function_def){
        std::shared_ptr<hl_function_def_node> node = std::static_pointer_cast<hl_function_def_node>(element);
        if(node->get_name() == entry_point)
            retval = node->get_body();
    } else{
        retval.push_back(element);
    }

    return retval;
}

