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


#include "frontend/C/C_pre_processor.hpp"

#include <utility>

C_pre_processor::C_pre_processor(std::istream &file, std::shared_ptr<variable_map> &varmap, std::shared_ptr<define_map> &defmap) {
    working_content = std::string((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    dmap = defmap;
    vmap = varmap;
}

std::string  C_pre_processor::get_preprocessed_file() {
    return working_content;
}

void C_pre_processor::process_file() {
    std::string line;
    std::string decommented_line;
    std::istringstream ss(working_content);
    std::ostringstream processed_file_ss;

    std::regex line_comment("\\/\\/.*");
    std::regex multiline_start("\\/\\*(.*)");
    std::regex multiline_stop("(.*)\\*\\/");

    bool in_muliline_comment = false;

    while (std::getline(ss,line)){
        bool ignore_cond_1 = std::regex_match(line, line_comment);
        bool ignore_cond_2 = line.empty();
        bool contain_multiline_start = std::regex_search(line, multiline_start);
        bool contain_multiline_stop = std::regex_search(line, multiline_stop);
        if(contain_multiline_start & !contain_multiline_stop){
            in_muliline_comment = true;
            decommented_line =  std::regex_replace(line, std::regex(multiline_start), "");
        } else if(!contain_multiline_start & contain_multiline_stop){
            in_muliline_comment = false;
            decommented_line =  std::regex_replace(line, std::regex(multiline_stop), "");
        }else if(!(ignore_cond_1 | ignore_cond_2 | in_muliline_comment)){
            decommented_line= std::regex_replace(line, std::regex(R"(\/\*(.*)\*\/)"), "");
        }else if(ignore_cond_2 | ignore_cond_1 | in_muliline_comment){
            continue;
        }
        process_pragmas(decommented_line);
        process_define(decommented_line);

        std::string rel_include_text = process_rel_includes(decommented_line);
        std::string abs_include_text = process_abs_includes(decommented_line);

        if(!rel_include_text.empty()){
            processed_file_ss << rel_include_text << std::endl;
        } else if(!abs_include_text.empty()){
            processed_file_ss << abs_include_text << std::endl;
        } else{
            processed_file_ss << line << std::endl;
        }

    }
    working_content = processed_file_ss.str();
}

void C_pre_processor::process_pragmas(const std::string& line) {
    std::regex io_pragma_regex(R"(#pragma\s+(input|output)\s*\(\s?(.*),\s*r(\d*)\s*\))");
    std::smatch match;

    if(std::regex_search( line,match,io_pragma_regex)){
        if(match.size() != 4){
            std::cout << "ERROR: Malformed pragma expression:" << std::endl << line << std::endl;
            exit(1);
        }
        std::string type = match.str(1);
        std::string var_name = match.str(2);
        std::string reg = match.str(3);
        std::shared_ptr<variable> v = std::make_shared<variable>(false, var_name);
        v->type = type == "output" ? TYPE_OUTPUT : TYPE_INPUT;
        v->set_bound_reg(std::stoul(reg));
        vmap->insert(var_name, v);
    }
}

void C_pre_processor::process_define(const std::string& line) {
    std::regex define_regex(R"(#define\s+([A-Za-z0-9_]*)\s+(.*))");
    std::smatch match;
    if(std::regex_search( line,match,define_regex)){
        std::string name = match.str(1);
        std::string value = match.str(2);
        std::shared_ptr<define> def = std::make_shared<define>(0, name, value);
        dmap->insert(name, def);
    }
}

std::string C_pre_processor::process_rel_includes(const std::string& line) {
    std::regex rel_include_regex(R"(#include\s*\"(.*)\")");
    std::smatch match;
    if(std::regex_search( line,match,rel_include_regex)){
        std::string target = match.str(1);
        if(!target.empty()){
            if(std::find(allowed_relative_includes.begin(), allowed_relative_includes.end(), target) != allowed_relative_includes.end()){

                std::ifstream ifs(std::filesystem::canonical("./" + target));
                C_pre_processor include_preproc(ifs, vmap, dmap);
                include_preproc.set_relative_includes(allowed_relative_includes);
                include_preproc.set_absolute_includes(allowed_absolute_includes);
                include_preproc.process_file();
                return include_preproc.get_preprocessed_file();
            } else {
                throw std::runtime_error("included file: " + target + " not found");
            }
        }
    }
    return "";
}

std::string C_pre_processor::process_abs_includes(const std::string &line) {
    std::regex abs_include_regex(R"(#include\s*<(.*)>)");
    std::smatch match;
    if(std::regex_search( line,match,abs_include_regex)){
        std::string target = match.str(1);
        if(!target.empty()){
            if(std::find(allowed_absolute_includes.begin(), allowed_absolute_includes.end(), target) != allowed_absolute_includes.end()){
                //TODO: implement absolute includes
            } else {
                throw std::runtime_error("included file: " + target + " not supported");
            }
        }
    }
    return "";
}

void C_pre_processor::set_relative_includes(std::vector<std::string> list) {
    allowed_relative_includes = std::move(list);
}

void C_pre_processor::set_absolute_includes(std::vector<std::string> list) {
    allowed_absolute_includes = std::move(list);
}


