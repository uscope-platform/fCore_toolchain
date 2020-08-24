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

#include <memory>
#include <string>
#include <unordered_map>
#include <iterator>
#include "../code_elements/variable.hpp"
#include "../code_elements/code_element.hpp"
class variable_map {
public:
    std::shared_ptr<variable> operator[](const std::string& key);
    std::shared_ptr<variable> at(const std::string& key);
    void insert(const std::string& key, std::shared_ptr<variable>item);
    int count(const std::string& key);

    unsigned int n_inputs() const {return n_inputs_;};
    unsigned int n_outputs() const {return n_outputs_;};
    unsigned int n_variables() const {return n_variables_;};
private:
    unsigned int n_inputs_ = 0;
    unsigned int n_outputs_ = 0;
    unsigned int n_variables_ = 0;
    std::unordered_map<std::string, std::shared_ptr<variable>> map;
};


#endif //FCORE_HAS_VARIABLE_MAP_HPP
