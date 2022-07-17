
// Generated from /home/fils/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"


namespace C_parser {


class  C_grammarLexer : public antlr4::Lexer {
public:
  enum {
    Case = 1, Char = 2, Const = 3, Else = 4, Float = 5, For = 6, If = 7, 
    Int = 8, Long = 9, Return = 10, Short = 11, Signed = 12, Typedef = 13, 
    Unsigned = 14, Void = 15, Volatile = 16, While = 17, LeftParen = 18, 
    RightParen = 19, LeftBracket = 20, RightBracket = 21, LeftBrace = 22, 
    RightBrace = 23, Less = 24, LessEqual = 25, Greater = 26, GreaterEqual = 27, 
    LeftShift = 28, RightShift = 29, Plus = 30, PlusPlus = 31, Minus = 32, 
    MinusMinus = 33, Star = 34, Div = 35, Mod = 36, And = 37, Or = 38, AndAnd = 39, 
    OrOr = 40, Caret = 41, Not = 42, Tilde = 43, Question = 44, Colon = 45, 
    Semi = 46, Comma = 47, Assign = 48, StarAssign = 49, DivAssign = 50, 
    ModAssign = 51, PlusAssign = 52, MinusAssign = 53, LeftShiftAssign = 54, 
    RightShiftAssign = 55, AndAssign = 56, XorAssign = 57, OrAssign = 58, 
    Equal = 59, NotEqual = 60, Arrow = 61, Dot = 62, Ellipsis = 63, Identifier = 64, 
    IntegerConstant = 65, FloatingConstant = 66, DigitSequence = 67, CharacterConstant = 68, 
    StringLiteral = 69, ComplexDefine = 70, IncludeDirective = 71, AsmBlock = 72, 
    LineAfterPreprocessing = 73, LineDirective = 74, PragmaDirective = 75, 
    Whitespace = 76, Newline = 77, BlockComment = 78, LineComment = 79
  };

  explicit C_grammarLexer(antlr4::CharStream *input);
  ~C_grammarLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace C_parser
