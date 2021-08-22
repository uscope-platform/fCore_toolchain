// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_TOOLCHAIN_DEFINE_MAP_HPP
#define FCORE_TOOLCHAIN_DEFINE_MAP_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <utility>

#include "tools/define.hpp"

class define_map {
public:

    std::shared_ptr<define> operator[](const std::string& key);
    std::shared_ptr<define> at(const std::string& key);
    void insert(const std::string& key, std::shared_ptr<define>item);
    unsigned int count(const std::string& key);

    unsigned int size() {return defines.size();};
    std::__detail::_Node_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<define>>, false, true> begin() {return defines.begin();}
    std::__detail::_Node_const_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<define>>, false, true> begin() const { return defines.begin();}
    std::__detail::_Node_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<define>>, false, true> end() {return defines.end();}
    std::__detail::_Node_const_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<define>>, false, true> end() const { return defines.end();}

private:
    std::unordered_map<std::string, std::shared_ptr<define>> defines;
};


#endif //FCORE_TOOLCHAIN_DEFINE_MAP_HPP
