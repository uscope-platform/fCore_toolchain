
// Generated from /home/filssavi/git/fCore_toolchain/src/frontend/C_grammar.g4 by ANTLR 4.13.2


#include "C_grammarListener.h"
#include "C_grammarVisitor.h"

#include "C_grammarParser.h"


using namespace antlrcpp;
using namespace C_parser;

using namespace antlr4;

namespace {

struct C_grammarParserStaticData final {
  C_grammarParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  C_grammarParserStaticData(const C_grammarParserStaticData&) = delete;
  C_grammarParserStaticData(C_grammarParserStaticData&&) = delete;
  C_grammarParserStaticData& operator=(const C_grammarParserStaticData&) = delete;
  C_grammarParserStaticData& operator=(C_grammarParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag c_grammarParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<C_grammarParserStaticData> c_grammarParserStaticData = nullptr;

void c_grammarParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (c_grammarParserStaticData != nullptr) {
    return;
  }
#else
  assert(c_grammarParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<C_grammarParserStaticData>(
    std::vector<std::string>{
      "compilationUnit", "primaryExpression", "structExpression", "unaryExpression", 
      "arrayAccessExpression", "unaryOperator", "multiplicativeOperator", 
      "multiplicativeExpression", "additiveOperator", "additiveExpression", 
      "shiftOperator", "shiftExpression", "relationalOperator", "relationalExpression", 
      "equalityOperator", "equalityExpression", "andExpression", "exclusiveOrExpression", 
      "inclusiveOrExpression", "logicalAndExpression", "logicalOrExpression", 
      "conditionalExpression", "assignmentExpression", "assignmentOperator", 
      "expression", "constantExpression", "declaration", "initDeclaratorList", 
      "initDeclarator", "typeSpecifier", "structOrUnionSpecifier", "structOrUnion", 
      "structDeclarationList", "specifierQualifierList", "structDeclaration", 
      "structDeclaratorList", "structDeclarator", "declarator", "directDeclarator", 
      "arrayDeclarator", "nestedParenthesesBlock", "parameterTypeList", 
      "parameterList", "parameterDeclaration", "identifierList", "typeName", 
      "typedefName", "initializer", "functionCallExpression", "argumentExpressionList", 
      "argumentExpression", "initializerList", "designation", "designatorList", 
      "designator", "statement", "compoundStatement", "blockItem", "expressionStatement", 
      "ifContent", "elseContent", "conditionalBlockItem", "conditionContent", 
      "selectionStatement", "iterationStatement", "forContent", "forBlockItem", 
      "forExitCondition", "forDeclaration", "forIterationExpression", "returnStatement", 
      "translationUnit", "externalDeclaration", "functionDefinition", "declarationList", 
      "constant"
    },
    std::vector<std::string>{
      "", "'struct'", "'union'", "'case'", "'char'", "'const'", "'else'", 
      "'float'", "'for'", "'if'", "'int'", "'long'", "'return'", "'short'", 
      "'signed'", "'typedef'", "'unsigned'", "'void'", "'volatile'", "'while'", 
      "'('", "')'", "'['", "']'", "'{'", "'}'", "'<'", "'<='", "'>'", "'>='", 
      "'<<'", "'>>'", "'+'", "'++'", "'-'", "'--'", "'*'", "'/'", "'%'", 
      "'&'", "'|'", "'&&'", "'||'", "'^'", "'!'", "'~'", "'\\u003F'", "':'", 
      "';'", "','", "'='", "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", 
      "'>>='", "'&='", "'^='", "'|='", "'=='", "'!='", "'->'", "'.'", "'...'"
    },
    std::vector<std::string>{
      "", "", "", "Case", "Char", "Const", "Else", "Float", "For", "If", 
      "Int", "Long", "Return", "Short", "Signed", "Typedef", "Unsigned", 
      "Void", "Volatile", "While", "LeftParen", "RightParen", "LeftBracket", 
      "RightBracket", "LeftBrace", "RightBrace", "Less", "LessEqual", "Greater", 
      "GreaterEqual", "LeftShift", "RightShift", "Plus", "PlusPlus", "Minus", 
      "MinusMinus", "Star", "Div", "Mod", "And", "Or", "AndAnd", "OrOr", 
      "Caret", "Not", "Tilde", "Question", "Colon", "Semi", "Comma", "Assign", 
      "StarAssign", "DivAssign", "ModAssign", "PlusAssign", "MinusAssign", 
      "LeftShiftAssign", "RightShiftAssign", "AndAssign", "XorAssign", "OrAssign", 
      "Equal", "NotEqual", "Arrow", "Dot", "Ellipsis", "Identifier", "IntegerConstant", 
      "FloatingConstant", "DigitSequence", "CharacterConstant", "StringLiteral", 
      "ComplexDefine", "IncludeDirective", "AsmBlock", "LineAfterPreprocessing", 
      "LineDirective", "PragmaDirective", "Whitespace", "Newline", "BlockComment", 
      "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,81,726,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,1,0,3,0,154,8,0,
  	1,0,1,0,1,1,1,1,1,1,4,1,161,8,1,11,1,12,1,162,1,1,1,1,1,1,1,1,3,1,169,
  	8,1,1,2,1,2,1,2,1,2,1,3,5,3,176,8,3,10,3,12,3,179,9,3,1,3,1,3,1,3,1,3,
  	1,3,3,3,186,8,3,1,3,3,3,189,8,3,1,4,1,4,1,4,1,4,1,4,4,4,196,8,4,11,4,
  	12,4,197,1,5,1,5,1,6,1,6,1,7,1,7,1,7,1,7,5,7,208,8,7,10,7,12,7,211,9,
  	7,1,8,1,8,1,9,1,9,1,9,1,9,5,9,219,8,9,10,9,12,9,222,9,9,1,10,1,10,1,11,
  	1,11,1,11,1,11,5,11,230,8,11,10,11,12,11,233,9,11,1,12,1,12,1,13,1,13,
  	1,13,1,13,5,13,241,8,13,10,13,12,13,244,9,13,1,14,1,14,1,15,1,15,1,15,
  	1,15,5,15,252,8,15,10,15,12,15,255,9,15,1,16,1,16,1,16,5,16,260,8,16,
  	10,16,12,16,263,9,16,1,17,1,17,1,17,5,17,268,8,17,10,17,12,17,271,9,17,
  	1,18,1,18,1,18,5,18,276,8,18,10,18,12,18,279,9,18,1,19,1,19,1,19,5,19,
  	284,8,19,10,19,12,19,287,9,19,1,20,1,20,1,20,5,20,292,8,20,10,20,12,20,
  	295,9,20,1,21,1,21,1,21,1,21,1,21,1,21,3,21,303,8,21,1,22,1,22,1,22,1,
  	22,1,22,1,22,3,22,311,8,22,1,23,1,23,1,24,1,24,1,24,5,24,318,8,24,10,
  	24,12,24,321,9,24,1,25,1,25,1,26,3,26,326,8,26,1,26,1,26,3,26,330,8,26,
  	1,27,1,27,1,27,5,27,335,8,27,10,27,12,27,338,9,27,1,28,1,28,1,28,3,28,
  	343,8,28,1,29,1,29,1,29,3,29,348,8,29,1,30,1,30,3,30,352,8,30,1,30,1,
  	30,1,30,1,30,1,30,1,30,1,30,3,30,361,8,30,1,31,1,31,1,32,4,32,366,8,32,
  	11,32,12,32,367,1,33,1,33,3,33,372,8,33,1,33,3,33,375,8,33,1,34,1,34,
  	1,34,1,34,1,34,1,34,1,34,3,34,384,8,34,1,35,1,35,1,35,5,35,389,8,35,10,
  	35,12,35,392,9,35,1,36,1,36,3,36,396,8,36,1,36,1,36,3,36,400,8,36,1,37,
  	1,37,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,3,38,413,8,38,1,38,
  	1,38,4,38,417,8,38,11,38,12,38,418,1,38,1,38,1,38,1,38,1,38,1,38,1,38,
  	1,38,3,38,429,8,38,1,38,5,38,432,8,38,10,38,12,38,435,9,38,1,39,1,39,
  	3,39,439,8,39,1,39,3,39,442,8,39,1,39,1,39,1,40,1,40,1,40,1,40,1,40,5,
  	40,451,8,40,10,40,12,40,454,9,40,1,41,1,41,1,41,3,41,459,8,41,1,42,1,
  	42,1,42,5,42,464,8,42,10,42,12,42,467,9,42,1,43,3,43,470,8,43,1,43,1,
  	43,1,43,1,44,1,44,1,44,5,44,478,8,44,10,44,12,44,481,9,44,1,45,3,45,484,
  	8,45,1,46,1,46,1,47,1,47,1,47,1,47,3,47,492,8,47,1,47,1,47,3,47,496,8,
  	47,1,48,1,48,1,48,3,48,501,8,48,1,48,1,48,1,49,1,49,1,49,5,49,508,8,49,
  	10,49,12,49,511,9,49,1,50,1,50,1,51,3,51,516,8,51,1,51,1,51,1,51,3,51,
  	521,8,51,1,51,5,51,524,8,51,10,51,12,51,527,9,51,1,52,1,52,1,52,1,53,
  	4,53,533,8,53,11,53,12,53,534,1,54,1,54,1,54,1,54,1,54,1,54,3,54,543,
  	8,54,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,1,55,5,55,555,8,55,
  	10,55,12,55,558,9,55,3,55,560,8,55,1,55,1,55,1,55,1,55,5,55,566,8,55,
  	10,55,12,55,569,9,55,3,55,571,8,55,5,55,573,8,55,10,55,12,55,576,9,55,
  	1,55,1,55,3,55,580,8,55,1,56,1,56,5,56,584,8,56,10,56,12,56,587,9,56,
  	1,56,1,56,1,57,1,57,1,57,1,57,3,57,595,8,57,1,58,3,58,598,8,58,1,59,1,
  	59,5,59,602,8,59,10,59,12,59,605,9,59,1,59,1,59,3,59,609,8,59,1,60,1,
  	60,5,60,613,8,60,10,60,12,60,616,9,60,1,60,1,60,3,60,620,8,60,1,61,1,
  	61,1,61,1,61,3,61,626,8,61,1,62,1,62,1,63,1,63,1,63,1,63,1,63,1,63,1,
  	63,3,63,637,8,63,1,64,1,64,1,64,1,64,1,64,1,64,1,64,1,64,1,64,1,64,1,
  	65,1,65,5,65,651,8,65,10,65,12,65,654,9,65,1,65,1,65,3,65,658,8,65,1,
  	66,1,66,1,66,1,66,3,66,664,8,66,1,67,1,67,1,68,1,68,1,69,1,69,1,69,5,
  	69,673,8,69,10,69,12,69,676,9,69,1,70,1,70,3,70,680,8,70,1,70,1,70,1,
  	71,4,71,685,8,71,11,71,12,71,686,1,72,1,72,1,72,1,72,1,72,3,72,694,8,
  	72,1,73,3,73,697,8,73,1,73,3,73,700,8,73,1,73,1,73,3,73,704,8,73,1,73,
  	1,73,1,74,1,74,1,74,4,74,711,8,74,11,74,12,74,712,1,75,3,75,716,8,75,
  	1,75,1,75,3,75,720,8,75,1,75,1,75,3,75,724,8,75,1,75,0,1,76,76,0,2,4,
  	6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,
  	54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,
  	100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,
  	136,138,140,142,144,146,148,150,0,11,2,0,33,33,35,35,2,0,34,34,44,45,
  	1,0,36,38,2,0,32,32,34,34,1,0,30,31,1,0,26,29,1,0,61,62,1,0,50,60,5,0,
  	4,4,7,7,10,11,13,14,16,17,1,0,1,2,1,0,20,21,747,0,153,1,0,0,0,2,168,1,
  	0,0,0,4,170,1,0,0,0,6,188,1,0,0,0,8,190,1,0,0,0,10,199,1,0,0,0,12,201,
  	1,0,0,0,14,203,1,0,0,0,16,212,1,0,0,0,18,214,1,0,0,0,20,223,1,0,0,0,22,
  	225,1,0,0,0,24,234,1,0,0,0,26,236,1,0,0,0,28,245,1,0,0,0,30,247,1,0,0,
  	0,32,256,1,0,0,0,34,264,1,0,0,0,36,272,1,0,0,0,38,280,1,0,0,0,40,288,
  	1,0,0,0,42,296,1,0,0,0,44,310,1,0,0,0,46,312,1,0,0,0,48,314,1,0,0,0,50,
  	322,1,0,0,0,52,325,1,0,0,0,54,331,1,0,0,0,56,339,1,0,0,0,58,347,1,0,0,
  	0,60,360,1,0,0,0,62,362,1,0,0,0,64,365,1,0,0,0,66,371,1,0,0,0,68,383,
  	1,0,0,0,70,385,1,0,0,0,72,399,1,0,0,0,74,401,1,0,0,0,76,412,1,0,0,0,78,
  	436,1,0,0,0,80,452,1,0,0,0,82,455,1,0,0,0,84,460,1,0,0,0,86,469,1,0,0,
  	0,88,474,1,0,0,0,90,483,1,0,0,0,92,485,1,0,0,0,94,495,1,0,0,0,96,497,
  	1,0,0,0,98,504,1,0,0,0,100,512,1,0,0,0,102,515,1,0,0,0,104,528,1,0,0,
  	0,106,532,1,0,0,0,108,542,1,0,0,0,110,579,1,0,0,0,112,581,1,0,0,0,114,
  	594,1,0,0,0,116,597,1,0,0,0,118,608,1,0,0,0,120,619,1,0,0,0,122,625,1,
  	0,0,0,124,627,1,0,0,0,126,629,1,0,0,0,128,638,1,0,0,0,130,657,1,0,0,0,
  	132,663,1,0,0,0,134,665,1,0,0,0,136,667,1,0,0,0,138,669,1,0,0,0,140,677,
  	1,0,0,0,142,684,1,0,0,0,144,693,1,0,0,0,146,699,1,0,0,0,148,710,1,0,0,
  	0,150,723,1,0,0,0,152,154,3,142,71,0,153,152,1,0,0,0,153,154,1,0,0,0,
  	154,155,1,0,0,0,155,156,5,0,0,1,156,1,1,0,0,0,157,169,5,66,0,0,158,169,
  	3,150,75,0,159,161,5,71,0,0,160,159,1,0,0,0,161,162,1,0,0,0,162,160,1,
  	0,0,0,162,163,1,0,0,0,163,169,1,0,0,0,164,165,5,20,0,0,165,166,3,48,24,
  	0,166,167,5,21,0,0,167,169,1,0,0,0,168,157,1,0,0,0,168,158,1,0,0,0,168,
  	160,1,0,0,0,168,164,1,0,0,0,169,3,1,0,0,0,170,171,3,2,1,0,171,172,5,64,
  	0,0,172,173,5,66,0,0,173,5,1,0,0,0,174,176,7,0,0,0,175,174,1,0,0,0,176,
  	179,1,0,0,0,177,175,1,0,0,0,177,178,1,0,0,0,178,185,1,0,0,0,179,177,1,
  	0,0,0,180,186,3,4,2,0,181,182,3,10,5,0,182,183,3,6,3,0,183,186,1,0,0,
  	0,184,186,3,96,48,0,185,180,1,0,0,0,185,181,1,0,0,0,185,184,1,0,0,0,186,
  	189,1,0,0,0,187,189,3,8,4,0,188,177,1,0,0,0,188,187,1,0,0,0,189,7,1,0,
  	0,0,190,195,3,2,1,0,191,192,5,22,0,0,192,193,3,2,1,0,193,194,5,23,0,0,
  	194,196,1,0,0,0,195,191,1,0,0,0,196,197,1,0,0,0,197,195,1,0,0,0,197,198,
  	1,0,0,0,198,9,1,0,0,0,199,200,7,1,0,0,200,11,1,0,0,0,201,202,7,2,0,0,
  	202,13,1,0,0,0,203,209,3,6,3,0,204,205,3,12,6,0,205,206,3,6,3,0,206,208,
  	1,0,0,0,207,204,1,0,0,0,208,211,1,0,0,0,209,207,1,0,0,0,209,210,1,0,0,
  	0,210,15,1,0,0,0,211,209,1,0,0,0,212,213,7,3,0,0,213,17,1,0,0,0,214,220,
  	3,14,7,0,215,216,3,16,8,0,216,217,3,14,7,0,217,219,1,0,0,0,218,215,1,
  	0,0,0,219,222,1,0,0,0,220,218,1,0,0,0,220,221,1,0,0,0,221,19,1,0,0,0,
  	222,220,1,0,0,0,223,224,7,4,0,0,224,21,1,0,0,0,225,231,3,18,9,0,226,227,
  	3,20,10,0,227,228,3,18,9,0,228,230,1,0,0,0,229,226,1,0,0,0,230,233,1,
  	0,0,0,231,229,1,0,0,0,231,232,1,0,0,0,232,23,1,0,0,0,233,231,1,0,0,0,
  	234,235,7,5,0,0,235,25,1,0,0,0,236,242,3,22,11,0,237,238,3,24,12,0,238,
  	239,3,22,11,0,239,241,1,0,0,0,240,237,1,0,0,0,241,244,1,0,0,0,242,240,
  	1,0,0,0,242,243,1,0,0,0,243,27,1,0,0,0,244,242,1,0,0,0,245,246,7,6,0,
  	0,246,29,1,0,0,0,247,253,3,26,13,0,248,249,3,28,14,0,249,250,3,26,13,
  	0,250,252,1,0,0,0,251,248,1,0,0,0,252,255,1,0,0,0,253,251,1,0,0,0,253,
  	254,1,0,0,0,254,31,1,0,0,0,255,253,1,0,0,0,256,261,3,30,15,0,257,258,
  	5,39,0,0,258,260,3,30,15,0,259,257,1,0,0,0,260,263,1,0,0,0,261,259,1,
  	0,0,0,261,262,1,0,0,0,262,33,1,0,0,0,263,261,1,0,0,0,264,269,3,32,16,
  	0,265,266,5,43,0,0,266,268,3,32,16,0,267,265,1,0,0,0,268,271,1,0,0,0,
  	269,267,1,0,0,0,269,270,1,0,0,0,270,35,1,0,0,0,271,269,1,0,0,0,272,277,
  	3,34,17,0,273,274,5,40,0,0,274,276,3,34,17,0,275,273,1,0,0,0,276,279,
  	1,0,0,0,277,275,1,0,0,0,277,278,1,0,0,0,278,37,1,0,0,0,279,277,1,0,0,
  	0,280,285,3,36,18,0,281,282,5,41,0,0,282,284,3,36,18,0,283,281,1,0,0,
  	0,284,287,1,0,0,0,285,283,1,0,0,0,285,286,1,0,0,0,286,39,1,0,0,0,287,
  	285,1,0,0,0,288,293,3,38,19,0,289,290,5,42,0,0,290,292,3,38,19,0,291,
  	289,1,0,0,0,292,295,1,0,0,0,293,291,1,0,0,0,293,294,1,0,0,0,294,41,1,
  	0,0,0,295,293,1,0,0,0,296,302,3,40,20,0,297,298,5,46,0,0,298,299,3,48,
  	24,0,299,300,5,47,0,0,300,301,3,42,21,0,301,303,1,0,0,0,302,297,1,0,0,
  	0,302,303,1,0,0,0,303,43,1,0,0,0,304,311,3,42,21,0,305,306,3,6,3,0,306,
  	307,3,46,23,0,307,308,3,44,22,0,308,311,1,0,0,0,309,311,5,69,0,0,310,
  	304,1,0,0,0,310,305,1,0,0,0,310,309,1,0,0,0,311,45,1,0,0,0,312,313,7,
  	7,0,0,313,47,1,0,0,0,314,319,3,44,22,0,315,316,5,49,0,0,316,318,3,44,
  	22,0,317,315,1,0,0,0,318,321,1,0,0,0,319,317,1,0,0,0,319,320,1,0,0,0,
  	320,49,1,0,0,0,321,319,1,0,0,0,322,323,3,42,21,0,323,51,1,0,0,0,324,326,
  	5,5,0,0,325,324,1,0,0,0,325,326,1,0,0,0,326,327,1,0,0,0,327,329,3,58,
  	29,0,328,330,3,54,27,0,329,328,1,0,0,0,329,330,1,0,0,0,330,53,1,0,0,0,
  	331,336,3,56,28,0,332,333,5,49,0,0,333,335,3,56,28,0,334,332,1,0,0,0,
  	335,338,1,0,0,0,336,334,1,0,0,0,336,337,1,0,0,0,337,55,1,0,0,0,338,336,
  	1,0,0,0,339,342,3,74,37,0,340,341,5,50,0,0,341,343,3,94,47,0,342,340,
  	1,0,0,0,342,343,1,0,0,0,343,57,1,0,0,0,344,348,7,8,0,0,345,348,3,60,30,
  	0,346,348,3,92,46,0,347,344,1,0,0,0,347,345,1,0,0,0,347,346,1,0,0,0,348,
  	59,1,0,0,0,349,351,3,62,31,0,350,352,5,66,0,0,351,350,1,0,0,0,351,352,
  	1,0,0,0,352,353,1,0,0,0,353,354,5,24,0,0,354,355,3,64,32,0,355,356,5,
  	25,0,0,356,361,1,0,0,0,357,358,3,62,31,0,358,359,5,66,0,0,359,361,1,0,
  	0,0,360,349,1,0,0,0,360,357,1,0,0,0,361,61,1,0,0,0,362,363,7,9,0,0,363,
  	63,1,0,0,0,364,366,3,68,34,0,365,364,1,0,0,0,366,367,1,0,0,0,367,365,
  	1,0,0,0,367,368,1,0,0,0,368,65,1,0,0,0,369,372,3,58,29,0,370,372,5,5,
  	0,0,371,369,1,0,0,0,371,370,1,0,0,0,372,374,1,0,0,0,373,375,3,66,33,0,
  	374,373,1,0,0,0,374,375,1,0,0,0,375,67,1,0,0,0,376,377,3,66,33,0,377,
  	378,3,70,35,0,378,379,5,48,0,0,379,384,1,0,0,0,380,381,3,66,33,0,381,
  	382,5,48,0,0,382,384,1,0,0,0,383,376,1,0,0,0,383,380,1,0,0,0,384,69,1,
  	0,0,0,385,390,3,72,36,0,386,387,5,49,0,0,387,389,3,72,36,0,388,386,1,
  	0,0,0,389,392,1,0,0,0,390,388,1,0,0,0,390,391,1,0,0,0,391,71,1,0,0,0,
  	392,390,1,0,0,0,393,400,3,74,37,0,394,396,3,74,37,0,395,394,1,0,0,0,395,
  	396,1,0,0,0,396,397,1,0,0,0,397,398,5,47,0,0,398,400,3,50,25,0,399,393,
  	1,0,0,0,399,395,1,0,0,0,400,73,1,0,0,0,401,402,3,76,38,0,402,75,1,0,0,
  	0,403,404,6,38,-1,0,404,413,5,66,0,0,405,406,5,20,0,0,406,407,3,74,37,
  	0,407,408,5,21,0,0,408,413,1,0,0,0,409,410,5,66,0,0,410,411,5,47,0,0,
  	411,413,5,69,0,0,412,403,1,0,0,0,412,405,1,0,0,0,412,409,1,0,0,0,413,
  	433,1,0,0,0,414,416,10,4,0,0,415,417,3,78,39,0,416,415,1,0,0,0,417,418,
  	1,0,0,0,418,416,1,0,0,0,418,419,1,0,0,0,419,432,1,0,0,0,420,421,10,3,
  	0,0,421,422,5,20,0,0,422,423,3,82,41,0,423,424,5,21,0,0,424,432,1,0,0,
  	0,425,426,10,2,0,0,426,428,5,20,0,0,427,429,3,88,44,0,428,427,1,0,0,0,
  	428,429,1,0,0,0,429,430,1,0,0,0,430,432,5,21,0,0,431,414,1,0,0,0,431,
  	420,1,0,0,0,431,425,1,0,0,0,432,435,1,0,0,0,433,431,1,0,0,0,433,434,1,
  	0,0,0,434,77,1,0,0,0,435,433,1,0,0,0,436,438,5,22,0,0,437,439,5,5,0,0,
  	438,437,1,0,0,0,438,439,1,0,0,0,439,441,1,0,0,0,440,442,3,44,22,0,441,
  	440,1,0,0,0,441,442,1,0,0,0,442,443,1,0,0,0,443,444,5,23,0,0,444,79,1,
  	0,0,0,445,451,8,10,0,0,446,447,5,20,0,0,447,448,3,80,40,0,448,449,5,21,
  	0,0,449,451,1,0,0,0,450,445,1,0,0,0,450,446,1,0,0,0,451,454,1,0,0,0,452,
  	450,1,0,0,0,452,453,1,0,0,0,453,81,1,0,0,0,454,452,1,0,0,0,455,458,3,
  	84,42,0,456,457,5,49,0,0,457,459,5,65,0,0,458,456,1,0,0,0,458,459,1,0,
  	0,0,459,83,1,0,0,0,460,465,3,86,43,0,461,462,5,49,0,0,462,464,3,86,43,
  	0,463,461,1,0,0,0,464,467,1,0,0,0,465,463,1,0,0,0,465,466,1,0,0,0,466,
  	85,1,0,0,0,467,465,1,0,0,0,468,470,5,5,0,0,469,468,1,0,0,0,469,470,1,
  	0,0,0,470,471,1,0,0,0,471,472,3,58,29,0,472,473,3,74,37,0,473,87,1,0,
  	0,0,474,479,5,66,0,0,475,476,5,49,0,0,476,478,5,66,0,0,477,475,1,0,0,
  	0,478,481,1,0,0,0,479,477,1,0,0,0,479,480,1,0,0,0,480,89,1,0,0,0,481,
  	479,1,0,0,0,482,484,3,66,33,0,483,482,1,0,0,0,483,484,1,0,0,0,484,91,
  	1,0,0,0,485,486,5,66,0,0,486,93,1,0,0,0,487,496,3,44,22,0,488,489,5,24,
  	0,0,489,491,3,102,51,0,490,492,5,49,0,0,491,490,1,0,0,0,491,492,1,0,0,
  	0,492,493,1,0,0,0,493,494,5,25,0,0,494,496,1,0,0,0,495,487,1,0,0,0,495,
  	488,1,0,0,0,496,95,1,0,0,0,497,498,3,92,46,0,498,500,5,20,0,0,499,501,
  	3,98,49,0,500,499,1,0,0,0,500,501,1,0,0,0,501,502,1,0,0,0,502,503,5,21,
  	0,0,503,97,1,0,0,0,504,509,3,100,50,0,505,506,5,49,0,0,506,508,3,100,
  	50,0,507,505,1,0,0,0,508,511,1,0,0,0,509,507,1,0,0,0,509,510,1,0,0,0,
  	510,99,1,0,0,0,511,509,1,0,0,0,512,513,3,44,22,0,513,101,1,0,0,0,514,
  	516,3,104,52,0,515,514,1,0,0,0,515,516,1,0,0,0,516,517,1,0,0,0,517,525,
  	3,94,47,0,518,520,5,49,0,0,519,521,3,104,52,0,520,519,1,0,0,0,520,521,
  	1,0,0,0,521,522,1,0,0,0,522,524,3,94,47,0,523,518,1,0,0,0,524,527,1,0,
  	0,0,525,523,1,0,0,0,525,526,1,0,0,0,526,103,1,0,0,0,527,525,1,0,0,0,528,
  	529,3,106,53,0,529,530,5,50,0,0,530,105,1,0,0,0,531,533,3,108,54,0,532,
  	531,1,0,0,0,533,534,1,0,0,0,534,532,1,0,0,0,534,535,1,0,0,0,535,107,1,
  	0,0,0,536,537,5,22,0,0,537,538,3,50,25,0,538,539,5,23,0,0,539,543,1,0,
  	0,0,540,541,5,64,0,0,541,543,5,66,0,0,542,536,1,0,0,0,542,540,1,0,0,0,
  	543,109,1,0,0,0,544,545,3,116,58,0,545,546,5,48,0,0,546,580,1,0,0,0,547,
  	580,3,126,63,0,548,580,3,128,64,0,549,580,3,140,70,0,550,559,5,20,0,0,
  	551,556,3,40,20,0,552,553,5,49,0,0,553,555,3,40,20,0,554,552,1,0,0,0,
  	555,558,1,0,0,0,556,554,1,0,0,0,556,557,1,0,0,0,557,560,1,0,0,0,558,556,
  	1,0,0,0,559,551,1,0,0,0,559,560,1,0,0,0,560,574,1,0,0,0,561,570,5,47,
  	0,0,562,567,3,40,20,0,563,564,5,49,0,0,564,566,3,40,20,0,565,563,1,0,
  	0,0,566,569,1,0,0,0,567,565,1,0,0,0,567,568,1,0,0,0,568,571,1,0,0,0,569,
  	567,1,0,0,0,570,562,1,0,0,0,570,571,1,0,0,0,571,573,1,0,0,0,572,561,1,
  	0,0,0,573,576,1,0,0,0,574,572,1,0,0,0,574,575,1,0,0,0,575,577,1,0,0,0,
  	576,574,1,0,0,0,577,578,5,21,0,0,578,580,5,48,0,0,579,544,1,0,0,0,579,
  	547,1,0,0,0,579,548,1,0,0,0,579,549,1,0,0,0,579,550,1,0,0,0,580,111,1,
  	0,0,0,581,585,5,24,0,0,582,584,3,114,57,0,583,582,1,0,0,0,584,587,1,0,
  	0,0,585,583,1,0,0,0,585,586,1,0,0,0,586,588,1,0,0,0,587,585,1,0,0,0,588,
  	589,5,25,0,0,589,113,1,0,0,0,590,595,3,110,55,0,591,592,3,52,26,0,592,
  	593,5,48,0,0,593,595,1,0,0,0,594,590,1,0,0,0,594,591,1,0,0,0,595,115,
  	1,0,0,0,596,598,3,48,24,0,597,596,1,0,0,0,597,598,1,0,0,0,598,117,1,0,
  	0,0,599,603,5,24,0,0,600,602,3,122,61,0,601,600,1,0,0,0,602,605,1,0,0,
  	0,603,601,1,0,0,0,603,604,1,0,0,0,604,606,1,0,0,0,605,603,1,0,0,0,606,
  	609,5,25,0,0,607,609,3,122,61,0,608,599,1,0,0,0,608,607,1,0,0,0,609,119,
  	1,0,0,0,610,614,5,24,0,0,611,613,3,122,61,0,612,611,1,0,0,0,613,616,1,
  	0,0,0,614,612,1,0,0,0,614,615,1,0,0,0,615,617,1,0,0,0,616,614,1,0,0,0,
  	617,620,5,25,0,0,618,620,3,122,61,0,619,610,1,0,0,0,619,618,1,0,0,0,620,
  	121,1,0,0,0,621,626,3,110,55,0,622,623,3,52,26,0,623,624,5,48,0,0,624,
  	626,1,0,0,0,625,621,1,0,0,0,625,622,1,0,0,0,626,123,1,0,0,0,627,628,3,
  	48,24,0,628,125,1,0,0,0,629,630,5,9,0,0,630,631,5,20,0,0,631,632,3,124,
  	62,0,632,633,5,21,0,0,633,636,3,118,59,0,634,635,5,6,0,0,635,637,3,120,
  	60,0,636,634,1,0,0,0,636,637,1,0,0,0,637,127,1,0,0,0,638,639,5,8,0,0,
  	639,640,5,20,0,0,640,641,3,136,68,0,641,642,5,48,0,0,642,643,3,134,67,
  	0,643,644,5,48,0,0,644,645,3,138,69,0,645,646,5,21,0,0,646,647,3,130,
  	65,0,647,129,1,0,0,0,648,652,5,24,0,0,649,651,3,132,66,0,650,649,1,0,
  	0,0,651,654,1,0,0,0,652,650,1,0,0,0,652,653,1,0,0,0,653,655,1,0,0,0,654,
  	652,1,0,0,0,655,658,5,25,0,0,656,658,3,132,66,0,657,648,1,0,0,0,657,656,
  	1,0,0,0,658,131,1,0,0,0,659,664,3,110,55,0,660,661,3,52,26,0,661,662,
  	5,48,0,0,662,664,1,0,0,0,663,659,1,0,0,0,663,660,1,0,0,0,664,133,1,0,
  	0,0,665,666,3,44,22,0,666,135,1,0,0,0,667,668,3,52,26,0,668,137,1,0,0,
  	0,669,674,3,44,22,0,670,671,5,49,0,0,671,673,3,44,22,0,672,670,1,0,0,
  	0,673,676,1,0,0,0,674,672,1,0,0,0,674,675,1,0,0,0,675,139,1,0,0,0,676,
  	674,1,0,0,0,677,679,5,12,0,0,678,680,3,48,24,0,679,678,1,0,0,0,679,680,
  	1,0,0,0,680,681,1,0,0,0,681,682,5,48,0,0,682,141,1,0,0,0,683,685,3,144,
  	72,0,684,683,1,0,0,0,685,686,1,0,0,0,686,684,1,0,0,0,686,687,1,0,0,0,
  	687,143,1,0,0,0,688,694,3,146,73,0,689,690,3,52,26,0,690,691,5,48,0,0,
  	691,694,1,0,0,0,692,694,5,48,0,0,693,688,1,0,0,0,693,689,1,0,0,0,693,
  	692,1,0,0,0,694,145,1,0,0,0,695,697,5,5,0,0,696,695,1,0,0,0,696,697,1,
  	0,0,0,697,698,1,0,0,0,698,700,3,58,29,0,699,696,1,0,0,0,699,700,1,0,0,
  	0,700,701,1,0,0,0,701,703,3,74,37,0,702,704,3,148,74,0,703,702,1,0,0,
  	0,703,704,1,0,0,0,704,705,1,0,0,0,705,706,3,112,56,0,706,147,1,0,0,0,
  	707,708,3,52,26,0,708,709,5,48,0,0,709,711,1,0,0,0,710,707,1,0,0,0,711,
  	712,1,0,0,0,712,710,1,0,0,0,712,713,1,0,0,0,713,149,1,0,0,0,714,716,5,
  	34,0,0,715,714,1,0,0,0,715,716,1,0,0,0,716,717,1,0,0,0,717,724,5,67,0,
  	0,718,720,5,34,0,0,719,718,1,0,0,0,719,720,1,0,0,0,720,721,1,0,0,0,721,
  	724,5,68,0,0,722,724,5,70,0,0,723,715,1,0,0,0,723,719,1,0,0,0,723,722,
  	1,0,0,0,724,151,1,0,0,0,86,153,162,168,177,185,188,197,209,220,231,242,
  	253,261,269,277,285,293,302,310,319,325,329,336,342,347,351,360,367,371,
  	374,383,390,395,399,412,418,428,431,433,438,441,450,452,458,465,469,479,
  	483,491,495,500,509,515,520,525,534,542,556,559,567,570,574,579,585,594,
  	597,603,608,614,619,625,636,652,657,663,674,679,686,693,696,699,703,712,
  	715,719,723
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  c_grammarParserStaticData = std::move(staticData);
}

}

C_grammarParser::C_grammarParser(TokenStream *input) : C_grammarParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

C_grammarParser::C_grammarParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  C_grammarParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *c_grammarParserStaticData->atn, c_grammarParserStaticData->decisionToDFA, c_grammarParserStaticData->sharedContextCache, options);
}

C_grammarParser::~C_grammarParser() {
  delete _interpreter;
}

const atn::ATN& C_grammarParser::getATN() const {
  return *c_grammarParserStaticData->atn;
}

std::string C_grammarParser::getGrammarFileName() const {
  return "C_grammar.g4";
}

const std::vector<std::string>& C_grammarParser::getRuleNames() const {
  return c_grammarParserStaticData->ruleNames;
}

const dfa::Vocabulary& C_grammarParser::getVocabulary() const {
  return c_grammarParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView C_grammarParser::getSerializedATN() const {
  return c_grammarParserStaticData->serializedATN;
}


//----------------- CompilationUnitContext ------------------------------------------------------------------

C_grammarParser::CompilationUnitContext::CompilationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::CompilationUnitContext::EOF() {
  return getToken(C_grammarParser::EOF, 0);
}

C_grammarParser::TranslationUnitContext* C_grammarParser::CompilationUnitContext::translationUnit() {
  return getRuleContext<C_grammarParser::TranslationUnitContext>(0);
}


size_t C_grammarParser::CompilationUnitContext::getRuleIndex() const {
  return C_grammarParser::RuleCompilationUnit;
}

void C_grammarParser::CompilationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompilationUnit(this);
}

void C_grammarParser::CompilationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompilationUnit(this);
}


std::any C_grammarParser::CompilationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitCompilationUnit(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::CompilationUnitContext* C_grammarParser::compilationUnit() {
  CompilationUnitContext *_localctx = _tracker.createInstance<CompilationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, C_grammarParser::RuleCompilationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474977983670) != 0) || _la == C_grammarParser::Identifier) {
      setState(152);
      translationUnit();
    }
    setState(155);
    match(C_grammarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

C_grammarParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

C_grammarParser::ConstantContext* C_grammarParser::PrimaryExpressionContext::constant() {
  return getRuleContext<C_grammarParser::ConstantContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::PrimaryExpressionContext::StringLiteral() {
  return getTokens(C_grammarParser::StringLiteral);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::StringLiteral(size_t i) {
  return getToken(C_grammarParser::StringLiteral, i);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::PrimaryExpressionContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::PrimaryExpressionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}


size_t C_grammarParser::PrimaryExpressionContext::getRuleIndex() const {
  return C_grammarParser::RulePrimaryExpression;
}

void C_grammarParser::PrimaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpression(this);
}

void C_grammarParser::PrimaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpression(this);
}


std::any C_grammarParser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 2, C_grammarParser::RulePrimaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(168);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(157);
        match(C_grammarParser::Identifier);
        break;
      }

      case C_grammarParser::Minus:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::CharacterConstant: {
        enterOuterAlt(_localctx, 2);
        setState(158);
        constant();
        break;
      }

      case C_grammarParser::StringLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(160); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(159);
          match(C_grammarParser::StringLiteral);
          setState(162); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == C_grammarParser::StringLiteral);
        break;
      }

      case C_grammarParser::LeftParen: {
        enterOuterAlt(_localctx, 4);
        setState(164);
        match(C_grammarParser::LeftParen);
        setState(165);
        expression();
        setState(166);
        match(C_grammarParser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructExpressionContext ------------------------------------------------------------------

C_grammarParser::StructExpressionContext::StructExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::StructExpressionContext::primaryExpression() {
  return getRuleContext<C_grammarParser::PrimaryExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::StructExpressionContext::Dot() {
  return getToken(C_grammarParser::Dot, 0);
}

tree::TerminalNode* C_grammarParser::StructExpressionContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::StructExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleStructExpression;
}

void C_grammarParser::StructExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructExpression(this);
}

void C_grammarParser::StructExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructExpression(this);
}


