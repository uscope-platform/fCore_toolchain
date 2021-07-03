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
}


void C_Tree_visitor::exitFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) {

    std::string func_name = ctx->declarator()->directDeclarator()->directDeclarator()->getText();
    if(ctx->declarator()->directDeclarator()->parameterTypeList() != nullptr){

        C_parser::C_grammarParser::ParameterListContext  *parameters = ctx->declarator()->directDeclarator()->parameterTypeList()->parameterList();
        for(auto item:parameters->parameterDeclaration()){
            std::vector<C_parser::C_grammarParser::DeclarationSpecifierContext *> param_specifiers = item->declarationSpecifiers()->declarationSpecifier();
            std::string param_type;
            for (auto param_type_item:param_specifiers) {
                std::string content;
                if(param_type_item->storageClassSpecifier() != nullptr)  content = param_type_item->storageClassSpecifier()->toString();
                if(param_type_item->typeSpecifier() != nullptr)  param_type = param_type_item->typeSpecifier()->getText();
                if(param_type_item->typeQualifier() != nullptr)  content = param_type_item->typeQualifier()->toString();
            }
        }
        std::string type = declaration_type.top();
        declaration_type.pop();
        std::shared_ptr<hl_function_node> node = std::make_shared<hl_function_node>(hl_ast_node_type_function, hl_ast_node::string_to_type(type), func_name);
        node->set_parameters_list(parameters_list);
        node->set_body(function_body);
        function_body.clear();
        in_function_declaration = false;
        functions.push_back(node);
    }
}

void C_Tree_visitor::exitDeclarationSpecifiers(C_parser::C_grammarParser::DeclarationSpecifiersContext *ctx) {
    std::string type;
    for (auto item:ctx->declarationSpecifier()) {
        std::string content;
        if(item->storageClassSpecifier() != nullptr)  content = item->storageClassSpecifier()->toString();
        if(item->typeSpecifier() != nullptr)  type = item->typeSpecifier()->getText();
        if(item->typeQualifier() != nullptr)  content = item->typeQualifier()->toString();
    }
        declaration_type.push(type);
}

void C_Tree_visitor::exitParameterDeclaration(C_parser::C_grammarParser::ParameterDeclarationContext *ctx) {
    std::string id_name = ctx->declarator()->directDeclarator()->Identifier()->getText();
    std::string type = declaration_type.top();
    declaration_type.pop();
    std::shared_ptr<hl_identifier_node> identifier = std::make_shared<hl_identifier_node>(hl_ast_node_type_identifier, id_name, hl_ast_node::string_to_type(type));
    if(in_function_declaration) {
        parameters_list.push_back(identifier);
    }
}

void C_Tree_visitor::enterCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) {
    in_function_body = true;
}

void C_Tree_visitor::exitInitDeclarator(C_parser::C_grammarParser::InitDeclaratorContext *ctx) {
    std::string id_name = ctx->declarator()->directDeclarator()->getText();

    std::string type = declaration_type.top();
    declaration_type.pop();

    std::shared_ptr<hl_identifier_node> identifier = std::make_shared<hl_identifier_node>(hl_ast_node_type_identifier, id_name, hl_ast_node::string_to_type(type));

    if(in_function_body) {
        function_body.push_back(identifier);
    }

}

void C_Tree_visitor::exitDeclaration(C_parser::C_grammarParser::DeclarationContext *ctx) {
    if(ctx->initDeclaratorList() == nullptr){
        std::string id_name = "ERROR_WRONG_NAME_DETECTED";
        for(auto item : ctx->declarationSpecifiers()->declarationSpecifier()){
            if(item->typeSpecifier() != nullptr){
                id_name = item->typeSpecifier()->getText();
            }
        }
        std::string type = declaration_type.top();
        declaration_type.pop();
        std::shared_ptr<hl_identifier_node> identifier = std::make_shared<hl_identifier_node>(hl_ast_node_type_identifier, id_name, hl_ast_node::string_to_type(type));
        if(in_function_body) {
            function_body.push_back(identifier);
        }
    }

}

void C_Tree_visitor::exitCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) {
    //std::shared_ptr<hl_identifier_node> id = std::static_pointer_cast<hl_identifier_node>(function_body[0]);
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
