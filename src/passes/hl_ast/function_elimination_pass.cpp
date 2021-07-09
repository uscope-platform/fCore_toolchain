//
// Created by fils on 09/07/2021.
//

#include "passes/hl_ast/function_elimination_pass.h"

function_elimination_pass::function_elimination_pass() : pass_base<hl_ast_node>("function elimination pass"){ {

}

}
std::shared_ptr<hl_ast_node> function_elimination_pass::process_global(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> retval = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    std::shared_ptr<hl_function_def_node> ep = std::static_pointer_cast<hl_function_def_node>(element->get_content()[0]);

    retval->set_content(ep->get_body());
    return retval;
}
