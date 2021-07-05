// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_HAS_PASS_MANAGER_HPP
#define FCORE_HAS_PASS_MANAGER_HPP

#include <memory>
#include <vector>
#include <unordered_map>
#include "code_elements/ll_ast/ll_ast_node.hpp"

#define NONE_PASS 0
#define NODE_PASS 1
#define LEAF_PASS 2
#define ANALYSIS_PASS 3

class pass_base {
public:
    virtual std::vector<std::shared_ptr<ll_ast_node>>process_node(std::shared_ptr<ll_ast_node> element){
        std::vector<std::shared_ptr<ll_ast_node>> elem;
        elem.push_back(element);
        return elem;
    };
    virtual std::shared_ptr<ll_ast_node> process_leaf(std::shared_ptr<ll_ast_node> element){
        return element;
    };
    virtual void analyze_element(std::shared_ptr<ll_ast_node> element) {};
    virtual std::vector<int> get_analysis_result() {return std::vector<int>();};
    virtual int get_pass_type() { return NONE_PASS;};
};

class pass_manager {
public:
    void add_pass(const std::shared_ptr<pass_base>& pass);
    std::shared_ptr<ll_ast_node> run_morphing_passes(std::shared_ptr<ll_ast_node> AST);
    std::vector<std::vector<int>> run_analysis_passes(const std::shared_ptr<ll_ast_node>& AST);
    void analyze_tree(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base>& pass);
    std::vector<std::shared_ptr<ll_ast_node>> process_nodes(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base>& pass);
    std::shared_ptr<ll_ast_node> process_leaves(const std::shared_ptr<ll_ast_node> &subtree, const std::shared_ptr<pass_base>& pass);
    std::unordered_map<std::string, std::shared_ptr<pass_base>> analysis_passes;
private:
    std::vector<std::shared_ptr<pass_base>> passes = {};
};


#endif //FCORE_HAS_PASS_MANAGER_HPP
