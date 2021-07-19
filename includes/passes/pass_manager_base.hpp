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

#ifndef FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP
#define FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP

#include <memory>
#include <utility>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include "pass_base.hpp"



template<class E>
class pass_manager_base {
public:
    // API FOR MORPHING PASSES
    void add_morphing_pass(const std::shared_ptr<pass_base<E>>& pass);
    void add_morphing_pass_group(const std::vector<std::shared_ptr<pass_base<E>>>& group);
    void run_morphing_passes(std::shared_ptr<E> AST);
    virtual void run_morphing_pass(std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>>& pass) {};
    virtual void run_morphing_pass_group(std::shared_ptr<E> &subtree, const std::vector<std::shared_ptr<pass_base<E>>>& group) {};

    std::vector<int> get_pass_order() { return pass_order;};
    void set_pass_order(std::vector<int> order) {pass_order = std::move(order);};

    std::vector<std::vector<int>> run_analysis_passes(const std::shared_ptr<E>& AST);
    void analyze_tree(const std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>>& pass);
    std::unordered_map<std::string, std::shared_ptr<pass_base<E>>> analysis_passes;
protected:
    std::vector<std::shared_ptr<pass_base<E>>> morphing_passes = {};
    std::vector<int> pass_order;
    std::vector<std::vector<std::shared_ptr<pass_base<E>>>> morphing_passes_groups{};
};


template<class E>
void pass_manager_base<E>::add_morphing_pass(const std::shared_ptr<pass_base<E>>& pass) {
    morphing_passes.push_back(pass);
}


template<class E>
void pass_manager_base<E>::run_morphing_passes(std::shared_ptr<E> AST) {
    for(auto& idx:pass_order){
        if(idx>=0){
            int pass_index = idx-1;
            std::shared_ptr<pass_base<E>> pass = morphing_passes[pass_index];
            run_morphing_pass(AST, pass);
        } else {
            int pass_index = -idx -1;
            run_morphing_pass_group(AST, morphing_passes_groups[pass_index]);
        }

    }

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

template<class E>
void pass_manager_base<E>::add_morphing_pass_group(const std::vector<std::shared_ptr<pass_base<E>>> &group) {
    morphing_passes_groups.push_back(group);
}


#endif //FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP
