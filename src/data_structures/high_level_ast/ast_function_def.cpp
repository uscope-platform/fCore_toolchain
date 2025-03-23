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

#include "data_structures/high_level_ast/ast_function_def.hpp"

namespace fcore{

    ast_function_def::ast_function_def() : ast_node(hl_ast_node_type_function_def) {
        return_type = c_type_void;
    }

    void ast_function_def::set_parameters_list(std::vector<std::shared_ptr<ast_definition>> list) {
        parameters_list = std::move(list);
    }

    void ast_function_def::set_body(std::vector<std::shared_ptr<ast_node>> b) {
        function_body = std::move(b);
    }

    void ast_function_def::set_return(std::shared_ptr<ast_node> r) {
        return_expression = std::move(r);
    }

    void ast_function_def::set_name(std::string n) {
        name = std::move(n);
    }

    void ast_function_def::set_return_type(c_types_t ret_val) {
        return_type = ret_val;

    }

    std::vector<std::shared_ptr<ast_node>> ast_function_def::get_body() {
        return function_body;
    }

    std::string ast_function_def::pretty_print() {
        std::ostringstream ss;

        ss << variable::type_to_string(return_type) << " " << name << "(";
        if(!parameters_list.empty()){
            for(int i = 0; i<parameters_list.size(); i++){
                ss << parameters_list[i]->pretty_print();
                if(i!=parameters_list.size()-1) ss << ", ";
            }
        }
        ss << ") {" << std::endl;
        if(!function_body.empty()){
            for(const auto& item:function_body){
                ss <<  "    "<<ast_node::pretty_print(item) << std::endl;
            }
        }
        if(return_expression != nullptr) {
            ss << "    return "<< ast_node::pretty_print(return_expression) << std::endl;
        }
        ss << "}";
        std::string ret = ss.str();
        return ret;
    }

    std::shared_ptr<ast_node> ast_function_def::get_return() {
        return return_expression;
    }

    std::string ast_function_def::get_name() {
        return name;
    }

    std::shared_ptr<ast_function_def>
    ast_function_def::deep_copy(const std::shared_ptr<ast_function_def> &orig) {
        std::shared_ptr<ast_function_def> copied_obj = std::make_shared<ast_function_def>();

        copied_obj->set_return_type(orig->get_return_type());
        copied_obj->set_name(orig->get_name());
        std::shared_ptr<ast_node> ret_expr = ast_node::deep_copy(orig->get_return());
        copied_obj->set_return(ret_expr);

        std::vector<std::shared_ptr<ast_definition>> params;
        for(const auto& i:orig->get_parameters_list()){
            params.push_back(std::static_pointer_cast<ast_definition>(ast_node::deep_copy(i)));
        }
        copied_obj->set_parameters_list(params);

        std::vector<std::shared_ptr<ast_node>> body;
        for(const auto& i:orig->get_body()){
            body.push_back(ast_node::deep_copy(i));
        }
        copied_obj->set_body(body);

        return copied_obj;
    }

}
