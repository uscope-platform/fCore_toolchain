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

#ifndef FCORE_TOOLCHAIN_LL_PASSES_HPP
#define FCORE_TOOLCHAIN_LL_PASSES_HPP

#include "pass_manager_base.hpp"
// LL passes
#include "passes/low_level/pseudo_instructions_pass.hpp"
#include "passes/low_level/load_intercalation_pass.hpp"

#include "tools/variable_map.hpp"
#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "passes/low_level/ll_pass_manager.hpp"
#include "passes/pass_base.hpp"

namespace fcore{
    static ll_pass_manager create_ll_pass_manager(int dump_ast_level){
        ll_pass_manager manager(dump_ast_level);
        manager.add_morphing_pass("Pseudo Instruction Implementation", std::make_shared<pseudo_instructions_pass>());
        return manager;
    }
}


#endif //FCORE_TOOLCHAIN_LL_PASSES_HPP
