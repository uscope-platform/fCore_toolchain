

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

#include "passes/semantic_analysis/infrastructure/type_check_base.hpp"

#include "passes/semantic_analysis/assignments.hpp"
#include "passes/semantic_analysis/function_calls.hpp"

namespace fcore{
    struct check_pass {
        std::shared_ptr<type_check_base> pass;
        std::string name;
    };
    class type_checking_engine {
        public:

            void check(const std::shared_ptr<hl_code_block> & ast);
            void add_check(const std::string& name, const std::shared_ptr<type_check_base>& pass);
        private:
          std::vector<check_pass> passes;
    };


    static type_checking_engine create_type_checking_engine(){
        type_checking_engine engine;
        engine.add_check("Function calls",  std::make_shared<function_calls_checks>());
        engine.add_check("Assignments", std::make_shared<assignments_checks>());


        return engine;
    }
}




#endif //TYPE_CHECKING_ENGINE_HPP
