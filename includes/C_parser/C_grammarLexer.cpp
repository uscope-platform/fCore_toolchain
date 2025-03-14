
// Generated from /home/filssavi/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.13.2


#include "C_grammarLexer.h"


using namespace antlr4;

using namespace C_parser;


using namespace antlr4;

namespace {

struct C_grammarLexerStaticData final {
  C_grammarLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  C_grammarLexerStaticData(const C_grammarLexerStaticData&) = delete;
  C_grammarLexerStaticData(C_grammarLexerStaticData&&) = delete;
  C_grammarLexerStaticData& operator=(const C_grammarLexerStaticData&) = delete;
  C_grammarLexerStaticData& operator=(C_grammarLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag c_grammarlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<C_grammarLexerStaticData> c_grammarlexerLexerStaticData = nullptr;

void c_grammarlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (c_grammarlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(c_grammarlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<C_grammarLexerStaticData>(
    std::vector<std::string>{
      "T__0", "Case", "Char", "Const", "Else", "Float", "For", "If", "Int", 
      "Long", "Return", "Short", "Signed", "Typedef", "Unsigned", "Void", 
      "Volatile", "While", "LeftParen", "RightParen", "LeftBracket", "RightBracket", 
      "LeftBrace", "RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", 
      "LeftShift", "RightShift", "Plus", "PlusPlus", "Minus", "MinusMinus", 
      "Star", "Div", "Mod", "And", "Or", "AndAnd", "OrOr", "Caret", "Not", 
      "Tilde", "Question", "Colon", "Semi", "Comma", "Assign", "StarAssign", 
      "DivAssign", "ModAssign", "PlusAssign", "MinusAssign", "LeftShiftAssign", 
      "RightShiftAssign", "AndAssign", "XorAssign", "OrAssign", "Equal", 
      "NotEqual", "Arrow", "Dot", "Ellipsis", "Identifier", "IdentifierNondigit", 
      "Nondigit", "Digit", "UniversalCharacterName", "HexQuad", "IntegerConstant", 
      "BinaryConstant", "DecimalConstant", "OctalConstant", "HexadecimalConstant", 
      "HexadecimalPrefix", "NonzeroDigit", "OctalDigit", "HexadecimalDigit", 
      "IntegerSuffix", "UnsignedSuffix", "LongSuffix", "LongLongSuffix", 
      "FloatingConstant", "DecimalFloatingConstant", "HexadecimalFloatingConstant", 
      "FractionalConstant", "ExponentPart", "Sign", "DigitSequence", "HexadecimalFractionalConstant", 
      "BinaryExponentPart", "HexadecimalDigitSequence", "FloatingSuffix", 
      "CharacterConstant", "CCharSequence", "CChar", "EscapeSequence", "SimpleEscapeSequence", 
      "OctalEscapeSequence", "HexadecimalEscapeSequence", "StringLiteral", 
      "EncodingPrefix", "SCharSequence", "SChar", "ComplexDefine", "IncludeDirective", 
      "AsmBlock", "LineAfterPreprocessing", "LineDirective", "PragmaDirective", 
      "Whitespace", "Newline", "BlockComment", "LineComment"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'struct'", "'case'", "'char'", "'const'", "'else'", "'float'", 
      "'for'", "'if'", "'int'", "'long'", "'return'", "'short'", "'signed'", 
      "'typedef'", "'unsigned'", "'void'", "'volatile'", "'while'", "'('", 
      "')'", "'['", "']'", "'{'", "'}'", "'<'", "'<='", "'>'", "'>='", "'<<'", 
      "'>>'", "'+'", "'++'", "'-'", "'--'", "'*'", "'/'", "'%'", "'&'", 
      "'|'", "'&&'", "'||'", "'^'", "'!'", "'~'", "'\\u003F'", "':'", "';'", 
      "','", "'='", "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", 
      "'&='", "'^='", "'|='", "'=='", "'!='", "'->'", "'.'", "'...'"
    },
    std::vector<std::string>{
      "", "", "Case", "Char", "Const", "Else", "Float", "For", "If", "Int", 
      "Long", "Return", "Short", "Signed", "Typedef", "Unsigned", "Void", 
      "Volatile", "While", "LeftParen", "RightParen", "LeftBracket", "RightBracket", 
      "LeftBrace", "RightBrace", "Less", "LessEqual", "Greater", "GreaterEqual", 
      "LeftShift", "RightShift", "Plus", "PlusPlus", "Minus", "MinusMinus", 
      "Star", "Div", "Mod", "And", "Or", "AndAnd", "OrOr", "Caret", "Not", 
      "Tilde", "Question", "Colon", "Semi", "Comma", "Assign", "StarAssign", 
      "DivAssign", "ModAssign", "PlusAssign", "MinusAssign", "LeftShiftAssign", 
      "RightShiftAssign", "AndAssign", "XorAssign", "OrAssign", "Equal", 
      "NotEqual", "Arrow", "Dot", "Ellipsis", "Identifier", "IntegerConstant", 
      "FloatingConstant", "DigitSequence", "CharacterConstant", "StringLiteral", 
      "ComplexDefine", "IncludeDirective", "AsmBlock", "LineAfterPreprocessing", 
      "LineDirective", "PragmaDirective", "Whitespace", "Newline", "BlockComment", 
      "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,80,903,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,
  	7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,
  	7,56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,
  	7,63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,
  	7,70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,
  	7,77,2,78,7,78,2,79,7,79,2,80,7,80,2,81,7,81,2,82,7,82,2,83,7,83,2,84,
  	7,84,2,85,7,85,2,86,7,86,2,87,7,87,2,88,7,88,2,89,7,89,2,90,7,90,2,91,
  	7,91,2,92,7,92,2,93,7,93,2,94,7,94,2,95,7,95,2,96,7,96,2,97,7,97,2,98,
  	7,98,2,99,7,99,2,100,7,100,2,101,7,101,2,102,7,102,2,103,7,103,2,104,
  	7,104,2,105,7,105,2,106,7,106,2,107,7,107,2,108,7,108,2,109,7,109,2,110,
  	7,110,2,111,7,111,2,112,7,112,2,113,7,113,2,114,7,114,1,0,1,0,1,0,1,0,
  	1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,
  	1,7,1,7,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,18,1,18,1,19,1,19,
  	1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,1,25,1,26,
  	1,26,1,27,1,27,1,27,1,28,1,28,1,28,1,29,1,29,1,29,1,30,1,30,1,31,1,31,
  	1,31,1,32,1,32,1,33,1,33,1,33,1,34,1,34,1,35,1,35,1,36,1,36,1,37,1,37,
  	1,38,1,38,1,39,1,39,1,39,1,40,1,40,1,40,1,41,1,41,1,42,1,42,1,43,1,43,
  	1,44,1,44,1,45,1,45,1,46,1,46,1,47,1,47,1,48,1,48,1,49,1,49,1,49,1,50,
  	1,50,1,50,1,51,1,51,1,51,1,52,1,52,1,52,1,53,1,53,1,53,1,54,1,54,1,54,
  	1,54,1,55,1,55,1,55,1,55,1,56,1,56,1,56,1,57,1,57,1,57,1,58,1,58,1,58,
  	1,59,1,59,1,59,1,60,1,60,1,60,1,61,1,61,1,61,1,62,1,62,1,63,1,63,1,63,
  	1,63,1,64,1,64,1,64,5,64,459,8,64,10,64,12,64,462,9,64,1,65,1,65,3,65,
  	466,8,65,1,66,1,66,1,67,1,67,1,68,1,68,1,68,1,68,1,68,1,68,1,68,1,68,
  	1,68,1,68,3,68,482,8,68,1,69,1,69,1,69,1,69,1,69,1,70,1,70,3,70,491,8,
  	70,1,70,1,70,3,70,495,8,70,1,70,1,70,3,70,499,8,70,1,70,3,70,502,8,70,
  	1,71,1,71,1,71,4,71,507,8,71,11,71,12,71,508,1,72,1,72,5,72,513,8,72,
  	10,72,12,72,516,9,72,1,73,1,73,5,73,520,8,73,10,73,12,73,523,9,73,1,74,
  	1,74,4,74,527,8,74,11,74,12,74,528,1,75,1,75,1,75,1,76,1,76,1,77,1,77,
  	1,78,1,78,1,79,1,79,3,79,542,8,79,1,79,1,79,1,79,1,79,1,79,3,79,549,8,
  	79,1,79,1,79,3,79,553,8,79,3,79,555,8,79,1,80,1,80,1,81,1,81,1,82,1,82,
  	1,82,1,82,3,82,565,8,82,1,83,1,83,3,83,569,8,83,1,84,1,84,3,84,573,8,
  	84,1,84,3,84,576,8,84,1,84,1,84,1,84,3,84,581,8,84,3,84,583,8,84,1,85,
  	1,85,1,85,3,85,588,8,85,1,85,1,85,3,85,592,8,85,1,86,3,86,595,8,86,1,
  	86,1,86,1,86,1,86,1,86,3,86,602,8,86,1,87,1,87,3,87,606,8,87,1,87,1,87,
  	1,88,1,88,1,89,4,89,613,8,89,11,89,12,89,614,1,90,3,90,618,8,90,1,90,
  	1,90,1,90,1,90,1,90,3,90,625,8,90,1,91,1,91,3,91,629,8,91,1,91,1,91,1,
  	92,4,92,634,8,92,11,92,12,92,635,1,93,1,93,1,94,1,94,1,94,1,94,1,94,1,
  	94,1,94,1,94,1,94,1,94,1,94,1,94,1,94,1,94,1,94,1,94,1,94,1,94,1,94,1,
  	94,1,94,1,94,3,94,662,8,94,1,95,4,95,665,8,95,11,95,12,95,666,1,96,1,
  	96,3,96,671,8,96,1,97,1,97,1,97,1,97,3,97,677,8,97,1,98,1,98,1,98,1,99,
  	1,99,1,99,3,99,685,8,99,1,99,3,99,688,8,99,1,100,1,100,1,100,1,100,4,
  	100,694,8,100,11,100,12,100,695,1,101,3,101,699,8,101,1,101,1,101,3,101,
  	703,8,101,1,101,1,101,1,102,1,102,1,102,3,102,710,8,102,1,103,4,103,713,
  	8,103,11,103,12,103,714,1,104,1,104,1,104,1,104,1,104,1,104,1,104,3,104,
  	724,8,104,1,105,1,105,3,105,728,8,105,1,105,1,105,1,105,1,105,1,105,1,
  	105,1,105,1,105,5,105,738,8,105,10,105,12,105,741,9,105,1,105,1,105,1,
  	106,1,106,3,106,747,8,106,1,106,1,106,1,106,1,106,1,106,1,106,1,106,1,
  	106,1,106,3,106,758,8,106,1,106,1,106,5,106,762,8,106,10,106,12,106,765,
  	9,106,1,106,1,106,1,106,5,106,770,8,106,10,106,12,106,773,9,106,1,106,
  	3,106,776,8,106,1,106,3,106,779,8,106,1,106,1,106,1,106,1,106,1,107,1,
  	107,1,107,1,107,1,107,5,107,790,8,107,10,107,12,107,793,9,107,1,107,1,
  	107,5,107,797,8,107,10,107,12,107,800,9,107,1,107,1,107,1,107,1,107,1,
  	108,1,108,1,108,1,108,1,108,1,108,1,108,5,108,813,8,108,10,108,12,108,
  	816,9,108,1,108,5,108,819,8,108,10,108,12,108,822,9,108,1,108,1,108,1,
  	109,1,109,3,109,828,8,109,1,109,1,109,3,109,832,8,109,1,109,1,109,5,109,
  	836,8,109,10,109,12,109,839,9,109,1,109,1,109,1,110,1,110,3,110,845,8,
  	110,1,110,1,110,1,110,1,110,1,110,1,110,1,110,1,110,1,110,5,110,856,8,
  	110,10,110,12,110,859,9,110,1,110,1,110,1,111,4,111,864,8,111,11,111,
  	12,111,865,1,111,1,111,1,112,1,112,3,112,872,8,112,1,112,3,112,875,8,
  	112,1,112,1,112,1,113,1,113,1,113,1,113,5,113,883,8,113,10,113,12,113,
  	886,9,113,1,113,1,113,1,113,1,113,1,113,1,114,1,114,1,114,1,114,5,114,
  	897,8,114,10,114,12,114,900,9,114,1,114,1,114,1,884,0,115,1,1,3,2,5,3,
  	7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,
  	33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,
  	28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,75,38,77,39,
  	79,40,81,41,83,42,85,43,87,44,89,45,91,46,93,47,95,48,97,49,99,50,101,
  	51,103,52,105,53,107,54,109,55,111,56,113,57,115,58,117,59,119,60,121,
  	61,123,62,125,63,127,64,129,65,131,0,133,0,135,0,137,0,139,0,141,66,143,
  	0,145,0,147,0,149,0,151,0,153,0,155,0,157,0,159,0,161,0,163,0,165,0,167,
  	67,169,0,171,0,173,0,175,0,177,0,179,68,181,0,183,0,185,0,187,0,189,69,
  	191,0,193,0,195,0,197,0,199,0,201,0,203,70,205,0,207,0,209,0,211,71,213,
  	72,215,73,217,74,219,75,221,76,223,77,225,78,227,79,229,80,1,0,23,3,0,
  	65,90,95,95,97,122,1,0,48,57,2,0,66,66,98,98,1,0,48,49,2,0,88,88,120,
  	120,1,0,49,57,1,0,48,55,3,0,48,57,65,70,97,102,2,0,85,85,117,117,2,0,
  	76,76,108,108,2,0,69,69,101,101,2,0,43,43,45,45,2,0,80,80,112,112,4,0,
  	70,70,76,76,102,102,108,108,4,0,10,10,13,13,39,39,92,92,10,0,34,34,39,
  	39,63,63,92,92,97,98,102,102,110,110,114,114,116,116,118,118,3,0,76,76,
  	85,85,117,117,4,0,10,10,13,13,34,34,92,92,3,0,10,10,13,13,35,35,2,0,10,
  	10,13,13,1,0,123,123,1,0,125,125,2,0,9,9,32,32,943,0,1,1,0,0,0,0,3,1,
  	0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,
  	15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,
  	0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,
  	0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,
  	47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,
  	0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,
  	0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,
  	79,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,
  	0,0,0,0,91,1,0,0,0,0,93,1,0,0,0,0,95,1,0,0,0,0,97,1,0,0,0,0,99,1,0,0,
  	0,0,101,1,0,0,0,0,103,1,0,0,0,0,105,1,0,0,0,0,107,1,0,0,0,0,109,1,0,0,
  	0,0,111,1,0,0,0,0,113,1,0,0,0,0,115,1,0,0,0,0,117,1,0,0,0,0,119,1,0,0,
  	0,0,121,1,0,0,0,0,123,1,0,0,0,0,125,1,0,0,0,0,127,1,0,0,0,0,129,1,0,0,
  	0,0,141,1,0,0,0,0,167,1,0,0,0,0,179,1,0,0,0,0,189,1,0,0,0,0,203,1,0,0,
  	0,0,211,1,0,0,0,0,213,1,0,0,0,0,215,1,0,0,0,0,217,1,0,0,0,0,219,1,0,0,
  	0,0,221,1,0,0,0,0,223,1,0,0,0,0,225,1,0,0,0,0,227,1,0,0,0,0,229,1,0,0,
  	0,1,231,1,0,0,0,3,238,1,0,0,0,5,243,1,0,0,0,7,248,1,0,0,0,9,254,1,0,0,
  	0,11,259,1,0,0,0,13,265,1,0,0,0,15,269,1,0,0,0,17,272,1,0,0,0,19,276,
  	1,0,0,0,21,281,1,0,0,0,23,288,1,0,0,0,25,294,1,0,0,0,27,301,1,0,0,0,29,
  	309,1,0,0,0,31,318,1,0,0,0,33,323,1,0,0,0,35,332,1,0,0,0,37,338,1,0,0,
  	0,39,340,1,0,0,0,41,342,1,0,0,0,43,344,1,0,0,0,45,346,1,0,0,0,47,348,
  	1,0,0,0,49,350,1,0,0,0,51,352,1,0,0,0,53,355,1,0,0,0,55,357,1,0,0,0,57,
  	360,1,0,0,0,59,363,1,0,0,0,61,366,1,0,0,0,63,368,1,0,0,0,65,371,1,0,0,
  	0,67,373,1,0,0,0,69,376,1,0,0,0,71,378,1,0,0,0,73,380,1,0,0,0,75,382,
  	1,0,0,0,77,384,1,0,0,0,79,386,1,0,0,0,81,389,1,0,0,0,83,392,1,0,0,0,85,
  	394,1,0,0,0,87,396,1,0,0,0,89,398,1,0,0,0,91,400,1,0,0,0,93,402,1,0,0,
  	0,95,404,1,0,0,0,97,406,1,0,0,0,99,408,1,0,0,0,101,411,1,0,0,0,103,414,
  	1,0,0,0,105,417,1,0,0,0,107,420,1,0,0,0,109,423,1,0,0,0,111,427,1,0,0,
  	0,113,431,1,0,0,0,115,434,1,0,0,0,117,437,1,0,0,0,119,440,1,0,0,0,121,
  	443,1,0,0,0,123,446,1,0,0,0,125,449,1,0,0,0,127,451,1,0,0,0,129,455,1,
  	0,0,0,131,465,1,0,0,0,133,467,1,0,0,0,135,469,1,0,0,0,137,481,1,0,0,0,
  	139,483,1,0,0,0,141,501,1,0,0,0,143,503,1,0,0,0,145,510,1,0,0,0,147,517,
  	1,0,0,0,149,524,1,0,0,0,151,530,1,0,0,0,153,533,1,0,0,0,155,535,1,0,0,
  	0,157,537,1,0,0,0,159,554,1,0,0,0,161,556,1,0,0,0,163,558,1,0,0,0,165,
  	564,1,0,0,0,167,568,1,0,0,0,169,582,1,0,0,0,171,584,1,0,0,0,173,601,1,
  	0,0,0,175,603,1,0,0,0,177,609,1,0,0,0,179,612,1,0,0,0,181,624,1,0,0,0,
  	183,626,1,0,0,0,185,633,1,0,0,0,187,637,1,0,0,0,189,661,1,0,0,0,191,664,
  	1,0,0,0,193,670,1,0,0,0,195,676,1,0,0,0,197,678,1,0,0,0,199,681,1,0,0,
  	0,201,689,1,0,0,0,203,698,1,0,0,0,205,709,1,0,0,0,207,712,1,0,0,0,209,
  	723,1,0,0,0,211,725,1,0,0,0,213,744,1,0,0,0,215,784,1,0,0,0,217,805,1,
  	0,0,0,219,825,1,0,0,0,221,842,1,0,0,0,223,863,1,0,0,0,225,874,1,0,0,0,
  	227,878,1,0,0,0,229,892,1,0,0,0,231,232,5,115,0,0,232,233,5,116,0,0,233,
  	234,5,114,0,0,234,235,5,117,0,0,235,236,5,99,0,0,236,237,5,116,0,0,237,
  	2,1,0,0,0,238,239,5,99,0,0,239,240,5,97,0,0,240,241,5,115,0,0,241,242,
  	5,101,0,0,242,4,1,0,0,0,243,244,5,99,0,0,244,245,5,104,0,0,245,246,5,
  	97,0,0,246,247,5,114,0,0,247,6,1,0,0,0,248,249,5,99,0,0,249,250,5,111,
  	0,0,250,251,5,110,0,0,251,252,5,115,0,0,252,253,5,116,0,0,253,8,1,0,0,
  	0,254,255,5,101,0,0,255,256,5,108,0,0,256,257,5,115,0,0,257,258,5,101,
  	0,0,258,10,1,0,0,0,259,260,5,102,0,0,260,261,5,108,0,0,261,262,5,111,
  	0,0,262,263,5,97,0,0,263,264,5,116,0,0,264,12,1,0,0,0,265,266,5,102,0,
  	0,266,267,5,111,0,0,267,268,5,114,0,0,268,14,1,0,0,0,269,270,5,105,0,
  	0,270,271,5,102,0,0,271,16,1,0,0,0,272,273,5,105,0,0,273,274,5,110,0,
  	0,274,275,5,116,0,0,275,18,1,0,0,0,276,277,5,108,0,0,277,278,5,111,0,
  	0,278,279,5,110,0,0,279,280,5,103,0,0,280,20,1,0,0,0,281,282,5,114,0,
  	0,282,283,5,101,0,0,283,284,5,116,0,0,284,285,5,117,0,0,285,286,5,114,
  	0,0,286,287,5,110,0,0,287,22,1,0,0,0,288,289,5,115,0,0,289,290,5,104,
  	0,0,290,291,5,111,0,0,291,292,5,114,0,0,292,293,5,116,0,0,293,24,1,0,
  	0,0,294,295,5,115,0,0,295,296,5,105,0,0,296,297,5,103,0,0,297,298,5,110,
  	0,0,298,299,5,101,0,0,299,300,5,100,0,0,300,26,1,0,0,0,301,302,5,116,
  	0,0,302,303,5,121,0,0,303,304,5,112,0,0,304,305,5,101,0,0,305,306,5,100,
  	0,0,306,307,5,101,0,0,307,308,5,102,0,0,308,28,1,0,0,0,309,310,5,117,
  	0,0,310,311,5,110,0,0,311,312,5,115,0,0,312,313,5,105,0,0,313,314,5,103,
  	0,0,314,315,5,110,0,0,315,316,5,101,0,0,316,317,5,100,0,0,317,30,1,0,
  	0,0,318,319,5,118,0,0,319,320,5,111,0,0,320,321,5,105,0,0,321,322,5,100,
  	0,0,322,32,1,0,0,0,323,324,5,118,0,0,324,325,5,111,0,0,325,326,5,108,
  	0,0,326,327,5,97,0,0,327,328,5,116,0,0,328,329,5,105,0,0,329,330,5,108,
  	0,0,330,331,5,101,0,0,331,34,1,0,0,0,332,333,5,119,0,0,333,334,5,104,
  	0,0,334,335,5,105,0,0,335,336,5,108,0,0,336,337,5,101,0,0,337,36,1,0,
  	0,0,338,339,5,40,0,0,339,38,1,0,0,0,340,341,5,41,0,0,341,40,1,0,0,0,342,
  	343,5,91,0,0,343,42,1,0,0,0,344,345,5,93,0,0,345,44,1,0,0,0,346,347,5,
  	123,0,0,347,46,1,0,0,0,348,349,5,125,0,0,349,48,1,0,0,0,350,351,5,60,
  	0,0,351,50,1,0,0,0,352,353,5,60,0,0,353,354,5,61,0,0,354,52,1,0,0,0,355,
  	356,5,62,0,0,356,54,1,0,0,0,357,358,5,62,0,0,358,359,5,61,0,0,359,56,
  	1,0,0,0,360,361,5,60,0,0,361,362,5,60,0,0,362,58,1,0,0,0,363,364,5,62,
  	0,0,364,365,5,62,0,0,365,60,1,0,0,0,366,367,5,43,0,0,367,62,1,0,0,0,368,
  	369,5,43,0,0,369,370,5,43,0,0,370,64,1,0,0,0,371,372,5,45,0,0,372,66,
  	1,0,0,0,373,374,5,45,0,0,374,375,5,45,0,0,375,68,1,0,0,0,376,377,5,42,
  	0,0,377,70,1,0,0,0,378,379,5,47,0,0,379,72,1,0,0,0,380,381,5,37,0,0,381,
  	74,1,0,0,0,382,383,5,38,0,0,383,76,1,0,0,0,384,385,5,124,0,0,385,78,1,
  	0,0,0,386,387,5,38,0,0,387,388,5,38,0,0,388,80,1,0,0,0,389,390,5,124,
  	0,0,390,391,5,124,0,0,391,82,1,0,0,0,392,393,5,94,0,0,393,84,1,0,0,0,
  	394,395,5,33,0,0,395,86,1,0,0,0,396,397,5,126,0,0,397,88,1,0,0,0,398,
  	399,5,63,0,0,399,90,1,0,0,0,400,401,5,58,0,0,401,92,1,0,0,0,402,403,5,
  	59,0,0,403,94,1,0,0,0,404,405,5,44,0,0,405,96,1,0,0,0,406,407,5,61,0,
  	0,407,98,1,0,0,0,408,409,5,42,0,0,409,410,5,61,0,0,410,100,1,0,0,0,411,
  	412,5,47,0,0,412,413,5,61,0,0,413,102,1,0,0,0,414,415,5,37,0,0,415,416,
  	5,61,0,0,416,104,1,0,0,0,417,418,5,43,0,0,418,419,5,61,0,0,419,106,1,
  	0,0,0,420,421,5,45,0,0,421,422,5,61,0,0,422,108,1,0,0,0,423,424,5,60,
  	0,0,424,425,5,60,0,0,425,426,5,61,0,0,426,110,1,0,0,0,427,428,5,62,0,
  	0,428,429,5,62,0,0,429,430,5,61,0,0,430,112,1,0,0,0,431,432,5,38,0,0,
  	432,433,5,61,0,0,433,114,1,0,0,0,434,435,5,94,0,0,435,436,5,61,0,0,436,
  	116,1,0,0,0,437,438,5,124,0,0,438,439,5,61,0,0,439,118,1,0,0,0,440,441,
  	5,61,0,0,441,442,5,61,0,0,442,120,1,0,0,0,443,444,5,33,0,0,444,445,5,
  	61,0,0,445,122,1,0,0,0,446,447,5,45,0,0,447,448,5,62,0,0,448,124,1,0,
  	0,0,449,450,5,46,0,0,450,126,1,0,0,0,451,452,5,46,0,0,452,453,5,46,0,
  	0,453,454,5,46,0,0,454,128,1,0,0,0,455,460,3,131,65,0,456,459,3,131,65,
  	0,457,459,3,135,67,0,458,456,1,0,0,0,458,457,1,0,0,0,459,462,1,0,0,0,
  	460,458,1,0,0,0,460,461,1,0,0,0,461,130,1,0,0,0,462,460,1,0,0,0,463,466,
  	3,133,66,0,464,466,3,137,68,0,465,463,1,0,0,0,465,464,1,0,0,0,466,132,
  	1,0,0,0,467,468,7,0,0,0,468,134,1,0,0,0,469,470,7,1,0,0,470,136,1,0,0,
  	0,471,472,5,92,0,0,472,473,5,117,0,0,473,474,1,0,0,0,474,482,3,139,69,
  	0,475,476,5,92,0,0,476,477,5,85,0,0,477,478,1,0,0,0,478,479,3,139,69,
  	0,479,480,3,139,69,0,480,482,1,0,0,0,481,471,1,0,0,0,481,475,1,0,0,0,
  	482,138,1,0,0,0,483,484,3,157,78,0,484,485,3,157,78,0,485,486,3,157,78,
  	0,486,487,3,157,78,0,487,140,1,0,0,0,488,490,3,145,72,0,489,491,3,159,
  	79,0,490,489,1,0,0,0,490,491,1,0,0,0,491,502,1,0,0,0,492,494,3,147,73,
  	0,493,495,3,159,79,0,494,493,1,0,0,0,494,495,1,0,0,0,495,502,1,0,0,0,
  	496,498,3,149,74,0,497,499,3,159,79,0,498,497,1,0,0,0,498,499,1,0,0,0,
  	499,502,1,0,0,0,500,502,3,143,71,0,501,488,1,0,0,0,501,492,1,0,0,0,501,
  	496,1,0,0,0,501,500,1,0,0,0,502,142,1,0,0,0,503,504,5,48,0,0,504,506,
  	7,2,0,0,505,507,7,3,0,0,506,505,1,0,0,0,507,508,1,0,0,0,508,506,1,0,0,
  	0,508,509,1,0,0,0,509,144,1,0,0,0,510,514,3,153,76,0,511,513,3,135,67,
  	0,512,511,1,0,0,0,513,516,1,0,0,0,514,512,1,0,0,0,514,515,1,0,0,0,515,
  	146,1,0,0,0,516,514,1,0,0,0,517,521,5,48,0,0,518,520,3,155,77,0,519,518,
  	1,0,0,0,520,523,1,0,0,0,521,519,1,0,0,0,521,522,1,0,0,0,522,148,1,0,0,
  	0,523,521,1,0,0,0,524,526,3,151,75,0,525,527,3,157,78,0,526,525,1,0,0,
  	0,527,528,1,0,0,0,528,526,1,0,0,0,528,529,1,0,0,0,529,150,1,0,0,0,530,
  	531,5,48,0,0,531,532,7,4,0,0,532,152,1,0,0,0,533,534,7,5,0,0,534,154,
  	1,0,0,0,535,536,7,6,0,0,536,156,1,0,0,0,537,538,7,7,0,0,538,158,1,0,0,
  	0,539,541,3,161,80,0,540,542,3,163,81,0,541,540,1,0,0,0,541,542,1,0,0,
  	0,542,555,1,0,0,0,543,544,3,161,80,0,544,545,3,165,82,0,545,555,1,0,0,
  	0,546,548,3,163,81,0,547,549,3,161,80,0,548,547,1,0,0,0,548,549,1,0,0,
  	0,549,555,1,0,0,0,550,552,3,165,82,0,551,553,3,161,80,0,552,551,1,0,0,
  	0,552,553,1,0,0,0,553,555,1,0,0,0,554,539,1,0,0,0,554,543,1,0,0,0,554,
  	546,1,0,0,0,554,550,1,0,0,0,555,160,1,0,0,0,556,557,7,8,0,0,557,162,1,
  	0,0,0,558,559,7,9,0,0,559,164,1,0,0,0,560,561,5,108,0,0,561,565,5,108,
  	0,0,562,563,5,76,0,0,563,565,5,76,0,0,564,560,1,0,0,0,564,562,1,0,0,0,
  	565,166,1,0,0,0,566,569,3,169,84,0,567,569,3,171,85,0,568,566,1,0,0,0,
  	568,567,1,0,0,0,569,168,1,0,0,0,570,572,3,173,86,0,571,573,3,175,87,0,
  	572,571,1,0,0,0,572,573,1,0,0,0,573,575,1,0,0,0,574,576,3,187,93,0,575,
  	574,1,0,0,0,575,576,1,0,0,0,576,583,1,0,0,0,577,578,3,179,89,0,578,580,
  	3,175,87,0,579,581,3,187,93,0,580,579,1,0,0,0,580,581,1,0,0,0,581,583,
  	1,0,0,0,582,570,1,0,0,0,582,577,1,0,0,0,583,170,1,0,0,0,584,587,3,151,
  	75,0,585,588,3,181,90,0,586,588,3,185,92,0,587,585,1,0,0,0,587,586,1,
  	0,0,0,588,589,1,0,0,0,589,591,3,183,91,0,590,592,3,187,93,0,591,590,1,
  	0,0,0,591,592,1,0,0,0,592,172,1,0,0,0,593,595,3,179,89,0,594,593,1,0,
  	0,0,594,595,1,0,0,0,595,596,1,0,0,0,596,597,5,46,0,0,597,602,3,179,89,
  	0,598,599,3,179,89,0,599,600,5,46,0,0,600,602,1,0,0,0,601,594,1,0,0,0,
  	601,598,1,0,0,0,602,174,1,0,0,0,603,605,7,10,0,0,604,606,3,177,88,0,605,
  	604,1,0,0,0,605,606,1,0,0,0,606,607,1,0,0,0,607,608,3,179,89,0,608,176,
  	1,0,0,0,609,610,7,11,0,0,610,178,1,0,0,0,611,613,3,135,67,0,612,611,1,
  	0,0,0,613,614,1,0,0,0,614,612,1,0,0,0,614,615,1,0,0,0,615,180,1,0,0,0,
  	616,618,3,185,92,0,617,616,1,0,0,0,617,618,1,0,0,0,618,619,1,0,0,0,619,
  	620,5,46,0,0,620,625,3,185,92,0,621,622,3,185,92,0,622,623,5,46,0,0,623,
  	625,1,0,0,0,624,617,1,0,0,0,624,621,1,0,0,0,625,182,1,0,0,0,626,628,7,
  	12,0,0,627,629,3,177,88,0,628,627,1,0,0,0,628,629,1,0,0,0,629,630,1,0,
  	0,0,630,631,3,179,89,0,631,184,1,0,0,0,632,634,3,157,78,0,633,632,1,0,
  	0,0,634,635,1,0,0,0,635,633,1,0,0,0,635,636,1,0,0,0,636,186,1,0,0,0,637,
  	638,7,13,0,0,638,188,1,0,0,0,639,640,5,39,0,0,640,641,3,191,95,0,641,
  	642,5,39,0,0,642,662,1,0,0,0,643,644,5,76,0,0,644,645,5,39,0,0,645,646,
  	1,0,0,0,646,647,3,191,95,0,647,648,5,39,0,0,648,662,1,0,0,0,649,650,5,
  	117,0,0,650,651,5,39,0,0,651,652,1,0,0,0,652,653,3,191,95,0,653,654,5,
  	39,0,0,654,662,1,0,0,0,655,656,5,85,0,0,656,657,5,39,0,0,657,658,1,0,
  	0,0,658,659,3,191,95,0,659,660,5,39,0,0,660,662,1,0,0,0,661,639,1,0,0,
  	0,661,643,1,0,0,0,661,649,1,0,0,0,661,655,1,0,0,0,662,190,1,0,0,0,663,
  	665,3,193,96,0,664,663,1,0,0,0,665,666,1,0,0,0,666,664,1,0,0,0,666,667,
  	1,0,0,0,667,192,1,0,0,0,668,671,8,14,0,0,669,671,3,195,97,0,670,668,1,
  	0,0,0,670,669,1,0,0,0,671,194,1,0,0,0,672,677,3,197,98,0,673,677,3,199,
  	99,0,674,677,3,201,100,0,675,677,3,137,68,0,676,672,1,0,0,0,676,673,1,
  	0,0,0,676,674,1,0,0,0,676,675,1,0,0,0,677,196,1,0,0,0,678,679,5,92,0,
  	0,679,680,7,15,0,0,680,198,1,0,0,0,681,682,5,92,0,0,682,684,3,155,77,
  	0,683,685,3,155,77,0,684,683,1,0,0,0,684,685,1,0,0,0,685,687,1,0,0,0,
  	686,688,3,155,77,0,687,686,1,0,0,0,687,688,1,0,0,0,688,200,1,0,0,0,689,
  	690,5,92,0,0,690,691,5,120,0,0,691,693,1,0,0,0,692,694,3,157,78,0,693,
  	692,1,0,0,0,694,695,1,0,0,0,695,693,1,0,0,0,695,696,1,0,0,0,696,202,1,
  	0,0,0,697,699,3,205,102,0,698,697,1,0,0,0,698,699,1,0,0,0,699,700,1,0,
  	0,0,700,702,5,34,0,0,701,703,3,207,103,0,702,701,1,0,0,0,702,703,1,0,
  	0,0,703,704,1,0,0,0,704,705,5,34,0,0,705,204,1,0,0,0,706,707,5,117,0,
  	0,707,710,5,56,0,0,708,710,7,16,0,0,709,706,1,0,0,0,709,708,1,0,0,0,710,
  	206,1,0,0,0,711,713,3,209,104,0,712,711,1,0,0,0,713,714,1,0,0,0,714,712,
  	1,0,0,0,714,715,1,0,0,0,715,208,1,0,0,0,716,724,8,17,0,0,717,724,3,195,
  	97,0,718,719,5,92,0,0,719,724,5,10,0,0,720,721,5,92,0,0,721,722,5,13,
  	0,0,722,724,5,10,0,0,723,716,1,0,0,0,723,717,1,0,0,0,723,718,1,0,0,0,
  	723,720,1,0,0,0,724,210,1,0,0,0,725,727,5,35,0,0,726,728,3,223,111,0,
  	727,726,1,0,0,0,727,728,1,0,0,0,728,729,1,0,0,0,729,730,5,100,0,0,730,
  	731,5,101,0,0,731,732,5,102,0,0,732,733,5,105,0,0,733,734,5,110,0,0,734,
  	735,5,101,0,0,735,739,1,0,0,0,736,738,8,18,0,0,737,736,1,0,0,0,738,741,
  	1,0,0,0,739,737,1,0,0,0,739,740,1,0,0,0,740,742,1,0,0,0,741,739,1,0,0,
  	0,742,743,6,105,0,0,743,212,1,0,0,0,744,746,5,35,0,0,745,747,3,223,111,
  	0,746,745,1,0,0,0,746,747,1,0,0,0,747,748,1,0,0,0,748,749,5,105,0,0,749,
  	750,5,110,0,0,750,751,5,99,0,0,751,752,5,108,0,0,752,753,5,117,0,0,753,
  	754,5,100,0,0,754,755,5,101,0,0,755,757,1,0,0,0,756,758,3,223,111,0,757,
  	756,1,0,0,0,757,758,1,0,0,0,758,775,1,0,0,0,759,763,5,34,0,0,760,762,
  	8,19,0,0,761,760,1,0,0,0,762,765,1,0,0,0,763,761,1,0,0,0,763,764,1,0,
  	0,0,764,766,1,0,0,0,765,763,1,0,0,0,766,776,5,34,0,0,767,771,5,60,0,0,
  	768,770,8,19,0,0,769,768,1,0,0,0,770,773,1,0,0,0,771,769,1,0,0,0,771,
  	772,1,0,0,0,772,774,1,0,0,0,773,771,1,0,0,0,774,776,5,62,0,0,775,759,
  	1,0,0,0,775,767,1,0,0,0,776,778,1,0,0,0,777,779,3,223,111,0,778,777,1,
  	0,0,0,778,779,1,0,0,0,779,780,1,0,0,0,780,781,3,225,112,0,781,782,1,0,
  	0,0,782,783,6,106,0,0,783,214,1,0,0,0,784,785,5,97,0,0,785,786,5,115,
  	0,0,786,787,5,109,0,0,787,791,1,0,0,0,788,790,8,20,0,0,789,788,1,0,0,
  	0,790,793,1,0,0,0,791,789,1,0,0,0,791,792,1,0,0,0,792,794,1,0,0,0,793,
  	791,1,0,0,0,794,798,5,123,0,0,795,797,8,21,0,0,796,795,1,0,0,0,797,800,
  	1,0,0,0,798,796,1,0,0,0,798,799,1,0,0,0,799,801,1,0,0,0,800,798,1,0,0,
  	0,801,802,5,125,0,0,802,803,1,0,0,0,803,804,6,107,0,0,804,216,1,0,0,0,
  	805,806,5,35,0,0,806,807,5,108,0,0,807,808,5,105,0,0,808,809,5,110,0,
  	0,809,810,5,101,0,0,810,814,1,0,0,0,811,813,3,223,111,0,812,811,1,0,0,
  	0,813,816,1,0,0,0,814,812,1,0,0,0,814,815,1,0,0,0,815,820,1,0,0,0,816,
  	814,1,0,0,0,817,819,8,19,0,0,818,817,1,0,0,0,819,822,1,0,0,0,820,818,
  	1,0,0,0,820,821,1,0,0,0,821,823,1,0,0,0,822,820,1,0,0,0,823,824,6,108,
  	0,0,824,218,1,0,0,0,825,827,5,35,0,0,826,828,3,223,111,0,827,826,1,0,
  	0,0,827,828,1,0,0,0,828,829,1,0,0,0,829,831,3,145,72,0,830,832,3,223,
  	111,0,831,830,1,0,0,0,831,832,1,0,0,0,832,833,1,0,0,0,833,837,3,203,101,
  	0,834,836,8,19,0,0,835,834,1,0,0,0,836,839,1,0,0,0,837,835,1,0,0,0,837,
  	838,1,0,0,0,838,840,1,0,0,0,839,837,1,0,0,0,840,841,6,109,0,0,841,220,
  	1,0,0,0,842,844,5,35,0,0,843,845,3,223,111,0,844,843,1,0,0,0,844,845,
  	1,0,0,0,845,846,1,0,0,0,846,847,5,112,0,0,847,848,5,114,0,0,848,849,5,
  	97,0,0,849,850,5,103,0,0,850,851,5,109,0,0,851,852,5,97,0,0,852,853,1,
  	0,0,0,853,857,3,223,111,0,854,856,8,19,0,0,855,854,1,0,0,0,856,859,1,
  	0,0,0,857,855,1,0,0,0,857,858,1,0,0,0,858,860,1,0,0,0,859,857,1,0,0,0,
  	860,861,6,110,0,0,861,222,1,0,0,0,862,864,7,22,0,0,863,862,1,0,0,0,864,
  	865,1,0,0,0,865,863,1,0,0,0,865,866,1,0,0,0,866,867,1,0,0,0,867,868,6,
  	111,0,0,868,224,1,0,0,0,869,871,5,13,0,0,870,872,5,10,0,0,871,870,1,0,
  	0,0,871,872,1,0,0,0,872,875,1,0,0,0,873,875,5,10,0,0,874,869,1,0,0,0,
  	874,873,1,0,0,0,875,876,1,0,0,0,876,877,6,112,0,0,877,226,1,0,0,0,878,
  	879,5,47,0,0,879,880,5,42,0,0,880,884,1,0,0,0,881,883,9,0,0,0,882,881,
  	1,0,0,0,883,886,1,0,0,0,884,885,1,0,0,0,884,882,1,0,0,0,885,887,1,0,0,
  	0,886,884,1,0,0,0,887,888,5,42,0,0,888,889,5,47,0,0,889,890,1,0,0,0,890,
  	891,6,113,0,0,891,228,1,0,0,0,892,893,5,47,0,0,893,894,5,47,0,0,894,898,
  	1,0,0,0,895,897,8,19,0,0,896,895,1,0,0,0,897,900,1,0,0,0,898,896,1,0,
  	0,0,898,899,1,0,0,0,899,901,1,0,0,0,900,898,1,0,0,0,901,902,6,114,0,0,
  	902,230,1,0,0,0,67,0,458,460,465,481,490,494,498,501,508,514,521,528,
  	541,548,552,554,564,568,572,575,580,582,587,591,594,601,605,614,617,624,
  	628,635,661,666,670,676,684,687,695,698,702,709,714,723,727,739,746,757,
  	763,771,775,778,791,798,814,820,827,831,837,844,857,865,871,874,884,898,
  	1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  c_grammarlexerLexerStaticData = std::move(staticData);
}

}

C_grammarLexer::C_grammarLexer(CharStream *input) : Lexer(input) {
  C_grammarLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *c_grammarlexerLexerStaticData->atn, c_grammarlexerLexerStaticData->decisionToDFA, c_grammarlexerLexerStaticData->sharedContextCache);
}

C_grammarLexer::~C_grammarLexer() {
  delete _interpreter;
}

std::string C_grammarLexer::getGrammarFileName() const {
  return "C_grammar.g4";
}

const std::vector<std::string>& C_grammarLexer::getRuleNames() const {
  return c_grammarlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& C_grammarLexer::getChannelNames() const {
  return c_grammarlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& C_grammarLexer::getModeNames() const {
  return c_grammarlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& C_grammarLexer::getVocabulary() const {
  return c_grammarlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView C_grammarLexer::getSerializedATN() const {
  return c_grammarlexerLexerStaticData->serializedATN;
}

const atn::ATN& C_grammarLexer::getATN() const {
  return *c_grammarlexerLexerStaticData->atn;
}




void C_grammarLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  c_grammarlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(c_grammarlexerLexerOnceFlag, c_grammarlexerLexerInitialize);
#endif
}
