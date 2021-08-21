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

#ifndef FCORE_TOOLCHAIN_INSTRUCTION_STREAM_BUILDER_HPP
#define FCORE_TOOLCHAIN_INSTRUCTION_STREAM_BUILDER_HPP

#include "data_structures/instruction_stream.hpp"

class instruction_stream_builder {
public:
    static instruction_stream build_stream(const std::shared_ptr<ll_ast_node>& tree);

};


#endif //FCORE_TOOLCHAIN_INSTRUCTION_STREAM_BUILDER_HPP
