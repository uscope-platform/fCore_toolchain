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
