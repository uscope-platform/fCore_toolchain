
// Generated from /home/filssavi/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace C_parser {


class  C_grammarLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, Case = 3, Char = 4, Const = 5, Else = 6, Float = 7, 
    For = 8, If = 9, Int = 10, Long = 11, Return = 12, Short = 13, Signed = 14, 
    Typedef = 15, Unsigned = 16, Void = 17, Volatile = 18, While = 19, LeftParen = 20, 
    RightParen = 21, LeftBracket = 22, RightBracket = 23, LeftBrace = 24, 
    RightBrace = 25, Less = 26, LessEqual = 27, Greater = 28, GreaterEqual = 29, 
    LeftShift = 30, RightShift = 31, Plus = 32, PlusPlus = 33, Minus = 34, 
    MinusMinus = 35, Star = 36, Div = 37, Mod = 38, And = 39, Or = 40, AndAnd = 41, 
    OrOr = 42, Caret = 43, Not = 44, Tilde = 45, Question = 46, Colon = 47, 
    Semi = 48, Comma = 49, Assign = 50, StarAssign = 51, DivAssign = 52, 
    ModAssign = 53, PlusAssign = 54, MinusAssign = 55, LeftShiftAssign = 56, 
    RightShiftAssign = 57, AndAssign = 58, XorAssign = 59, OrAssign = 60, 
    Equal = 61, NotEqual = 62, Arrow = 63, Dot = 64, Ellipsis = 65, Identifier = 66, 
    IntegerConstant = 67, FloatingConstant = 68, DigitSequence = 69, CharacterConstant = 70, 
    StringLiteral = 71, ComplexDefine = 72, IncludeDirective = 73, AsmBlock = 74, 
    LineAfterPreprocessing = 75, LineDirective = 76, PragmaDirective = 77, 
    Whitespace = 78, Newline = 79, BlockComment = 80, LineComment = 81
  };

  explicit C_grammarLexer(antlr4::CharStream *input);

  ~C_grammarLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace C_parser
