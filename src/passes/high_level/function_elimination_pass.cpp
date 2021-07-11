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
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.09/07/2021.
//

#include "passes/high_level/function_elimination_pass.hpp"

function_elimination_pass::function_elimination_pass() : pass_base<hl_ast_node>("function elimination pass"){ {

}

}
std::shared_ptr<hl_ast_node> function_elimination_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::shared_ptr<hl_function_def_node> ep = std::static_pointer_cast<hl_function_def_node>(element->get_content()[0]);

    retval->set_content(ep->get_body());
    return retval;
}
