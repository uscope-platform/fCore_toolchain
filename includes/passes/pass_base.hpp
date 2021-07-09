//
// Created by fils on 09/07/2021.
//

#ifndef FCORE_HAS_PASS_BASE_HPP
#define FCORE_HAS_PASS_BASE_HPP

#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>

#define NONE_PASS 0
#define NODE_PASS 1
#define LEAF_PASS 2
#define GLOBAL_PASS 3
#define ANALYSIS_PASS 4


template<class E>
class pass_base {
public:
    pass_base(std::string n) {name = std::move(n);};
    virtual std::vector<std::shared_ptr<E>>process_node(std::shared_ptr<E> element){
        std::vector<std::shared_ptr<E>> elem;
        elem.push_back(element);
        return elem;
    };
    virtual std::shared_ptr<E> process_global(std::shared_ptr<E> element) {
        return element;
    };
    virtual std::shared_ptr<E> process_leaf(std::shared_ptr<E> element){
        return element;
    };
    std::string get_name() {return name;};
    virtual void analyze_element(std::shared_ptr<E> element) {};
    virtual std::vector<int> get_analysis_result() {return std::vector<int>();};
    virtual int get_pass_type() { return NONE_PASS;};
private:
    std::string name;
};

#endif //FCORE_HAS_PASS_BASE_HPP
