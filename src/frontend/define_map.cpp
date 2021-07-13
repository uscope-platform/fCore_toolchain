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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.29/06/2021.
//

#include "frontend/define_map.hpp"

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
