// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#ifndef FCORE_HAS_VARIABLE_MAP_HPP
#define FCORE_HAS_VARIABLE_MAP_HPP

#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <iterator>
#include <utility>
#include <cmath>
#include "ast/variable.hpp"
#include "ast/low_level/ll_ast_node.hpp"

class variable_map {
public:
    variable_map();
    std::shared_ptr<variable> operator[](const std::string& key);
    std::shared_ptr<variable> at(const std::string& key);
    void insert(const std::string& key, std::shared_ptr<variable>item);
    unsigned int count(const std::string& key);
    unsigned int size();

    unsigned int n_inputs() const {return n_inputs_;};
    unsigned int n_outputs() const {return n_outputs_;};
    unsigned int n_variables() const {return n_variables_;};
    friend bool operator==(const variable_map& lhs, const variable_map& rhs);

    std::__detail::_Node_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<variable>>, false, true> begin() {return map.begin();}
    std::__detail::_Node_const_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<variable>>, false, true> begin() const { return map.begin();}
    std::__detail::_Node_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<variable>>, false, true> end() {return map.end();}
    std::__detail::_Node_const_iterator<std::pair<const std::basic_string<char>, std::shared_ptr<variable>>, false, true> end() const { return map.end();}

private:
    unsigned int n_inputs_ = 0;
    unsigned int n_outputs_ = 0;
    unsigned int n_variables_ = 0;
    std::unordered_map<std::string, std::shared_ptr<variable>> map;
};


#endif //FCORE_HAS_VARIABLE_MAP_HPP
