//
// Created by fils on 13/06/20.
//

#include "variable_map.hpp"

#include <utility>

std::shared_ptr<variable> variable_map::operator[](const std::string& key) {
    return map[key];
}

void variable_map::insert(const std::string& key, std::shared_ptr<variable>item) {
    switch (item->type) {
        case TYPE_INPUT:
            n_inputs_++;
            break;
        case TYPE_REGULAR:
            if(!fcore_registers.count(key))
                n_variables_++;
            break;
        case TYPE_OUTPUT:
            n_outputs_++;
            break;
    }
    map[key] = std::move(item);
}

int variable_map::count(const std::string &key) {
    return map.count(key);
}

std::shared_ptr<variable> variable_map::at(const std::string &key) {
    return map.at(key);
}

void variable_map::merge(const variable_map& in_map) {
    std::unordered_map<std::string, std::shared_ptr<variable>> arg_map = in_map.getMap();
    map.insert(arg_map.begin(), arg_map.end());
}

const std::unordered_map<std::string, std::shared_ptr<variable>> &variable_map::getMap() const {
    return map;
}
