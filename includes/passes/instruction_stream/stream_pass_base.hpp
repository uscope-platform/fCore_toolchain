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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.09/07/2021.
//

#ifndef FCORE_TOOLCHAIN_STREAM_PASS_BASE_HPP
#define FCORE_TOOLCHAIN_STREAM_PASS_BASE_HPP

#include "data_structures/low_level_ast/low_level_ast.hpp"

class stream_pass_base {
public:
    explicit stream_pass_base(std::string n) {name = std::move(n);};

    virtual std::shared_ptr<ll_instruction_node> apply_pass(std::shared_ptr<ll_instruction_node> element) {
        return element;
    };

private:
    std::string name;
};

#endif //FCORE_TOOLCHAIN_STREAM_PASS_BASE_HPP
