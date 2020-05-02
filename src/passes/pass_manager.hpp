//
// Created by fils on 01/05/20.
//

#ifndef FCORE_HAS_PASS_MANAGER_HPP
#define FCORE_HAS_PASS_MANAGER_HPP

#include <memory>
#include <vector>
#include "../code_elements/code_element.hpp"


class pass_base {
public:

    virtual std::shared_ptr<code_element> process_element_enter(std::shared_ptr<code_element> element)  { return  element;};
    virtual std::shared_ptr<code_element> process_element_exit(std::shared_ptr<code_element> element)  { return  element;};
};

class pass_manager {
public:
    void add_pass(const std::shared_ptr<pass_base>& pass);
    std::shared_ptr<code_element> run_passes(std::shared_ptr<code_element> AST);
    static std::shared_ptr<code_element> process_subtree(const std::shared_ptr<code_element> &subtree, const std::shared_ptr<pass_base>&  pass) ;
private:
    std::vector<std::shared_ptr<pass_base>> passes = {};
};


#endif //FCORE_HAS_PASS_MANAGER_HPP
