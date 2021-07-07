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

#ifndef FCORE_HAS_FUNCTION_MAPPING_H
#define FCORE_HAS_FUNCTION_MAPPING_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include "passes/pass_manager_base.hpp"
#include "code_elements/hl_ast/hl_expression_node.h"
#include "code_elements/hl_ast/hl_function_def_node.h"

class function_mapping : public pass_base<hl_ast_node> {
    public:
        function_mapping();
        std::vector<std::shared_ptr<hl_ast_node>>process_node(std::shared_ptr<hl_ast_node> element) override;
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> get_map_ref ();
        int get_pass_type() override { return NODE_PASS;};
    protected:
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> functions_map;
};



#endif //FCORE_HAS_FUNCTION_MAPPING_H
