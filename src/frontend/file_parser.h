//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_FILE_PARSER_H
#define FCORE_HAS_FILE_PARSER_H

#include <string>
#include <sstream>
#include <vector>

#include "../code_elements/code_element.hpp"
#include "Tree_visitor.hpp"
#include "../code_elements/code_element.hpp"
#include "ErrorHandling.hpp"

#include "antlr4-runtime.h"
#include "../../include/fs_parser/fs_grammarParser.h"
#include "../../include/fs_parser/fs_grammarLexer.h"


class parser{
    public:
    explicit parser(std::istream &stream);
    parser(std::istream &stream, std::shared_ptr<variable_map> new_varmap);
    void construct_parser(std::istream &stream, std::shared_ptr<variable_map> existing_varmap);

    unsigned int n_inputs() const {return n_inputs_;};
    unsigned int n_outputs() const {return n_outputs_;};
    unsigned int n_variables() const {return n_variables_;};

    ast_t AST;
    varmap_t var_map;

    std::string error;


    private:

    unsigned int n_inputs_ = 0;
    unsigned int n_outputs_ = 0;
    unsigned int n_variables_ = 0;
};


#endif //FCORE_HAS_FILE_PARSER_H