std::any C_grammarParser::StructExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructExpressionContext* C_grammarParser::structExpression() {
  StructExpressionContext *_localctx = _tracker.createInstance<StructExpressionContext>(_ctx, getState());
  enterRule(_localctx, 4, C_grammarParser::RuleStructExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    primaryExpression();
    setState(171);
    match(C_grammarParser::Dot);
    setState(172);
    match(C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

C_grammarParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StructExpressionContext* C_grammarParser::UnaryExpressionContext::structExpression() {
  return getRuleContext<C_grammarParser::StructExpressionContext>(0);
}

C_grammarParser::UnaryOperatorContext* C_grammarParser::UnaryExpressionContext::unaryOperator() {
  return getRuleContext<C_grammarParser::UnaryOperatorContext>(0);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(0);
}

C_grammarParser::FunctionCallExpressionContext* C_grammarParser::UnaryExpressionContext::functionCallExpression() {
  return getRuleContext<C_grammarParser::FunctionCallExpressionContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::UnaryExpressionContext::PlusPlus() {
  return getTokens(C_grammarParser::PlusPlus);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::PlusPlus(size_t i) {
  return getToken(C_grammarParser::PlusPlus, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::UnaryExpressionContext::MinusMinus() {
  return getTokens(C_grammarParser::MinusMinus);
}

tree::TerminalNode* C_grammarParser::UnaryExpressionContext::MinusMinus(size_t i) {
  return getToken(C_grammarParser::MinusMinus, i);
}

C_grammarParser::ArrayAccessExpressionContext* C_grammarParser::UnaryExpressionContext::arrayAccessExpression() {
  return getRuleContext<C_grammarParser::ArrayAccessExpressionContext>(0);
}


size_t C_grammarParser::UnaryExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleUnaryExpression;
}

void C_grammarParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void C_grammarParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}


std::any C_grammarParser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, C_grammarParser::RuleUnaryExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(188);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(177);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C_grammarParser::PlusPlus

      || _la == C_grammarParser::MinusMinus) {
        setState(174);
        _la = _input->LA(1);
        if (!(_la == C_grammarParser::PlusPlus

        || _la == C_grammarParser::MinusMinus)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(179);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(185);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(180);
        structExpression();
        break;
      }

      case 2: {
        setState(181);
        unaryOperator();
        setState(182);
        unaryExpression();
        break;
      }

      case 3: {
        setState(184);
        functionCallExpression();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(187);
      arrayAccessExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayAccessExpressionContext ------------------------------------------------------------------

C_grammarParser::ArrayAccessExpressionContext::ArrayAccessExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::PrimaryExpressionContext *> C_grammarParser::ArrayAccessExpressionContext::primaryExpression() {
  return getRuleContexts<C_grammarParser::PrimaryExpressionContext>();
}

C_grammarParser::PrimaryExpressionContext* C_grammarParser::ArrayAccessExpressionContext::primaryExpression(size_t i) {
  return getRuleContext<C_grammarParser::PrimaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ArrayAccessExpressionContext::LeftBracket() {
  return getTokens(C_grammarParser::LeftBracket);
}

tree::TerminalNode* C_grammarParser::ArrayAccessExpressionContext::LeftBracket(size_t i) {
  return getToken(C_grammarParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ArrayAccessExpressionContext::RightBracket() {
  return getTokens(C_grammarParser::RightBracket);
}

tree::TerminalNode* C_grammarParser::ArrayAccessExpressionContext::RightBracket(size_t i) {
  return getToken(C_grammarParser::RightBracket, i);
}


size_t C_grammarParser::ArrayAccessExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleArrayAccessExpression;
}

void C_grammarParser::ArrayAccessExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayAccessExpression(this);
}

void C_grammarParser::ArrayAccessExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayAccessExpression(this);
}


std::any C_grammarParser::ArrayAccessExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArrayAccessExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArrayAccessExpressionContext* C_grammarParser::arrayAccessExpression() {
  ArrayAccessExpressionContext *_localctx = _tracker.createInstance<ArrayAccessExpressionContext>(_ctx, getState());
  enterRule(_localctx, 8, C_grammarParser::RuleArrayAccessExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    primaryExpression();
    setState(195); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(191);
      match(C_grammarParser::LeftBracket);
      setState(192);
      primaryExpression();
      setState(193);
      match(C_grammarParser::RightBracket);
      setState(197); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == C_grammarParser::LeftBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOperatorContext ------------------------------------------------------------------

C_grammarParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Minus() {
  return getToken(C_grammarParser::Minus, 0);
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Tilde() {
  return getToken(C_grammarParser::Tilde, 0);
}

tree::TerminalNode* C_grammarParser::UnaryOperatorContext::Not() {
  return getToken(C_grammarParser::Not, 0);
}


size_t C_grammarParser::UnaryOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleUnaryOperator;
}

void C_grammarParser::UnaryOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryOperator(this);
}

void C_grammarParser::UnaryOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryOperator(this);
}


std::any C_grammarParser::UnaryOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitUnaryOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::UnaryOperatorContext* C_grammarParser::unaryOperator() {
  UnaryOperatorContext *_localctx = _tracker.createInstance<UnaryOperatorContext>(_ctx, getState());
  enterRule(_localctx, 10, C_grammarParser::RuleUnaryOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 52793738002432) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeOperatorContext ------------------------------------------------------------------

C_grammarParser::MultiplicativeOperatorContext::MultiplicativeOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::MultiplicativeOperatorContext::Star() {
  return getToken(C_grammarParser::Star, 0);
}

tree::TerminalNode* C_grammarParser::MultiplicativeOperatorContext::Div() {
  return getToken(C_grammarParser::Div, 0);
}

tree::TerminalNode* C_grammarParser::MultiplicativeOperatorContext::Mod() {
  return getToken(C_grammarParser::Mod, 0);
}


size_t C_grammarParser::MultiplicativeOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleMultiplicativeOperator;
}

void C_grammarParser::MultiplicativeOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeOperator(this);
}

void C_grammarParser::MultiplicativeOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeOperator(this);
}


std::any C_grammarParser::MultiplicativeOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::MultiplicativeOperatorContext* C_grammarParser::multiplicativeOperator() {
  MultiplicativeOperatorContext *_localctx = _tracker.createInstance<MultiplicativeOperatorContext>(_ctx, getState());
  enterRule(_localctx, 12, C_grammarParser::RuleMultiplicativeOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 481036337152) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

C_grammarParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::UnaryExpressionContext *> C_grammarParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<C_grammarParser::UnaryExpressionContext>();
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(i);
}

std::vector<C_grammarParser::MultiplicativeOperatorContext *> C_grammarParser::MultiplicativeExpressionContext::multiplicativeOperator() {
  return getRuleContexts<C_grammarParser::MultiplicativeOperatorContext>();
}

C_grammarParser::MultiplicativeOperatorContext* C_grammarParser::MultiplicativeExpressionContext::multiplicativeOperator(size_t i) {
  return getRuleContext<C_grammarParser::MultiplicativeOperatorContext>(i);
}


size_t C_grammarParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleMultiplicativeExpression;
}

void C_grammarParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void C_grammarParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}


std::any C_grammarParser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::MultiplicativeExpressionContext* C_grammarParser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 14, C_grammarParser::RuleMultiplicativeExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    unaryExpression();
    setState(209);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 481036337152) != 0)) {
      setState(204);
      multiplicativeOperator();
      setState(205);
      unaryExpression();
      setState(211);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveOperatorContext ------------------------------------------------------------------

C_grammarParser::AdditiveOperatorContext::AdditiveOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::AdditiveOperatorContext::Plus() {
  return getToken(C_grammarParser::Plus, 0);
}

tree::TerminalNode* C_grammarParser::AdditiveOperatorContext::Minus() {
  return getToken(C_grammarParser::Minus, 0);
}


size_t C_grammarParser::AdditiveOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleAdditiveOperator;
}

