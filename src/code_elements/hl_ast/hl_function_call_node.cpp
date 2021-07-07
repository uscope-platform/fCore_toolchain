//
// Created by fils on 01/07/2021.
//

#include "code_elements/hl_ast/hl_function_call_node.h"

#include <utility>



hl_function_call_node::hl_function_call_node(std::string n, std::vector<std::shared_ptr<hl_ast_node>> a) : hl_ast_node(hl_ast_node_type_function_call){
    name = std::move(n);
    arguments = std::move(a);
}

std::string hl_function_call_node::pretty_print() {
    std::ostringstream ss;
    ss << name<<"( ";
    if(!arguments.empty()){
        for(const auto& item:arguments){
            if(item->node_type == hl_ast_node_type_expr){
                ss << std::static_pointer_cast<hl_expression_node>(item)->pretty_print();
            } else if(item->node_type == hl_ast_node_type_operand){
                hl_ast_operand op = *std::static_pointer_cast<hl_ast_operand>(item);
                std::string op_s = op;
                ss <<  op_s;
            }
            ss<<", ";
        }
    }
    std::string ret = ss.str();

    ret.pop_back();
    ret.pop_back();
    ret += " )";
    return ret;
}

bool operator==(const hl_function_call_node &lhs, const hl_function_call_node &rhs) {
    bool ret_val = true;

   ret_val &= lhs.name == rhs.name;

    if(lhs.arguments.empty() && rhs.arguments.empty()){
        ret_val &= true;
    } else if(lhs.arguments.empty() || rhs.arguments.empty()){
        ret_val = false;
    } else{
        bool args_equal = true;
        args_equal &= lhs.arguments.size() == rhs.arguments.size();
        for(int i = 0; i<lhs.arguments.size(); i++){
            args_equal &= *lhs.arguments[i] == *rhs.arguments[i];
            if(lhs.node_type != rhs.node_type) {
                ret_val = false;
            } else if(lhs.arguments[i]->node_type == hl_ast_node_type_expr){
                ret_val &= *std::static_pointer_cast<hl_expression_node>(lhs.arguments[i]) == *std::static_pointer_cast<hl_expression_node>(rhs.arguments[i]);
            } else if(lhs.arguments[i]->node_type == hl_ast_node_type_operand){
                ret_val &= *std::static_pointer_cast<hl_ast_operand>(lhs.arguments[i]) == *std::static_pointer_cast<hl_ast_operand>(rhs.arguments[i]);
            }
        }
        ret_val &= args_equal;
    }

    return ret_val;
}

void hl_function_call_node::set_body(std::vector<std::shared_ptr<hl_ast_node>> i) {
    function_body = std::move(i);
}

void hl_function_call_node::set_return(std::shared_ptr<hl_ast_node> r) {
    function_return = std::move(r);
}
