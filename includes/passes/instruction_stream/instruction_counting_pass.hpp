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

#ifndef FCORE_TOOLCHAIN_INSTRUCTION_COUNTING_PASS_HPP
#define FCORE_TOOLCHAIN_INSTRUCTION_COUNTING_PASS_HPP


#include "passes/instruction_stream/stream_pass_base.hpp"

namespace fcore{

    struct instruction_count{
        uint32_t load = 0;
        uint32_t efi = 0;
        uint32_t regular = 0;
        uint32_t stop = 1;
    };

    class instruction_counting_pass : public stream_pass_base {
    public:
        explicit instruction_counting_pass(std::shared_ptr<struct instruction_count> &c);
        std::optional<instruction_variant> apply_pass(const instruction_variant &element, uint32_t n) override;
    private:
        std::shared_ptr<struct instruction_count> count;
    };
}


#endif //FCORE_TOOLCHAIN_INSTRUCTION_COUNTING_PASS_HPP