void C_grammarParser::AdditiveOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveOperator(this);
}

void C_grammarParser::AdditiveOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveOperator(this);
}


std::any C_grammarParser::AdditiveOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAdditiveOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AdditiveOperatorContext* C_grammarParser::additiveOperator() {
  AdditiveOperatorContext *_localctx = _tracker.createInstance<AdditiveOperatorContext>(_ctx, getState());
  enterRule(_localctx, 16, C_grammarParser::RuleAdditiveOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::Plus

    || _la == C_grammarParser::Minus)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

C_grammarParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::MultiplicativeExpressionContext *> C_grammarParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContexts<C_grammarParser::MultiplicativeExpressionContext>();
}

C_grammarParser::MultiplicativeExpressionContext* C_grammarParser::AdditiveExpressionContext::multiplicativeExpression(size_t i) {
  return getRuleContext<C_grammarParser::MultiplicativeExpressionContext>(i);
}

std::vector<C_grammarParser::AdditiveOperatorContext *> C_grammarParser::AdditiveExpressionContext::additiveOperator() {
  return getRuleContexts<C_grammarParser::AdditiveOperatorContext>();
}

C_grammarParser::AdditiveOperatorContext* C_grammarParser::AdditiveExpressionContext::additiveOperator(size_t i) {
  return getRuleContext<C_grammarParser::AdditiveOperatorContext>(i);
}


size_t C_grammarParser::AdditiveExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleAdditiveExpression;
}

void C_grammarParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void C_grammarParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}


std::any C_grammarParser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AdditiveExpressionContext* C_grammarParser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 18, C_grammarParser::RuleAdditiveExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(214);
    multiplicativeExpression();
    setState(220);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Plus

    || _la == C_grammarParser::Minus) {
      setState(215);
      additiveOperator();
      setState(216);
      multiplicativeExpression();
      setState(222);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftOperatorContext ------------------------------------------------------------------

C_grammarParser::ShiftOperatorContext::ShiftOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ShiftOperatorContext::LeftShift() {
  return getToken(C_grammarParser::LeftShift, 0);
}

tree::TerminalNode* C_grammarParser::ShiftOperatorContext::RightShift() {
  return getToken(C_grammarParser::RightShift, 0);
}


size_t C_grammarParser::ShiftOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleShiftOperator;
}

void C_grammarParser::ShiftOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftOperator(this);
}

void C_grammarParser::ShiftOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftOperator(this);
}


std::any C_grammarParser::ShiftOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitShiftOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ShiftOperatorContext* C_grammarParser::shiftOperator() {
  ShiftOperatorContext *_localctx = _tracker.createInstance<ShiftOperatorContext>(_ctx, getState());
  enterRule(_localctx, 20, C_grammarParser::RuleShiftOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::LeftShift

    || _la == C_grammarParser::RightShift)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShiftExpressionContext ------------------------------------------------------------------

C_grammarParser::ShiftExpressionContext::ShiftExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AdditiveExpressionContext *> C_grammarParser::ShiftExpressionContext::additiveExpression() {
  return getRuleContexts<C_grammarParser::AdditiveExpressionContext>();
}

C_grammarParser::AdditiveExpressionContext* C_grammarParser::ShiftExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<C_grammarParser::AdditiveExpressionContext>(i);
}

std::vector<C_grammarParser::ShiftOperatorContext *> C_grammarParser::ShiftExpressionContext::shiftOperator() {
  return getRuleContexts<C_grammarParser::ShiftOperatorContext>();
}

C_grammarParser::ShiftOperatorContext* C_grammarParser::ShiftExpressionContext::shiftOperator(size_t i) {
  return getRuleContext<C_grammarParser::ShiftOperatorContext>(i);
}


size_t C_grammarParser::ShiftExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleShiftExpression;
}

void C_grammarParser::ShiftExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShiftExpression(this);
}

void C_grammarParser::ShiftExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShiftExpression(this);
}


