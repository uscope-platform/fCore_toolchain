// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP
#define FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP

#include <memory>
#include <utility>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include "pass_base.hpp"

#include <nlohmann/json.hpp>

namespace fcore{

    enum pass_type {single_pass=0, pass_group = 1};

    template<class E>
    class pass_manager_base {
    public:
        // API FOR MORPHING PASSES
        void add_morphing_pass(const std::string& name, const std::shared_ptr<pass_base<E>>& pass);
        void add_morphing_pass_group(const std::string& name, const std::vector<std::shared_ptr<pass_base<E>>>& group);
        void run_morphing_passes(std::shared_ptr<E> AST);
        virtual void run_morphing_pass(std::shared_ptr<E> &, const std::shared_ptr<pass_base<E>>& ) {};
        virtual std::vector<nlohmann::json> run_morphing_pass_group(std::shared_ptr<E> &, const std::vector<std::shared_ptr<pass_base<E>>>& , int ) {return nlohmann::json();};

        void disable_all();
        void enable_pass(const std::string& name);
        void disable_pass(const std::string& name);
        nlohmann::json get_dump();

        std::vector<std::vector<int>> run_analysis_passes(const std::shared_ptr<E>& AST);
        void analyze_tree(const std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>>& pass);
        std::unordered_map<std::string, std::shared_ptr<pass_base<E>>> analysis_passes;
    protected:

        struct opt_pass {
            std::vector<std::shared_ptr<pass_base<E>>> pass;
            pass_type type = single_pass;
            std::string name;
            bool enabled = true;
        };


        std::vector<opt_pass> passes;

        // DUMP DATA STRUCTURES
        nlohmann::json pre_opt_dump;
        std::vector<nlohmann::json> in_opt_dump;
        nlohmann::json post_opt_dump;
        int dump_ast_level = 0;
    };

    template<class E>
    void pass_manager_base<E>::disable_pass(const std::string &name) {
        for(auto& p:passes) {
            if(p.name == name) {
                p.enabled = false;
                return;
            }
        }
        throw std::runtime_error("Required pass not found");
    }

    template<class E>
    void pass_manager_base<E>::enable_pass(const std::string& name) {
        for(auto& p:passes) {
            if(p.name == name) {
                p.enabled = true;
                return;
            }
        }
        throw std::runtime_error("Required pass not found");
    }

    template<class E>
    void pass_manager_base<E>::disable_all() {
        for(auto& p:passes) {
            p.enabled = false;
        }
    }


    template<class E>
    void pass_manager_base<E>::add_morphing_pass(const std::string& name, const std::shared_ptr<pass_base<E>>& pass) {
        opt_pass p;
        p.pass = {pass};
        p.type = single_pass;
        p.name = name;
        p.enabled = true;
        passes.push_back(p);
    }


    template<class E>
    void pass_manager_base<E>::run_morphing_passes(std::shared_ptr<E> AST) {
        if(dump_ast_level>0) {
            pre_opt_dump = AST->dump();
        }
        for(auto& p:passes){
            if(p.type == single_pass){
                if(p.enabled){
                    std::shared_ptr<pass_base<E>> pass = p.pass[0];
                    run_morphing_pass(AST, pass);
                    if(dump_ast_level>1){
                        nlohmann::json ast_dump;
                        ast_dump["pass_name"] = pass->get_name();
                        ast_dump["ast"]= AST->dump();
                        in_opt_dump.push_back(ast_dump);
                    }
                }
            } else if(p.type == pass_group){
                if(p.enabled){
                    std::vector<nlohmann::json> result = run_morphing_pass_group(AST, p.pass, dump_ast_level);
                    in_opt_dump.insert(in_opt_dump.end(), result.begin(), result.end());
                }
            } else {
                throw std::runtime_error("ERROR: unexpected pass type");
            }


        }
        if(dump_ast_level>0)  post_opt_dump = AST->dump();
    }

    template<class E>
    std::vector<std::vector<int>> pass_manager_base<E>::run_analysis_passes(const std::shared_ptr<E>& AST) {
        std::vector<std::vector<int>> results;
        for( auto& p:passes){
            if(p.pass[0]->get_pass_type() == ANALYSIS_PASS){
                analyze_tree(AST, p.pass[0]);
                results.push_back(p.pass[0]->get_analysis_result());
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
    void pass_manager_base<E>::add_morphing_pass_group(const std::string& name, const std::vector<std::shared_ptr<pass_base<E>>> &group) {
        opt_pass p;
        p.pass = group;
        p.type = pass_group;
        p.name = name;
        p.enabled = true;
        passes.push_back(p);
    }

    template<class E>
    nlohmann::json pass_manager_base<E>::get_dump() {
        nlohmann::json retval;

        retval["pre-opt"] = pre_opt_dump;
        retval["in-opt"] = in_opt_dump;
        retval["post-opt"] = post_opt_dump;

        return retval;
    }
}


#endif //FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP
