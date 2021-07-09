//
// Created by fils on 30/06/2021.
//

#ifndef FCORE_HAS_AST_NODE_BASE_H
#define FCORE_HAS_AST_NODE_BASE_H

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


#endif //FCORE_HAS_AST_NODE_BASE_H