std::any C_grammarParser::ShiftExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitShiftExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ShiftExpressionContext* C_grammarParser::shiftExpression() {
  ShiftExpressionContext *_localctx = _tracker.createInstance<ShiftExpressionContext>(_ctx, getState());
  enterRule(_localctx, 22, C_grammarParser::RuleShiftExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    additiveExpression();
    setState(231);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::LeftShift

    || _la == C_grammarParser::RightShift) {
      setState(226);
      shiftOperator();
      setState(227);
      additiveExpression();
      setState(233);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalOperatorContext ------------------------------------------------------------------

C_grammarParser::RelationalOperatorContext::RelationalOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::Less() {
  return getToken(C_grammarParser::Less, 0);
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::Greater() {
  return getToken(C_grammarParser::Greater, 0);
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::LessEqual() {
  return getToken(C_grammarParser::LessEqual, 0);
}

tree::TerminalNode* C_grammarParser::RelationalOperatorContext::GreaterEqual() {
  return getToken(C_grammarParser::GreaterEqual, 0);
}


size_t C_grammarParser::RelationalOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleRelationalOperator;
}

void C_grammarParser::RelationalOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalOperator(this);
}

void C_grammarParser::RelationalOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalOperator(this);
}


std::any C_grammarParser::RelationalOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitRelationalOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::RelationalOperatorContext* C_grammarParser::relationalOperator() {
  RelationalOperatorContext *_localctx = _tracker.createInstance<RelationalOperatorContext>(_ctx, getState());
  enterRule(_localctx, 24, C_grammarParser::RuleRelationalOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1006632960) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

C_grammarParser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ShiftExpressionContext *> C_grammarParser::RelationalExpressionContext::shiftExpression() {
  return getRuleContexts<C_grammarParser::ShiftExpressionContext>();
}

C_grammarParser::ShiftExpressionContext* C_grammarParser::RelationalExpressionContext::shiftExpression(size_t i) {
  return getRuleContext<C_grammarParser::ShiftExpressionContext>(i);
}

std::vector<C_grammarParser::RelationalOperatorContext *> C_grammarParser::RelationalExpressionContext::relationalOperator() {
  return getRuleContexts<C_grammarParser::RelationalOperatorContext>();
}

C_grammarParser::RelationalOperatorContext* C_grammarParser::RelationalExpressionContext::relationalOperator(size_t i) {
  return getRuleContext<C_grammarParser::RelationalOperatorContext>(i);
}


size_t C_grammarParser::RelationalExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleRelationalExpression;
}

void C_grammarParser::RelationalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationalExpression(this);
}

void C_grammarParser::RelationalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationalExpression(this);
}


std::any C_grammarParser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::RelationalExpressionContext* C_grammarParser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 26, C_grammarParser::RuleRelationalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(236);
    shiftExpression();
    setState(242);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1006632960) != 0)) {
      setState(237);
      relationalOperator();
      setState(238);
      shiftExpression();
      setState(244);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityOperatorContext ------------------------------------------------------------------

C_grammarParser::EqualityOperatorContext::EqualityOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::EqualityOperatorContext::Equal() {
  return getToken(C_grammarParser::Equal, 0);
}

tree::TerminalNode* C_grammarParser::EqualityOperatorContext::NotEqual() {
  return getToken(C_grammarParser::NotEqual, 0);
}


size_t C_grammarParser::EqualityOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleEqualityOperator;
}

void C_grammarParser::EqualityOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityOperator(this);
}

void C_grammarParser::EqualityOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityOperator(this);
}


std::any C_grammarParser::EqualityOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEqualityOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EqualityOperatorContext* C_grammarParser::equalityOperator() {
  EqualityOperatorContext *_localctx = _tracker.createInstance<EqualityOperatorContext>(_ctx, getState());
  enterRule(_localctx, 28, C_grammarParser::RuleEqualityOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(245);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::Equal

    || _la == C_grammarParser::NotEqual)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqualityExpressionContext ------------------------------------------------------------------

C_grammarParser::EqualityExpressionContext::EqualityExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::RelationalExpressionContext *> C_grammarParser::EqualityExpressionContext::relationalExpression() {
  return getRuleContexts<C_grammarParser::RelationalExpressionContext>();
}

C_grammarParser::RelationalExpressionContext* C_grammarParser::EqualityExpressionContext::relationalExpression(size_t i) {
  return getRuleContext<C_grammarParser::RelationalExpressionContext>(i);
}

std::vector<C_grammarParser::EqualityOperatorContext *> C_grammarParser::EqualityExpressionContext::equalityOperator() {
  return getRuleContexts<C_grammarParser::EqualityOperatorContext>();
}

C_grammarParser::EqualityOperatorContext* C_grammarParser::EqualityExpressionContext::equalityOperator(size_t i) {
  return getRuleContext<C_grammarParser::EqualityOperatorContext>(i);
}


size_t C_grammarParser::EqualityExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleEqualityExpression;
}

void C_grammarParser::EqualityExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityExpression(this);
}

void C_grammarParser::EqualityExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityExpression(this);
}


std::any C_grammarParser::EqualityExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitEqualityExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::EqualityExpressionContext* C_grammarParser::equalityExpression() {
  EqualityExpressionContext *_localctx = _tracker.createInstance<EqualityExpressionContext>(_ctx, getState());
  enterRule(_localctx, 30, C_grammarParser::RuleEqualityExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(247);
    relationalExpression();
    setState(253);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Equal

    || _la == C_grammarParser::NotEqual) {
      setState(248);
      equalityOperator();
      setState(249);
      relationalExpression();
      setState(255);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AndExpressionContext ------------------------------------------------------------------

C_grammarParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::EqualityExpressionContext *> C_grammarParser::AndExpressionContext::equalityExpression() {
  return getRuleContexts<C_grammarParser::EqualityExpressionContext>();
}

C_grammarParser::EqualityExpressionContext* C_grammarParser::AndExpressionContext::equalityExpression(size_t i) {
  return getRuleContext<C_grammarParser::EqualityExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::AndExpressionContext::And() {
  return getTokens(C_grammarParser::And);
}

tree::TerminalNode* C_grammarParser::AndExpressionContext::And(size_t i) {
  return getToken(C_grammarParser::And, i);
}


size_t C_grammarParser::AndExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleAndExpression;
}

void C_grammarParser::AndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpression(this);
}

void C_grammarParser::AndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpression(this);
}


std::any C_grammarParser::AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAndExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AndExpressionContext* C_grammarParser::andExpression() {
  AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, C_grammarParser::RuleAndExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(256);
    equalityExpression();
    setState(261);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::And) {
      setState(257);
      match(C_grammarParser::And);
      setState(258);
      equalityExpression();
      setState(263);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExclusiveOrExpressionContext ------------------------------------------------------------------

C_grammarParser::ExclusiveOrExpressionContext::ExclusiveOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AndExpressionContext *> C_grammarParser::ExclusiveOrExpressionContext::andExpression() {
  return getRuleContexts<C_grammarParser::AndExpressionContext>();
}

C_grammarParser::AndExpressionContext* C_grammarParser::ExclusiveOrExpressionContext::andExpression(size_t i) {
  return getRuleContext<C_grammarParser::AndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ExclusiveOrExpressionContext::Caret() {
  return getTokens(C_grammarParser::Caret);
}

tree::TerminalNode* C_grammarParser::ExclusiveOrExpressionContext::Caret(size_t i) {
  return getToken(C_grammarParser::Caret, i);
}


size_t C_grammarParser::ExclusiveOrExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleExclusiveOrExpression;
}

void C_grammarParser::ExclusiveOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExclusiveOrExpression(this);
}

void C_grammarParser::ExclusiveOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExclusiveOrExpression(this);
}


std::any C_grammarParser::ExclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExclusiveOrExpressionContext* C_grammarParser::exclusiveOrExpression() {
  ExclusiveOrExpressionContext *_localctx = _tracker.createInstance<ExclusiveOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 34, C_grammarParser::RuleExclusiveOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(264);
    andExpression();
    setState(269);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Caret) {
      setState(265);
      match(C_grammarParser::Caret);
      setState(266);
      andExpression();
      setState(271);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InclusiveOrExpressionContext ------------------------------------------------------------------

C_grammarParser::InclusiveOrExpressionContext::InclusiveOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ExclusiveOrExpressionContext *> C_grammarParser::InclusiveOrExpressionContext::exclusiveOrExpression() {
  return getRuleContexts<C_grammarParser::ExclusiveOrExpressionContext>();
}

C_grammarParser::ExclusiveOrExpressionContext* C_grammarParser::InclusiveOrExpressionContext::exclusiveOrExpression(size_t i) {
  return getRuleContext<C_grammarParser::ExclusiveOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::InclusiveOrExpressionContext::Or() {
  return getTokens(C_grammarParser::Or);
}

tree::TerminalNode* C_grammarParser::InclusiveOrExpressionContext::Or(size_t i) {
  return getToken(C_grammarParser::Or, i);
}


size_t C_grammarParser::InclusiveOrExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleInclusiveOrExpression;
}

void C_grammarParser::InclusiveOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInclusiveOrExpression(this);
}

void C_grammarParser::InclusiveOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInclusiveOrExpression(this);
}


std::any C_grammarParser::InclusiveOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInclusiveOrExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InclusiveOrExpressionContext* C_grammarParser::inclusiveOrExpression() {
  InclusiveOrExpressionContext *_localctx = _tracker.createInstance<InclusiveOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 36, C_grammarParser::RuleInclusiveOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(272);
    exclusiveOrExpression();
    setState(277);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Or) {
      setState(273);
      match(C_grammarParser::Or);
      setState(274);
      exclusiveOrExpression();
      setState(279);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalAndExpressionContext ------------------------------------------------------------------

C_grammarParser::LogicalAndExpressionContext::LogicalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::InclusiveOrExpressionContext *> C_grammarParser::LogicalAndExpressionContext::inclusiveOrExpression() {
  return getRuleContexts<C_grammarParser::InclusiveOrExpressionContext>();
}

C_grammarParser::InclusiveOrExpressionContext* C_grammarParser::LogicalAndExpressionContext::inclusiveOrExpression(size_t i) {
  return getRuleContext<C_grammarParser::InclusiveOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::LogicalAndExpressionContext::AndAnd() {
  return getTokens(C_grammarParser::AndAnd);
}

tree::TerminalNode* C_grammarParser::LogicalAndExpressionContext::AndAnd(size_t i) {
  return getToken(C_grammarParser::AndAnd, i);
}


size_t C_grammarParser::LogicalAndExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleLogicalAndExpression;
}

void C_grammarParser::LogicalAndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAndExpression(this);
}

void C_grammarParser::LogicalAndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAndExpression(this);
}


std::any C_grammarParser::LogicalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitLogicalAndExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::LogicalAndExpressionContext* C_grammarParser::logicalAndExpression() {
  LogicalAndExpressionContext *_localctx = _tracker.createInstance<LogicalAndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 38, C_grammarParser::RuleLogicalAndExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(280);
    inclusiveOrExpression();
    setState(285);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::AndAnd) {
      setState(281);
      match(C_grammarParser::AndAnd);
      setState(282);
      inclusiveOrExpression();
      setState(287);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogicalOrExpressionContext ------------------------------------------------------------------

C_grammarParser::LogicalOrExpressionContext::LogicalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::LogicalAndExpressionContext *> C_grammarParser::LogicalOrExpressionContext::logicalAndExpression() {
  return getRuleContexts<C_grammarParser::LogicalAndExpressionContext>();
}

C_grammarParser::LogicalAndExpressionContext* C_grammarParser::LogicalOrExpressionContext::logicalAndExpression(size_t i) {
  return getRuleContext<C_grammarParser::LogicalAndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::LogicalOrExpressionContext::OrOr() {
  return getTokens(C_grammarParser::OrOr);
}

tree::TerminalNode* C_grammarParser::LogicalOrExpressionContext::OrOr(size_t i) {
  return getToken(C_grammarParser::OrOr, i);
}


size_t C_grammarParser::LogicalOrExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleLogicalOrExpression;
}

void C_grammarParser::LogicalOrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOrExpression(this);
}

void C_grammarParser::LogicalOrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOrExpression(this);
}


