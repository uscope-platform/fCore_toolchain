//
// Created by fils on 13/06/20.
//

#ifndef FCORE_HAS_VARIABLE_MAP_HPP
#define FCORE_HAS_VARIABLE_MAP_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <iterator>
#include "../code_elements/variable.hpp"

class variable_map {
public:
    std::shared_ptr<variable> operator[](const std::string& key);
    std::shared_ptr<variable> at(const std::string& key);
    void insert(const std::string& key, std::shared_ptr<variable>item);
    void merge(const variable_map& map);
    int count(const std::string& key);

    unsigned int n_inputs() const {return n_inputs_;};
    unsigned int n_outputs() const {return n_outputs_;};
    unsigned int n_variables() const {return n_variables_;};
private:
    unsigned int n_inputs_ = 0;
    unsigned int n_outputs_ = 0;
    unsigned int n_variables_ = 0;
    std::unordered_map<std::string, std::shared_ptr<variable>> map;
public:
    const std::unordered_map<std::string, std::shared_ptr<variable>> &getMap() const;
};


#endif //FCORE_HAS_VARIABLE_MAP_HPP
