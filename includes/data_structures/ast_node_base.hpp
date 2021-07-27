// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_AST_NODE_BASE_HPP
#define FCORE_TOOLCHAIN_AST_NODE_BASE_HPP

#include <vector>
#include <memory>

template<class E>
class ast_node_base {
    public:


        // CONTENT MANIPULATION
        void add_content(const std::shared_ptr<E>& element);
        void set_content(const std::vector<std::shared_ptr<E>>& c);
        void prepend_content(const std::vector<std::shared_ptr<E>>& c);
        void append_content(const std::vector<std::shared_ptr<E>>& c);

        // CONTENT ACCESS
        bool has_content();
        std::vector<std::shared_ptr<E>> get_content();


protected:
    std::vector<std::shared_ptr<E>> content;
};




template<class E>
void ast_node_base<E>::add_content(const std::shared_ptr<E> &element) {
    content.push_back(element);
}

template<class E>
std::vector<std::shared_ptr<E>> ast_node_base<E>::get_content() {
    return content;
}

template<class E>
bool ast_node_base<E>::has_content() {
    return !content.empty();
}

template<class E>
void ast_node_base<E>::append_content(const std::vector<std::shared_ptr<E>> &c) {
    content.insert(content.end(), c.begin(), c.end());
}

template<class E>
void ast_node_base<E>::prepend_content(const std::vector<std::shared_ptr<E>> &c) {
    content.insert(content.begin(), c.begin(), c.end());
}

template<class E>
void ast_node_base<E>::set_content(const std::vector<std::shared_ptr<E>> &c) {
    content = c;
}


#endif //FCORE_TOOLCHAIN_AST_NODE_BASE_HPP
