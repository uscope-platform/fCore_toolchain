// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.29/06/2021.
//


#include "frontend/C/C_pre_processor.hpp"

#include <utility>

namespace fcore{

    C_pre_processor::C_pre_processor(std::istream &stream, std::shared_ptr<define_map> &defmap) {
        working_content = std::string((std::istreambuf_iterator<char>(stream)),std::istreambuf_iterator<char>());
        dmap = defmap;
    }


    C_pre_processor::C_pre_processor(const std::string &path, std::shared_ptr<define_map> &defmap) {
        std::ifstream file(path);
        working_content = std::string((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
        dmap = defmap;
    }

    std::string  C_pre_processor::get_preprocessed_file() {
        return working_content;
    }

    result<void> C_pre_processor::process_file() {
        std::string line;
        std::string decommented_line;
        std::istringstream ss(working_content);
        std::ostringstream processed_file_ss;

        bool in_muliline_comment = false;

        while (std::getline(ss,line)){

            if(line.empty() || line.starts_with("//")) continue;

            bool can_be_multiline_start = line.find("/*") != std::string::npos;
            bool can_be_multiline_stop = line.find("*/") != std::string::npos;

            bool skip_line = false;
            if(can_be_multiline_start || can_be_multiline_stop){

                std::regex multiline_start("\\/\\*(.*)");
                std::regex multiline_stop("(.*)\\*\\/");

                bool contain_multiline_start = std::regex_search(line, multiline_start);
                bool contain_multiline_stop = std::regex_search(line, multiline_stop);
                if(contain_multiline_start & !contain_multiline_stop){
                    in_muliline_comment = true;
                    decommented_line =  std::regex_replace(line, std::regex(multiline_start), "");
                } else if(!contain_multiline_start & contain_multiline_stop){
                    in_muliline_comment = false;
                    decommented_line =  std::regex_replace(line, std::regex(multiline_stop), "");
                }else if(!in_muliline_comment){
                    decommented_line= std::regex_replace(line, std::regex(R"(\/\*(.*)\*\/)"), "");
                }else {
                    continue;
                }
            } else {
                decommented_line = line;
            }

            skip_line |= process_define(decommented_line);

            auto rel_include = process_rel_includes(decommented_line);
            if(!rel_include) return fail(std::move(rel_include).error());
            auto abs_include = process_abs_includes(decommented_line);
            if(!abs_include) return fail(std::move(abs_include).error());
            const std::string rel_include_text = rel_include.value();
            const std::string abs_include_text = abs_include.value();

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
        return {};
    }

    bool C_pre_processor::process_define(const std::string& line) {
        bool line_contains_str = false;

        if(line.find('#') != std::string::npos) {
            std::regex define_regex(R"(#define\s+([A-Za-z0-9_]*)\s+(.*))");
            std::smatch match;
            if(std::regex_search( line,match,define_regex)){
                std::string name = match.str(1);
                std::string value = match.str(2);
                std::shared_ptr<define> def = std::make_shared<define>(0, name, value);
                dmap->insert(name, def);
                line_contains_str = true;
            }
        }

        return line_contains_str;
    }

    result<std::string> C_pre_processor::process_rel_includes(const std::string& line) {

        if(line.find('#') != std::string::npos) {
            std::regex rel_include_regex(R"(#include\s*\"(.*)\")");
            std::smatch match;
            if(std::regex_search( line,match,rel_include_regex)){
                std::string target = match.str(1);
                if(!target.empty()){
                    std::error_code ec;
                    std::string target_path = std::filesystem::canonical("./" + target, ec).string();
                    if(ec){
                        return fail(error_code::preprocessor_error,
                                    "included file: " + target + " could not be resolved: " + ec.message());
                    }
                    C_pre_processor include_preproc(target_path, dmap);
                    include_preproc.set_absolute_includes(allowed_absolute_includes);
                    auto processed = include_preproc.process_file();
                    if(!processed){
                        return fail(std::move(processed).error().with_context("processing included file " + target));
                    }
                    return include_preproc.get_preprocessed_file();
                }
            }
        }

        return "";
    }

    result<std::string> C_pre_processor::process_abs_includes(const std::string &line) {
        if(line.find('#') != std::string::npos) {
            std::regex abs_include_regex(R"(#include\s*<(.*)>)");
            std::smatch match;
            if (std::regex_search(line, match, abs_include_regex)) {
                std::string target = match.str(1);
                if (!target.empty()) {
                    if (std::find(allowed_absolute_includes.begin(), allowed_absolute_includes.end(), target) !=
                        allowed_absolute_includes.end()) {
                        //TODO: implement absolute includes
                    } else {
                        return fail(error_code::preprocessor_error, "included file: " + target + " not supported");
                    }
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
        for(uint32_t i = 0; i<positions.size(); i++){
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
}