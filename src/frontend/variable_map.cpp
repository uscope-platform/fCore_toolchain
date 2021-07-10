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

#include "frontend/variable_map.hpp"



std::shared_ptr<variable> variable_map::operator[](const std::string& key) {
    return map[key];
}

void variable_map::insert(const std::string& key, std::shared_ptr<variable>item) {
    std::regex re("r(\\d\\d?)");
    std::smatch m;
    if(map.count(key)>0) return;
    switch (item->type) {
        case TYPE_INPUT:
            n_inputs_++;
            break;
        case TYPE_REGULAR:
            std::regex_match(key, m, re);
            if(m.empty())
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

bool operator==(const variable_map &lhs, const variable_map &rhs) {
    bool retval = true;

    retval &= lhs.n_inputs_ == rhs.n_inputs_;
    retval &= lhs.n_outputs_ == rhs.n_outputs_;
    retval &= lhs.n_variables_ == rhs.n_variables_;

    for(auto &i: lhs.map){
        if(rhs.map.count(i.first)){
            retval &= *rhs.map.at(i.first) == *lhs.map.at(i.first);
        } else{
            retval &= false;
        }

    }
    for(auto &i: rhs.map){
        if(lhs.map.count(i.first)){
            retval &= *rhs.map.at(i.first) == *lhs.map.at(i.first);
        } else{
            retval &= false;
        }
    }
    return retval;
}
