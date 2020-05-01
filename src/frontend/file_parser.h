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


std::shared_ptr<code_element> parse(const std::string& filename);

#endif //FCORE_HAS_FILE_PARSER_H
