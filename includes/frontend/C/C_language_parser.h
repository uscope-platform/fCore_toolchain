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

#ifndef FCORE_HAS_ASM_LANGUAGE_PARSER_H
#define FCORE_HAS_FILE_PARSER_H

#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <regex>
#include <gtest/gtest_prod.h>

#include "code_elements/code_element.hpp"
#include "C_Tree_visitor.hpp"
#include "C_ErrorHandling.hpp"
#include "C_pre_processor.h"

#include "antlr4-runtime.h"
#include "C_parser/C_grammarLexer.h"
#include "C_parser/C_grammarParser.h"


class C_language_parser{
    public:
    explicit C_language_parser(std::istream &stream);
    C_language_parser(std::istream &stream, std::shared_ptr<variable_map> new_varmap, std::shared_ptr<define_map> new_defmap);

    void construct_parser(std::istream &stream, std::shared_ptr<variable_map> &existing_varmap, const std::shared_ptr<define_map>& existing_defmap);
    void pre_processor(std::istream &stream, const std::shared_ptr<variable_map>& existing_varmap, const std::shared_ptr<define_map>& existing_defmap);

    unsigned int n_inputs() const {return n_inputs_;};
    unsigned int n_outputs() const {return n_outputs_;};
    unsigned int n_variables() const {return n_variables_;};

    ast_t AST;
    std::string error;

    private:

    FRIEND_TEST(cFrontend, preprocessor_decomment);
    FRIEND_TEST(cFrontend, preprocessor_pragma);


    unsigned int n_inputs_ = 0;
    unsigned int n_outputs_ = 0;
    unsigned int n_variables_ = 0;
    std::string preprocessed_content;
};


#endif //FCORE_HAS_ASM_LANGUAGE_PARSER_H
