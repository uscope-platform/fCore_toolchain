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

C_pre_processor::C_pre_processor(std::string &path, std::shared_ptr<define_map> &defmap) {
    std::ifstream file(path);
    file_path = path;
    working_content = std::string((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    dmap = defmap;
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
        bool skip_line = false;
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
        skip_line |= process_define(decommented_line);

        std::string rel_include_text = process_rel_includes(decommented_line);
        std::string abs_include_text = process_abs_includes(decommented_line);

        if(!rel_include_text.empty()){
            processed_file_ss << rel_include_text << std::endl;
        } else if(!abs_include_text.empty()){
            processed_file_ss << abs_include_text << std::endl;
        } else{
            if(!skip_line){
                processed_file_ss << line << std::endl;
            }
        }

    }
    working_content = processed_file_ss.str();
}

void C_pre_processor::process_pragmas(const std::string& line) {
    std::regex scalar_io_pragma_regex(R"(#pragma\s+(input|memory|output)\s*\(\s?(.*?),\s*\{*(.*?)\}?\))");
    std::smatch match;

    if(std::regex_search(line, match, scalar_io_pragma_regex)){
        if(match.size() != 4){
            std::cout << "ERROR: Malformed pragma expression:" << std::endl << line << std::endl;
            exit(1);
        }
        std::string type_str = match.str(1);
        std::string var_name = match.str(2);
        std::string reg = match.str(3);
        size_t n = std::count(reg.begin(), reg.end(), ',');
        variable_class_t type;
        if(type_str == "output")
            type = variable_output_type;
        else if(type_str == "input")
            type = variable_input_type;
        else if(type_str == "memory")
            type = variable_memory_type;
        else
            type = variable_regular_type;

        std::shared_ptr<variable> v = std::make_shared<variable>( var_name);
        v->set_variable_class(type);

        if(n==0){
            reg = reg.substr(1, reg.size()-1);
            v->set_bound_reg(std::stoul(reg));
        } else {
            std::smatch regs_match;
            std::vector<unsigned int> array_bound_reg;
            while(std::regex_search(reg, regs_match, std::regex(R"((r(\d+))*\s?\,?\s?)"))){
                std::string reg_number = regs_match[2].str();
                if(reg_number.empty()) break;
                array_bound_reg.push_back(std::stoul(reg_number));
                reg = regs_match.suffix().str();
            }
            v->set_bound_reg_array(array_bound_reg);
        }
        iom_map[var_name] = v;
    }
}

bool C_pre_processor::process_define(const std::string& line) {
    bool line_contains_str = false;
    std::regex define_regex(R"(#define\s+([A-Za-z0-9_]*)\s+(.*))");
    std::smatch match;
    if(std::regex_search( line,match,define_regex)){
        std::string name = match.str(1);
        std::string value = match.str(2);
        std::shared_ptr<define> def = std::make_shared<define>(0, name, value);
        dmap->insert(name, def);
        line_contains_str = true;
    }
    return line_contains_str;
}

std::string C_pre_processor::process_rel_includes(const std::string& line) {
    std::regex rel_include_regex(R"(#include\s*\"(.*)\")");
    std::smatch match;
    if(std::regex_search( line,match,rel_include_regex)){
        std::string target = match.str(1);
        if(!target.empty()){
            std::string target_path = std::filesystem::canonical("./" + target);
            C_pre_processor include_preproc(target_path, dmap);
            iom_map.insert(include_preproc.get_iom_map().begin(), iom_map.end());
            include_preproc.set_absolute_includes(allowed_absolute_includes);
            include_preproc.process_file();
            return include_preproc.get_preprocessed_file();
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


void C_pre_processor::set_absolute_includes(std::vector<std::string> list) {
    allowed_absolute_includes = std::move(list);
}

void C_pre_processor::substitute_defines() {

    std::string line;
    std::istringstream ss(working_content);
    std::ostringstream processed_file_ss;



    while (std::getline(ss,line)){
        std::string new_line = line;
        for(auto &item:*dmap){
           new_line = substitute_defines_in_line(new_line, item);
        }
        processed_file_ss << new_line << std::endl;
    }

    working_content = processed_file_ss.str();

}

std::string C_pre_processor::substitute_defines_in_line(std::string &line, const std::pair<std::string, std::shared_ptr<define>>& item) {

    std::string operating_line;
    std::vector<std::smatch> false_positives = {};

    std::vector<unsigned int> positions;
    std::vector<unsigned int> lengths;
    std::regex define_regex(item.first);
    for(std::sregex_iterator i = std::sregex_iterator(line.begin(), line.end(), define_regex);
    i != std::sregex_iterator(); ++i) {
        std::smatch m = *i;
        positions.push_back(m.position());
        lengths.push_back(m.length());
    }

    //USE POSITIONS AND LENGTHS
    unsigned int substring_start = 0;
    for(int i = 0; i<positions.size(); i++){
        std::string preceding_symbol = {line[positions[i]-1]};
        std::string following_symbol = {line[positions[i]+lengths[i]]};

        operating_line += line.substr(substring_start, positions[i]-substring_start);

        if(!(std::regex_match(preceding_symbol, std::regex("[a-zA-Z_]")) || std::regex_match(following_symbol, std::regex("[a-zA-Z_]"))) ){
            operating_line += item.second->get_content();
        } else{
            operating_line += item.first;
        }
        substring_start = positions[i]+lengths[i];
    }
    operating_line += line.substr(substring_start, line.size()-substring_start);
    return operating_line;
}
