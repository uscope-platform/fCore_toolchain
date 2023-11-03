
//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.05/07/2021.

// Generated from ../../src/frontend/asm_grammar.g4 by ANTLR 4.13.1


#include "asm_grammarLexer.h"


using namespace antlr4;

using namespace asm_parser;


using namespace antlr4;

namespace {

struct Asm_grammarLexerStaticData final {
  Asm_grammarLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  Asm_grammarLexerStaticData(const Asm_grammarLexerStaticData&) = delete;
  Asm_grammarLexerStaticData(Asm_grammarLexerStaticData&&) = delete;
  Asm_grammarLexerStaticData& operator=(const Asm_grammarLexerStaticData&) = delete;
  Asm_grammarLexerStaticData& operator=(Asm_grammarLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag asm_grammarlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
Asm_grammarLexerStaticData *asm_grammarlexerLexerStaticData = nullptr;

void asm_grammarlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (asm_grammarlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(asm_grammarlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<Asm_grammarLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "T__24", 
      "T__25", "T__26", "T__27", "T__28", "T__29", "T__30", "T__31", "T__32", 
      "T__33", "T__34", "T__35", "T__36", "T__37", "T__38", "T__39", "T__40", 
      "T__41", "T__42", "T__43", "Register", "Identifier", "Hexnum", "Integer", 
      "Octalnum", "HexDigit", "FloatingPointLiteral", "Exponent", "String", 
      "Letter", "Digit", "Label", "WS", "BlockComment", "LineComment"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "','", "'ldc'", "'stop'", "'nop'", "'add'", "'sub'", "'mul'", 
      "'and'", "'or'", "'satp'", "'satn'", "'efi'", "'bset'", "'bsel'", 
      "'xor'", "'itf'", "'fti'", "'not'", "'rec'", "'abs'", "'popcnt'", 
      "'ldr'", "'ble'", "'bgt'", "'beq'", "'bne'", "'mov'", "'for('", "';'", 
      "')'", "'{'", "'}'", "'++'", "'--'", "'='", "'<'", "'>'", "'<='", 
      "'>='", "'#pragma '", "'let'", "'const'", "'input'", "'output'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "Register", "Identifier", 
      "Hexnum", "Integer", "Octalnum", "FloatingPointLiteral", "String", 
      "Label", "WS", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,55,425,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,
  	7,49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,
  	7,56,2,57,7,57,2,58,7,58,1,0,1,0,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,
  	1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,
  	7,1,7,1,7,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,
  	11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,
  	14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,
  	17,1,17,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,
  	20,1,20,1,20,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,
  	23,1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,27,1,
  	27,1,27,1,27,1,27,1,28,1,28,1,29,1,29,1,30,1,30,1,31,1,31,1,32,1,32,1,
  	32,1,33,1,33,1,33,1,34,1,34,1,35,1,35,1,36,1,36,1,37,1,37,1,37,1,38,1,
  	38,1,38,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,40,1,40,1,40,1,
  	40,1,41,1,41,1,41,1,41,1,41,1,41,1,42,1,42,1,42,1,42,1,42,1,42,1,43,1,
  	43,1,43,1,43,1,43,1,43,1,43,1,44,1,44,4,44,298,8,44,11,44,12,44,299,1,
  	45,1,45,1,45,1,45,5,45,306,8,45,10,45,12,45,309,9,45,1,46,1,46,1,46,1,
  	46,4,46,315,8,46,11,46,12,46,316,1,47,4,47,320,8,47,11,47,12,47,321,1,
  	48,4,48,325,8,48,11,48,12,48,326,1,48,1,48,1,49,1,49,1,50,3,50,334,8,
  	50,1,50,4,50,337,8,50,11,50,12,50,338,1,50,1,50,5,50,343,8,50,10,50,12,
  	50,346,9,50,1,50,3,50,349,8,50,1,50,1,50,4,50,353,8,50,11,50,12,50,354,
  	1,50,3,50,358,8,50,1,50,4,50,361,8,50,11,50,12,50,362,1,50,3,50,366,8,
  	50,1,51,1,51,3,51,370,8,51,1,51,4,51,373,8,51,11,51,12,51,374,1,52,1,
  	52,1,52,1,52,1,52,1,52,5,52,383,8,52,10,52,12,52,386,9,52,1,52,1,52,1,
  	53,1,53,1,54,1,54,1,55,1,55,1,55,1,56,1,56,1,56,1,56,1,57,1,57,1,57,1,
  	57,5,57,405,8,57,10,57,12,57,408,9,57,1,57,1,57,1,57,1,57,1,57,1,58,1,
  	58,1,58,1,58,5,58,419,8,58,10,58,12,58,422,9,58,1,58,1,58,1,406,0,59,
  	1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,
  	29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,
  	26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,71,36,73,37,
  	75,38,77,39,79,40,81,41,83,42,85,43,87,44,89,45,91,46,93,47,95,48,97,
  	49,99,0,101,50,103,0,105,51,107,0,109,0,111,52,113,53,115,54,117,55,1,
  	0,8,2,0,79,79,111,111,3,0,48,57,65,70,97,102,2,0,69,69,101,101,2,0,43,
  	43,45,45,2,0,39,39,92,92,2,0,65,90,97,122,3,0,9,10,13,13,32,32,2,0,10,
  	10,13,13,442,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,
  	0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,
  	0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,
  	1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,
  	0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,
  	0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,
  	1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,73,1,0,
  	0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,
  	0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,0,93,1,0,0,0,0,95,
  	1,0,0,0,0,97,1,0,0,0,0,101,1,0,0,0,0,105,1,0,0,0,0,111,1,0,0,0,0,113,
  	1,0,0,0,0,115,1,0,0,0,0,117,1,0,0,0,1,119,1,0,0,0,3,121,1,0,0,0,5,125,
  	1,0,0,0,7,130,1,0,0,0,9,134,1,0,0,0,11,138,1,0,0,0,13,142,1,0,0,0,15,
  	146,1,0,0,0,17,150,1,0,0,0,19,153,1,0,0,0,21,158,1,0,0,0,23,163,1,0,0,
  	0,25,167,1,0,0,0,27,172,1,0,0,0,29,177,1,0,0,0,31,181,1,0,0,0,33,185,
  	1,0,0,0,35,189,1,0,0,0,37,193,1,0,0,0,39,197,1,0,0,0,41,201,1,0,0,0,43,
  	208,1,0,0,0,45,212,1,0,0,0,47,216,1,0,0,0,49,220,1,0,0,0,51,224,1,0,0,
  	0,53,228,1,0,0,0,55,232,1,0,0,0,57,237,1,0,0,0,59,239,1,0,0,0,61,241,
  	1,0,0,0,63,243,1,0,0,0,65,245,1,0,0,0,67,248,1,0,0,0,69,251,1,0,0,0,71,
  	253,1,0,0,0,73,255,1,0,0,0,75,257,1,0,0,0,77,260,1,0,0,0,79,263,1,0,0,
  	0,81,272,1,0,0,0,83,276,1,0,0,0,85,282,1,0,0,0,87,288,1,0,0,0,89,295,
  	1,0,0,0,91,301,1,0,0,0,93,310,1,0,0,0,95,319,1,0,0,0,97,324,1,0,0,0,99,
  	330,1,0,0,0,101,365,1,0,0,0,103,367,1,0,0,0,105,376,1,0,0,0,107,389,1,
  	0,0,0,109,391,1,0,0,0,111,393,1,0,0,0,113,396,1,0,0,0,115,400,1,0,0,0,
  	117,414,1,0,0,0,119,120,5,44,0,0,120,2,1,0,0,0,121,122,5,108,0,0,122,
  	123,5,100,0,0,123,124,5,99,0,0,124,4,1,0,0,0,125,126,5,115,0,0,126,127,
  	5,116,0,0,127,128,5,111,0,0,128,129,5,112,0,0,129,6,1,0,0,0,130,131,5,
  	110,0,0,131,132,5,111,0,0,132,133,5,112,0,0,133,8,1,0,0,0,134,135,5,97,
  	0,0,135,136,5,100,0,0,136,137,5,100,0,0,137,10,1,0,0,0,138,139,5,115,
  	0,0,139,140,5,117,0,0,140,141,5,98,0,0,141,12,1,0,0,0,142,143,5,109,0,
  	0,143,144,5,117,0,0,144,145,5,108,0,0,145,14,1,0,0,0,146,147,5,97,0,0,
  	147,148,5,110,0,0,148,149,5,100,0,0,149,16,1,0,0,0,150,151,5,111,0,0,
  	151,152,5,114,0,0,152,18,1,0,0,0,153,154,5,115,0,0,154,155,5,97,0,0,155,
  	156,5,116,0,0,156,157,5,112,0,0,157,20,1,0,0,0,158,159,5,115,0,0,159,
  	160,5,97,0,0,160,161,5,116,0,0,161,162,5,110,0,0,162,22,1,0,0,0,163,164,
  	5,101,0,0,164,165,5,102,0,0,165,166,5,105,0,0,166,24,1,0,0,0,167,168,
  	5,98,0,0,168,169,5,115,0,0,169,170,5,101,0,0,170,171,5,116,0,0,171,26,
  	1,0,0,0,172,173,5,98,0,0,173,174,5,115,0,0,174,175,5,101,0,0,175,176,
  	5,108,0,0,176,28,1,0,0,0,177,178,5,120,0,0,178,179,5,111,0,0,179,180,
  	5,114,0,0,180,30,1,0,0,0,181,182,5,105,0,0,182,183,5,116,0,0,183,184,
  	5,102,0,0,184,32,1,0,0,0,185,186,5,102,0,0,186,187,5,116,0,0,187,188,
  	5,105,0,0,188,34,1,0,0,0,189,190,5,110,0,0,190,191,5,111,0,0,191,192,
  	5,116,0,0,192,36,1,0,0,0,193,194,5,114,0,0,194,195,5,101,0,0,195,196,
  	5,99,0,0,196,38,1,0,0,0,197,198,5,97,0,0,198,199,5,98,0,0,199,200,5,115,
  	0,0,200,40,1,0,0,0,201,202,5,112,0,0,202,203,5,111,0,0,203,204,5,112,
  	0,0,204,205,5,99,0,0,205,206,5,110,0,0,206,207,5,116,0,0,207,42,1,0,0,
  	0,208,209,5,108,0,0,209,210,5,100,0,0,210,211,5,114,0,0,211,44,1,0,0,
  	0,212,213,5,98,0,0,213,214,5,108,0,0,214,215,5,101,0,0,215,46,1,0,0,0,
  	216,217,5,98,0,0,217,218,5,103,0,0,218,219,5,116,0,0,219,48,1,0,0,0,220,
  	221,5,98,0,0,221,222,5,101,0,0,222,223,5,113,0,0,223,50,1,0,0,0,224,225,
  	5,98,0,0,225,226,5,110,0,0,226,227,5,101,0,0,227,52,1,0,0,0,228,229,5,
  	109,0,0,229,230,5,111,0,0,230,231,5,118,0,0,231,54,1,0,0,0,232,233,5,
  	102,0,0,233,234,5,111,0,0,234,235,5,114,0,0,235,236,5,40,0,0,236,56,1,
  	0,0,0,237,238,5,59,0,0,238,58,1,0,0,0,239,240,5,41,0,0,240,60,1,0,0,0,
  	241,242,5,123,0,0,242,62,1,0,0,0,243,244,5,125,0,0,244,64,1,0,0,0,245,
  	246,5,43,0,0,246,247,5,43,0,0,247,66,1,0,0,0,248,249,5,45,0,0,249,250,
  	5,45,0,0,250,68,1,0,0,0,251,252,5,61,0,0,252,70,1,0,0,0,253,254,5,60,
  	0,0,254,72,1,0,0,0,255,256,5,62,0,0,256,74,1,0,0,0,257,258,5,60,0,0,258,
  	259,5,61,0,0,259,76,1,0,0,0,260,261,5,62,0,0,261,262,5,61,0,0,262,78,
  	1,0,0,0,263,264,5,35,0,0,264,265,5,112,0,0,265,266,5,114,0,0,266,267,
  	5,97,0,0,267,268,5,103,0,0,268,269,5,109,0,0,269,270,5,97,0,0,270,271,
  	5,32,0,0,271,80,1,0,0,0,272,273,5,108,0,0,273,274,5,101,0,0,274,275,5,
  	116,0,0,275,82,1,0,0,0,276,277,5,99,0,0,277,278,5,111,0,0,278,279,5,110,
  	0,0,279,280,5,115,0,0,280,281,5,116,0,0,281,84,1,0,0,0,282,283,5,105,
  	0,0,283,284,5,110,0,0,284,285,5,112,0,0,285,286,5,117,0,0,286,287,5,116,
  	0,0,287,86,1,0,0,0,288,289,5,111,0,0,289,290,5,117,0,0,290,291,5,116,
  	0,0,291,292,5,112,0,0,292,293,5,117,0,0,293,294,5,116,0,0,294,88,1,0,
  	0,0,295,297,5,114,0,0,296,298,3,109,54,0,297,296,1,0,0,0,298,299,1,0,
  	0,0,299,297,1,0,0,0,299,300,1,0,0,0,300,90,1,0,0,0,301,307,3,107,53,0,
  	302,306,5,95,0,0,303,306,3,107,53,0,304,306,3,109,54,0,305,302,1,0,0,
  	0,305,303,1,0,0,0,305,304,1,0,0,0,306,309,1,0,0,0,307,305,1,0,0,0,307,
  	308,1,0,0,0,308,92,1,0,0,0,309,307,1,0,0,0,310,311,5,48,0,0,311,312,5,
  	120,0,0,312,314,1,0,0,0,313,315,3,99,49,0,314,313,1,0,0,0,315,316,1,0,
  	0,0,316,314,1,0,0,0,316,317,1,0,0,0,317,94,1,0,0,0,318,320,3,109,54,0,
  	319,318,1,0,0,0,320,321,1,0,0,0,321,319,1,0,0,0,321,322,1,0,0,0,322,96,
  	1,0,0,0,323,325,2,48,55,0,324,323,1,0,0,0,325,326,1,0,0,0,326,324,1,0,
  	0,0,326,327,1,0,0,0,327,328,1,0,0,0,328,329,7,0,0,0,329,98,1,0,0,0,330,
  	331,7,1,0,0,331,100,1,0,0,0,332,334,5,45,0,0,333,332,1,0,0,0,333,334,
  	1,0,0,0,334,336,1,0,0,0,335,337,2,48,57,0,336,335,1,0,0,0,337,338,1,0,
  	0,0,338,336,1,0,0,0,338,339,1,0,0,0,339,340,1,0,0,0,340,344,5,46,0,0,
  	341,343,2,48,57,0,342,341,1,0,0,0,343,346,1,0,0,0,344,342,1,0,0,0,344,
  	345,1,0,0,0,345,348,1,0,0,0,346,344,1,0,0,0,347,349,3,103,51,0,348,347,
  	1,0,0,0,348,349,1,0,0,0,349,366,1,0,0,0,350,352,5,46,0,0,351,353,2,48,
  	57,0,352,351,1,0,0,0,353,354,1,0,0,0,354,352,1,0,0,0,354,355,1,0,0,0,
  	355,357,1,0,0,0,356,358,3,103,51,0,357,356,1,0,0,0,357,358,1,0,0,0,358,
  	366,1,0,0,0,359,361,2,48,57,0,360,359,1,0,0,0,361,362,1,0,0,0,362,360,
  	1,0,0,0,362,363,1,0,0,0,363,364,1,0,0,0,364,366,3,103,51,0,365,333,1,
  	0,0,0,365,350,1,0,0,0,365,360,1,0,0,0,366,102,1,0,0,0,367,369,7,2,0,0,
  	368,370,7,3,0,0,369,368,1,0,0,0,369,370,1,0,0,0,370,372,1,0,0,0,371,373,
  	2,48,57,0,372,371,1,0,0,0,373,374,1,0,0,0,374,372,1,0,0,0,374,375,1,0,
  	0,0,375,104,1,0,0,0,376,377,5,32,0,0,377,378,5,39,0,0,378,384,1,0,0,0,
  	379,380,5,92,0,0,380,383,9,0,0,0,381,383,8,4,0,0,382,379,1,0,0,0,382,
  	381,1,0,0,0,383,386,1,0,0,0,384,382,1,0,0,0,384,385,1,0,0,0,385,387,1,
  	0,0,0,386,384,1,0,0,0,387,388,5,39,0,0,388,106,1,0,0,0,389,390,7,5,0,
  	0,390,108,1,0,0,0,391,392,2,48,57,0,392,110,1,0,0,0,393,394,3,91,45,0,
  	394,395,5,58,0,0,395,112,1,0,0,0,396,397,7,6,0,0,397,398,1,0,0,0,398,
  	399,6,56,0,0,399,114,1,0,0,0,400,401,5,47,0,0,401,402,5,42,0,0,402,406,
  	1,0,0,0,403,405,9,0,0,0,404,403,1,0,0,0,405,408,1,0,0,0,406,407,1,0,0,
  	0,406,404,1,0,0,0,407,409,1,0,0,0,408,406,1,0,0,0,409,410,5,42,0,0,410,
  	411,5,47,0,0,411,412,1,0,0,0,412,413,6,57,0,0,413,116,1,0,0,0,414,415,
  	5,47,0,0,415,416,5,47,0,0,416,420,1,0,0,0,417,419,8,7,0,0,418,417,1,0,
  	0,0,419,422,1,0,0,0,420,418,1,0,0,0,420,421,1,0,0,0,421,423,1,0,0,0,422,
  	420,1,0,0,0,423,424,6,58,0,0,424,118,1,0,0,0,21,0,299,305,307,316,321,
  	326,333,338,344,348,354,357,362,365,369,374,382,384,406,420,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  asm_grammarlexerLexerStaticData = staticData.release();
}

}

asm_grammarLexer::asm_grammarLexer(CharStream *input) : Lexer(input) {
  asm_grammarLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *asm_grammarlexerLexerStaticData->atn, asm_grammarlexerLexerStaticData->decisionToDFA, asm_grammarlexerLexerStaticData->sharedContextCache);
}

asm_grammarLexer::~asm_grammarLexer() {
  delete _interpreter;
}

std::string asm_grammarLexer::getGrammarFileName() const {
  return "asm_grammar.g4";
}

const std::vector<std::string>& asm_grammarLexer::getRuleNames() const {
  return asm_grammarlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& asm_grammarLexer::getChannelNames() const {
  return asm_grammarlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& asm_grammarLexer::getModeNames() const {
  return asm_grammarlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& asm_grammarLexer::getVocabulary() const {
  return asm_grammarlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView asm_grammarLexer::getSerializedATN() const {
  return asm_grammarlexerLexerStaticData->serializedATN;
}

const atn::ATN& asm_grammarLexer::getATN() const {
  return *asm_grammarlexerLexerStaticData->atn;
}




void asm_grammarLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  asm_grammarlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(asm_grammarlexerLexerOnceFlag, asm_grammarlexerLexerInitialize);
#endif
}
