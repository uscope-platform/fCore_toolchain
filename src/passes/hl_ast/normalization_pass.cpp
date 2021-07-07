//
// Created by fils on 07/07/2021.
//

#include "passes/hl_ast/normalization_pass.h"

normalization_pass::normalization_pass() : pass_base<hl_ast_node>("normalizzation pass"){

}

std::vector<std::shared_ptr<hl_ast_node>> normalization_pass::process_node(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;
    retval.push_back(element);

    return retval;
}
