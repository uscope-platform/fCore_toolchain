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
#include <nlohmann/json.hpp>

#include "pass_base.hpp"
#include "instrumentation/instrumentation_core.hpp"

namespace fcore{

    enum pass_type {
        single_pass=0,
        repeating_pass_group = 1,
        unique_pass_group = 2
    };

    template<class E>
    class pass_manager_base {
    public:
        // API FOR MORPHING PASSES

        virtual void run_single_pass(std::shared_ptr<E> &, const std::shared_ptr<pass_base<E>>& ) {};
        virtual void run_repeating_pass_group(std::shared_ptr<E> &, const std::vector<std::shared_ptr<pass_base<E>>>&) {};
        virtual void run_unique_pass_group(std::shared_ptr<E> &, const std::vector<std::shared_ptr<pass_base<E>>>&) {};

        void disable_all();
        void enable_pass(const std::string& name);

        void set_profiler(std::shared_ptr<instrumentation_core> &p){
            this->ic = p;
        };

        void analyze_tree(const std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>>& pass);
        std::unordered_map<std::string, std::shared_ptr<pass_base<E>>> analysis_passes;

    private:
    protected:

        struct opt_pass {
            std::vector<std::shared_ptr<pass_base<E>>> pass;
            pass_type type = single_pass;
            std::string name;
            bool enabled = true;
        };

        std::shared_ptr<instrumentation_core> ic;

        std::vector<opt_pass> passes;

    };


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
    void
    pass_manager_base<E>::analyze_tree(const std::shared_ptr<E> &subtree, const std::shared_ptr<pass_base<E>> &pass) {
        for(auto &i : subtree->get_content()){
            analyze_tree(i,pass);
        }
        pass->analyze_element(subtree);
    }


}


#endif //FCORE_TOOLCHAIN_PASS_MANAGER_BASE_HPP
