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

#include "data_structures/high_level_ast/hl_function_def_node.hpp"

namespace fcore{

    hl_function_def_node::hl_function_def_node() : hl_ast_node(hl_ast_node_type_function_def) {
        return_type = c_type_void;
    }

    void hl_function_def_node::set_parameters_list(std::vector<std::shared_ptr<hl_definition_node>> list) {
        parameters_list = std::move(list);
    }

    void hl_function_def_node::set_body(std::vector<std::shared_ptr<hl_ast_node>> b) {
        function_body = std::move(b);
    }

    void hl_function_def_node::set_return(std::shared_ptr<hl_ast_node> r) {
        return_expression = std::move(r);
    }

    void hl_function_def_node::set_name(std::string n) {
        name = std::move(n);
    }

    void hl_function_def_node::set_return_type(c_types_t ret_val) {
        return_type = ret_val;

    }

    std::vector<std::shared_ptr<hl_ast_node>> hl_function_def_node::get_body() {
        return function_body;
    }

    std::string hl_function_def_node::pretty_print() {
        std::ostringstream ss;

        ss << hl_ast_node::type_to_string(return_type) << " " << name << "(";
        if(!parameters_list.empty()){
            for(const auto& item: parameters_list){
                ss<< item->pretty_print() << ", ";
            }
        }
        ss << ") {" << std::endl;
        if(!function_body.empty()){
            for(const auto& item:function_body){
                if(item->node_type == hl_ast_node_type_expr){
                    ss << std::static_pointer_cast<hl_expression_node>(item)->pretty_print() << std::endl;
                } else if(item->node_type == hl_ast_node_type_definition){
                    ss << std::static_pointer_cast<hl_definition_node>(item)->pretty_print() << std::endl;
                }
            }
        }
        ss << "}";
        std::string ret = ss.str();
        return ret;
    }

    std::shared_ptr<hl_ast_node> hl_function_def_node::get_return() {
        return return_expression;
    }

    std::string hl_function_def_node::get_name() {
        return name;
    }

    nlohmann::json hl_function_def_node::dump() {
        nlohmann::json retval = hl_ast_node::dump();

        std::vector<nlohmann::json> parameters_list_dump;
        for(auto &i:parameters_list){
            parameters_list_dump.push_back(i->dump());
        }

        retval["name"] = name;
        retval["function_body"] = hl_ast_node::dump_array(function_body);
        if(return_expression != nullptr){
            retval["return_expression"] = return_expression->dump();
        }
        retval["return_type"] = c_types_to_string(return_type);
        retval["parameters_list"] = parameters_list_dump;

        return retval;
    }
}
