
// Generated from /home/fils/git/fCore_has/src/fs_grammar.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"


namespace fs_parser {


class  fs_grammarParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, Identifier = 42, Hexnum = 43, Integer = 44, 
    Octalnum = 45, FloatingPointLiteral = 46, String = 47, Label = 48, WS = 49, 
    BlockComment = 50, LineComment = 51
  };

  enum {
    RuleProgram = 0, RuleCode = 1, RuleReg_instr = 2, RuleImm_instr = 3, 
    RuleIndep_instr = 4, RuleReg_opcode = 5, RuleImm_opcode = 6, RuleFcore_reg = 7, 
    RuleFor_block = 8, RuleFor_incr = 9, RuleFor_dec = 10, RuleFor_decl = 11, 
    RuleFor_end = 12
  };

  fs_grammarParser(antlr4::TokenStream *input);
  ~fs_grammarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ProgramContext;
  class CodeContext;
  class Reg_instrContext;
  class Imm_instrContext;
  class Indep_instrContext;
  class Reg_opcodeContext;
  class Imm_opcodeContext;
  class Fcore_regContext;
  class For_blockContext;
  class For_incrContext;
  class For_decContext;
  class For_declContext;
  class For_endContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CodeContext *code();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  CodeContext : public antlr4::ParserRuleContext {
  public:
    CodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Reg_instrContext *> reg_instr();
    Reg_instrContext* reg_instr(size_t i);
    std::vector<Imm_instrContext *> imm_instr();
    Imm_instrContext* imm_instr(size_t i);
    std::vector<Indep_instrContext *> indep_instr();
    Indep_instrContext* indep_instr(size_t i);
    std::vector<For_blockContext *> for_block();
    For_blockContext* for_block(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CodeContext* code();

  class  Reg_instrContext : public antlr4::ParserRuleContext {
  public:
    Reg_instrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reg_opcodeContext *reg_opcode();
    std::vector<Fcore_regContext *> fcore_reg();
    Fcore_regContext* fcore_reg(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Reg_instrContext* reg_instr();

  class  Imm_instrContext : public antlr4::ParserRuleContext {
  public:
    Imm_instrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Imm_opcodeContext *imm_opcode();
    Fcore_regContext *fcore_reg();
    antlr4::tree::TerminalNode *Integer();
    antlr4::tree::TerminalNode *Hexnum();
    antlr4::tree::TerminalNode *Octalnum();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Imm_instrContext* imm_instr();

  class  Indep_instrContext : public antlr4::ParserRuleContext {
  public:
    Indep_instrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Indep_instrContext* indep_instr();

  class  Reg_opcodeContext : public antlr4::ParserRuleContext {
  public:
    Reg_opcodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Reg_opcodeContext* reg_opcode();

  class  Imm_opcodeContext : public antlr4::ParserRuleContext {
  public:
    Imm_opcodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Imm_opcodeContext* imm_opcode();

  class  Fcore_regContext : public antlr4::ParserRuleContext {
  public:
    Fcore_regContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Fcore_regContext* fcore_reg();

  class  For_blockContext : public antlr4::ParserRuleContext {
  public:
    For_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    For_declContext *for_decl();
    For_endContext *for_end();
    CodeContext *code();
    For_incrContext *for_incr();
    For_decContext *for_dec();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_blockContext* for_block();

  class  For_incrContext : public antlr4::ParserRuleContext {
  public:
    For_incrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_incrContext* for_incr();

  class  For_decContext : public antlr4::ParserRuleContext {
  public:
    For_decContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_decContext* for_dec();

  class  For_declContext : public antlr4::ParserRuleContext {
  public:
    For_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Integer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_declContext* for_decl();

  class  For_endContext : public antlr4::ParserRuleContext {
  public:
    For_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Integer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_endContext* for_end();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace fs_parser
