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
// limitations under the License.01/07/2021.
//

#include "data_structures/high_level_ast/ast_definition.hpp"
#include "data_structures/high_level_ast/ast_struct.hpp"
#include <utility>

namespace fcore {

    ast_definition::ast_definition(std::string n, c_types_t ct, std::shared_ptr<variable> v) : ast_node(hl_ast_node_type_definition) {
        name = std::move(n);
        type = ct;
        constant = false;
        inner_variable = std::move(v);
    }

    ast_definition::ast_definition(std::string n, std::shared_ptr<ast_struct> s): ast_node(hl_ast_node_type_definition) {
        name = std::move(n);
        type = c_type_struct;
        constant = false;
        struct_specs = std::move(s);
        inner_variable = std::make_shared<variable>(n);
    }

    bool ast_definition::is_initialized() const {
        return !initializer.empty();
    }

    void ast_definition::set_scalar_initializer(const std::shared_ptr<ast_node>& init) {
        initializer.clear();
        initializer.push_back(init);

    }

    void ast_definition::set_constant(bool c) {
        constant = c;
    }

    bool ast_definition::is_constant() const {
        return constant;
    }

    std::shared_ptr<ast_node> ast_definition::get_scalar_initializer() {
        return initializer[0];
    }

    void ast_definition::set_scalar_initializer(const std::shared_ptr<ast_node> &init, uint32_t idx) {
        if(initializer.size()<idx) throw std::runtime_error("Error: Attempt to set undefined initializer");
        initializer[idx] = init;
    }

    std::string ast_definition::pretty_print() {


        std::ostringstream ss;
        if(constant) ss << "const ";
        ss << variable::type_to_string(type);
        if(struct_specs != nullptr) ss << " " << struct_specs->get_name();
        ss << " " << name;

        if(!initializer.empty()){
            ss << " = ";
            if(is_scalar()){
                ss << ast_node::pretty_print(initializer[0]);
            } else {
                ss << "{";
                for(int i = 0; i< initializer.size(); i++){
                    ss << ast_node::pretty_print(initializer[i]);
                    if(i != initializer.size()-1) ss << ", ";
                }
                ss << "}";
            }


        }


        std::string ret = ss.str();
        return ret;

    }

    void ast_definition::set_name(std::string n) {
        name = std::move(n);
    }

    bool ast_definition::is_scalar() {
        return inner_variable->get_type() != var_type_array;
    }

    std::shared_ptr<ast_definition> ast_definition::deep_copy(const std::shared_ptr<ast_definition> &orig) {
        std::shared_ptr<ast_definition> copied_obj;
        if(orig->struct_specs != nullptr) {
            auto new_struct =  std::static_pointer_cast<ast_struct>(ast_node::deep_copy(orig->struct_specs));
            copied_obj = std::make_shared<ast_definition>(orig->get_name(), new_struct);

            if(orig->inner_variable != nullptr) {
                copied_obj->set_variable(variable::deep_copy(orig->get_variable()));
            }
        } else {
            std::shared_ptr<variable> new_var = variable::deep_copy(orig->get_variable());
            copied_obj = std::make_shared<ast_definition>(orig->get_name(), orig->get_type(), new_var);

        }
        copied_obj->set_constant(orig->is_constant());
        if(orig->is_initialized()){
            std::vector<std::shared_ptr<ast_node>> old_initializer = orig->get_array_initializer();
            std::vector<std::shared_ptr<ast_node>> new_initializer;
            for(auto &item:old_initializer){
                new_initializer.push_back(ast_node::deep_copy(item));
            }
            copied_obj->set_array_initializer(new_initializer);
        }


        std::vector<std::shared_ptr<ast_node>> index;
        for(const auto& i:orig->get_array_index()){
            index.push_back(ast_node::deep_copy(i));
        }
        copied_obj->set_array_index(index);

        std::vector<int> shape = orig->get_array_shape();
        copied_obj->set_array_shape(shape);

        return copied_obj;
    }

}
