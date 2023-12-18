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

#include "frontend/C/C_ErrorHandling.hpp"

void C_ErrorHandling::syntaxError(antlr4::Recognizer *, antlr4::Token *, size_t ,
                                size_t , const std::string &msg, std::exception_ptr ) {
    throw std::runtime_error(msg);
}

void C_ErrorHandling::reportAmbiguity(antlr4::Parser *, const antlr4::dfa::DFA &, size_t ,
                                    size_t , bool , const antlrcpp::BitSet &,
                                    antlr4::atn::ATNConfigSet *) {

}

void
C_ErrorHandling::reportAttemptingFullContext(antlr4::Parser *, const antlr4::dfa::DFA &, size_t ,
                                           size_t , const antlrcpp::BitSet &,
                                           antlr4::atn::ATNConfigSet *) {

}

void C_ErrorHandling::reportContextSensitivity(antlr4::Parser *, const antlr4::dfa::DFA &, size_t ,
                                             size_t , size_t , antlr4::atn::ATNConfigSet *) {

}
