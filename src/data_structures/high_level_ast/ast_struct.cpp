

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

#include "data_structures/high_level_ast/ast_struct.hpp"
#include "data_structures/high_level_ast/ast_definition.hpp"

namespace fcore {

    ast_struct::ast_struct(const std::string &n) : ast_node(hl_ast_node_type_struct) {
        name = n;
    }

    bool ast_struct::is_initialized() const {
        bool ret_val = false;
        if(definitions.empty()) return true;
        for(auto &def: definitions) {
            ret_val |= def->is_initialized();
        }
        return ret_val;
    }

    std::shared_ptr<ast_struct> ast_struct::deep_copy(const std::shared_ptr<ast_struct> &node) {
        auto ret_val = std::make_shared<ast_struct>(node->name);
        for(auto &def: node->definitions) {
            auto new_node = std::static_pointer_cast<ast_definition>(ast_node::deep_copy(def));
            ret_val->add_definition(new_node);
        }
        std::vector<std::shared_ptr<ast_node>> new_initializers;
        for(auto &init: node->initializers) {
            new_initializers.push_back(ast_node::deep_copy(init));
        }
        ret_val->add_initializers(new_initializers);
        return ret_val;
    }


    std::string ast_struct::pretty_print() {
        std::stringstream ss;
        ss << "struct " + name + " {\n";
        for(const auto &def: definitions) {
            ss << "    "<< def->pretty_print() << ";\n";
        }
        ss << "};\n";
        return ss.str();
    }

    bool operator==(const ast_struct &lhs, const ast_struct &rhs) {
        bool ret_val = true;

        if(lhs.definitions.size() != rhs.definitions.size()) return false;

        for(uint32_t i = 0; i<lhs.definitions.size(); i++){
            ret_val &= *lhs.definitions[i] == *rhs.definitions[i];
        }

        if(lhs.initializers.size() != rhs.initializers.size()) return false;
        for(uint32_t i = 0; i<lhs.initializers.size(); i++){
            if((lhs.initializers[i] == nullptr) != (rhs.initializers[i] == nullptr)) return false;
            ret_val &= *lhs.initializers[i] == *rhs.initializers[i];
        }

        ret_val &= lhs.name == rhs.name;

        return ret_val;
    }

}