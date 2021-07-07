// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_has.

// fCore_has is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_has is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_has.  If not, see <https://www.gnu.org/licenses/>.

#include "frontend/C/C_Tree_visitor.hpp"


C_Tree_visitor::C_Tree_visitor() {
    in_function_declaration = false;
    in_function_body = false;
    expression_nesting_level = 0;
}



void C_Tree_visitor::enterFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) {
    in_function_declaration = true;
    current_function = std::make_shared<hl_function_def_node>();
}


void C_Tree_visitor::exitFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) {

    std::string func_name = ctx->declarator()->directDeclarator()->directDeclarator()->getText();
    if(ctx->declarator()->directDeclarator()->parameterTypeList() != nullptr){

        C_parser::C_grammarParser::ParameterListContext  *parameters = ctx->declarator()->directDeclarator()->parameterTypeList()->parameterList();
        for(auto item:parameters->parameterDeclaration()){
            std::string param_type =item->typeSpecifier()->getText();
        }
    }
        std::string type = ctx->typeSpecifier()->getText();

    current_function->set_return_type(hl_ast_node::string_to_type(type));
        current_function->set_name(func_name);
        current_function->set_parameters_list(parameters_list);
        current_function->set_body(function_body);

        function_body.clear();
        in_function_declaration = false;
        functions.push_back(current_function);

}

void C_Tree_visitor::exitParameterDeclaration(C_parser::C_grammarParser::ParameterDeclarationContext *ctx) {
    std::string id_name = ctx->declarator()->directDeclarator()->Identifier()->getText();
    std::string type = ctx->typeSpecifier()->getText();
    std::shared_ptr<hl_definition_node> identifier = std::make_shared<hl_definition_node>(id_name, hl_ast_node::string_to_type(type));
    if(in_function_declaration) {
        parameters_list.push_back(identifier);
    }
    current_block_item = current_initializer;
}

void C_Tree_visitor::enterCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) {
    in_function_body = true;
}


void C_Tree_visitor::exitDeclaration(C_parser::C_grammarParser::DeclarationContext *ctx) {
    bool is_const = ctx->Const() != nullptr;
    std::string type_name = ctx->typeSpecifier()->getText();
    std::string name = ctx->initDeclaratorList()->initDeclarator()[0]->declarator()->directDeclarator()->getText();
    std::shared_ptr<hl_definition_node> node = std::make_shared<hl_definition_node>(name, hl_ast_node::string_to_type(type_name));
    node->set_constant(is_const);
    if(ctx->initDeclaratorList() != nullptr){
        node->set_initializer(current_initializer);
    }
    if(in_function_body){
        current_block_item = node;
    } else {
        ext_decl.push_back(node);
    }

}

void C_Tree_visitor::exitInitializer(C_parser::C_grammarParser::InitializerContext *ctx) {
    if(ctx->assignmentExpression() != nullptr){
        current_initializer = expressions_stack.top();
        expressions_stack.pop();
    } else if(ctx->initializerList() != nullptr){
        throw std::runtime_error("ERROR: Initializer lists are not supported yet");
    }
}



void C_Tree_visitor::exitCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) {
    in_function_body = false;

}

void C_Tree_visitor::exitUnaryExpression(C_parser::C_grammarParser::UnaryExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;
    expression_type_t expr;

    if(ctx->unaryExpression() != nullptr){

        if(ctx->unaryOperator()->getText() == "!"){
            expr = expr_not_l;
        } else if(ctx->unaryOperator()->getText() == "~"){
            expr = expr_not_b;
        } else if(ctx->unaryOperator()->getText() == "-"){
            expr = expr_neg;
        }

        expression = std::make_shared<hl_expression_node>( expr);
        if(ctx->unaryExpression()->primaryExpression()!= nullptr){
            if(expression_nesting_level==0){
                expression->set_rhs(operands_stack.top());
                operands_stack.pop();
            } else{
                expression->set_rhs(expressions_stack.top());
                expressions_stack.pop();
                expression_nesting_level--;
            }
        } else{
            expression->set_rhs(expressions_stack.top());
            expressions_stack.pop();
        }
        expressions_stack.push(expression);
    }

}

