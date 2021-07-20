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

#include "tools/define.hpp"



define::define(int l, std::string n, std::string c) {
line = l;
name = std::move(n);
content = std::move(c);
}

bool operator==(const define &lhs, const define &rhs) {
    bool cond = lhs.name == rhs.name;
    cond &= lhs.line == rhs.line;
    cond &= lhs.content == rhs.content;
    return cond;
}
