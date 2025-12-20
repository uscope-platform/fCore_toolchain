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

#ifndef FCORE_TOOLCHAIN_STREAM_PASS_BASE_HPP
#define FCORE_TOOLCHAIN_STREAM_PASS_BASE_HPP

#include "data_structures/instruction_stream/instruction_stream.hpp"

namespace fcore{

    enum stream_pass_type {
        high_level_pass =0,
        asm_pass = 1,
        global_pass = 2
    };

    class stream_pass_base {
    public:

        explicit stream_pass_base(std::string name, uint32_t n_scans, bool is_mutable, stream_pass_type type){
            this->name = std::move(name);
            this->n_scans = n_scans;
            this->is_mutable = is_mutable;
            this->is_vector = false;
            this->pass_type= type;
        }

        virtual void setup() {}
        virtual void inter_pass() {}

        virtual std::optional<instruction_variant> apply_mutable_pass(instruction_variant &element, uint32_t n) {
            return element;
        }

        virtual std::vector<instruction_variant> apply_vector_mutable_pass(instruction_variant &element, uint32_t n_pass) {
            return {element};
        }

        virtual std::optional<instruction_variant> apply_pass(const instruction_variant &element, uint32_t n) {
            return element;
        }

        std::string get_name() {return name;}

        virtual ~stream_pass_base() = default;

        stream_pass_type pass_type;

        uint32_t n_scans;
        bool is_mutable;
        bool is_vector;
    private:
        std::string name;
    };
}

#endif //FCORE_TOOLCHAIN_STREAM_PASS_BASE_HPP
