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
#define ANALYSIS_PASS 3

class pass_base {
public:
    virtual std::vector<std::shared_ptr<code_element>>process_node(std::shared_ptr<code_element> element) = 0;
    virtual std::shared_ptr<code_element> process_leaf(std::shared_ptr<code_element> element) = 0;
    virtual void analyze_element(std::shared_ptr<code_element> element) = 0;
    virtual std::vector<int> get_analysis_result() = 0;
    virtual int get_pass_type() { return NONE_PASS;};
};

class pass_manager {
public:
    void add_pass(const std::shared_ptr<pass_base>& pass);
    std::shared_ptr<code_element> run_morphing_passes(std::shared_ptr<code_element> AST);
    std::vector<std::vector<int>> run_analysis_passes(const std::shared_ptr<code_element>& AST);
    void analyze_tree(const std::shared_ptr<code_element> &subtree, const std::shared_ptr<pass_base>& pass);
    std::vector<std::shared_ptr<code_element>> process_nodes(const std::shared_ptr<code_element> &subtree, const std::shared_ptr<pass_base>& pass);
    std::shared_ptr<code_element> process_leaves(const std::shared_ptr<code_element> &subtree, const std::shared_ptr<pass_base>& pass);
private:
    std::vector<std::shared_ptr<pass_base>> passes = {};
};


#endif //FCORE_HAS_PASS_MANAGER_HPP
