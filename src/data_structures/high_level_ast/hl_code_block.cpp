

//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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

#include "data_structures/high_level_ast/hl_code_block.hpp"

namespace fcore{

    hl_code_block::hl_code_block() : hl_ast_node(hl_ast_node_type_code_block){

    }

    std::shared_ptr<hl_code_block> hl_code_block::deep_copy(const std::shared_ptr<hl_code_block> &node) {
        std::shared_ptr<hl_code_block> copied_obj = std::make_shared<hl_code_block>();

        std::vector<std::shared_ptr<hl_ast_node>> args;
        for(const auto &i :node->get_content()){
            args.push_back(hl_ast_node::deep_copy(i));
        }

        copied_obj->set_content(args);
        return copied_obj;
    }
}

