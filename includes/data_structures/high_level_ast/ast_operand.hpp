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

#ifndef FCORE_TOOLCHAIN_AST_OPERAND_HPP
#define FCORE_TOOLCHAIN_AST_OPERAND_HPP

#include "ast_node.hpp"
#include "data_structures/common/variable.hpp"
#include <nlohmann/json.hpp>

#include <string>

namespace fcore{

    class ast_operand : public ast_node{
    public:
        explicit ast_operand(std::shared_ptr<variable> iv);
        // VARIABLE NAME
        void set_name(const std::string &name)  {inner_variable->set_name(name);}
        std::string get_name() { return inner_variable->get_name();}
        std::string get_identifier() { return inner_variable->get_identifier();}

        // INTEGER IMMEDIATE VALUE
        void set_immediate(const int &v) {inner_variable->set_immediate(v);}
        [[nodiscard]] int get_int_value() const {return inner_variable->get_int_value();}
        // FLOAT IMMEDIATE VALUE
        void set_immediate(const float &v) {inner_variable->set_immediate(v);}
        [[nodiscard]] float get_float_val() const {return inner_variable->get_float_val();}

        // TYPE
        variable_type_t get_type(){return inner_variable->get_type();}
        void set_type(variable_type_t type) {inner_variable->set_type(type);}
        // ARRAY INDEX
        std::vector<std::shared_ptr<ast_node>> get_array_index(){return array_index;}
        void set_array_index(std::vector<std::shared_ptr<ast_node>> idx){array_index = std::move(idx);}

        // ARRAY CONTIGUITY
        void set_contiguity(bool c) { inner_variable->set_contiguity(c);}
        bool get_contiguity() {return inner_variable->is_contiguous();}

        //INNER VARIABLE
        void set_variable(std::shared_ptr<variable> v) {inner_variable = std::move(v);}
        std::shared_ptr<variable> get_variable() {return inner_variable;}


        bool is_scalar() {return  inner_variable->get_type()!=var_type_array;}
        bool is_constant() {return inner_variable->is_constant();}

        std::string pretty_print();
        operator std::string(){return pretty_print();}

        friend bool operator==(const ast_operand& lhs, const ast_operand& rhs){
            bool ret_val = true;
            ret_val &= lhs.node_type == rhs.node_type;

            if(lhs.inner_variable == nullptr && rhs.inner_variable == nullptr) ret_val &= true;
            else if (lhs.inner_variable == nullptr || rhs.inner_variable == nullptr) ret_val &= false;
            else ret_val &= *lhs.inner_variable == *rhs.inner_variable;

            ret_val &= compare_vectors(lhs.array_index, rhs.array_index);

            return ret_val;
        };

        static std::shared_ptr<ast_operand> deep_copy(const std::shared_ptr<ast_operand> &node);

    private:

        std::vector<std::shared_ptr<ast_node>> array_index;
        std::shared_ptr<variable> inner_variable;
    };
}


#endif //FCORE_TOOLCHAIN_AST_OPERAND_HPP
