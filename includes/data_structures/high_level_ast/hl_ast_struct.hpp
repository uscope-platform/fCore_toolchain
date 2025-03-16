

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

#ifndef HL_AST_STRUCT_HPP
#define HL_AST_STRUCT_HPP

#include "hl_ast_node.hpp"


namespace fcore {
    class hl_definition_node;

    class hl_ast_struct : public hl_ast_node {
        public:
            explicit hl_ast_struct(const std::string &name);

            void add_definition(const std::shared_ptr<hl_definition_node> &d){definitions.push_back(d);}
            std::vector<std::shared_ptr<hl_definition_node>> get_definitions() {return definitions;};
            std::string get_name() {return name;};

            std::string pretty_print();
            bool is_initialized() const;

            friend bool operator==(const hl_ast_struct &lhs, const hl_ast_struct &rhs);

            static std::shared_ptr<hl_ast_struct> deep_copy(const std::shared_ptr<hl_ast_struct> &node);


        private:
            std::string name;
            std::vector<std::shared_ptr<hl_definition_node>> definitions;

    };
}



#endif //HL_AST_STRUCT_HPP
