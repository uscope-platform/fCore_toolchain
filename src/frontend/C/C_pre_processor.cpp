//
// Created by fils on 29/06/2021.
//


#include "frontend/C/C_pre_processor.h"

C_pre_processor::C_pre_processor(std::istream &file, std::shared_ptr<variable_map> varmap) {
    working_content = std::string((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    vmap = varmap;
    remove_comments();
    process_pragmas();
}

std::string  C_pre_processor::get_preprocessed_file() {
    return working_content;
}

void C_pre_processor::remove_comments() {
    std::string line;
    std::istringstream ss(working_content);
    std::ostringstream decommented_file;

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
            std::string tmp =  std::regex_replace(line, std::regex(multiline_start), "");
            decommented_file << tmp + "\n";
        } else if(!contain_multiline_start & contain_multiline_stop){
            in_muliline_comment = false;
            std::string tmp =  std::regex_replace(line, std::regex(multiline_stop), "");
            decommented_file << tmp + "\n";
        }else if(!(ignore_cond_1 | ignore_cond_2 | in_muliline_comment)){
            std::string tmp = std::regex_replace(line, std::regex(R"(\/\*(.*)\*\/)"), "");
            decommented_file << tmp + "\n";
        }
    }
    working_content = decommented_file.str();
}

void C_pre_processor::process_pragmas() {
    std::regex io_pragma_regex(R"(#pragma\s+(input|output)\s*\(\s?(.*),\s*r(\d*)\s*\))");
    std::istringstream ss(working_content);
    std::string line;
    std::smatch match;
    while (std::getline(ss,line)){
        if(std::regex_match( line,match,io_pragma_regex)){
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
    int i = 0;
}
