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
// limitations under the License.

#ifndef FCORE_TOOLCHAIN_C_LANGUAGE_PARSER_HPP
#define FCORE_TOOLCHAIN_C_LANGUAGE_PARSER_HPP

#include <string>
#include <vector>
#include <regex>

#include "C_Tree_visitor.hpp"
#include "C_ErrorHandling.hpp"
#include "C_pre_processor.hpp"

#include "antlr4-runtime.h"
#include "C_parser/C_grammarLexer.h"
#include "C_parser/C_grammarParser.h"

namespace fcore{

    class C_language_parser{
    public:
        explicit C_language_parser();
        C_language_parser(std::istream &file, std::shared_ptr<define_map> def_map);
        C_language_parser(const std::string &path, std::shared_ptr<define_map> def_map);

        void pre_process(const std::vector<std::string> &abs_includes);
        void parse(std::unordered_map<std::string, variable_class_t> dma_specs);
        std::shared_ptr<hl_code_block> AST;
        std::string error;

        std::vector<std::shared_ptr<hl_ast_node>> get_ext_decl(){return visitor.get_ext_decl();}
        std::vector<std::shared_ptr<hl_ast_node>> get_functions(){return visitor.get_functions();}
    private:

        C_Tree_visitor visitor;


        std::unique_ptr<C_pre_processor> preproc;
        std::shared_ptr<define_map> dmap;

        std::string preprocessed_content;
    };
}


#endif //FCORE_TOOLCHAIN_C_LANGUAGE_PARSER_HPP
