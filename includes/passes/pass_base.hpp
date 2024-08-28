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

#ifndef FCORE_TOOLCHAIN_PASS_BASE_HPP
#define FCORE_TOOLCHAIN_PASS_BASE_HPP

#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

#define NONE_PASS 0
#define LEAF_PASS 2
#define GLOBAL_PASS 3

namespace fcore{
    template<class E>
    class pass_base {
    public:
        pass_base(std::string n) {name = std::move(n);};

        virtual std::shared_ptr<E> process_global(std::shared_ptr<E> element) {
            return element;
        };
        virtual std::shared_ptr<E> process_leaf(std::shared_ptr<E> element){
            return element;
        };
        std::string get_name() {return name;};
        virtual int get_pass_type() { return NONE_PASS;};
    private:
        std::string name;
    };
}

#endif //FCORE_TOOLCHAIN_PASS_BASE_HPP
