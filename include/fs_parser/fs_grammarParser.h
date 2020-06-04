
// Generated from /home/fils/git/fCore_has/src/frontend/fs_grammar.g4 by ANTLR 4.8

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
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    Identifier = 51, Hexnum = 52, Integer = 53, Octalnum = 54, FloatingPointLiteral = 55, 
    String = 56, Label = 57, WS = 58, BlockComment = 59, LineComment = 60
  };

  enum {
    RuleProgram = 0, RuleCode = 1, RuleInstruction = 2, RuleReg_instr = 3, 
    RuleImm_instr = 4, RuleImm_alu_instr = 5, RuleBranch_instr = 6, RuleIndep_instr = 7, 
    RulePseudo_instr = 8, RuleReg_opcode = 9, RuleImm_alu_opcode = 10, RuleImm_opcode = 11, 
    RuleBranch_opcode = 12, RulePseudo_opcode = 13, RuleFcore_reg = 14, 
    RuleFor_block = 15, RuleFor_incr = 16, RuleFor_dec = 17, RuleFor_decl = 18, 
    RuleFor_end = 19, RuleFor_end_comp_type = 20, RulePragma = 21, RuleImmediate = 22
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
  class InstructionContext;
  class Reg_instrContext;
  class Imm_instrContext;
  class Imm_alu_instrContext;
  class Branch_instrContext;
  class Indep_instrContext;
  class Pseudo_instrContext;
  class Reg_opcodeContext;
  class Imm_alu_opcodeContext;
  class Imm_opcodeContext;
  class Branch_opcodeContext;
  class Pseudo_opcodeContext;
  class Fcore_regContext;
  class For_blockContext;
  class For_incrContext;
  class For_decContext;
  class For_declContext;
  class For_endContext;
  class For_end_comp_typeContext;
  class PragmaContext;
  class ImmediateContext; 

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
    std::vector<InstructionContext *> instruction();
    InstructionContext* instruction(size_t i);
    std::vector<For_blockContext *> for_block();
    For_blockContext* for_block(size_t i);
    std::vector<PragmaContext *> pragma();
    PragmaContext* pragma(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CodeContext* code();

  class  InstructionContext : public antlr4::ParserRuleContext {
  public:
    InstructionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Reg_instrContext *reg_instr();
    Imm_instrContext *imm_instr();
    Indep_instrContext *indep_instr();
    Pseudo_instrContext *pseudo_instr();
    Branch_instrContext *branch_instr();
    Imm_alu_instrContext *imm_alu_instr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InstructionContext* instruction();

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

  class  Imm_alu_instrContext : public antlr4::ParserRuleContext {
  public:
    Imm_alu_instrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Imm_alu_opcodeContext *imm_alu_opcode();
    std::vector<Fcore_regContext *> fcore_reg();
    Fcore_regContext* fcore_reg(size_t i);
    antlr4::tree::TerminalNode *Integer();
    antlr4::tree::TerminalNode *Hexnum();
    antlr4::tree::TerminalNode *Octalnum();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Imm_alu_instrContext* imm_alu_instr();

  class  Branch_instrContext : public antlr4::ParserRuleContext {
  public:
    Branch_instrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Branch_opcodeContext *branch_opcode();
    std::vector<Fcore_regContext *> fcore_reg();
    Fcore_regContext* fcore_reg(size_t i);
    ImmediateContext *immediate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Branch_instrContext* branch_instr();

  class  Indep_instrContext : public antlr4::ParserRuleContext {
  public:
    Indep_instrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Indep_instrContext* indep_instr();

  class  Pseudo_instrContext : public antlr4::ParserRuleContext {
  public:
    Pseudo_instrContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Pseudo_opcodeContext *pseudo_opcode();
    std::vector<Fcore_regContext *> fcore_reg();
    Fcore_regContext* fcore_reg(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pseudo_instrContext* pseudo_instr();

  class  Reg_opcodeContext : public antlr4::ParserRuleContext {
  public:
    Reg_opcodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Reg_opcodeContext* reg_opcode();

  class  Imm_alu_opcodeContext : public antlr4::ParserRuleContext {
  public:
    Imm_alu_opcodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Imm_alu_opcodeContext* imm_alu_opcode();

  class  Imm_opcodeContext : public antlr4::ParserRuleContext {
  public:
    Imm_opcodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Imm_opcodeContext* imm_opcode();

  class  Branch_opcodeContext : public antlr4::ParserRuleContext {
  public:
    Branch_opcodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Branch_opcodeContext* branch_opcode();

  class  Pseudo_opcodeContext : public antlr4::ParserRuleContext {
  public:
    Pseudo_opcodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pseudo_opcodeContext* pseudo_opcode();

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
    For_end_comp_typeContext *for_end_comp_type();
    antlr4::tree::TerminalNode *Integer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_endContext* for_end();

  class  For_end_comp_typeContext : public antlr4::ParserRuleContext {
  public:
    For_end_comp_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_end_comp_typeContext* for_end_comp_type();

  class  PragmaContext : public antlr4::ParserRuleContext {
  public:
    PragmaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PragmaContext* pragma();

  class  ImmediateContext : public antlr4::ParserRuleContext {
  public:
    ImmediateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Integer();
    antlr4::tree::TerminalNode *Hexnum();
    antlr4::tree::TerminalNode *Octalnum();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImmediateContext* immediate();


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
