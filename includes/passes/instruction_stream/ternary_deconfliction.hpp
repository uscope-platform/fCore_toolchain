

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

#ifndef TERNARY_DECONFLICTION_HPP
#define TERNARY_DECONFLICTION_HPP

#include <passes/instruction_stream/stream_pass_base.hpp>

namespace fcore {
    class ternary_deconfliction : public stream_pass_base{
    public:
        ternary_deconfliction();
        std::vector<instruction_variant> apply_vector_mutable_pass(instruction_variant &element,
            uint32_t n_pass) override;
    private:
        void map_ternaries(const instruction_variant &element);


        std::map<std::string, uint32_t> condition_usage_map;
        std::map<std::string, uint32_t> condition_progressives;
        std::vector<instruction_variant>deconflict(instruction_variant &element);
    };
}




#endif //TERNARY_DECONFLICTION_HPP
