//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_function_def_node.h"

#include <utility>

hl_function_def_node::hl_function_def_node() : hl_ast_node(hl_ast_node_type_function_def) {
    return_type = c_type_void;
}

void hl_function_def_node::set_parameters_list(std::vector<std::shared_ptr<hl_definition_node>> list) {
    parameters_list = std::move(list);
}

void hl_function_def_node::set_body(std::vector<std::shared_ptr<hl_ast_node>> b) {
    function_body = std::move(b);
}

void hl_function_def_node::set_return(std::shared_ptr<hl_expression_node> r) {
    return_expression = std::move(r);
}

void hl_function_def_node::set_name(std::string &n) {
    name = n;
}

void hl_function_def_node::set_type(c_types_t ret_val) {
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

bool operator==(const hl_function_def_node &lhs, const hl_function_def_node &rhs) {
    bool ret_val = true;

    ret_val &= lhs.name == rhs.name;
    ret_val &= lhs.return_type == rhs.return_type;

    if(lhs.parameters_list.empty() && rhs.parameters_list.empty()){
        ret_val &= true;
    } else if(lhs.parameters_list.empty() || rhs.parameters_list.empty()){
        ret_val = false;
    } else{
        bool param_equal = true;
        param_equal &= lhs.parameters_list.size() == rhs.parameters_list.size();
        for(int i = 0; i<lhs.parameters_list.size(); i++){
            param_equal &= *lhs.parameters_list[i] == *rhs.parameters_list[i];
        }
        ret_val &= param_equal;
    }

    if(lhs.function_body.empty() && rhs.function_body.empty()){
        ret_val &= true;
    } else if(lhs.function_body.empty() || rhs.function_body.empty()){
        ret_val = false;
    } else{
        bool body_equal = true;
        body_equal &= lhs.function_body.size() == rhs.function_body.size();

        for(int i = 0; i<lhs.function_body.size(); i++){
            body_equal &= *lhs.function_body[i] == *rhs.function_body[i];
        }
        ret_val &= body_equal;
    }

    if(lhs.return_expression != nullptr && rhs.return_expression != nullptr){
        ret_val &= *lhs.return_expression == *rhs.return_expression;
    } else if (lhs.return_expression != nullptr || rhs.return_expression != nullptr){
        ret_val &= false;
    }

    return ret_val;
}
