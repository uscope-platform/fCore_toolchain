//
// Created by fils on 01/05/20.
//

#ifndef FCORE_HAS_PASS_MANAGER_HPP
#define FCORE_HAS_PASS_MANAGER_HPP

#include <memory>
#include <vector>
#include "../code_elements/code_element.hpp"

#define NONE_PASS 0
#define NODE_PASS 1
#define LEAF_PASS 2

class pass_base {
public:

    virtual std::vector<std::shared_ptr<code_element>>process_element(std::shared_ptr<code_element> element){
        std::vector<std::shared_ptr<code_element>> elem;
        elem.push_back(element);
        return elem;
    };
    virtual std::vector<std::shared_ptr<code_element>>process_node(std::shared_ptr<code_element> element){
        std::vector<std::shared_ptr<code_element>> elem;
        elem.push_back(element);
        return elem;
    };
    virtual std::shared_ptr<code_element> process_leaf(std::shared_ptr<code_element> element){
        return element;
    };
    virtual int get_pass_type() { return NONE_PASS;};
};

class pass_manager {
public:
    void add_pass(const std::shared_ptr<pass_base>& pass);
    std::shared_ptr<code_element> run_passes(std::shared_ptr<code_element> AST);
    std::vector<std::shared_ptr<code_element>> process_nodes(const std::shared_ptr<code_element> &subtree, const std::shared_ptr<pass_base>& pass);
    std::shared_ptr<code_element> process_leaves(const std::shared_ptr<code_element> &subtree, const std::shared_ptr<pass_base>& pass);
private:
    std::vector<std::shared_ptr<pass_base>> passes = {};
};


#endif //FCORE_HAS_PASS_MANAGER_HPP