std::any C_grammarParser::LogicalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitLogicalOrExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::LogicalOrExpressionContext* C_grammarParser::logicalOrExpression() {
  LogicalOrExpressionContext *_localctx = _tracker.createInstance<LogicalOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 40, C_grammarParser::RuleLogicalOrExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(288);
    logicalAndExpression();
    setState(293);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::OrOr) {
      setState(289);
      match(C_grammarParser::OrOr);
      setState(290);
      logicalAndExpression();
      setState(295);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalExpressionContext ------------------------------------------------------------------

C_grammarParser::ConditionalExpressionContext::ConditionalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::LogicalOrExpressionContext* C_grammarParser::ConditionalExpressionContext::logicalOrExpression() {
  return getRuleContext<C_grammarParser::LogicalOrExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::ConditionalExpressionContext::Question() {
  return getToken(C_grammarParser::Question, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::ConditionalExpressionContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::ConditionalExpressionContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::ConditionalExpressionContext::conditionalExpression() {
  return getRuleContext<C_grammarParser::ConditionalExpressionContext>(0);
}


size_t C_grammarParser::ConditionalExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleConditionalExpression;
}

void C_grammarParser::ConditionalExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalExpression(this);
}

void C_grammarParser::ConditionalExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalExpression(this);
}


std::any C_grammarParser::ConditionalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConditionalExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::conditionalExpression() {
  ConditionalExpressionContext *_localctx = _tracker.createInstance<ConditionalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 42, C_grammarParser::RuleConditionalExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(296);
    logicalOrExpression();
    setState(302);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Question) {
      setState(297);
      match(C_grammarParser::Question);
      setState(298);
      expression();
      setState(299);
      match(C_grammarParser::Colon);
      setState(300);
      conditionalExpression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentExpressionContext ------------------------------------------------------------------

C_grammarParser::AssignmentExpressionContext::AssignmentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::AssignmentExpressionContext::conditionalExpression() {
  return getRuleContext<C_grammarParser::ConditionalExpressionContext>(0);
}

C_grammarParser::UnaryExpressionContext* C_grammarParser::AssignmentExpressionContext::unaryExpression() {
  return getRuleContext<C_grammarParser::UnaryExpressionContext>(0);
}

C_grammarParser::AssignmentOperatorContext* C_grammarParser::AssignmentExpressionContext::assignmentOperator() {
  return getRuleContext<C_grammarParser::AssignmentOperatorContext>(0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::AssignmentExpressionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::AssignmentExpressionContext::DigitSequence() {
  return getToken(C_grammarParser::DigitSequence, 0);
}


size_t C_grammarParser::AssignmentExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleAssignmentExpression;
}

void C_grammarParser::AssignmentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentExpression(this);
}

void C_grammarParser::AssignmentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentExpression(this);
}


std::any C_grammarParser::AssignmentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAssignmentExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::assignmentExpression() {
  AssignmentExpressionContext *_localctx = _tracker.createInstance<AssignmentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 44, C_grammarParser::RuleAssignmentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(310);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(304);
      conditionalExpression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(305);
      unaryExpression();
      setState(306);
      assignmentOperator();
      setState(307);
      assignmentExpression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(309);
      match(C_grammarParser::DigitSequence);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentOperatorContext ------------------------------------------------------------------

C_grammarParser::AssignmentOperatorContext::AssignmentOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::StarAssign() {
  return getToken(C_grammarParser::StarAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::DivAssign() {
  return getToken(C_grammarParser::DivAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::ModAssign() {
  return getToken(C_grammarParser::ModAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::PlusAssign() {
  return getToken(C_grammarParser::PlusAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::MinusAssign() {
  return getToken(C_grammarParser::MinusAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::LeftShiftAssign() {
  return getToken(C_grammarParser::LeftShiftAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::RightShiftAssign() {
  return getToken(C_grammarParser::RightShiftAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::AndAssign() {
  return getToken(C_grammarParser::AndAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::XorAssign() {
  return getToken(C_grammarParser::XorAssign, 0);
}

tree::TerminalNode* C_grammarParser::AssignmentOperatorContext::OrAssign() {
  return getToken(C_grammarParser::OrAssign, 0);
}


size_t C_grammarParser::AssignmentOperatorContext::getRuleIndex() const {
  return C_grammarParser::RuleAssignmentOperator;
}

void C_grammarParser::AssignmentOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignmentOperator(this);
}

void C_grammarParser::AssignmentOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignmentOperator(this);
}


std::any C_grammarParser::AssignmentOperatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitAssignmentOperator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::AssignmentOperatorContext* C_grammarParser::assignmentOperator() {
  AssignmentOperatorContext *_localctx = _tracker.createInstance<AssignmentOperatorContext>(_ctx, getState());
  enterRule(_localctx, 46, C_grammarParser::RuleAssignmentOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2304717109306851328) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

C_grammarParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AssignmentExpressionContext *> C_grammarParser::ExpressionContext::assignmentExpression() {
  return getRuleContexts<C_grammarParser::AssignmentExpressionContext>();
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ExpressionContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ExpressionContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleExpression;
}

void C_grammarParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void C_grammarParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any C_grammarParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExpressionContext* C_grammarParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 48, C_grammarParser::RuleExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
    assignmentExpression();
    setState(319);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(315);
      match(C_grammarParser::Comma);
      setState(316);
      assignmentExpression();
      setState(321);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantExpressionContext ------------------------------------------------------------------

C_grammarParser::ConstantExpressionContext::ConstantExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ConditionalExpressionContext* C_grammarParser::ConstantExpressionContext::conditionalExpression() {
  return getRuleContext<C_grammarParser::ConditionalExpressionContext>(0);
}


size_t C_grammarParser::ConstantExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleConstantExpression;
}

void C_grammarParser::ConstantExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstantExpression(this);
}

void C_grammarParser::ConstantExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstantExpression(this);
}


std::any C_grammarParser::ConstantExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConstantExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::constantExpression() {
  ConstantExpressionContext *_localctx = _tracker.createInstance<ConstantExpressionContext>(_ctx, getState());
  enterRule(_localctx, 50, C_grammarParser::RuleConstantExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(322);
    conditionalExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

C_grammarParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::DeclarationContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

tree::TerminalNode* C_grammarParser::DeclarationContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}

C_grammarParser::InitDeclaratorListContext* C_grammarParser::DeclarationContext::initDeclaratorList() {
  return getRuleContext<C_grammarParser::InitDeclaratorListContext>(0);
}


size_t C_grammarParser::DeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclaration;
}

void C_grammarParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void C_grammarParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


std::any C_grammarParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclarationContext* C_grammarParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 52, C_grammarParser::RuleDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Const) {
      setState(324);
      match(C_grammarParser::Const);
    }
    setState(327);
    typeSpecifier();
    setState(329);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftParen

    || _la == C_grammarParser::Identifier) {
      setState(328);
      initDeclaratorList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitDeclaratorListContext ------------------------------------------------------------------

C_grammarParser::InitDeclaratorListContext::InitDeclaratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::InitDeclaratorContext *> C_grammarParser::InitDeclaratorListContext::initDeclarator() {
  return getRuleContexts<C_grammarParser::InitDeclaratorContext>();
}

C_grammarParser::InitDeclaratorContext* C_grammarParser::InitDeclaratorListContext::initDeclarator(size_t i) {
  return getRuleContext<C_grammarParser::InitDeclaratorContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::InitDeclaratorListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::InitDeclaratorListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::InitDeclaratorListContext::getRuleIndex() const {
  return C_grammarParser::RuleInitDeclaratorList;
}

void C_grammarParser::InitDeclaratorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitDeclaratorList(this);
}

void C_grammarParser::InitDeclaratorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitDeclaratorList(this);
}


std::any C_grammarParser::InitDeclaratorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitDeclaratorList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitDeclaratorListContext* C_grammarParser::initDeclaratorList() {
  InitDeclaratorListContext *_localctx = _tracker.createInstance<InitDeclaratorListContext>(_ctx, getState());
  enterRule(_localctx, 54, C_grammarParser::RuleInitDeclaratorList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(331);
    initDeclarator();
    setState(336);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(332);
      match(C_grammarParser::Comma);
      setState(333);
      initDeclarator();
      setState(338);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitDeclaratorContext ------------------------------------------------------------------

C_grammarParser::InitDeclaratorContext::InitDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclaratorContext* C_grammarParser::InitDeclaratorContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::InitDeclaratorContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}

C_grammarParser::InitializerContext* C_grammarParser::InitDeclaratorContext::initializer() {
  return getRuleContext<C_grammarParser::InitializerContext>(0);
}


size_t C_grammarParser::InitDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleInitDeclarator;
}

void C_grammarParser::InitDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitDeclarator(this);
}

void C_grammarParser::InitDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitDeclarator(this);
}


std::any C_grammarParser::InitDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitDeclaratorContext* C_grammarParser::initDeclarator() {
  InitDeclaratorContext *_localctx = _tracker.createInstance<InitDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 56, C_grammarParser::RuleInitDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(339);
    declarator();
    setState(342);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Assign) {
      setState(340);
      match(C_grammarParser::Assign);
      setState(341);
      initializer();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSpecifierContext ------------------------------------------------------------------

C_grammarParser::TypeSpecifierContext::TypeSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Void() {
  return getToken(C_grammarParser::Void, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Char() {
  return getToken(C_grammarParser::Char, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Short() {
  return getToken(C_grammarParser::Short, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Int() {
  return getToken(C_grammarParser::Int, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Long() {
  return getToken(C_grammarParser::Long, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Float() {
  return getToken(C_grammarParser::Float, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Signed() {
  return getToken(C_grammarParser::Signed, 0);
}

tree::TerminalNode* C_grammarParser::TypeSpecifierContext::Unsigned() {
  return getToken(C_grammarParser::Unsigned, 0);
}

C_grammarParser::StructOrUnionSpecifierContext* C_grammarParser::TypeSpecifierContext::structOrUnionSpecifier() {
  return getRuleContext<C_grammarParser::StructOrUnionSpecifierContext>(0);
}

C_grammarParser::TypedefNameContext* C_grammarParser::TypeSpecifierContext::typedefName() {
  return getRuleContext<C_grammarParser::TypedefNameContext>(0);
}


size_t C_grammarParser::TypeSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleTypeSpecifier;
}

void C_grammarParser::TypeSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSpecifier(this);
}

void C_grammarParser::TypeSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSpecifier(this);
}


std::any C_grammarParser::TypeSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypeSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::typeSpecifier() {
  TypeSpecifierContext *_localctx = _tracker.createInstance<TypeSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 58, C_grammarParser::RuleTypeSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(347);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::Char:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void: {
        enterOuterAlt(_localctx, 1);
        setState(344);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 224400) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case C_grammarParser::T__0:
      case C_grammarParser::T__1: {
        enterOuterAlt(_localctx, 2);
        setState(345);
        structOrUnionSpecifier();
        break;
      }

      case C_grammarParser::Identifier: {
        enterOuterAlt(_localctx, 3);
        setState(346);
        typedefName();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructOrUnionSpecifierContext ------------------------------------------------------------------

C_grammarParser::StructOrUnionSpecifierContext::StructOrUnionSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StructOrUnionContext* C_grammarParser::StructOrUnionSpecifierContext::structOrUnion() {
  return getRuleContext<C_grammarParser::StructOrUnionContext>(0);
}

tree::TerminalNode* C_grammarParser::StructOrUnionSpecifierContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

C_grammarParser::StructDeclarationListContext* C_grammarParser::StructOrUnionSpecifierContext::structDeclarationList() {
  return getRuleContext<C_grammarParser::StructDeclarationListContext>(0);
}

tree::TerminalNode* C_grammarParser::StructOrUnionSpecifierContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

tree::TerminalNode* C_grammarParser::StructOrUnionSpecifierContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::StructOrUnionSpecifierContext::getRuleIndex() const {
  return C_grammarParser::RuleStructOrUnionSpecifier;
}

void C_grammarParser::StructOrUnionSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructOrUnionSpecifier(this);
}

void C_grammarParser::StructOrUnionSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructOrUnionSpecifier(this);
}


std::any C_grammarParser::StructOrUnionSpecifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructOrUnionSpecifier(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructOrUnionSpecifierContext* C_grammarParser::structOrUnionSpecifier() {
  StructOrUnionSpecifierContext *_localctx = _tracker.createInstance<StructOrUnionSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 60, C_grammarParser::RuleStructOrUnionSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(360);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(349);
      structOrUnion();
      setState(351);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Identifier) {
        setState(350);
        match(C_grammarParser::Identifier);
      }
      setState(353);
      match(C_grammarParser::LeftBrace);
      setState(354);
      structDeclarationList();
      setState(355);
      match(C_grammarParser::RightBrace);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(357);
      structOrUnion();
      setState(358);
      match(C_grammarParser::Identifier);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructOrUnionContext ------------------------------------------------------------------

C_grammarParser::StructOrUnionContext::StructOrUnionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t C_grammarParser::StructOrUnionContext::getRuleIndex() const {
  return C_grammarParser::RuleStructOrUnion;
}

void C_grammarParser::StructOrUnionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructOrUnion(this);
}

void C_grammarParser::StructOrUnionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructOrUnion(this);
}


std::any C_grammarParser::StructOrUnionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructOrUnion(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructOrUnionContext* C_grammarParser::structOrUnion() {
  StructOrUnionContext *_localctx = _tracker.createInstance<StructOrUnionContext>(_ctx, getState());
  enterRule(_localctx, 62, C_grammarParser::RuleStructOrUnion);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(362);
    _la = _input->LA(1);
    if (!(_la == C_grammarParser::T__0

    || _la == C_grammarParser::T__1)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDeclarationListContext ------------------------------------------------------------------

C_grammarParser::StructDeclarationListContext::StructDeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::StructDeclarationContext *> C_grammarParser::StructDeclarationListContext::structDeclaration() {
  return getRuleContexts<C_grammarParser::StructDeclarationContext>();
}

C_grammarParser::StructDeclarationContext* C_grammarParser::StructDeclarationListContext::structDeclaration(size_t i) {
  return getRuleContext<C_grammarParser::StructDeclarationContext>(i);
}


size_t C_grammarParser::StructDeclarationListContext::getRuleIndex() const {
  return C_grammarParser::RuleStructDeclarationList;
}

void C_grammarParser::StructDeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDeclarationList(this);
}

void C_grammarParser::StructDeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDeclarationList(this);
}


std::any C_grammarParser::StructDeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructDeclarationListContext* C_grammarParser::structDeclarationList() {
  StructDeclarationListContext *_localctx = _tracker.createInstance<StructDeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 64, C_grammarParser::RuleStructDeclarationList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(365); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(364);
      structDeclaration();
      setState(367); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 224438) != 0) || _la == C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SpecifierQualifierListContext ------------------------------------------------------------------

C_grammarParser::SpecifierQualifierListContext::SpecifierQualifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::SpecifierQualifierListContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

tree::TerminalNode* C_grammarParser::SpecifierQualifierListContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::SpecifierQualifierListContext::specifierQualifierList() {
  return getRuleContext<C_grammarParser::SpecifierQualifierListContext>(0);
}


size_t C_grammarParser::SpecifierQualifierListContext::getRuleIndex() const {
  return C_grammarParser::RuleSpecifierQualifierList;
}

void C_grammarParser::SpecifierQualifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSpecifierQualifierList(this);
}

void C_grammarParser::SpecifierQualifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSpecifierQualifierList(this);
}


std::any C_grammarParser::SpecifierQualifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitSpecifierQualifierList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::specifierQualifierList() {
  SpecifierQualifierListContext *_localctx = _tracker.createInstance<SpecifierQualifierListContext>(_ctx, getState());
  enterRule(_localctx, 66, C_grammarParser::RuleSpecifierQualifierList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(371);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::T__0:
      case C_grammarParser::T__1:
      case C_grammarParser::Char:
      case C_grammarParser::Float:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::Identifier: {
        setState(369);
        typeSpecifier();
        break;
      }

      case C_grammarParser::Const: {
        setState(370);
        match(C_grammarParser::Const);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(374);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      setState(373);
      specifierQualifierList();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDeclarationContext ------------------------------------------------------------------

C_grammarParser::StructDeclarationContext::StructDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::StructDeclarationContext::specifierQualifierList() {
  return getRuleContext<C_grammarParser::SpecifierQualifierListContext>(0);
}

C_grammarParser::StructDeclaratorListContext* C_grammarParser::StructDeclarationContext::structDeclaratorList() {
  return getRuleContext<C_grammarParser::StructDeclaratorListContext>(0);
}

tree::TerminalNode* C_grammarParser::StructDeclarationContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::StructDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleStructDeclaration;
}

void C_grammarParser::StructDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDeclaration(this);
}

void C_grammarParser::StructDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDeclaration(this);
}


std::any C_grammarParser::StructDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructDeclarationContext* C_grammarParser::structDeclaration() {
  StructDeclarationContext *_localctx = _tracker.createInstance<StructDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 68, C_grammarParser::RuleStructDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(383);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(376);
      specifierQualifierList();
      setState(377);
      structDeclaratorList();
      setState(378);
      match(C_grammarParser::Semi);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(380);
      specifierQualifierList();
      setState(381);
      match(C_grammarParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDeclaratorListContext ------------------------------------------------------------------

C_grammarParser::StructDeclaratorListContext::StructDeclaratorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::StructDeclaratorContext *> C_grammarParser::StructDeclaratorListContext::structDeclarator() {
  return getRuleContexts<C_grammarParser::StructDeclaratorContext>();
}

C_grammarParser::StructDeclaratorContext* C_grammarParser::StructDeclaratorListContext::structDeclarator(size_t i) {
  return getRuleContext<C_grammarParser::StructDeclaratorContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::StructDeclaratorListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::StructDeclaratorListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::StructDeclaratorListContext::getRuleIndex() const {
  return C_grammarParser::RuleStructDeclaratorList;
}

void C_grammarParser::StructDeclaratorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDeclaratorList(this);
}

void C_grammarParser::StructDeclaratorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDeclaratorList(this);
}


std::any C_grammarParser::StructDeclaratorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructDeclaratorList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructDeclaratorListContext* C_grammarParser::structDeclaratorList() {
  StructDeclaratorListContext *_localctx = _tracker.createInstance<StructDeclaratorListContext>(_ctx, getState());
  enterRule(_localctx, 70, C_grammarParser::RuleStructDeclaratorList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(385);
    structDeclarator();
    setState(390);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(386);
      match(C_grammarParser::Comma);
      setState(387);
      structDeclarator();
      setState(392);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDeclaratorContext ------------------------------------------------------------------

C_grammarParser::StructDeclaratorContext::StructDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclaratorContext* C_grammarParser::StructDeclaratorContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::StructDeclaratorContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::StructDeclaratorContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}


size_t C_grammarParser::StructDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleStructDeclarator;
}

void C_grammarParser::StructDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStructDeclarator(this);
}

void C_grammarParser::StructDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStructDeclarator(this);
}


std::any C_grammarParser::StructDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStructDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StructDeclaratorContext* C_grammarParser::structDeclarator() {
  StructDeclaratorContext *_localctx = _tracker.createInstance<StructDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 72, C_grammarParser::RuleStructDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(399);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(393);
      declarator();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(395);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::LeftParen

      || _la == C_grammarParser::Identifier) {
        setState(394);
        declarator();
      }
      setState(397);
      match(C_grammarParser::Colon);
      setState(398);
      constantExpression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclaratorContext ------------------------------------------------------------------

C_grammarParser::DeclaratorContext::DeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::DeclaratorContext::directDeclarator() {
  return getRuleContext<C_grammarParser::DirectDeclaratorContext>(0);
}


size_t C_grammarParser::DeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclarator;
}

void C_grammarParser::DeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarator(this);
}

void C_grammarParser::DeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarator(this);
}


std::any C_grammarParser::DeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclaratorContext* C_grammarParser::declarator() {
  DeclaratorContext *_localctx = _tracker.createInstance<DeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 74, C_grammarParser::RuleDeclarator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(401);
    directDeclarator(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DirectDeclaratorContext ------------------------------------------------------------------

C_grammarParser::DirectDeclaratorContext::DirectDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::DeclaratorContext* C_grammarParser::DirectDeclaratorContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::Colon() {
  return getToken(C_grammarParser::Colon, 0);
}

tree::TerminalNode* C_grammarParser::DirectDeclaratorContext::DigitSequence() {
  return getToken(C_grammarParser::DigitSequence, 0);
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::DirectDeclaratorContext::directDeclarator() {
  return getRuleContext<C_grammarParser::DirectDeclaratorContext>(0);
}

std::vector<C_grammarParser::ArrayDeclaratorContext *> C_grammarParser::DirectDeclaratorContext::arrayDeclarator() {
  return getRuleContexts<C_grammarParser::ArrayDeclaratorContext>();
}

C_grammarParser::ArrayDeclaratorContext* C_grammarParser::DirectDeclaratorContext::arrayDeclarator(size_t i) {
  return getRuleContext<C_grammarParser::ArrayDeclaratorContext>(i);
}

C_grammarParser::ParameterTypeListContext* C_grammarParser::DirectDeclaratorContext::parameterTypeList() {
  return getRuleContext<C_grammarParser::ParameterTypeListContext>(0);
}

C_grammarParser::IdentifierListContext* C_grammarParser::DirectDeclaratorContext::identifierList() {
  return getRuleContext<C_grammarParser::IdentifierListContext>(0);
}


size_t C_grammarParser::DirectDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleDirectDeclarator;
}

void C_grammarParser::DirectDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirectDeclarator(this);
}

void C_grammarParser::DirectDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirectDeclarator(this);
}


std::any C_grammarParser::DirectDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDirectDeclarator(this);
  else
    return visitor->visitChildren(this);
}


C_grammarParser::DirectDeclaratorContext* C_grammarParser::directDeclarator() {
   return directDeclarator(0);
}

C_grammarParser::DirectDeclaratorContext* C_grammarParser::directDeclarator(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  C_grammarParser::DirectDeclaratorContext *_localctx = _tracker.createInstance<DirectDeclaratorContext>(_ctx, parentState);
  C_grammarParser::DirectDeclaratorContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 76;
  enterRecursionRule(_localctx, 76, C_grammarParser::RuleDirectDeclarator, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(412);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(404);
      match(C_grammarParser::Identifier);
      break;
    }

    case 2: {
      setState(405);
      match(C_grammarParser::LeftParen);
      setState(406);
      declarator();
      setState(407);
      match(C_grammarParser::RightParen);
      break;
    }

    case 3: {
      setState(409);
      match(C_grammarParser::Identifier);
      setState(410);
      match(C_grammarParser::Colon);
      setState(411);
      match(C_grammarParser::DigitSequence);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(433);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(431);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(414);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(416); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(415);
                    arrayDeclarator();
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(418); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(420);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(421);
          match(C_grammarParser::LeftParen);
          setState(422);
          parameterTypeList();
          setState(423);
          match(C_grammarParser::RightParen);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<DirectDeclaratorContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleDirectDeclarator);
          setState(425);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(426);
          match(C_grammarParser::LeftParen);
          setState(428);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == C_grammarParser::Identifier) {
            setState(427);
            identifierList();
          }
          setState(430);
          match(C_grammarParser::RightParen);
          break;
        }

        default:
          break;
        } 
      }
      setState(435);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ArrayDeclaratorContext ------------------------------------------------------------------

C_grammarParser::ArrayDeclaratorContext::ArrayDeclaratorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ArrayDeclaratorContext::LeftBracket() {
  return getToken(C_grammarParser::LeftBracket, 0);
}

tree::TerminalNode* C_grammarParser::ArrayDeclaratorContext::RightBracket() {
  return getToken(C_grammarParser::RightBracket, 0);
}

tree::TerminalNode* C_grammarParser::ArrayDeclaratorContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ArrayDeclaratorContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}


size_t C_grammarParser::ArrayDeclaratorContext::getRuleIndex() const {
  return C_grammarParser::RuleArrayDeclarator;
}

void C_grammarParser::ArrayDeclaratorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayDeclarator(this);
}

void C_grammarParser::ArrayDeclaratorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayDeclarator(this);
}


std::any C_grammarParser::ArrayDeclaratorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArrayDeclarator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArrayDeclaratorContext* C_grammarParser::arrayDeclarator() {
  ArrayDeclaratorContext *_localctx = _tracker.createInstance<ArrayDeclaratorContext>(_ctx, getState());
  enterRule(_localctx, 78, C_grammarParser::RuleArrayDeclarator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
    match(C_grammarParser::LeftBracket);
    setState(438);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Const) {
      setState(437);
      match(C_grammarParser::Const);
    }
    setState(441);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 20) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 20)) & 4433230933581825) != 0)) {
      setState(440);
      assignmentExpression();
    }
    setState(443);
    match(C_grammarParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NestedParenthesesBlockContext ------------------------------------------------------------------

C_grammarParser::NestedParenthesesBlockContext::NestedParenthesesBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> C_grammarParser::NestedParenthesesBlockContext::LeftParen() {
  return getTokens(C_grammarParser::LeftParen);
}

tree::TerminalNode* C_grammarParser::NestedParenthesesBlockContext::LeftParen(size_t i) {
  return getToken(C_grammarParser::LeftParen, i);
}

std::vector<C_grammarParser::NestedParenthesesBlockContext *> C_grammarParser::NestedParenthesesBlockContext::nestedParenthesesBlock() {
  return getRuleContexts<C_grammarParser::NestedParenthesesBlockContext>();
}

C_grammarParser::NestedParenthesesBlockContext* C_grammarParser::NestedParenthesesBlockContext::nestedParenthesesBlock(size_t i) {
  return getRuleContext<C_grammarParser::NestedParenthesesBlockContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::NestedParenthesesBlockContext::RightParen() {
  return getTokens(C_grammarParser::RightParen);
}

tree::TerminalNode* C_grammarParser::NestedParenthesesBlockContext::RightParen(size_t i) {
  return getToken(C_grammarParser::RightParen, i);
}


size_t C_grammarParser::NestedParenthesesBlockContext::getRuleIndex() const {
  return C_grammarParser::RuleNestedParenthesesBlock;
}

void C_grammarParser::NestedParenthesesBlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNestedParenthesesBlock(this);
}

void C_grammarParser::NestedParenthesesBlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNestedParenthesesBlock(this);
}


std::any C_grammarParser::NestedParenthesesBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitNestedParenthesesBlock(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::NestedParenthesesBlockContext* C_grammarParser::nestedParenthesesBlock() {
  NestedParenthesesBlockContext *_localctx = _tracker.createInstance<NestedParenthesesBlockContext>(_ctx, getState());
  enterRule(_localctx, 80, C_grammarParser::RuleNestedParenthesesBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(452);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -2097154) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 262143) != 0)) {
      setState(450);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case C_grammarParser::T__0:
        case C_grammarParser::T__1:
        case C_grammarParser::Case:
        case C_grammarParser::Char:
        case C_grammarParser::Const:
        case C_grammarParser::Else:
        case C_grammarParser::Float:
        case C_grammarParser::For:
        case C_grammarParser::If:
        case C_grammarParser::Int:
        case C_grammarParser::Long:
        case C_grammarParser::Return:
        case C_grammarParser::Short:
        case C_grammarParser::Signed:
        case C_grammarParser::Typedef:
        case C_grammarParser::Unsigned:
        case C_grammarParser::Void:
        case C_grammarParser::Volatile:
        case C_grammarParser::While:
        case C_grammarParser::LeftBracket:
        case C_grammarParser::RightBracket:
        case C_grammarParser::LeftBrace:
        case C_grammarParser::RightBrace:
        case C_grammarParser::Less:
        case C_grammarParser::LessEqual:
        case C_grammarParser::Greater:
        case C_grammarParser::GreaterEqual:
        case C_grammarParser::LeftShift:
        case C_grammarParser::RightShift:
        case C_grammarParser::Plus:
        case C_grammarParser::PlusPlus:
        case C_grammarParser::Minus:
        case C_grammarParser::MinusMinus:
        case C_grammarParser::Star:
        case C_grammarParser::Div:
        case C_grammarParser::Mod:
        case C_grammarParser::And:
        case C_grammarParser::Or:
        case C_grammarParser::AndAnd:
        case C_grammarParser::OrOr:
        case C_grammarParser::Caret:
        case C_grammarParser::Not:
        case C_grammarParser::Tilde:
        case C_grammarParser::Question:
        case C_grammarParser::Colon:
        case C_grammarParser::Semi:
        case C_grammarParser::Comma:
        case C_grammarParser::Assign:
        case C_grammarParser::StarAssign:
        case C_grammarParser::DivAssign:
        case C_grammarParser::ModAssign:
        case C_grammarParser::PlusAssign:
        case C_grammarParser::MinusAssign:
        case C_grammarParser::LeftShiftAssign:
        case C_grammarParser::RightShiftAssign:
        case C_grammarParser::AndAssign:
        case C_grammarParser::XorAssign:
        case C_grammarParser::OrAssign:
        case C_grammarParser::Equal:
        case C_grammarParser::NotEqual:
        case C_grammarParser::Arrow:
        case C_grammarParser::Dot:
        case C_grammarParser::Ellipsis:
        case C_grammarParser::Identifier:
        case C_grammarParser::IntegerConstant:
        case C_grammarParser::FloatingConstant:
        case C_grammarParser::DigitSequence:
        case C_grammarParser::CharacterConstant:
        case C_grammarParser::StringLiteral:
        case C_grammarParser::ComplexDefine:
        case C_grammarParser::IncludeDirective:
        case C_grammarParser::AsmBlock:
        case C_grammarParser::LineAfterPreprocessing:
        case C_grammarParser::LineDirective:
        case C_grammarParser::PragmaDirective:
        case C_grammarParser::Whitespace:
        case C_grammarParser::Newline:
        case C_grammarParser::BlockComment:
        case C_grammarParser::LineComment: {
          setState(445);
          _la = _input->LA(1);
          if (_la == 0 || _la == Token::EOF || (_la == C_grammarParser::LeftParen

          || _la == C_grammarParser::RightParen)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        case C_grammarParser::LeftParen: {
          setState(446);
          match(C_grammarParser::LeftParen);
          setState(447);
          nestedParenthesesBlock();
          setState(448);
          match(C_grammarParser::RightParen);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(454);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterTypeListContext ------------------------------------------------------------------

C_grammarParser::ParameterTypeListContext::ParameterTypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ParameterListContext* C_grammarParser::ParameterTypeListContext::parameterList() {
  return getRuleContext<C_grammarParser::ParameterListContext>(0);
}

tree::TerminalNode* C_grammarParser::ParameterTypeListContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}

tree::TerminalNode* C_grammarParser::ParameterTypeListContext::Ellipsis() {
  return getToken(C_grammarParser::Ellipsis, 0);
}


size_t C_grammarParser::ParameterTypeListContext::getRuleIndex() const {
  return C_grammarParser::RuleParameterTypeList;
}

void C_grammarParser::ParameterTypeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterTypeList(this);
}

void C_grammarParser::ParameterTypeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterTypeList(this);
}


std::any C_grammarParser::ParameterTypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitParameterTypeList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ParameterTypeListContext* C_grammarParser::parameterTypeList() {
  ParameterTypeListContext *_localctx = _tracker.createInstance<ParameterTypeListContext>(_ctx, getState());
  enterRule(_localctx, 82, C_grammarParser::RuleParameterTypeList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(455);
    parameterList();
    setState(458);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Comma) {
      setState(456);
      match(C_grammarParser::Comma);
      setState(457);
      match(C_grammarParser::Ellipsis);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

C_grammarParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ParameterDeclarationContext *> C_grammarParser::ParameterListContext::parameterDeclaration() {
  return getRuleContexts<C_grammarParser::ParameterDeclarationContext>();
}

C_grammarParser::ParameterDeclarationContext* C_grammarParser::ParameterListContext::parameterDeclaration(size_t i) {
  return getRuleContext<C_grammarParser::ParameterDeclarationContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ParameterListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ParameterListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ParameterListContext::getRuleIndex() const {
  return C_grammarParser::RuleParameterList;
}

void C_grammarParser::ParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterList(this);
}

void C_grammarParser::ParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterList(this);
}


std::any C_grammarParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ParameterListContext* C_grammarParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 84, C_grammarParser::RuleParameterList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(460);
    parameterDeclaration();
    setState(465);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(461);
        match(C_grammarParser::Comma);
        setState(462);
        parameterDeclaration(); 
      }
      setState(467);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterDeclarationContext ------------------------------------------------------------------

C_grammarParser::ParameterDeclarationContext::ParameterDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::ParameterDeclarationContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

C_grammarParser::DeclaratorContext* C_grammarParser::ParameterDeclarationContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

tree::TerminalNode* C_grammarParser::ParameterDeclarationContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}


