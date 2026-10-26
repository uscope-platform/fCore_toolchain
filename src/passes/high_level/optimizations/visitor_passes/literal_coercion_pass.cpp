

//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and

#include "passes/high_level/optimizations/visitor_passes/literal_coercion_pass.hpp"

namespace fcore {

    literal_coercion_pass::literal_coercion_pass() : pass_base("literal coercion") {
    }

    pass_result literal_coercion_pass::process_global(std::shared_ptr<ast_code_block> element, const std::vector<std::shared_ptr<ast_definition>> &globals) {
        scope.clear();
        global_scope.clear();
        signatures.clear();

        for(const auto &g: globals) global_scope[g->get_name()] = g->get_type();
        for(const auto &node: element->get_content()) {
            if(node->node_type != hl_ast_node_type_function_def) continue;
            auto f = std::static_pointer_cast<ast_function_def>(node);
            std::vector<c_types_t> params;
            for(const auto &p: f->get_parameters_list()) params.push_back(p->get_type());
            signatures[f->get_name()] = params;
        }
        scope = global_scope;

        hl_acting_visitor raw_visitor;
        hl_acting_visitor_operations raw_ops;
        raw_ops.post.visit_function_call = [this](const auto &call) { return resolve_raw(call); };
        raw_ops.should_stop = stop_condition();
        auto resolved = raw_visitor.visit(raw_ops, element);
        if(!resolved || failed()) return finish(resolved);
        element = resolved.value();

        hl_observing_visitor visitor;
        hl_observing_visitor_operations ops;
        ops.pre.visit_definition = [this](const auto &def) { process_definition(def); };
        ops.pre.visit_function_def = [this](const auto &def) { process_function_def(def); };
        ops.pre.visit_expression = [this](const auto &exp) { process_expression(exp); };
        ops.pre.visit_function_call = [this](const auto &call) { process_call(call); };
        ops.should_stop = stop_condition();

        auto visited = visitor.visit(ops, element);
        return finish(visited, element);
    }

    std::vector<std::shared_ptr<ast_node>> literal_coercion_pass::resolve_raw(const std::shared_ptr<ast_call> &call) {
        if(call->get_name() != "raw") return {call};

        auto args = call->get_arguments();
        if(args.size() != 1 || args[0]->node_type != hl_ast_node_type_operand ||
           std::static_pointer_cast<ast_operand>(args[0])->get_type() != var_type_int_const) {
            report(error(error_code::type_error, "raw() takes exactly one integer literal"));
            return {call};
        }

        auto literal = std::static_pointer_cast<ast_operand>(args[0]);
        literal->get_variable()->set_raw_bits(true);
        return {literal};
    }

    void literal_coercion_pass::process_definition(const std::shared_ptr<ast_definition> &def) {
        scope[def->get_name()] = def->get_type();
        if(def->get_type() != c_type_float) return;

        auto initializer = def->get_array_initializer();
        for(auto &item: initializer) {
            if(is_int_literal(item)) item = to_float(item);
        }
        def->set_array_initializer(initializer);
    }

    void literal_coercion_pass::process_function_def(const std::shared_ptr<ast_function_def> &def) {
        scope = global_scope;
        for(const auto &p: def->get_parameters_list()) scope[p->get_name()] = p->get_type();

        if(def->get_return_type() == c_type_float && def->has_return() && is_int_literal(def->get_return())) {
            def->set_return(to_float(def->get_return()));
        }
    }

    void literal_coercion_pass::process_expression(const std::shared_ptr<ast_expression> &exp) {
        if(exp->is_unary() || exp->is_ternary() || !exp->get_lhs().has_value()) return;

        switch(exp->get_type()) {
            case ast_expression::ASSIGN:
            case ast_expression::ADD:
            case ast_expression::SUB:
            case ast_expression::MULT:
            case ast_expression::DIV:
            case ast_expression::EQ:
            case ast_expression::NEQ:
            case ast_expression::LT:
            case ast_expression::GT:
            case ast_expression::LTE:
            case ast_expression::GTE:
            case ast_expression::SATP:
            case ast_expression::SATN:
                break;
            default:
                return;
        }

        auto lhs = exp->get_lhs().value();
        auto rhs = exp->get_rhs();
        if(is_int_literal(rhs) && is_float(lhs)) exp->set_rhs(to_float(rhs));
        else if(is_int_literal(lhs) && is_float(rhs) && exp->get_type() != ast_expression::ASSIGN) exp->set_lhs(to_float(lhs));
    }

    void literal_coercion_pass::process_call(const std::shared_ptr<ast_call> &call) {
        auto sig = signatures.find(call->get_name());
        if(sig == signatures.end()) return;

        auto args = call->get_arguments();
        for(size_t i = 0; i < args.size() && i < sig->second.size(); i++) {
            if(sig->second[i] == c_type_float && is_int_literal(args[i])) args[i] = to_float(args[i]);
        }
        call->set_arguments(args);
    }

    bool literal_coercion_pass::is_int_literal(const std::shared_ptr<ast_node> &node) {
        if(node == nullptr || node->node_type != hl_ast_node_type_operand) return false;
        auto op = std::static_pointer_cast<ast_operand>(node);
        return op->get_type() == var_type_int_const && !op->get_variable()->is_raw_bits();
    }

    bool literal_coercion_pass::is_float(const std::shared_ptr<ast_node> &node) {
        if(node == nullptr || node->node_type != hl_ast_node_type_operand) return false;
        auto op = std::static_pointer_cast<ast_operand>(node);
        if(op->get_type() == var_type_float_const) return true;
        if(op->is_constant()) return false;
        auto it = scope.find(op->get_name());
        return it != scope.end() && it->second == c_type_float;
    }

    std::shared_ptr<ast_node> literal_coercion_pass::to_float(const std::shared_ptr<ast_node> &node) {
        auto op = std::static_pointer_cast<ast_operand>(node);
        auto var = std::make_shared<variable>("constant", static_cast<float>(op->get_int_value()));
        return std::make_shared<ast_operand>(var);
    }

}
