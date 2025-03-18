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

    std::shared_ptr<hl_code_block> destructuring_pass::process_global(std::shared_ptr<hl_code_block> element, const std::vector<std::shared_ptr<hl_definition_node>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_definition = [this](auto && arg) { return process_definition(std::forward<decltype(arg)>(arg));};
        visitor.visit(ops, element);

        hl_acting_visitor_operations ops2;
        return  visitor.visit(ops2, element);
    }

    std::vector<std::shared_ptr<hl_ast_node>> destructuring_pass::process_definition(
        std::shared_ptr<hl_definition_node> exp) {
        return {exp};
    }
}
