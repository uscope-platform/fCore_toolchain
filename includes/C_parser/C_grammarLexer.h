
// Generated from /home/fils/git/fCore_has/src/frontend/C_grammar.g4 by ANTLR 4.9.1

#pragma once


#include "antlr4-runtime.h"


namespace C_parser {


class  C_grammarLexer : public antlr4::Lexer {
public:
  enum {
    Auto = 1, Break = 2, Case = 3, Char = 4, Const = 5, Continue = 6, Default = 7, 
    Do = 8, Double = 9, Else = 10, Enum = 11, Extern = 12, Float = 13, For = 14, 
    Goto = 15, If = 16, Inline = 17, Int = 18, Long = 19, Register = 20, 
    Restrict = 21, Return = 22, Short = 23, Signed = 24, Static = 25, Struct = 26, 
    Switch = 27, Typedef = 28, Unsigned = 29, Void = 30, Volatile = 31, 
    While = 32, LeftParen = 33, RightParen = 34, LeftBracket = 35, RightBracket = 36, 
    LeftBrace = 37, RightBrace = 38, Less = 39, LessEqual = 40, Greater = 41, 
    GreaterEqual = 42, LeftShift = 43, RightShift = 44, Plus = 45, PlusPlus = 46, 
    Minus = 47, MinusMinus = 48, Star = 49, Div = 50, Mod = 51, And = 52, 
    Or = 53, AndAnd = 54, OrOr = 55, Caret = 56, Not = 57, Tilde = 58, Question = 59, 
    Colon = 60, Semi = 61, Comma = 62, Assign = 63, StarAssign = 64, DivAssign = 65, 
    ModAssign = 66, PlusAssign = 67, MinusAssign = 68, LeftShiftAssign = 69, 
    RightShiftAssign = 70, AndAssign = 71, XorAssign = 72, OrAssign = 73, 
    Equal = 74, NotEqual = 75, Arrow = 76, Dot = 77, Ellipsis = 78, Identifier = 79, 
    Constant = 80, DigitSequence = 81, StringLiteral = 82, ComplexDefine = 83, 
    IncludeDirective = 84, AsmBlock = 85, LineAfterPreprocessing = 86, LineDirective = 87, 
    PragmaDirective = 88, Whitespace = 89, Newline = 90, BlockComment = 91, 
    LineComment = 92
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
