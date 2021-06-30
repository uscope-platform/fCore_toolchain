//
// Created by fils on 29/06/2021.
//

#ifndef FCORE_HAS_C_PRE_PROCESSOR_H
#define FCORE_HAS_C_PRE_PROCESSOR_H

#include <istream>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <regex>
#include <stdexcept>

#include "code_elements/variable.hpp"
#include "code_elements/define.h"
#include "frontend/variable_map.hpp"
#include "frontend/define_map.h"

class C_pre_processor {
public:
    explicit C_pre_processor(std::istream &file,std::shared_ptr<variable_map> &new_varmap,  std::shared_ptr<define_map> &defmap);
    std::string get_preprocessed_file();
    void set_relative_includes(std::vector<std::string> list);
    void set_absolute_includes(std::vector<std::string> list);
    void process_file();

private:


    void process_pragmas(const std::string& line);
    void process_define(const std::string& line);
    std::string process_rel_includes(const std::string& line);
    std::string process_abs_includes(const std::string& line);

    std::vector<std::string> allowed_absolute_includes = {};
    std::vector<std::string> allowed_relative_includes = {};
    std::string working_content;
    std::shared_ptr<variable_map> vmap;
    std::shared_ptr<define_map> dmap;
};


#endif //FCORE_HAS_C_PRE_PROCESSOR_H
