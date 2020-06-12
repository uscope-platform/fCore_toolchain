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
    virtual std::vector<ast_t>process_node(ast_t element) = 0;
    virtual ast_t process_leaf(ast_t element) = 0;
    virtual void analyze_element(ast_t element) = 0;
    virtual std::vector<int> get_analysis_result() = 0;
    virtual int get_pass_type() { return NONE_PASS;};
};

class pass_manager {
public:
    void add_pass(const std::shared_ptr<pass_base>& pass);
    ast_t run_morphing_passes(ast_t AST);
    std::vector<std::vector<int>> run_analysis_passes(const ast_t& AST);
    void analyze_tree(const ast_t &subtree, const std::shared_ptr<pass_base>& pass);
    std::vector<ast_t> process_nodes(const ast_t &subtree, const std::shared_ptr<pass_base>& pass);
    ast_t process_leaves(const ast_t &subtree, const std::shared_ptr<pass_base>& pass);
private:
    std::vector<std::shared_ptr<pass_base>> passes = {};
};


#endif //FCORE_HAS_PASS_MANAGER_HPP
