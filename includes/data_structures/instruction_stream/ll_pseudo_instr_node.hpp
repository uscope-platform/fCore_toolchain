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

#ifndef FCORE_TOOLCHAIN_LL_PSEUDO_INSTR_NODE_HPP
#define FCORE_TOOLCHAIN_LL_PSEUDO_INSTR_NODE_HPP

#include <utility>

#include "data_structures/instruction_stream/ll_instruction_node.hpp"
#include "data_structures/common/variable.hpp"
namespace fcore{

    class ll_pseudo_instr_node :public ll_instruction_node {
    public:
        ll_pseudo_instr_node(std::string op, std::vector<std::shared_ptr<variable>> args);

        std::vector<std::shared_ptr<variable>> get_arguments() {return arguments;};
        void set_arguments(std::vector<std::shared_ptr<variable>> a) {arguments = std::move(a);};
        int instruction_count() override;

        nlohmann::json dump();

        friend bool operator==(const ll_pseudo_instr_node& lhs, const ll_pseudo_instr_node& rhs){
            bool retval = true;

            if(lhs.arguments.empty() && rhs.arguments.empty()){
                retval &= true;
            } else if(lhs.arguments.empty() || rhs.arguments.empty()){
                retval = false;
            } else {
                bool args_equal = true;
                args_equal &= lhs.arguments.size() == rhs.arguments.size();
                for (int i = 0; i < lhs.arguments.size(); i++) {
                    args_equal &= *lhs.arguments[i] == *rhs.arguments[i];
                }
                retval &= args_equal;
            }
            return retval;
        };
    private:
        std::vector<std::shared_ptr<variable>> arguments;
    };
}


#endif //FCORE_TOOLCHAIN_LL_PSEUDO_INSTR_NODE_HPP
