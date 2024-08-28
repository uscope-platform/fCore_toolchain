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

#include "data_structures/high_level_ast/hl_definition_node.hpp"

namespace fcore {

    hl_definition_node::hl_definition_node(std::string n, c_types_t ct, std::shared_ptr<variable> v) : hl_ast_node(hl_ast_node_type_definition) {
        name = std::move(n);
        type = ct;
        constant = false;
        inner_variable = std::move(v);
    }

    bool hl_definition_node::is_initialized() {
        return !initializer.empty();
    }

    void hl_definition_node::set_scalar_initializer(const std::shared_ptr<hl_ast_node>& init) {
        initializer.clear();
        initializer.push_back(init);

    }

    void hl_definition_node::set_constant(bool c) {
        constant = c;
    }

    bool hl_definition_node::is_constant() const {
        return constant;
    }

    std::shared_ptr<hl_ast_node> hl_definition_node::get_scalar_initializer() {
        return initializer[0];
    }

    void hl_definition_node::set_scalar_initializer(const std::shared_ptr<hl_ast_node> &init, uint32_t idx) {
        if(initializer.size()<idx) throw std::runtime_error("Error: Attempt to set undefined initializer");
        initializer[idx] = init;
    }

    std::string hl_definition_node::pretty_print() {


        std::ostringstream ss;
        if(constant) ss << "const ";
        ss << hl_ast_node::type_to_string(type) << " " << name;

        if(!initializer.empty()){
            ss << " = ";
            if(is_scalar()){
                if(initializer[0]->node_type == hl_ast_node_type_function_call){
                    ss << std::static_pointer_cast<hl_function_call_node>(initializer[0])->pretty_print();
                } else{
                    ss << std::static_pointer_cast<hl_expression_node>(initializer[0])->pretty_print();
                }
            } else {
                ss << "{";
                for(int i = 0; i< initializer.size(); i++){
                    if(initializer[i]->node_type == hl_ast_node_type_function_call){
                        ss << std::static_pointer_cast<hl_function_call_node>(initializer[i])->pretty_print();
                    } else{
                        ss << std::static_pointer_cast<hl_expression_node>(initializer[i])->pretty_print();
                    }
                    if(i != initializer.size()-1) ss << ", ";
                }
                ss << "}";
            }


        }


        std::string ret = ss.str();
        return ret;

    }

    void hl_definition_node::set_name(std::string n) {
        name = std::move(n);
    }

    bool hl_definition_node::is_scalar() {
        return inner_variable->get_type() != var_type_array;
    }

    std::shared_ptr<hl_definition_node> hl_definition_node::deep_copy(const std::shared_ptr<hl_definition_node> &orig) {
        std::shared_ptr<variable> new_var = variable::deep_copy(orig->get_variable());
        std::shared_ptr<hl_definition_node> copied_obj = std::make_shared<hl_definition_node>(orig->get_name(), orig->get_type(), new_var);
        copied_obj->set_constant(orig->is_constant());
        if(orig->is_initialized()){
            std::vector<std::shared_ptr<hl_ast_node>> old_initializer = orig->get_array_initializer();
            std::vector<std::shared_ptr<hl_ast_node>> new_initializer;
            for(auto &item:old_initializer){
                new_initializer.push_back(hl_ast_node::deep_copy(item));
            }
            copied_obj->set_array_initializer(new_initializer);
        }


        std::vector<std::shared_ptr<hl_ast_node>> index;
        for(const auto& i:orig->get_array_index()){
            index.push_back(hl_ast_node::deep_copy(i));
        }
        copied_obj->set_array_index(index);

        std::vector<int> shape = orig->get_array_shape();
        copied_obj->set_array_shape(shape);

        return copied_obj;
    }

}