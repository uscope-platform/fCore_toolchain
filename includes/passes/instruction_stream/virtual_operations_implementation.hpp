

//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_VIRTUAL_OPERATIONS_IMPLEMENTATION_HPP
#define FCORE_TOOLCHAIN_VIRTUAL_OPERATIONS_IMPLEMENTATION_HPP

#include "stream_pass_base.hpp"
#include "fCore_isa.hpp"

namespace fcore {
    class virtual_operations_implementation : public stream_pass_base {
    public:
        explicit virtual_operations_implementation();

        std::shared_ptr<ll_instruction_node> apply_pass(std::shared_ptr<ll_instruction_node> element, uint32_t n) override;
    };
}

#endif //FCORE_TOOLCHAIN_VIRTUAL_OPERATIONS_IMPLEMENTATION_HPP
