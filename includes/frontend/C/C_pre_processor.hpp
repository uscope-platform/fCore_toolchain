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

#ifndef FCORE_TOOLCHAIN_C_PRE_PROCESSOR_HPP
#define FCORE_TOOLCHAIN_C_PRE_PROCESSOR_HPP

#include <istream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <regex>
#include <stdexcept>

#include "tools/variable.hpp"
#include "tools/define.hpp"
#include "tools/variable_map.hpp"
#include "tools/define_map.hpp"

class C_pre_processor {
public:
    explicit C_pre_processor(std::istream &file,  std::shared_ptr<define_map> &defmap);
    std::string get_preprocessed_file();
    void set_relative_includes(std::vector<std::string> list);
    void set_absolute_includes(std::vector<std::string> list);
    void process_file();
    std::unordered_map<std::string, std::shared_ptr<variable>> get_iom_map() { return iom_map;};
    void substitute_defines();
    std::string substitute_defines_in_line(std::string &line, const std::pair<std::string, std::shared_ptr<define>>& item);
private:


    void process_pragmas(const std::string& line);
    bool process_define(const std::string& line);
    std::string process_rel_includes(const std::string& line);
    std::string process_abs_includes(const std::string& line);

    std::vector<std::string> allowed_absolute_includes = {};
    std::vector<std::string> allowed_relative_includes = {};
    std::string working_content;
    std::shared_ptr<define_map> dmap;
    std::unordered_map<std::string, std::shared_ptr<variable>> iom_map;
};


#endif //FCORE_TOOLCHAIN_C_PRE_PROCESSOR_HPP