size_t C_grammarParser::ParameterDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleParameterDeclaration;
}

void C_grammarParser::ParameterDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterDeclaration(this);
}

void C_grammarParser::ParameterDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterDeclaration(this);
}


std::any C_grammarParser::ParameterDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitParameterDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ParameterDeclarationContext* C_grammarParser::parameterDeclaration() {
  ParameterDeclarationContext *_localctx = _tracker.createInstance<ParameterDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 86, C_grammarParser::RuleParameterDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(469);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::Const) {
      setState(468);
      match(C_grammarParser::Const);
    }
    setState(471);
    typeSpecifier();
    setState(472);
    declarator();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierListContext ------------------------------------------------------------------

C_grammarParser::IdentifierListContext::IdentifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> C_grammarParser::IdentifierListContext::Identifier() {
  return getTokens(C_grammarParser::Identifier);
}

tree::TerminalNode* C_grammarParser::IdentifierListContext::Identifier(size_t i) {
  return getToken(C_grammarParser::Identifier, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::IdentifierListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::IdentifierListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::IdentifierListContext::getRuleIndex() const {
  return C_grammarParser::RuleIdentifierList;
}

void C_grammarParser::IdentifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierList(this);
}

void C_grammarParser::IdentifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierList(this);
}


std::any C_grammarParser::IdentifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitIdentifierList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::IdentifierListContext* C_grammarParser::identifierList() {
  IdentifierListContext *_localctx = _tracker.createInstance<IdentifierListContext>(_ctx, getState());
  enterRule(_localctx, 88, C_grammarParser::RuleIdentifierList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(474);
    match(C_grammarParser::Identifier);
    setState(479);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(475);
      match(C_grammarParser::Comma);
      setState(476);
      match(C_grammarParser::Identifier);
      setState(481);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameContext ------------------------------------------------------------------

C_grammarParser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::SpecifierQualifierListContext* C_grammarParser::TypeNameContext::specifierQualifierList() {
  return getRuleContext<C_grammarParser::SpecifierQualifierListContext>(0);
}


size_t C_grammarParser::TypeNameContext::getRuleIndex() const {
  return C_grammarParser::RuleTypeName;
}

void C_grammarParser::TypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeName(this);
}

void C_grammarParser::TypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeName(this);
}


std::any C_grammarParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypeNameContext* C_grammarParser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 90, C_grammarParser::RuleTypeName);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(483);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 224438) != 0) || _la == C_grammarParser::Identifier) {
      setState(482);
      specifierQualifierList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypedefNameContext ------------------------------------------------------------------

C_grammarParser::TypedefNameContext::TypedefNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::TypedefNameContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::TypedefNameContext::getRuleIndex() const {
  return C_grammarParser::RuleTypedefName;
}

void C_grammarParser::TypedefNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypedefName(this);
}

void C_grammarParser::TypedefNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypedefName(this);
}


std::any C_grammarParser::TypedefNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTypedefName(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TypedefNameContext* C_grammarParser::typedefName() {
  TypedefNameContext *_localctx = _tracker.createInstance<TypedefNameContext>(_ctx, getState());
  enterRule(_localctx, 92, C_grammarParser::RuleTypedefName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(485);
    match(C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerContext ------------------------------------------------------------------

C_grammarParser::InitializerContext::InitializerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::InitializerContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::InitializerContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

C_grammarParser::InitializerListContext* C_grammarParser::InitializerContext::initializerList() {
  return getRuleContext<C_grammarParser::InitializerListContext>(0);
}

tree::TerminalNode* C_grammarParser::InitializerContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

tree::TerminalNode* C_grammarParser::InitializerContext::Comma() {
  return getToken(C_grammarParser::Comma, 0);
}


size_t C_grammarParser::InitializerContext::getRuleIndex() const {
  return C_grammarParser::RuleInitializer;
}

void C_grammarParser::InitializerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializer(this);
}

void C_grammarParser::InitializerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializer(this);
}


std::any C_grammarParser::InitializerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitializer(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitializerContext* C_grammarParser::initializer() {
  InitializerContext *_localctx = _tracker.createInstance<InitializerContext>(_ctx, getState());
  enterRule(_localctx, 94, C_grammarParser::RuleInitializer);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(495);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(487);
        assignmentExpression();
        break;
      }

      case C_grammarParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(488);
        match(C_grammarParser::LeftBrace);
        setState(489);
        initializerList();
        setState(491);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::Comma) {
          setState(490);
          match(C_grammarParser::Comma);
        }
        setState(493);
        match(C_grammarParser::RightBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallExpressionContext ------------------------------------------------------------------

C_grammarParser::FunctionCallExpressionContext::FunctionCallExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::TypedefNameContext* C_grammarParser::FunctionCallExpressionContext::typedefName() {
  return getRuleContext<C_grammarParser::TypedefNameContext>(0);
}

tree::TerminalNode* C_grammarParser::FunctionCallExpressionContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::FunctionCallExpressionContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::ArgumentExpressionListContext* C_grammarParser::FunctionCallExpressionContext::argumentExpressionList() {
  return getRuleContext<C_grammarParser::ArgumentExpressionListContext>(0);
}


size_t C_grammarParser::FunctionCallExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleFunctionCallExpression;
}

void C_grammarParser::FunctionCallExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCallExpression(this);
}

void C_grammarParser::FunctionCallExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCallExpression(this);
}


std::any C_grammarParser::FunctionCallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitFunctionCallExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::FunctionCallExpressionContext* C_grammarParser::functionCallExpression() {
  FunctionCallExpressionContext *_localctx = _tracker.createInstance<FunctionCallExpressionContext>(_ctx, getState());
  enterRule(_localctx, 96, C_grammarParser::RuleFunctionCallExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(497);
    typedefName();
    setState(498);
    match(C_grammarParser::LeftParen);
    setState(500);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 20) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 20)) & 4433230933581825) != 0)) {
      setState(499);
      argumentExpressionList();
    }
    setState(502);
    match(C_grammarParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentExpressionListContext ------------------------------------------------------------------

C_grammarParser::ArgumentExpressionListContext::ArgumentExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ArgumentExpressionContext *> C_grammarParser::ArgumentExpressionListContext::argumentExpression() {
  return getRuleContexts<C_grammarParser::ArgumentExpressionContext>();
}

C_grammarParser::ArgumentExpressionContext* C_grammarParser::ArgumentExpressionListContext::argumentExpression(size_t i) {
  return getRuleContext<C_grammarParser::ArgumentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ArgumentExpressionListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ArgumentExpressionListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ArgumentExpressionListContext::getRuleIndex() const {
  return C_grammarParser::RuleArgumentExpressionList;
}

void C_grammarParser::ArgumentExpressionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentExpressionList(this);
}

void C_grammarParser::ArgumentExpressionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentExpressionList(this);
}


std::any C_grammarParser::ArgumentExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArgumentExpressionList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArgumentExpressionListContext* C_grammarParser::argumentExpressionList() {
  ArgumentExpressionListContext *_localctx = _tracker.createInstance<ArgumentExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 98, C_grammarParser::RuleArgumentExpressionList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(504);
    argumentExpression();
    setState(509);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(505);
      match(C_grammarParser::Comma);
      setState(506);
      argumentExpression();
      setState(511);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentExpressionContext ------------------------------------------------------------------

C_grammarParser::ArgumentExpressionContext::ArgumentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ArgumentExpressionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}


size_t C_grammarParser::ArgumentExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleArgumentExpression;
}

void C_grammarParser::ArgumentExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentExpression(this);
}

void C_grammarParser::ArgumentExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentExpression(this);
}


