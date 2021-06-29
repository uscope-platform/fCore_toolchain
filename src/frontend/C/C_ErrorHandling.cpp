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

#include "frontend/C/C_ErrorHandling.hpp"

void C_ErrorHandling::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                                size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
    throw std::runtime_error(msg);
}

void C_ErrorHandling::reportAmbiguity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                    size_t stopIndex, bool exact, const antlrcpp::BitSet &ambigAlts,
                                    antlr4::atn::ATNConfigSet *configs) {
    int i = 0;
    i++;
}

void
C_ErrorHandling::reportAttemptingFullContext(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                           size_t stopIndex, const antlrcpp::BitSet &conflictingAlts,
                                           antlr4::atn::ATNConfigSet *configs) {
    int i = 0;
    i++;
}

void C_ErrorHandling::reportContextSensitivity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                             size_t stopIndex, size_t prediction, antlr4::atn::ATNConfigSet *configs) {
    int i = 0;
    i++;
}
