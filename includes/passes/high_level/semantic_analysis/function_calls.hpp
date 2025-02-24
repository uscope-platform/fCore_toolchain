

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

#ifndef FUNCTION_CALLS_HPP
#define FUNCTION_CALLS_HPP

#include "passes/high_level/infrastructure/pass_base.hpp"

namespace fcore {
    class function_calls_checks : public pass_base{
    public:
        function_calls_checks();
        std::shared_ptr<hl_code_block> process_global(std::shared_ptr<hl_code_block> element) override;
    private:
    };
}




#endif //FUNCTION_CALLS_HPP
