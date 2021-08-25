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
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/

#ifndef FCORE_TOOLCHAIN_FCORE_EMU_H
#define FCORE_TOOLCHAIN_FCORE_EMU_H

#include <istream>
#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "frontend/binary_loader.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"

#include "backend/emulator.hpp"

class fcore_emu {
public:
    fcore_emu(std::istream &input, bin_loader_input_type_t in_type);
    void write_json(const std::string& output_file);

private:
    std::shared_ptr<ll_ast_node> ll_ast;
    std::string error_code;
};


#endif //FCORE_TOOLCHAIN_FCORE_EMU_H
