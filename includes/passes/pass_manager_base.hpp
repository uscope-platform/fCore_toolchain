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

#ifndef FCORE_HAS_PASS_MANAGER_BASE_HPP
#define FCORE_HAS_PASS_MANAGER_BASE_HPP

#include <memory>
#include <vector>
#include <utility>
#include <unordered_map>

#define NONE_PASS 0
#define NODE_PASS 1
#define LEAF_PASS 2
#define ANALYSIS_PASS 3

template<class E>
class pass_base {
public:
    virtual std::vector<std::shared_ptr<E>>process_node(std::shared_ptr<E> element){
        std::vector<std::shared_ptr<E>> elem;
        elem.push_back(element);
        return elem;
    };
    virtual std::shared_ptr<E> process_leaf(std::shared_ptr<E> element){
        return element;
    };
    virtual void analyze_element(std::shared_ptr<E> element) {};
    virtual std::vector<int> get_analysis_result() {return std::vector<int>();};
    virtual int get_pass_type() { return NONE_PASS;};
};


template<class E>
class pass_manager_base {
public:
    void add_pass(const std::shared_ptr<pass_base<E>>& pass);
    std::shared_ptr<E> run_morphing_passes(std::shared_ptr<E> AST);
    virtual std::shared_ptr<E> run_pass(const std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>>& pass) {return std::shared_ptr<E>();};
    std::vector<std::vector<int>> run_analysis_passes(const std::shared_ptr<E>& AST);
    void analyze_tree(const std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>>& pass);
    std::unordered_map<std::string, std::shared_ptr<pass_base<E>>> analysis_passes;
protected:
    std::vector<std::shared_ptr<pass_base<E>>> morphing_passes = {};
};


template<class E>
void pass_manager_base<E>::add_pass(const std::shared_ptr<pass_base<E>>& pass) {
    morphing_passes.push_back(pass);
}

template<class E>
std::shared_ptr<E> pass_manager_base<E>::run_morphing_passes(std::shared_ptr<E> AST) {
    std::shared_ptr<E> working_tree = std::move(AST);
    for( auto& pass:morphing_passes){
        working_tree = run_pass(working_tree, pass);
    }
    return working_tree;
}

template<class E>
std::vector<std::vector<int>> pass_manager_base<E>::run_analysis_passes(const std::shared_ptr<E>& AST) {
    std::vector<std::vector<int>> results;
    for( auto& pass:morphing_passes){
        if(pass->get_pass_type() == ANALYSIS_PASS){
            analyze_tree(AST, pass);
            results.push_back(pass->get_analysis_result());
        }
    }
    return results;
}


template<class E>
void
pass_manager_base<E>::analyze_tree(const std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>> &pass) {
    for(auto &i : subtree->get_content()){
        analyze_tree(i,pass);
    }
    pass->analyze_element(subtree);
}




#endif //FCORE_HAS_PASS_MANAGER_BASE_HPP
