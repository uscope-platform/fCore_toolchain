//
// Created by fils on 01/05/20.
//

#include "pass_manager.hpp"

#include <utility>

void pass_manager::add_pass(const std::shared_ptr<pass_base>& pass) {
    passes.push_back(pass);
}

std::shared_ptr<code_element> pass_manager::run_passes(std::shared_ptr<code_element> AST) {
    std::shared_ptr<code_element> working_tree = std::move(AST);
    for(auto &pass:passes){
        working_tree = process_subtree(working_tree, pass);;
    }
    return working_tree;
}

std::shared_ptr<code_element> pass_manager::process_subtree(const std::shared_ptr<code_element> &subtree, const std::shared_ptr<pass_base>& pass) {
    std::shared_ptr<code_element> working_tree = subtree;
    std::vector<std::shared_ptr<code_element>> content = working_tree->get_content();
    for(auto &item:content){
        if(item->is_terminal()){ //TODO: when processing internals of a for loop this call's overload fails, and it gets routed to the base class method(code element instead of instruction subclass)
            item = pass->process_element_enter(item);
            item = pass->process_element_exit(item);
        } else{
            item = pass->process_element_enter(item);
            item = process_subtree(item, pass);
            item = pass->process_element_exit(item);
        }
    }
    working_tree->set_content(content);
    return working_tree;
}

