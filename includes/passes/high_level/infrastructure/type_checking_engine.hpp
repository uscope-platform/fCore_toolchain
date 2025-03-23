

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

#ifndef TYPE_CHECKING_ENGINE_HPP
#define TYPE_CHECKING_ENGINE_HPP

#include <string>
#include <vector>

#include "passes/high_level/infrastructure/pass_base.hpp"

#include "passes/high_level/semantic_analysis/assignments.hpp"
#include "passes/high_level/semantic_analysis/undefined_variables.hpp"
#include "passes/high_level/semantic_analysis/function_calls.hpp"
#include "passes/high_level/semantic_analysis/type_propagation.hpp"
#include "passes/high_level/semantic_analysis/mixed_type_operations.hpp"

#include "passes/high_level/infrastructure/hl_pass_manager.hpp"

namespace fcore{


    static hl_pass_manager create_type_checking_engine(){
        hl_pass_manager engine;
        engine.add_analysis_pass("Undefined Variables", std::make_shared<undefined_variables>(), 1);
        engine.add_analysis_pass("Function calls",  std::make_shared<function_calls_checks>(), 1);
        engine.add_analysis_pass("Assignments", std::make_shared<assignments_checks>(), 1);
        engine.add_analysis_pass("Type propagation", std::make_shared<type_propagation>(), 1);
        engine.add_analysis_pass("Mixed Operation checking", std::make_shared<mixed_type_operations>(), 1);

        return engine;
    }
}




#endif //TYPE_CHECKING_ENGINE_HPP
