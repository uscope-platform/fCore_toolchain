
// Generated from /home/fils/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace C_parser {


class  C_grammarLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, Case = 2, Char = 3, Const = 4, Else = 5, Float = 6, For = 7, 
    If = 8, Int = 9, Long = 10, Return = 11, Short = 12, Signed = 13, Typedef = 14, 
    Unsigned = 15, Void = 16, Volatile = 17, While = 18, LeftParen = 19, 
    RightParen = 20, LeftBracket = 21, RightBracket = 22, LeftBrace = 23, 
    RightBrace = 24, Less = 25, LessEqual = 26, Greater = 27, GreaterEqual = 28, 
    LeftShift = 29, RightShift = 30, Plus = 31, PlusPlus = 32, Minus = 33, 
    MinusMinus = 34, Star = 35, Div = 36, Mod = 37, And = 38, Or = 39, AndAnd = 40, 
    OrOr = 41, Caret = 42, Not = 43, Tilde = 44, Question = 45, Colon = 46, 
    Semi = 47, Comma = 48, Assign = 49, StarAssign = 50, DivAssign = 51, 
    ModAssign = 52, PlusAssign = 53, MinusAssign = 54, LeftShiftAssign = 55, 
    RightShiftAssign = 56, AndAssign = 57, XorAssign = 58, OrAssign = 59, 
    Equal = 60, NotEqual = 61, Arrow = 62, Dot = 63, Ellipsis = 64, Identifier = 65, 
    IntegerConstant = 66, FloatingConstant = 67, DigitSequence = 68, CharacterConstant = 69, 
    StringLiteral = 70, ComplexDefine = 71, IncludeDirective = 72, AsmBlock = 73, 
    LineAfterPreprocessing = 74, LineDirective = 75, PragmaDirective = 76, 
    Whitespace = 77, Newline = 78, BlockComment = 79, LineComment = 80
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
