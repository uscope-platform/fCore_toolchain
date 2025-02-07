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

#ifndef FCORE_TOOLCHAIN_HL_FUNCTION_DEF_NODE_HPP
#define FCORE_TOOLCHAIN_HL_FUNCTION_DEF_NODE_HPP

#include <string>

#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/hl_definition_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"

namespace fcore{
    class hl_function_def_node : public hl_ast_node{
    public:
        hl_function_def_node();
        void set_return_type(c_types_t ret_val);
        c_types_t get_return_type() {return return_type;};
        void set_name(std::string n);
        void set_parameters_list(std::vector<std::shared_ptr<hl_definition_node>> list);
        std::vector<std::shared_ptr<hl_definition_node>> get_parameters_list() { return parameters_list;};
        void set_body(std::vector<std::shared_ptr<hl_ast_node>> b);
        void set_return(std::shared_ptr<hl_ast_node> r);
        std::string get_name();
        std::shared_ptr<hl_ast_node> get_return();
        bool has_return(){ return return_expression != nullptr;};
        std::vector<std::shared_ptr<hl_ast_node>> get_body();
        std::string pretty_print();
        friend bool operator==(const hl_function_def_node& lhs, const hl_function_def_node& rhs){
            bool ret_val = true;

            ret_val &= lhs.name == rhs.name;
            ret_val &= lhs.return_type == rhs.return_type;

            if(lhs.parameters_list.empty() && rhs.parameters_list.empty()){
                ret_val &= true;
            } else if(lhs.parameters_list.empty() || rhs.parameters_list.empty()){
                ret_val = false;
            } else{
                bool param_equal = true;
                if(lhs.parameters_list.size() != rhs.parameters_list.size()) return false;

                for(uint32_t i = 0; i<lhs.parameters_list.size(); i++){
                    param_equal &= *lhs.parameters_list[i] == *rhs.parameters_list[i];
                }
                ret_val &= param_equal;
            }

            ret_val &= hl_ast_node::compare_vectors(lhs.function_body, rhs.function_body);

            if(lhs.return_expression != nullptr && rhs.return_expression != nullptr){
                ret_val &= *lhs.return_expression == *rhs.return_expression;
            } else if (lhs.return_expression != nullptr || rhs.return_expression != nullptr){
                ret_val &= false;
            }

            return ret_val;
        };

        bool is_terminal() override {
            return false;
        }

        static std::shared_ptr<hl_function_def_node> deep_copy(const std::shared_ptr<hl_function_def_node> &node);

    protected:
        c_types_t return_type;
        std::string name;
        std::vector<std::shared_ptr<hl_definition_node>> parameters_list;
        std::vector<std::shared_ptr<hl_ast_node>> function_body;
        std::shared_ptr<hl_ast_node> return_expression;
    };
}



#endif //FCORE_TOOLCHAIN_HL_FUNCTION_DEF_NODE_HPP
