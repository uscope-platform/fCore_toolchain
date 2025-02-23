//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "passes/semantic_analysis/infrastructure/type_checking_engine.hpp"


namespace fcore {
    void type_checking_engine::check(const std::shared_ptr<hl_code_block> & ast) {
        for (auto &[pass, name]:passes) {
            pass->run_check(ast);
        }

    };
    void type_checking_engine::add_check(const std::string& name, const std::shared_ptr<type_check_base>& pass) {
        passes.push_back({pass, name});
    };
}