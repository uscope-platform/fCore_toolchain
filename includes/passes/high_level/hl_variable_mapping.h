//
// Created by fils on 09/07/2021.
//

#ifndef FCORE_HAS_HL_VARIABLE_MAPPING_H
#define FCORE_HAS_HL_VARIABLE_MAPPING_H

#include "frontend/variable_map.hpp"
#include "passes/pass_base.hpp"

#include "ast/high_level/hl_ast_node.h"
#include "ast/high_level/hl_definition_node.h"
#include "ast/high_level/hl_expression_node.h"

class hl_variable_mapping : public pass_base<hl_ast_node> {
public:
    explicit hl_variable_mapping(std::shared_ptr<variable_map>  &v);
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    void process_var(std::shared_ptr<hl_ast_node> element);
    int get_pass_type() override { return GLOBAL_PASS;};
private:
    std::shared_ptr<variable_map> var_map;
};


#endif //FCORE_HAS_HL_VARIABLE_MAPPING_H
