// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//


#ifndef FCORE_TOOLCHAIN_DEAD_VARIABLE_ELIMINATION_HPP
#define FCORE_TOOLCHAIN_DEAD_VARIABLE_ELIMINATION_HPP

#include "passes/pass_base.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "tools/variable_map.hpp"


class dead_variable_elimination : public pass_base<hl_ast_node>{
public:
    explicit dead_variable_elimination();
    std::shared_ptr<hl_ast_node> process_global(std::shared_ptr<hl_ast_node> element) override;
    int get_pass_type() override { return GLOBAL_PASS;};


};


#endif //FCORE_TOOLCHAIN_DEAD_VARIABLE_ELIMINATION_HPP