std::any C_grammarParser::ArgumentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitArgumentExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ArgumentExpressionContext* C_grammarParser::argumentExpression() {
  ArgumentExpressionContext *_localctx = _tracker.createInstance<ArgumentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 100, C_grammarParser::RuleArgumentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(512);
    assignmentExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitializerListContext ------------------------------------------------------------------

C_grammarParser::InitializerListContext::InitializerListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::InitializerContext *> C_grammarParser::InitializerListContext::initializer() {
  return getRuleContexts<C_grammarParser::InitializerContext>();
}

C_grammarParser::InitializerContext* C_grammarParser::InitializerListContext::initializer(size_t i) {
  return getRuleContext<C_grammarParser::InitializerContext>(i);
}

std::vector<C_grammarParser::DesignationContext *> C_grammarParser::InitializerListContext::designation() {
  return getRuleContexts<C_grammarParser::DesignationContext>();
}

C_grammarParser::DesignationContext* C_grammarParser::InitializerListContext::designation(size_t i) {
  return getRuleContext<C_grammarParser::DesignationContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::InitializerListContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::InitializerListContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::InitializerListContext::getRuleIndex() const {
  return C_grammarParser::RuleInitializerList;
}

void C_grammarParser::InitializerListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInitializerList(this);
}

void C_grammarParser::InitializerListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInitializerList(this);
}


std::any C_grammarParser::InitializerListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitInitializerList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::InitializerListContext* C_grammarParser::initializerList() {
  InitializerListContext *_localctx = _tracker.createInstance<InitializerListContext>(_ctx, getState());
  enterRule(_localctx, 102, C_grammarParser::RuleInitializerList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(515);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == C_grammarParser::LeftBracket

    || _la == C_grammarParser::Dot) {
      setState(514);
      designation();
    }
    setState(517);
    initializer();
    setState(525);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(518);
        match(C_grammarParser::Comma);
        setState(520);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == C_grammarParser::LeftBracket

        || _la == C_grammarParser::Dot) {
          setState(519);
          designation();
        }
        setState(522);
        initializer(); 
      }
      setState(527);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignationContext ------------------------------------------------------------------

C_grammarParser::DesignationContext::DesignationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DesignatorListContext* C_grammarParser::DesignationContext::designatorList() {
  return getRuleContext<C_grammarParser::DesignatorListContext>(0);
}

tree::TerminalNode* C_grammarParser::DesignationContext::Assign() {
  return getToken(C_grammarParser::Assign, 0);
}


size_t C_grammarParser::DesignationContext::getRuleIndex() const {
  return C_grammarParser::RuleDesignation;
}

void C_grammarParser::DesignationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDesignation(this);
}

void C_grammarParser::DesignationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDesignation(this);
}


std::any C_grammarParser::DesignationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDesignation(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DesignationContext* C_grammarParser::designation() {
  DesignationContext *_localctx = _tracker.createInstance<DesignationContext>(_ctx, getState());
  enterRule(_localctx, 104, C_grammarParser::RuleDesignation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(528);
    designatorList();
    setState(529);
    match(C_grammarParser::Assign);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignatorListContext ------------------------------------------------------------------

C_grammarParser::DesignatorListContext::DesignatorListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::DesignatorContext *> C_grammarParser::DesignatorListContext::designator() {
  return getRuleContexts<C_grammarParser::DesignatorContext>();
}

C_grammarParser::DesignatorContext* C_grammarParser::DesignatorListContext::designator(size_t i) {
  return getRuleContext<C_grammarParser::DesignatorContext>(i);
}


size_t C_grammarParser::DesignatorListContext::getRuleIndex() const {
  return C_grammarParser::RuleDesignatorList;
}

void C_grammarParser::DesignatorListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDesignatorList(this);
}

void C_grammarParser::DesignatorListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDesignatorList(this);
}


std::any C_grammarParser::DesignatorListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDesignatorList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DesignatorListContext* C_grammarParser::designatorList() {
  DesignatorListContext *_localctx = _tracker.createInstance<DesignatorListContext>(_ctx, getState());
  enterRule(_localctx, 106, C_grammarParser::RuleDesignatorList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(532); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(531);
      designator();
      setState(534); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == C_grammarParser::LeftBracket

    || _la == C_grammarParser::Dot);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DesignatorContext ------------------------------------------------------------------

C_grammarParser::DesignatorContext::DesignatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::DesignatorContext::LeftBracket() {
  return getToken(C_grammarParser::LeftBracket, 0);
}

C_grammarParser::ConstantExpressionContext* C_grammarParser::DesignatorContext::constantExpression() {
  return getRuleContext<C_grammarParser::ConstantExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::DesignatorContext::RightBracket() {
  return getToken(C_grammarParser::RightBracket, 0);
}

tree::TerminalNode* C_grammarParser::DesignatorContext::Dot() {
  return getToken(C_grammarParser::Dot, 0);
}

tree::TerminalNode* C_grammarParser::DesignatorContext::Identifier() {
  return getToken(C_grammarParser::Identifier, 0);
}


size_t C_grammarParser::DesignatorContext::getRuleIndex() const {
  return C_grammarParser::RuleDesignator;
}

void C_grammarParser::DesignatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDesignator(this);
}

void C_grammarParser::DesignatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDesignator(this);
}


std::any C_grammarParser::DesignatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDesignator(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DesignatorContext* C_grammarParser::designator() {
  DesignatorContext *_localctx = _tracker.createInstance<DesignatorContext>(_ctx, getState());
  enterRule(_localctx, 108, C_grammarParser::RuleDesignator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(542);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBracket: {
        enterOuterAlt(_localctx, 1);
        setState(536);
        match(C_grammarParser::LeftBracket);
        setState(537);
        constantExpression();
        setState(538);
        match(C_grammarParser::RightBracket);
        break;
      }

      case C_grammarParser::Dot: {
        enterOuterAlt(_localctx, 2);
        setState(540);
        match(C_grammarParser::Dot);
        setState(541);
        match(C_grammarParser::Identifier);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

C_grammarParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ExpressionStatementContext* C_grammarParser::StatementContext::expressionStatement() {
  return getRuleContext<C_grammarParser::ExpressionStatementContext>(0);
}

tree::TerminalNode* C_grammarParser::StatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

C_grammarParser::SelectionStatementContext* C_grammarParser::StatementContext::selectionStatement() {
  return getRuleContext<C_grammarParser::SelectionStatementContext>(0);
}

C_grammarParser::IterationStatementContext* C_grammarParser::StatementContext::iterationStatement() {
  return getRuleContext<C_grammarParser::IterationStatementContext>(0);
}

C_grammarParser::ReturnStatementContext* C_grammarParser::StatementContext::returnStatement() {
  return getRuleContext<C_grammarParser::ReturnStatementContext>(0);
}

tree::TerminalNode* C_grammarParser::StatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

tree::TerminalNode* C_grammarParser::StatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

std::vector<C_grammarParser::LogicalOrExpressionContext *> C_grammarParser::StatementContext::logicalOrExpression() {
  return getRuleContexts<C_grammarParser::LogicalOrExpressionContext>();
}

C_grammarParser::LogicalOrExpressionContext* C_grammarParser::StatementContext::logicalOrExpression(size_t i) {
  return getRuleContext<C_grammarParser::LogicalOrExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::StatementContext::Colon() {
  return getTokens(C_grammarParser::Colon);
}

tree::TerminalNode* C_grammarParser::StatementContext::Colon(size_t i) {
  return getToken(C_grammarParser::Colon, i);
}

std::vector<tree::TerminalNode *> C_grammarParser::StatementContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::StatementContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::StatementContext::getRuleIndex() const {
  return C_grammarParser::RuleStatement;
}

void C_grammarParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void C_grammarParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any C_grammarParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::StatementContext* C_grammarParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 110, C_grammarParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(579);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(544);
      expressionStatement();
      setState(545);
      match(C_grammarParser::Semi);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(547);
      selectionStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(548);
      iterationStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(549);
      returnStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(550);
      match(C_grammarParser::LeftParen);
      setState(559);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 20) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 20)) & 3870280980160513) != 0)) {
        setState(551);
        logicalOrExpression();
        setState(556);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == C_grammarParser::Comma) {
          setState(552);
          match(C_grammarParser::Comma);
          setState(553);
          logicalOrExpression();
          setState(558);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(574);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == C_grammarParser::Colon) {
        setState(561);
        match(C_grammarParser::Colon);
        setState(570);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (((((_la - 20) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 20)) & 3870280980160513) != 0)) {
          setState(562);
          logicalOrExpression();
          setState(567);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == C_grammarParser::Comma) {
            setState(563);
            match(C_grammarParser::Comma);
            setState(564);
            logicalOrExpression();
            setState(569);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(576);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(577);
      match(C_grammarParser::RightParen);
      setState(578);
      match(C_grammarParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompoundStatementContext ------------------------------------------------------------------

C_grammarParser::CompoundStatementContext::CompoundStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::CompoundStatementContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::CompoundStatementContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::BlockItemContext *> C_grammarParser::CompoundStatementContext::blockItem() {
  return getRuleContexts<C_grammarParser::BlockItemContext>();
}

C_grammarParser::BlockItemContext* C_grammarParser::CompoundStatementContext::blockItem(size_t i) {
  return getRuleContext<C_grammarParser::BlockItemContext>(i);
}


size_t C_grammarParser::CompoundStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleCompoundStatement;
}

void C_grammarParser::CompoundStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompoundStatement(this);
}

void C_grammarParser::CompoundStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompoundStatement(this);
}


std::any C_grammarParser::CompoundStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitCompoundStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::CompoundStatementContext* C_grammarParser::compoundStatement() {
  CompoundStatementContext *_localctx = _tracker.createInstance<CompoundStatementContext>(_ctx, getState());
  enterRule(_localctx, 112, C_grammarParser::RuleCompoundStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(581);
    match(C_grammarParser::LeftBrace);
    setState(585);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 334311665663926) != 0) || ((((_la - 66) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 66)) & 63) != 0)) {
      setState(582);
      blockItem();
      setState(587);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(588);
    match(C_grammarParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

C_grammarParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StatementContext* C_grammarParser::BlockItemContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::BlockItemContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::BlockItemContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::BlockItemContext::getRuleIndex() const {
  return C_grammarParser::RuleBlockItem;
}

void C_grammarParser::BlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockItem(this);
}

void C_grammarParser::BlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockItem(this);
}


std::any C_grammarParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::BlockItemContext* C_grammarParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 114, C_grammarParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(594);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(590);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(591);
      declaration();
      setState(592);
      match(C_grammarParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

C_grammarParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ExpressionContext* C_grammarParser::ExpressionStatementContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ExpressionStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleExpressionStatement;
}

void C_grammarParser::ExpressionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStatement(this);
}

void C_grammarParser::ExpressionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStatement(this);
}


std::any C_grammarParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExpressionStatementContext* C_grammarParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 116, C_grammarParser::RuleExpressionStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(597);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 20) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 20)) & 4433230933581825) != 0)) {
      setState(596);
      expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfContentContext ------------------------------------------------------------------

C_grammarParser::IfContentContext::IfContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::IfContentContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::IfContentContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::ConditionalBlockItemContext *> C_grammarParser::IfContentContext::conditionalBlockItem() {
  return getRuleContexts<C_grammarParser::ConditionalBlockItemContext>();
}

C_grammarParser::ConditionalBlockItemContext* C_grammarParser::IfContentContext::conditionalBlockItem(size_t i) {
  return getRuleContext<C_grammarParser::ConditionalBlockItemContext>(i);
}


size_t C_grammarParser::IfContentContext::getRuleIndex() const {
  return C_grammarParser::RuleIfContent;
}

void C_grammarParser::IfContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfContent(this);
}

void C_grammarParser::IfContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfContent(this);
}


std::any C_grammarParser::IfContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitIfContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::IfContentContext* C_grammarParser::ifContent() {
  IfContentContext *_localctx = _tracker.createInstance<IfContentContext>(_ctx, getState());
  enterRule(_localctx, 118, C_grammarParser::RuleIfContent);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(608);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBrace: {
        setState(599);
        match(C_grammarParser::LeftBrace);
        setState(603);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 334311665663926) != 0) || ((((_la - 66) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 66)) & 63) != 0)) {
          setState(600);
          conditionalBlockItem();
          setState(605);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(606);
        match(C_grammarParser::RightBrace);
        break;
      }

      case C_grammarParser::T__0:
      case C_grammarParser::T__1:
      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Float:
      case C_grammarParser::For:
      case C_grammarParser::If:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Return:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Semi:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(607);
        conditionalBlockItem();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseContentContext ------------------------------------------------------------------

C_grammarParser::ElseContentContext::ElseContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ElseContentContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::ElseContentContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::ConditionalBlockItemContext *> C_grammarParser::ElseContentContext::conditionalBlockItem() {
  return getRuleContexts<C_grammarParser::ConditionalBlockItemContext>();
}

C_grammarParser::ConditionalBlockItemContext* C_grammarParser::ElseContentContext::conditionalBlockItem(size_t i) {
  return getRuleContext<C_grammarParser::ConditionalBlockItemContext>(i);
}


size_t C_grammarParser::ElseContentContext::getRuleIndex() const {
  return C_grammarParser::RuleElseContent;
}

void C_grammarParser::ElseContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseContent(this);
}

void C_grammarParser::ElseContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseContent(this);
}


std::any C_grammarParser::ElseContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitElseContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ElseContentContext* C_grammarParser::elseContent() {
  ElseContentContext *_localctx = _tracker.createInstance<ElseContentContext>(_ctx, getState());
  enterRule(_localctx, 120, C_grammarParser::RuleElseContent);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(619);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBrace: {
        setState(610);
        match(C_grammarParser::LeftBrace);
        setState(614);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 334311665663926) != 0) || ((((_la - 66) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 66)) & 63) != 0)) {
          setState(611);
          conditionalBlockItem();
          setState(616);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(617);
        match(C_grammarParser::RightBrace);
        break;
      }

      case C_grammarParser::T__0:
      case C_grammarParser::T__1:
      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Float:
      case C_grammarParser::For:
      case C_grammarParser::If:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Return:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Semi:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(618);
        conditionalBlockItem();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalBlockItemContext ------------------------------------------------------------------

C_grammarParser::ConditionalBlockItemContext::ConditionalBlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StatementContext* C_grammarParser::ConditionalBlockItemContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::ConditionalBlockItemContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::ConditionalBlockItemContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::ConditionalBlockItemContext::getRuleIndex() const {
  return C_grammarParser::RuleConditionalBlockItem;
}

void C_grammarParser::ConditionalBlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalBlockItem(this);
}

void C_grammarParser::ConditionalBlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalBlockItem(this);
}