void C_Tree_visitor::exitPrimaryExpression(C_parser::C_grammarParser::PrimaryExpressionContext *ctx) {
    std::shared_ptr<hl_ast_operand> operand;

    if(ctx->expression() != nullptr){
        expression_nesting_level++;
        return;
    } else if(ctx->Identifier() != nullptr){
        operand = std::make_shared<hl_ast_operand>( variable_operand);
        operand->set_name(ctx->Identifier()->getText());
    } else if(ctx->constant() != nullptr){
        if(ctx->constant()->FloatingConstant() != nullptr){
            operand = std::make_shared<hl_ast_operand>( float_immediate_operand);
            std::string constant = ctx->constant()->FloatingConstant()->getText();
            operand->set_immediate(std::stof(constant));
        } else if(ctx->constant()->IntegerConstant() != nullptr){
            operand = std::make_shared<hl_ast_operand>(integer_immediate_operand);
            std::string constant = ctx->constant()->IntegerConstant()->getText();
            operand->set_immediate(std::stoi(constant));
        } else if(ctx->constant()->CharacterConstant() != nullptr){
            throw std::runtime_error("character literals are not supported by the fCore toolchain");
        }
    } else { // string litteral
        operand = std::make_shared<hl_ast_operand>( string_operand);
        operand->set_string(ctx->getText());
    }

    operands_stack.push(operand);
}

void C_Tree_visitor::exitMultiplicativeExpression(C_parser::C_grammarParser::MultiplicativeExpressionContext *ctx) {

    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"*", expr_mult},
            {"/", expr_div},
            {"%", expr_modulo}
    };

    if(ctx->unaryExpression().size()>1){
        processExpression(ctx->multiplicativeOperator().size(), ctx->multiplicativeOperator(), expr_map);
    }

}

void C_Tree_visitor::exitAdditiveExpression(C_parser::C_grammarParser::AdditiveExpressionContext *ctx) {

    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"+", expr_add},
            {"-", expr_sub}
    };

    if(ctx->multiplicativeExpression().size()>1){
        processExpression(ctx->additiveOperator().size(), ctx->additiveOperator(), expr_map);
    }
}

void C_Tree_visitor::exitShiftExpression(C_parser::C_grammarParser::ShiftExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"<<", expr_lsh},
            {">>", expr_rsh}
    };

    if(ctx->additiveExpression().size()>1){
        processExpression(ctx->shiftOperator().size(), ctx->shiftOperator(), expr_map);
    }
}

void C_Tree_visitor::exitEqualityExpression(C_parser::C_grammarParser::EqualityExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"==", expr_eq},
            {"!=", expr_neq}
    };

    if(ctx->relationalExpression().size()>1){
        processExpression(ctx->equalityOperator().size(), ctx->equalityOperator(), expr_map);
    }
}

void C_Tree_visitor::exitRelationalExpression(C_parser::C_grammarParser::RelationalExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"<", expr_lt},
            {">", expr_gt},
            {"<=", expr_lte},
            {">=", expr_gte}
    };

    if(ctx->shiftExpression().size()>1){
        processExpression(ctx->relationalOperator().size(), ctx->relationalOperator(), expr_map);
    }
}


void C_Tree_visitor::exitInclusiveOrExpression(C_parser::C_grammarParser::InclusiveOrExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"|", expr_or_b},
    };

    if(ctx->exclusiveOrExpression().size()>1){
        processExpression(ctx->Or().size(), ctx->Or(), expr_map);
    }
}

void C_Tree_visitor::exitExclusiveOrExpression(C_parser::C_grammarParser::ExclusiveOrExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"^", expr_xor_b},
    };

    if(ctx->andExpression().size()>1){
        processExpression(ctx->Caret().size(), ctx->Caret(), expr_map);
    }
}

void C_Tree_visitor::exitAndExpression(C_parser::C_grammarParser::AndExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"&", expr_and_b},
    };

    if(ctx->equalityExpression().size()>1){
        processExpression(ctx->And().size(), ctx->And(), expr_map);
    }
}

void C_Tree_visitor::exitLogicalOrExpression(C_parser::C_grammarParser::LogicalOrExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"||", expr_or_l},
    };

    if(ctx->logicalAndExpression().size()>1){
        processExpression(ctx->OrOr().size(), ctx->OrOr(), expr_map);
    }
}

void C_Tree_visitor::exitLogicalAndExpression(C_parser::C_grammarParser::LogicalAndExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;

    std::map<std::string, expression_type_t> expr_map = {
            {"&&", expr_and_l},
    };

    if(ctx->inclusiveOrExpression().size()>1){
        processExpression(ctx->AndAnd().size(), ctx->AndAnd(), expr_map);
    }
}


