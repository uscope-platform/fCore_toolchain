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

#ifndef FCORE_TOOLCHAIN_HL_PASS_MANAGER_HPP
#define FCORE_TOOLCHAIN_HL_PASS_MANAGER_HPP


#include "instrumentation/instrumentation_core.hpp"
#include "data_structures/high_level_ast/high_level_ast.hpp"
#include "pass_base.hpp"

namespace fcore{

    enum pass_type {
        single_pass=0,
        repeating_pass_group = 1,
        unique_pass_group = 2
    };

    struct analysis_pass {
        std::shared_ptr<pass_base> pass;
        std::string name;
        uint8_t repetitions;
    };

    struct opt_pass {
        std::vector<std::shared_ptr<pass_base>> pass;
        pass_type type = single_pass;
        std::string name;
        bool enabled = true;
    };


    class hl_pass_manager {
    public:

        void add_optimization_pass(const std::string& name, const std::shared_ptr<pass_base>& pass);
        void add_optimization_pass_group(
            const std::string& name,
            const std::vector<std::shared_ptr<pass_base>>& group
            );

        void add_analysis_pass(const std::string&name, const std::shared_ptr<pass_base>& pass, uint8_t repetitions);

        [[nodiscard]] std::shared_ptr<ast_code_block> run_optimizations(
            const std::shared_ptr<ast_code_block>& AST,
            const std::vector<std::shared_ptr<ast_definition>> &globals
        );

        void run_semantic_analysis(
            std::shared_ptr<ast_code_block> AST,
            const std::vector<std::shared_ptr<ast_definition>> &globals
        );

        std::shared_ptr<ast_code_block> run_repeating_pass_group(
            std::shared_ptr<ast_code_block> &subtree,
            const std::vector<std::shared_ptr<pass_base>>& group,
            const std::vector<std::shared_ptr<ast_definition>> &globals
        );

        void disable_all();
        void enable_pass(const std::string& name);

        void set_profiler(std::shared_ptr<instrumentation_core> &p){
            this->ic = p;
        };

    private:

        std::shared_ptr<instrumentation_core> ic;
        std::vector<opt_pass> optimization_passes;
        std::vector<analysis_pass> analysis_passes;
    };
}



#endif //FCORE_TOOLCHAIN_HL_PASS_MANAGER_HPP
