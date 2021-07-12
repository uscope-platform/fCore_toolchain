//
// Created by fils on 12/07/2021.
//

#include "passes/high_level/intrinsics_implementation_pass.hpp"

intrinsics_implementation_pass::intrinsics_implementation_pass() : pass_base<hl_ast_node>("intrinsics implementation pass") {

}

std::vector<std::shared_ptr<hl_ast_node>>
intrinsics_implementation_pass::process_node(std::shared_ptr<hl_ast_node> element) {
    std::vector<std::shared_ptr<hl_ast_node>> retval;
    retval.push_back(element);
    return retval;
}
