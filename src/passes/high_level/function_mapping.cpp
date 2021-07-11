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
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.07/07/2021.
//

#include "passes/high_level/function_mapping.hpp"


function_mapping::function_mapping() : pass_base<hl_ast_node>("function mapping pass"){
    functions_map = std::make_shared<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>>();
}

std::vector<std::shared_ptr<hl_ast_node>> function_mapping::process_node(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;
    retval.push_back(element);
    if(element->node_type == hl_ast_node_type_function_def){
        std::shared_ptr<hl_function_def_node> node = std::static_pointer_cast<hl_function_def_node>(element);
        std::string name = node->get_name();
        functions_map->insert({name, node});
    }

    return retval;
}

std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>>
function_mapping::get_map_ref() {
    return functions_map;
}


