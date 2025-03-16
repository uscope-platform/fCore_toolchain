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

#ifndef FCORE_TOOLCHAIN_HL_DEFINITION_NODE_HPP
#define FCORE_TOOLCHAIN_HL_DEFINITION_NODE_HPP

#include "data_structures/high_level_ast/hl_ast_node.hpp"
#include "data_structures/high_level_ast/hl_expression_node.hpp"
#include "data_structures/high_level_ast/hl_ast_struct.hpp"
#include "data_structures/common/variable.hpp"

#include <utility>
#include <string>



namespace fcore{


    class hl_definition_node : public hl_ast_node{
    public:
        hl_definition_node(std::string n, c_types_t ct, std::shared_ptr<variable> v);
        hl_definition_node(std::string n, std::shared_ptr<hl_ast_struct> s);
        void set_name(std::string name);
        std::string get_name(){ return name;};
        c_types_t get_type(){ return type;};

        bool is_initialized() const;
        bool is_scalar();
        void set_constant(bool c);
        bool is_constant() const;
        bool is_struct();

        std::vector<std::shared_ptr<hl_ast_node>> get_array_index() {return array_index;};
        void set_array_index(std::vector<std::shared_ptr<hl_ast_node>> i) {array_index = std::move(i);};

        std::shared_ptr<hl_ast_node> get_scalar_initializer();
        void set_scalar_initializer(const std::shared_ptr<hl_ast_node>& init);
        void set_scalar_initializer(const std::shared_ptr<hl_ast_node>& init, uint32_t idx);

        std::vector<std::shared_ptr<hl_ast_node>> get_array_initializer() {return initializer;};
        void set_array_initializer(const std::vector<std::shared_ptr<hl_ast_node>> &init) {initializer = init;};

        std::shared_ptr<variable> get_variable() {return inner_variable;};
        void set_variable(std::shared_ptr<variable> var) {inner_variable = std::move(var);};

        void set_array_shape(std::vector<int> &shape){inner_variable->set_array_shape(shape);};
        std::vector<int> get_array_shape(){return inner_variable->get_array_shape();};


        std::string pretty_print();

        friend bool operator==(const hl_definition_node& lhs, const hl_definition_node& rhs){
            bool ret_val = true;

            ret_val &= lhs.constant == rhs.constant;
            ret_val &= lhs.type == rhs.type;
            ret_val &= lhs.name == rhs.name;


            ret_val &= compare_vectors(lhs.array_index, rhs.array_index);
            ret_val &= compare_vectors(lhs.initializer, rhs.initializer);

            if(lhs.inner_variable == nullptr && rhs.inner_variable == nullptr) ret_val &= true;
            else if (lhs.inner_variable == nullptr || rhs.inner_variable == nullptr) ret_val &= false;
            else ret_val &= *lhs.inner_variable == *rhs.inner_variable;

            if(lhs.struct_specs == nullptr && rhs.struct_specs == nullptr) ret_val &= true;
            else if (lhs.struct_specs == nullptr || rhs.struct_specs == nullptr) ret_val &= false;
            else ret_val &= *lhs.struct_specs == *rhs.struct_specs;

            return ret_val;
        };

        static std::shared_ptr<hl_definition_node> deep_copy(const std::shared_ptr<hl_definition_node> &node);


    protected:
        bool constant;
        std::string name;
        c_types_t type;
        std::shared_ptr<hl_ast_struct> struct_specs;
        std::vector<std::shared_ptr<hl_ast_node>> initializer;
        std::vector<std::shared_ptr<hl_ast_node>> array_index;
        std::shared_ptr<variable> inner_variable;

    };
}



#endif //FCORE_TOOLCHAIN_HL_DEFINITION_NODE_HPP
