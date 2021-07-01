
// Generated from /home/fils/git/fCore_has/src/frontend/C_grammar.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"


namespace C_parser {


class  C_grammarLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, Case = 6, Char = 7, 
    Const = 8, Else = 9, Float = 10, For = 11, If = 12, Int = 13, Long = 14, 
    Return = 15, Short = 16, Signed = 17, Typedef = 18, Unsigned = 19, Void = 20, 
    Volatile = 21, While = 22, LeftParen = 23, RightParen = 24, LeftBracket = 25, 
    RightBracket = 26, LeftBrace = 27, RightBrace = 28, Less = 29, LessEqual = 30, 
    Greater = 31, GreaterEqual = 32, LeftShift = 33, RightShift = 34, Plus = 35, 
    PlusPlus = 36, Minus = 37, MinusMinus = 38, Star = 39, Div = 40, Mod = 41, 
    And = 42, Or = 43, AndAnd = 44, OrOr = 45, Caret = 46, Not = 47, Tilde = 48, 
    Question = 49, Colon = 50, Semi = 51, Comma = 52, Assign = 53, StarAssign = 54, 
    DivAssign = 55, ModAssign = 56, PlusAssign = 57, MinusAssign = 58, LeftShiftAssign = 59, 
    RightShiftAssign = 60, AndAssign = 61, XorAssign = 62, OrAssign = 63, 
    Equal = 64, NotEqual = 65, Arrow = 66, Dot = 67, Ellipsis = 68, Identifier = 69, 
    IntegerConstant = 70, FloatingConstant = 71, DigitSequence = 72, CharacterConstant = 73, 
    StringLiteral = 74, ComplexDefine = 75, IncludeDirective = 76, AsmBlock = 77, 
    LineAfterPreprocessing = 78, LineDirective = 79, PragmaDirective = 80, 
    Whitespace = 81, Newline = 82, BlockComment = 83, LineComment = 84
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
