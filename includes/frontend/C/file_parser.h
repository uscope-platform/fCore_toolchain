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

#ifndef FCORE_HAS_FILE_PARSER_H
#define FCORE_HAS_FILE_PARSER_H

#include <string>
#include <sstream>
#include <vector>
#include <utility>

#include "code_elements/code_element.hpp"
#include "Tree_visitor.hpp"
#include "code_elements/code_element.hpp"
#include "ErrorHandling.hpp"

#include "antlr4-runtime.h"
#include "C_parser/C_grammarLexer.h"
#include "C_parser/C_grammarParser.h"

class c_language_parser{
    public:
    explicit c_language_parser(std::istream &stream);
    c_language_parser(std::istream &stream, std::shared_ptr<variable_map> new_varmap);
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