void C_Tree_visitor::exitAssignmentExpression(C_parser::C_grammarParser::AssignmentExpressionContext *ctx) {
    if(ctx->unaryExpression()!= nullptr){
        std::shared_ptr<hl_ast_operand> target = operands_stack.top();
        operands_stack.pop();
        std::shared_ptr<hl_expression_node> value = expressions_stack.top();
        expressions_stack.pop();
        std::shared_ptr<hl_expression_node> assignment = std::make_shared<hl_expression_node>(expr_assign);
        assignment->set_lhs(target);
        assignment->set_rhs(value);
        expressions_stack.push(assignment);
    }
}


void C_Tree_visitor::exitStatement(C_parser::C_grammarParser::StatementContext *ctx) {
    if (ctx->expressionStatement() != nullptr){
        if(!expressions_stack.empty()){
            current_block_item = expressions_stack.top();
            expressions_stack.pop();
        } else{
            std::string erorr_line = ctx->getText();
            throw std::runtime_error("ERROR: internal error, this condition should never happen, contact development team");
        }

    } else if (ctx->iterationStatement() != nullptr) {
        throw std::runtime_error("for loops are not supported yet: " + ctx->getText()+"\n");
    } else if(ctx->selectionStatement() != nullptr){
        throw std::runtime_error("if else control flow is not supported yet: " + ctx->getText()+"\n");
    } else if(ctx->returnStatement() != nullptr){
        if(!expressions_stack.empty()){
            current_function->set_return(expressions_stack.top());
            expressions_stack.pop();
        } else if(!operands_stack.empty()) {
            current_function->set_return(operands_stack.top());
            operands_stack.pop();
        }

    } else {
        throw std::runtime_error("The following statement is not supported: " + ctx->getText()+"\n");
    }
}

void C_Tree_visitor::exitCompilationUnit(C_parser::C_grammarParser::CompilationUnitContext *ctx) {
    root = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);

    root->set_content(functions);

}


template<typename T>
void C_Tree_visitor::processExpression(unsigned int expression_size, const T& operands_array,
                                       std::map<std::string, expression_type_t> &expr_map) {
    std::shared_ptr<hl_expression_node> expression;
    if(expression_nesting_level>0){
        std::shared_ptr<hl_expression_node> ex_1 = expressions_stack.top();
        expressions_stack.pop();
        std::shared_ptr<hl_expression_node> ex_2 = expressions_stack.top();
        expressions_stack.pop();
        int i = 0;
    } else {
        std::stack<std::string> operations;
        std::stack<std::shared_ptr<hl_ast_operand>> reversed_operands;

        for(int i = 0; i <= expression_size; ++i){
            reversed_operands.push(operands_stack.top());
            operands_stack.pop();
        }

        bool first_op = true;
        for(auto item: operands_array){
            expression_type_t type = expr_map[item->getText()];
            std::shared_ptr<hl_expression_node> ex = std::make_shared<hl_expression_node>(type);
            if(first_op){
                ex->set_lhs(reversed_operands.top());
                reversed_operands.pop();
                first_op = false;
            } else{
                ex->set_lhs(expression);
            }
            ex->set_rhs(reversed_operands.top());
            reversed_operands.pop();
            expression = ex;
        }
    }
    expressions_stack.push(expression);
}

void C_Tree_visitor::exitBlockItem(C_parser::C_grammarParser::BlockItemContext *ctx) {
    std::string test = ctx->getText();
    if(in_function_body){
        function_body.push_back(current_block_item);
    }
}

void C_Tree_visitor::exitFunctionCallExpression(C_parser::C_grammarParser::FunctionCallExpressionContext *ctx) {
    std::string name = ctx->typedefName()->getText();
    std::shared_ptr<hl_function_call_node> node = std::make_shared<hl_function_call_node>(name, argument_vector);

    std::shared_ptr<hl_expression_node> exp = std::make_shared<hl_expression_node>(expr_call);
    exp->set_rhs(node);
    expressions_stack.push(exp);
}

void C_Tree_visitor::exitArgumentExpression(C_parser::C_grammarParser::ArgumentExpressionContext *ctx) {
    if(!operands_stack.empty()){
        argument_vector.push_back(operands_stack.top());
        operands_stack.pop();
    } else{
        argument_vector.push_back(expressions_stack.top());
        expressions_stack.pop();
    }
}


