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
// limitations under the License.


#include "passes/high_level/optimizations/visitor_passes/destructuring_pass.hpp"


namespace fcore {

    destructuring_pass::destructuring_pass() : pass_base("destructuring pass"){

    }

    std::shared_ptr<hl_code_block> destructuring_pass::process_global(
        std::shared_ptr<hl_code_block> element,
        const std::vector<std::shared_ptr<hl_definition_node>> &globals
    ) {

        for(const auto& g : globals){
            if(g->is_struct()) struct_definitions[g->get_name()] = g->get_struct_specs();
        }

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_definition = [this](auto && arg) { return process_definition(std::forward<decltype(arg)>(arg));};
        ops.visit_operand    = [this](auto && arg) { return process_operand(std::forward<decltype(arg)>(arg));};
        visitor.visit(ops, element);

        hl_acting_visitor_operations ops2;
        return  visitor.visit(ops2, element);
    }

    std::vector<std::shared_ptr<hl_ast_node>> destructuring_pass::process_definition(
        const std::shared_ptr<hl_definition_node> &def) {
        if(def->is_struct()) {
            auto name = def->get_name();
            auto inst = def->get_struct_specs();
            inst->set_definitions(struct_definitions[inst->get_name()]->get_definitions());
            struct_instances.insert({name, inst});
        }
        return {def};
    }


    std::shared_ptr<hl_ast_node> destructuring_pass::process_operand(std::shared_ptr<hl_ast_operand> op) {
        auto var = op->get_variable();

        if(var->get_struct_accessors().empty()) return {op};
        if(var->get_struct_accessors().size() > 1) {
            throw std::runtime_error("Nested structs are not supported yet: "+ op->get_name());
        }
        if(!struct_instances.contains(op->get_name())) throw std::runtime_error("Encountered an undefined struct: "+ op->get_name());
        auto defs = struct_instances[op->get_name()]->get_definitions();
        auto inits = struct_instances[op->get_name()]->get_initializers();

        for(int i = 0; i< defs.size(); i++) {
            if(defs[i]->get_name() == op->get_variable()->get_struct_accessors()[0]) {
                op->set_variable(std::static_pointer_cast<hl_ast_operand>(inits[i])->get_variable());
                return {op};
            }
        }
        throw std::runtime_error("Encountered an undefined field ("+ op->get_variable()->get_struct_accessors()[0] + ") in struct: "+ op->get_name());
    }
}
