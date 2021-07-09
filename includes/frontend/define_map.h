//
// Created by fils on 29/06/2021.
//

#ifndef FCORE_HAS_DEFINE_MAP_H
#define FCORE_HAS_DEFINE_MAP_H

#include <unordered_map>
#include <string>
#include <memory>
#include <utility>

#include "ast/define.h"

class define_map {
public:

    std::shared_ptr<define> operator[](const std::string& key);
    std::shared_ptr<define> at(const std::string& key);
    void insert(const std::string& key, std::shared_ptr<define>item);
    unsigned int count(const std::string& key);


private:
    std::unordered_map<std::string, std::shared_ptr<define>> defines;
};


#endif //FCORE_HAS_DEFINE_MAP_H
