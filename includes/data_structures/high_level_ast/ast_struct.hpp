

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

#ifndef AST_STRUCT_HPP
#define AST_STRUCT_HPP

#include "ast_node.hpp"


namespace fcore {
    class ast_definition;

    class ast_struct : public ast_node {
        public:
            explicit ast_struct(const std::string &name);

            void add_definition(const std::shared_ptr<ast_definition> &d){definitions.push_back(d);}
            void set_definitions(const std::vector<std::shared_ptr<ast_definition>> &defs){definitions = defs;}
            std::vector<std::shared_ptr<ast_definition>> get_definitions() {return definitions;};

            void add_initializers(const std::vector<std::shared_ptr<ast_node>> &i) {initializers = i;}
            std::vector<std::shared_ptr<ast_node>> get_initializers() {return initializers;}
            std::string get_name() {return name;}

            std::string pretty_print();
            bool is_initialized() const;

            friend bool operator==(const ast_struct &lhs, const ast_struct &rhs);

            static std::shared_ptr<ast_struct> deep_copy(const std::shared_ptr<ast_struct> &node);


        private:
            std::string name;
            std::vector<std::shared_ptr<ast_definition>> definitions;
            std::vector<std::shared_ptr<ast_node>> initializers;
    };
}



#endif //AST_STRUCT_HPP
