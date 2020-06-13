//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_FILE_PARSER_H
#define FCORE_HAS_FILE_PARSER_H

#include <string>
#include <vector>

#include "../code_elements/code_element.hpp"
#include "Tree_visitor.hpp"
#include "../code_elements/code_element.hpp"

#include "antlr4-runtime.h"
#include "../../include/fs_parser/fs_grammarParser.h"
#include "../../include/fs_parser/fs_grammarLexer.h"


class parser{
    public:
    explicit parser(const std::string& filename);
    parser(const std::string& filename, varmap_t &new_varmap);
    void construct_parser(const std::string &filename, varmap_t &existing_varmap);
    ast_t AST;
    varmap_t var_map;
};


#endif //FCORE_HAS_FILE_PARSER_H
