

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

#ifndef TYPE_CHECK_BASE_HPP
#define TYPE_CHECK_BASE_HPP

#include <memory>
#include "data_structures/high_level_ast/high_level_ast.hpp"

namespace fcore{

    class type_check_base {
    public:
        virtual ~type_check_base() = default;

        explicit type_check_base(std::string n) {name = std::move(n);};

        virtual void run_check(const std::shared_ptr<hl_code_block>  &element) {};
        std::string get_name() {return name;};
    private:
        std::string name;
    };

}

#endif //TYPE_CHECK_BASE_HPP