std::any C_grammarParser::ConditionalBlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConditionalBlockItem(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConditionalBlockItemContext* C_grammarParser::conditionalBlockItem() {
  ConditionalBlockItemContext *_localctx = _tracker.createInstance<ConditionalBlockItemContext>(_ctx, getState());
  enterRule(_localctx, 122, C_grammarParser::RuleConditionalBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(625);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(621);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(622);
      declaration();
      setState(623);
      match(C_grammarParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContentContext ------------------------------------------------------------------

C_grammarParser::ConditionContentContext::ConditionContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::ExpressionContext* C_grammarParser::ConditionContentContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ConditionContentContext::getRuleIndex() const {
  return C_grammarParser::RuleConditionContent;
}

void C_grammarParser::ConditionContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionContent(this);
}

void C_grammarParser::ConditionContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionContent(this);
}


std::any C_grammarParser::ConditionContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConditionContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConditionContentContext* C_grammarParser::conditionContent() {
  ConditionContentContext *_localctx = _tracker.createInstance<ConditionContentContext>(_ctx, getState());
  enterRule(_localctx, 124, C_grammarParser::RuleConditionContent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(627);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectionStatementContext ------------------------------------------------------------------

C_grammarParser::SelectionStatementContext::SelectionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::If() {
  return getToken(C_grammarParser::If, 0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ConditionContentContext* C_grammarParser::SelectionStatementContext::conditionContent() {
  return getRuleContext<C_grammarParser::ConditionContentContext>(0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::IfContentContext* C_grammarParser::SelectionStatementContext::ifContent() {
  return getRuleContext<C_grammarParser::IfContentContext>(0);
}

tree::TerminalNode* C_grammarParser::SelectionStatementContext::Else() {
  return getToken(C_grammarParser::Else, 0);
}

C_grammarParser::ElseContentContext* C_grammarParser::SelectionStatementContext::elseContent() {
  return getRuleContext<C_grammarParser::ElseContentContext>(0);
}


size_t C_grammarParser::SelectionStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleSelectionStatement;
}

void C_grammarParser::SelectionStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectionStatement(this);
}

void C_grammarParser::SelectionStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectionStatement(this);
}


std::any C_grammarParser::SelectionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitSelectionStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::SelectionStatementContext* C_grammarParser::selectionStatement() {
  SelectionStatementContext *_localctx = _tracker.createInstance<SelectionStatementContext>(_ctx, getState());
  enterRule(_localctx, 126, C_grammarParser::RuleSelectionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(629);
    match(C_grammarParser::If);
    setState(630);
    match(C_grammarParser::LeftParen);
    setState(631);
    conditionContent();
    setState(632);
    match(C_grammarParser::RightParen);
    setState(633);
    ifContent();
    setState(636);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
    case 1: {
      setState(634);
      match(C_grammarParser::Else);
      setState(635);
      elseContent();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IterationStatementContext ------------------------------------------------------------------

C_grammarParser::IterationStatementContext::IterationStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::For() {
  return getToken(C_grammarParser::For, 0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::LeftParen() {
  return getToken(C_grammarParser::LeftParen, 0);
}

C_grammarParser::ForDeclarationContext* C_grammarParser::IterationStatementContext::forDeclaration() {
  return getRuleContext<C_grammarParser::ForDeclarationContext>(0);
}

std::vector<tree::TerminalNode *> C_grammarParser::IterationStatementContext::Semi() {
  return getTokens(C_grammarParser::Semi);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::Semi(size_t i) {
  return getToken(C_grammarParser::Semi, i);
}

C_grammarParser::ForExitConditionContext* C_grammarParser::IterationStatementContext::forExitCondition() {
  return getRuleContext<C_grammarParser::ForExitConditionContext>(0);
}

C_grammarParser::ForIterationExpressionContext* C_grammarParser::IterationStatementContext::forIterationExpression() {
  return getRuleContext<C_grammarParser::ForIterationExpressionContext>(0);
}

tree::TerminalNode* C_grammarParser::IterationStatementContext::RightParen() {
  return getToken(C_grammarParser::RightParen, 0);
}

C_grammarParser::ForContentContext* C_grammarParser::IterationStatementContext::forContent() {
  return getRuleContext<C_grammarParser::ForContentContext>(0);
}


size_t C_grammarParser::IterationStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleIterationStatement;
}

void C_grammarParser::IterationStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIterationStatement(this);
}

void C_grammarParser::IterationStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIterationStatement(this);
}


std::any C_grammarParser::IterationStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitIterationStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::IterationStatementContext* C_grammarParser::iterationStatement() {
  IterationStatementContext *_localctx = _tracker.createInstance<IterationStatementContext>(_ctx, getState());
  enterRule(_localctx, 128, C_grammarParser::RuleIterationStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(638);
    match(C_grammarParser::For);
    setState(639);
    match(C_grammarParser::LeftParen);
    setState(640);
    forDeclaration();
    setState(641);
    match(C_grammarParser::Semi);
    setState(642);
    forExitCondition();
    setState(643);
    match(C_grammarParser::Semi);
    setState(644);
    forIterationExpression();
    setState(645);
    match(C_grammarParser::RightParen);
    setState(646);
    forContent();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForContentContext ------------------------------------------------------------------

C_grammarParser::ForContentContext::ForContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ForContentContext::LeftBrace() {
  return getToken(C_grammarParser::LeftBrace, 0);
}

tree::TerminalNode* C_grammarParser::ForContentContext::RightBrace() {
  return getToken(C_grammarParser::RightBrace, 0);
}

std::vector<C_grammarParser::ForBlockItemContext *> C_grammarParser::ForContentContext::forBlockItem() {
  return getRuleContexts<C_grammarParser::ForBlockItemContext>();
}

C_grammarParser::ForBlockItemContext* C_grammarParser::ForContentContext::forBlockItem(size_t i) {
  return getRuleContext<C_grammarParser::ForBlockItemContext>(i);
}


size_t C_grammarParser::ForContentContext::getRuleIndex() const {
  return C_grammarParser::RuleForContent;
}

void C_grammarParser::ForContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForContent(this);
}

void C_grammarParser::ForContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForContent(this);
}


std::any C_grammarParser::ForContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForContent(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForContentContext* C_grammarParser::forContent() {
  ForContentContext *_localctx = _tracker.createInstance<ForContentContext>(_ctx, getState());
  enterRule(_localctx, 130, C_grammarParser::RuleForContent);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(657);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case C_grammarParser::LeftBrace: {
        setState(648);
        match(C_grammarParser::LeftBrace);
        setState(652);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 334311665663926) != 0) || ((((_la - 66) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 66)) & 63) != 0)) {
          setState(649);
          forBlockItem();
          setState(654);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(655);
        match(C_grammarParser::RightBrace);
        break;
      }

      case C_grammarParser::T__0:
      case C_grammarParser::T__1:
      case C_grammarParser::Char:
      case C_grammarParser::Const:
      case C_grammarParser::Float:
      case C_grammarParser::For:
      case C_grammarParser::If:
      case C_grammarParser::Int:
      case C_grammarParser::Long:
      case C_grammarParser::Return:
      case C_grammarParser::Short:
      case C_grammarParser::Signed:
      case C_grammarParser::Unsigned:
      case C_grammarParser::Void:
      case C_grammarParser::LeftParen:
      case C_grammarParser::PlusPlus:
      case C_grammarParser::Minus:
      case C_grammarParser::MinusMinus:
      case C_grammarParser::Not:
      case C_grammarParser::Tilde:
      case C_grammarParser::Semi:
      case C_grammarParser::Identifier:
      case C_grammarParser::IntegerConstant:
      case C_grammarParser::FloatingConstant:
      case C_grammarParser::DigitSequence:
      case C_grammarParser::CharacterConstant:
      case C_grammarParser::StringLiteral: {
        setState(656);
        forBlockItem();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForBlockItemContext ------------------------------------------------------------------

C_grammarParser::ForBlockItemContext::ForBlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::StatementContext* C_grammarParser::ForBlockItemContext::statement() {
  return getRuleContext<C_grammarParser::StatementContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::ForBlockItemContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::ForBlockItemContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::ForBlockItemContext::getRuleIndex() const {
  return C_grammarParser::RuleForBlockItem;
}

void C_grammarParser::ForBlockItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForBlockItem(this);
}

void C_grammarParser::ForBlockItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForBlockItem(this);
}


std::any C_grammarParser::ForBlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForBlockItem(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForBlockItemContext* C_grammarParser::forBlockItem() {
  ForBlockItemContext *_localctx = _tracker.createInstance<ForBlockItemContext>(_ctx, getState());
  enterRule(_localctx, 132, C_grammarParser::RuleForBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(663);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(659);
      statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(660);
      declaration();
      setState(661);
      match(C_grammarParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForExitConditionContext ------------------------------------------------------------------

C_grammarParser::ForExitConditionContext::ForExitConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ForExitConditionContext::assignmentExpression() {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(0);
}


size_t C_grammarParser::ForExitConditionContext::getRuleIndex() const {
  return C_grammarParser::RuleForExitCondition;
}

void C_grammarParser::ForExitConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForExitCondition(this);
}

void C_grammarParser::ForExitConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForExitCondition(this);
}


std::any C_grammarParser::ForExitConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForExitCondition(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForExitConditionContext* C_grammarParser::forExitCondition() {
  ForExitConditionContext *_localctx = _tracker.createInstance<ForExitConditionContext>(_ctx, getState());
  enterRule(_localctx, 134, C_grammarParser::RuleForExitCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(665);
    assignmentExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForDeclarationContext ------------------------------------------------------------------

C_grammarParser::ForDeclarationContext::ForDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclarationContext* C_grammarParser::ForDeclarationContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}


size_t C_grammarParser::ForDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleForDeclaration;
}

void C_grammarParser::ForDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForDeclaration(this);
}

void C_grammarParser::ForDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForDeclaration(this);
}


std::any C_grammarParser::ForDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForDeclarationContext* C_grammarParser::forDeclaration() {
  ForDeclarationContext *_localctx = _tracker.createInstance<ForDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 136, C_grammarParser::RuleForDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(667);
    declaration();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForIterationExpressionContext ------------------------------------------------------------------

C_grammarParser::ForIterationExpressionContext::ForIterationExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::AssignmentExpressionContext *> C_grammarParser::ForIterationExpressionContext::assignmentExpression() {
  return getRuleContexts<C_grammarParser::AssignmentExpressionContext>();
}

C_grammarParser::AssignmentExpressionContext* C_grammarParser::ForIterationExpressionContext::assignmentExpression(size_t i) {
  return getRuleContext<C_grammarParser::AssignmentExpressionContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::ForIterationExpressionContext::Comma() {
  return getTokens(C_grammarParser::Comma);
}

tree::TerminalNode* C_grammarParser::ForIterationExpressionContext::Comma(size_t i) {
  return getToken(C_grammarParser::Comma, i);
}


size_t C_grammarParser::ForIterationExpressionContext::getRuleIndex() const {
  return C_grammarParser::RuleForIterationExpression;
}

void C_grammarParser::ForIterationExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForIterationExpression(this);
}

void C_grammarParser::ForIterationExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForIterationExpression(this);
}


std::any C_grammarParser::ForIterationExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitForIterationExpression(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ForIterationExpressionContext* C_grammarParser::forIterationExpression() {
  ForIterationExpressionContext *_localctx = _tracker.createInstance<ForIterationExpressionContext>(_ctx, getState());
  enterRule(_localctx, 138, C_grammarParser::RuleForIterationExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(669);
    assignmentExpression();
    setState(674);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == C_grammarParser::Comma) {
      setState(670);
      match(C_grammarParser::Comma);
      setState(671);
      assignmentExpression();
      setState(676);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

C_grammarParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ReturnStatementContext::Return() {
  return getToken(C_grammarParser::Return, 0);
}

tree::TerminalNode* C_grammarParser::ReturnStatementContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}

C_grammarParser::ExpressionContext* C_grammarParser::ReturnStatementContext::expression() {
  return getRuleContext<C_grammarParser::ExpressionContext>(0);
}


size_t C_grammarParser::ReturnStatementContext::getRuleIndex() const {
  return C_grammarParser::RuleReturnStatement;
}

void C_grammarParser::ReturnStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void C_grammarParser::ReturnStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}


std::any C_grammarParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ReturnStatementContext* C_grammarParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 140, C_grammarParser::RuleReturnStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(677);
    match(C_grammarParser::Return);
    setState(679);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 20) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 20)) & 4433230933581825) != 0)) {
      setState(678);
      expression();
    }
    setState(681);
    match(C_grammarParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TranslationUnitContext ------------------------------------------------------------------

C_grammarParser::TranslationUnitContext::TranslationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::ExternalDeclarationContext *> C_grammarParser::TranslationUnitContext::externalDeclaration() {
  return getRuleContexts<C_grammarParser::ExternalDeclarationContext>();
}

C_grammarParser::ExternalDeclarationContext* C_grammarParser::TranslationUnitContext::externalDeclaration(size_t i) {
  return getRuleContext<C_grammarParser::ExternalDeclarationContext>(i);
}


size_t C_grammarParser::TranslationUnitContext::getRuleIndex() const {
  return C_grammarParser::RuleTranslationUnit;
}

void C_grammarParser::TranslationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTranslationUnit(this);
}

void C_grammarParser::TranslationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTranslationUnit(this);
}


std::any C_grammarParser::TranslationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitTranslationUnit(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::TranslationUnitContext* C_grammarParser::translationUnit() {
  TranslationUnitContext *_localctx = _tracker.createInstance<TranslationUnitContext>(_ctx, getState());
  enterRule(_localctx, 142, C_grammarParser::RuleTranslationUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(684); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(683);
      externalDeclaration();
      setState(686); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281474977983670) != 0) || _la == C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternalDeclarationContext ------------------------------------------------------------------

C_grammarParser::ExternalDeclarationContext::ExternalDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::FunctionDefinitionContext* C_grammarParser::ExternalDeclarationContext::functionDefinition() {
  return getRuleContext<C_grammarParser::FunctionDefinitionContext>(0);
}

C_grammarParser::DeclarationContext* C_grammarParser::ExternalDeclarationContext::declaration() {
  return getRuleContext<C_grammarParser::DeclarationContext>(0);
}

tree::TerminalNode* C_grammarParser::ExternalDeclarationContext::Semi() {
  return getToken(C_grammarParser::Semi, 0);
}


size_t C_grammarParser::ExternalDeclarationContext::getRuleIndex() const {
  return C_grammarParser::RuleExternalDeclaration;
}

void C_grammarParser::ExternalDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternalDeclaration(this);
}

void C_grammarParser::ExternalDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternalDeclaration(this);
}


std::any C_grammarParser::ExternalDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitExternalDeclaration(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ExternalDeclarationContext* C_grammarParser::externalDeclaration() {
  ExternalDeclarationContext *_localctx = _tracker.createInstance<ExternalDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 144, C_grammarParser::RuleExternalDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(693);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(688);
      functionDefinition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(689);
      declaration();
      setState(690);
      match(C_grammarParser::Semi);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(692);
      match(C_grammarParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefinitionContext ------------------------------------------------------------------

C_grammarParser::FunctionDefinitionContext::FunctionDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

C_grammarParser::DeclaratorContext* C_grammarParser::FunctionDefinitionContext::declarator() {
  return getRuleContext<C_grammarParser::DeclaratorContext>(0);
}

C_grammarParser::CompoundStatementContext* C_grammarParser::FunctionDefinitionContext::compoundStatement() {
  return getRuleContext<C_grammarParser::CompoundStatementContext>(0);
}

C_grammarParser::TypeSpecifierContext* C_grammarParser::FunctionDefinitionContext::typeSpecifier() {
  return getRuleContext<C_grammarParser::TypeSpecifierContext>(0);
}

C_grammarParser::DeclarationListContext* C_grammarParser::FunctionDefinitionContext::declarationList() {
  return getRuleContext<C_grammarParser::DeclarationListContext>(0);
}

tree::TerminalNode* C_grammarParser::FunctionDefinitionContext::Const() {
  return getToken(C_grammarParser::Const, 0);
}


size_t C_grammarParser::FunctionDefinitionContext::getRuleIndex() const {
  return C_grammarParser::RuleFunctionDefinition;
}

void C_grammarParser::FunctionDefinitionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDefinition(this);
}

void C_grammarParser::FunctionDefinitionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDefinition(this);
}


std::any C_grammarParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::FunctionDefinitionContext* C_grammarParser::functionDefinition() {
  FunctionDefinitionContext *_localctx = _tracker.createInstance<FunctionDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 146, C_grammarParser::RuleFunctionDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(699);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx)) {
    case 1: {
      setState(696);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Const) {
        setState(695);
        match(C_grammarParser::Const);
      }
      setState(698);
      typeSpecifier();
      break;
    }

    default:
      break;
    }
    setState(701);
    declarator();
    setState(703);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 224438) != 0) || _la == C_grammarParser::Identifier) {
      setState(702);
      declarationList();
    }
    setState(705);
    compoundStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationListContext ------------------------------------------------------------------

C_grammarParser::DeclarationListContext::DeclarationListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<C_grammarParser::DeclarationContext *> C_grammarParser::DeclarationListContext::declaration() {
  return getRuleContexts<C_grammarParser::DeclarationContext>();
}

C_grammarParser::DeclarationContext* C_grammarParser::DeclarationListContext::declaration(size_t i) {
  return getRuleContext<C_grammarParser::DeclarationContext>(i);
}

std::vector<tree::TerminalNode *> C_grammarParser::DeclarationListContext::Semi() {
  return getTokens(C_grammarParser::Semi);
}

tree::TerminalNode* C_grammarParser::DeclarationListContext::Semi(size_t i) {
  return getToken(C_grammarParser::Semi, i);
}


size_t C_grammarParser::DeclarationListContext::getRuleIndex() const {
  return C_grammarParser::RuleDeclarationList;
}

void C_grammarParser::DeclarationListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclarationList(this);
}

void C_grammarParser::DeclarationListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclarationList(this);
}


std::any C_grammarParser::DeclarationListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitDeclarationList(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::DeclarationListContext* C_grammarParser::declarationList() {
  DeclarationListContext *_localctx = _tracker.createInstance<DeclarationListContext>(_ctx, getState());
  enterRule(_localctx, 148, C_grammarParser::RuleDeclarationList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(710); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(707);
      declaration();
      setState(708);
      match(C_grammarParser::Semi);
      setState(712); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 224438) != 0) || _la == C_grammarParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

C_grammarParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* C_grammarParser::ConstantContext::IntegerConstant() {
  return getToken(C_grammarParser::IntegerConstant, 0);
}

tree::TerminalNode* C_grammarParser::ConstantContext::Minus() {
  return getToken(C_grammarParser::Minus, 0);
}

tree::TerminalNode* C_grammarParser::ConstantContext::FloatingConstant() {
  return getToken(C_grammarParser::FloatingConstant, 0);
}

tree::TerminalNode* C_grammarParser::ConstantContext::CharacterConstant() {
  return getToken(C_grammarParser::CharacterConstant, 0);
}


size_t C_grammarParser::ConstantContext::getRuleIndex() const {
  return C_grammarParser::RuleConstant;
}

void C_grammarParser::ConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstant(this);
}

void C_grammarParser::ConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<C_grammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstant(this);
}


std::any C_grammarParser::ConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<C_grammarVisitor*>(visitor))
    return parserVisitor->visitConstant(this);
  else
    return visitor->visitChildren(this);
}

C_grammarParser::ConstantContext* C_grammarParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 150, C_grammarParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(723);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(715);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Minus) {
        setState(714);
        match(C_grammarParser::Minus);
      }
      setState(717);
      match(C_grammarParser::IntegerConstant);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(719);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == C_grammarParser::Minus) {
        setState(718);
        match(C_grammarParser::Minus);
      }
      setState(721);
      match(C_grammarParser::FloatingConstant);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(722);
      match(C_grammarParser::CharacterConstant);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool C_grammarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 38: return directDeclaratorSempred(antlrcpp::downCast<DirectDeclaratorContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool C_grammarParser::directDeclaratorSempred(DirectDeclaratorContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);
    case 2: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void C_grammarParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  c_grammarParserInitialize();
#else
  ::antlr4::internal::call_once(c_grammarParserOnceFlag, c_grammarParserInitialize);
#endif
}
