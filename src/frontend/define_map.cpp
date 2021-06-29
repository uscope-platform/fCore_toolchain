//
// Created by fils on 29/06/2021.
//

#include "frontend/define_map.h"

void define_map::insert(const std::string &key, std::shared_ptr<define> item) {
    defines[key] = std::move(item);
}

unsigned int define_map::count(const std::string &key) {
    return defines.count(key);
}

std::shared_ptr<define> define_map::at(const std::string &key) {
    return defines.at(key);
}

std::shared_ptr<define> define_map::operator[](const std::string &key) {
    return defines[key];
}
