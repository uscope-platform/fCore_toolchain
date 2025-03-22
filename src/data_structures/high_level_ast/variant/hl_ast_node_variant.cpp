

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

#include "data_structures/high_level_ast/variant/hl_ast_node_variant.hpp"

namespace fcore{

    bool hl_ast_node_variant::is_terminal() {
        return false;
    }


    void hl_ast_node_variant::add_child(const hl_ast_node_variant &element) {
        children.push_back(element);
    }

    void hl_ast_node_variant::set_children(const std::vector<hl_ast_node_variant> &c) {
        children = c;
    }

    std::vector<hl_ast_node_variant> hl_ast_node_variant::get_children() {
        return children;
    }

    std::string hl_ast_node_variant::pretty_print() {
        std::ostringstream ss;

        for(auto &item:children){
            auto str =  std::visit([](auto &var) -> nlohmann::json {
                return var.pretty_print();
            }, item.content);
            ss << str << std::endl;
        }
        return ss.str();
    }
}
