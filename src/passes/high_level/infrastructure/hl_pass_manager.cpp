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
// limitations under the License.06/07/2021.
//

#include "passes/high_level/infrastructure/hl_pass_manager.hpp"

#include "passes/high_level/infrastructure/pass_base.hpp"

namespace fcore{


    std::shared_ptr<hl_code_block>  hl_pass_manager::run_repeating_pass_group(std::shared_ptr<hl_code_block> &subtree,
                                                                                 const std::vector<std::shared_ptr<pass_base>> &group) {

        auto working_tree =  std::static_pointer_cast<hl_code_block>(hl_ast_node::deep_copy(subtree));
        int run_number = 1;

        std::shared_ptr<hl_ast_node> old_tree;
        do{
            old_tree = hl_ast_node::deep_copy(working_tree);
            for(auto &pass:group){

                if(ic != nullptr) ic->start_event(pass->get_name(), false);
                auto pass_res = pass->process_global(std::static_pointer_cast<hl_code_block>(subtree));
                working_tree =  pass_res;
                if(ic != nullptr) ic->end_event(pass->get_name());

            }
            ++run_number;
        } while (!hl_ast_node::compare_content_by_type(old_tree, working_tree));
        return working_tree;
    }


    void hl_pass_manager::add_morphing_pass(const std::string& name, const std::shared_ptr<pass_base>& pass){
        opt_pass p;
        p.pass = {pass};
        p.type = single_pass;
        p.name = name;
        p.enabled = true;
        passes.push_back(p);
    }

    void hl_pass_manager::add_morphing_pass_group(const std::string& name, const std::vector<std::shared_ptr<pass_base>>& group){
        opt_pass p;
        p.pass = group;
        p.type = repeating_pass_group;
        p.name = name;
        p.enabled = true;
        passes.push_back(p);
    }

    std::shared_ptr<hl_code_block> hl_pass_manager::run_morphing_passes(std::shared_ptr<hl_code_block> AST) {
        auto working_ast = std::static_pointer_cast<hl_code_block>(hl_ast_node::deep_copy(AST));

        for(auto& p:passes){
            if(p.type == single_pass){
                if(p.enabled){
                    std::shared_ptr<pass_base> pass = p.pass[0];

                    if (ic != nullptr) ic->start_event(pass->get_name(), false);
                    auto pass_res = pass->process_global(std::static_pointer_cast<hl_code_block>(working_ast));
                    working_ast =  pass_res;
                    if (ic != nullptr) ic->end_event(pass->get_name());
                }
            } else if(p.type == repeating_pass_group) {
                if (p.enabled) {
                    working_ast = run_repeating_pass_group(working_ast, p.pass);
                }
            } else if(p.type == unique_pass_group) {
                if(p.enabled){
                    for(auto &pass:p.pass){

                        if(ic != nullptr) ic->start_event(pass->get_name(), false);
                        working_ast =  pass->process_global(std::static_pointer_cast<hl_code_block>(working_ast));
                        if(ic != nullptr) ic->end_event(pass->get_name());
                    }
                }
            } else {
                throw std::runtime_error("ERROR: unexpected pass type");
            }


        }
        return working_ast;
    }

    void hl_pass_manager::enable_pass(const std::string &name) {
        for(auto& p:passes) {
            if(p.name == name) {
                p.enabled = true;
                return;
            }
        }
        throw std::runtime_error("Required pass not found");
    }

    void hl_pass_manager::disable_all() {
        for(auto& p:passes) {
            p.enabled = false;
        }
    }

}