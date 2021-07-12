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

#ifndef FCORE_HAS_FCORE_CC_HPP
#define FCORE_HAS_FCORE_CC_HPP

#include <istream>
#include <vector>
#include <string>
#include <fstream>

#include "frontend/variable_map.hpp"
#include "frontend/define_map.hpp"
#include "frontend/C/C_language_parser.hpp"
#include "backend/output_generator.hpp"
#include "passes/hl_passes.hpp"
#include "passes/ll_passes.hpp"
#include "passes/high_level/hl_pass_manager.hpp"
#include "passes/low_level/ll_pass_manager.hpp"
#include "ast/transformations/high_level_ast_lowering.hpp"
#include "../third_party/json.hpp"

class fcore_cc {
public:
    fcore_cc(std::istream &input, std::vector<std::string> &includes);
    std::vector<uint32_t> get_hexfile(bool endian_swap);
    std::string get_errors();
    std::vector<std::string> get_verilog_memfile();
    void write_hexfile(const std::string& ouput_file);
    void write_verilog_memfile(const std::string& ouput_file);
    void write_json(const std::string& output_file);
    uint32_t get_program_size();
    uint32_t get_inst_count();
private:
    std::shared_ptr<hl_ast_node> hl_ast;
    std::shared_ptr<ll_ast_node> ll_ast;
    output_generator writer;
    hl_pass_manager  hl_manager;
    ll_pass_manager ll_manager;
    std::string error_code;
};



#endif //FCORE_HAS_FCORE_CC_HPP
