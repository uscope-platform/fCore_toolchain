//
// Created by fils on 24/08/2020.
//

#include "ErrorHandling.hpp"

void ErrorHandling::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                                size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
    throw std::runtime_error(msg);
}

void ErrorHandling::reportAmbiguity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                    size_t stopIndex, bool exact, const antlrcpp::BitSet &ambigAlts,
                                    antlr4::atn::ATNConfigSet *configs) {
    int i = 0;
    i++;
}

void
ErrorHandling::reportAttemptingFullContext(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                           size_t stopIndex, const antlrcpp::BitSet &conflictingAlts,
                                           antlr4::atn::ATNConfigSet *configs) {
    int i = 0;
    i++;
}

void ErrorHandling::reportContextSensitivity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, size_t startIndex,
                                             size_t stopIndex, size_t prediction, antlr4::atn::ATNConfigSet *configs) {
    int i = 0;
    i++;
}
