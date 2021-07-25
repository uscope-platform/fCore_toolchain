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


#include "passes/high_level/loop_unrolling_pass.hpp"

loop_unrolling_pass::loop_unrolling_pass() : pass_base<hl_ast_node>("C loop unrolling pass"){

}

std::shared_ptr<hl_ast_node> loop_unrolling_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    std::vector<std::shared_ptr<hl_ast_node>> body;

    for(const auto& item:element->get_content()){
        body.push_back(item);
    }


    retval->set_content(body);
    return retval;
}
