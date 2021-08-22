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

#ifndef FCORE_TOOLCHAIN_DEFINE_HPP
#define FCORE_TOOLCHAIN_DEFINE_HPP

#include <string>
#include <utility>

class define {
public:
    define(int l, std::string n, std::string c);
    std::string get_content() {return content;};
    friend bool operator==(const define& lhs, const define& rhs);
private:
    int line;
    std::string name;
    std::string content;
};


#endif //FCORE_TOOLCHAIN_DEFINE_HPP
