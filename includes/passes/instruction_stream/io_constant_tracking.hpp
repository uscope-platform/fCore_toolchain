//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
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


#ifndef FCORE_TOOLCHAIN_IO_CONSTANT_TRACKING_H
#define FCORE_TOOLCHAIN_IO_CONSTANT_TRACKING_H

#include "passes/instruction_stream/stream_pass_base.hpp"

namespace fcore{
    class io_constant_tracking : public stream_pass_base{
    public:
        io_constant_tracking(std::shared_ptr<std::unordered_map<std::string, std::pair<int,int>>> lam);
        std::optional<instruction_variant> apply_pass(const instruction_variant &element, uint32_t n)  override;
    private:
        void add_assignment(const std::string&);
        int index;
        std::shared_ptr<std::unordered_map<std::string, std::pair<int,int>>> last_assignment_map;
    };
}
#endif //FCORE_TOOLCHAIN_IO_CONSTANT_TRACKING_H
