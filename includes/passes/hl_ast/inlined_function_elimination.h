//
// Created by fils on 08/07/2021.
//

#ifndef FCORE_HAS_INLINED_FUNCTION_ELIMINATION_H
#define FCORE_HAS_INLINED_FUNCTION_ELIMINATION_H

#include <utility>

#include "code_elements/hl_ast/hl_ast_node.h"
#include "code_elements/hl_ast/hl_function_def_node.h"
#include "passes/pass_base.hpp"

class inlined_function_elimination : public  pass_base<hl_ast_node>{
public:
    explicit inlined_function_elimination(std::string entry_point_name);
    std::vector<std::shared_ptr<hl_ast_node>> process_node(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return NODE_PASS;};
private:
    std::string entry_point;
};



#endif //FCORE_HAS_INLINED_FUNCTION_ELIMINATION_H
