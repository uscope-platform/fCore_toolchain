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
// limitations under the License.08/07/2021.
//

#include "passes/high_level/optimizations/inlined_function_elimination.hpp"

namespace fcore{

    inlined_function_elimination::inlined_function_elimination(std::string entry_point_name) : pass_base("inlined function elimination pass") {
        entry_point = std::move(entry_point_name);
    }

    std::shared_ptr<hl_code_block> inlined_function_elimination::process_global(std::shared_ptr<hl_code_block> element) {

        hl_ast_visitor_operations ops;
        hl_ast_visitor visitor;

        ops.visit_function_def = [this](auto && arg) { return process_function_definition(std::forward<decltype(arg)>(arg));};

        return visitor.visit(ops, element);
    }

    std::vector<std::shared_ptr<hl_ast_node>>
    inlined_function_elimination::process_function_definition(std::shared_ptr<hl_function_def_node> element) {
        std::vector<std::shared_ptr<hl_ast_node>> new_content;
        if(element->get_name() == entry_point){
            std::vector<std::shared_ptr<hl_ast_node>> main_body = element->get_body();
            new_content.insert(new_content.end(), main_body.begin(), main_body.end());
        }
        return new_content;
    }
}


