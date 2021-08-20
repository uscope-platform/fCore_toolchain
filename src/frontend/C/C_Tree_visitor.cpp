// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#include "frontend/C/C_Tree_visitor.hpp"

#include <utility>


C_Tree_visitor::C_Tree_visitor() {
    in_function_declaration = false;
    in_function_body = false;
    in_foor_loop_block = false;
    in_conditional_block = false;
    in_array_declaration = false;
    in_array_access = false;
    in_initializer_list = false;
    initializer_array_level = 0;
}



void C_Tree_visitor::enterFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) {
    in_function_declaration = true;
    current_function = std::make_shared<hl_function_def_node>();
}


void C_Tree_visitor::exitDirectDeclarator(C_parser::C_grammarParser::DirectDeclaratorContext *ctx) {
    if(!ctx->arrayDeclarator().empty()){
        in_array_declaration = true;
    } else {
        in_array_declaration = false;
    }
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
    std::string id_name;
    unsigned int n_dimensions;
    if(ctx->declarator()->directDeclarator()->directDeclarator() == nullptr){
        id_name = ctx->declarator()->directDeclarator()->Identifier()->getText();
        n_dimensions = 0;
    } else {
        id_name =  id_name = ctx->declarator()->directDeclarator()->directDeclarator()->Identifier()->getText();
        n_dimensions = ctx->declarator()->directDeclarator()->arrayDeclarator().size();
    }

    std::string type = ctx->typeSpecifier()->getText();

    std::shared_ptr<variable> var;
    if(iom_map.count(id_name)>0){
        var = iom_map[id_name];
    } else {
        var = std::make_shared<variable>(id_name);
    }

    std::shared_ptr<hl_definition_node> identifier = std::make_shared<hl_definition_node>(id_name, hl_ast_node::string_to_type(type), var);
    if(n_dimensions>0){
        std::vector<int> shape;

        std::vector<std::shared_ptr<hl_ast_node>> idx_array;
        for(unsigned int i = 0; i< n_dimensions; ++i){
            shape.insert(shape.begin(), std::static_pointer_cast<hl_ast_operand>(expressions_stack.top())->get_int_value());
            idx_array.insert(idx_array.begin(), expressions_stack.top());
            expressions_stack.pop();
        }

        identifier->set_array_shape(shape);
        identifier->set_array_index(idx_array);
    }





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
    std::string raw_name = ctx->initDeclaratorList()->initDeclarator()[0]->declarator()->directDeclarator()->getText();
    std::string name = raw_name.substr(0, raw_name.find('['));

    std::shared_ptr<variable> var;
    if(iom_map.count(name)>0){
        var = iom_map[name];
    } else {
        var = std::make_shared<variable>( name);
        if(in_array_declaration)
            var->set_type(var_type_array);
    }

    std::shared_ptr<hl_definition_node> node = std::make_shared<hl_definition_node>(name, hl_ast_node::string_to_type(type_name), var);
    node->set_constant(is_const);

    if(in_array_declaration){

        in_array_declaration = false;
        unsigned int d = ctx->initDeclaratorList()->initDeclarator()[0]->declarator()->directDeclarator()->arrayDeclarator().size();
        std::vector<int> shape;

        std::vector<std::shared_ptr<hl_ast_node>> idx_array;
        for(unsigned int i = 0; i< d; ++i){
            shape.insert(shape.begin(), std::static_pointer_cast<hl_ast_operand>(expressions_stack.top())->get_int_value());
            idx_array.insert(idx_array.begin(), expressions_stack.top());
            expressions_stack.pop();
        }

        node->set_array_shape(shape);
        node->set_array_index(idx_array);
        node->set_array_initializer(array_initializer_data);
        array_initializer_data.clear();
    } else{
        if(current_initializer != nullptr){
            node->set_scalar_initializer(current_initializer);
            current_initializer = nullptr;
        }
    }



    if(in_function_body | in_conditional_block | in_foor_loop_block){
        current_block_item = node;
    } else {
        ext_decl.push_back(node);
    }
}

void C_Tree_visitor::enterArrayAccessExpression(C_parser::C_grammarParser::ArrayAccessExpressionContext *ctx) {
    in_array_access = true;
}

void C_Tree_visitor::exitArrayAccessExpression(C_parser::C_grammarParser::ArrayAccessExpressionContext *ctx) {

    std::vector<std::shared_ptr<hl_ast_node>> idx_array;
    for(unsigned int i = 0; i< ctx->primaryExpression().size(); ++i){
        idx_array.insert(idx_array.begin(), expressions_stack.top());
        expressions_stack.pop();
    }
    std::shared_ptr<hl_ast_operand> operand = std::static_pointer_cast<hl_ast_operand>(idx_array[0]);
    idx_array.erase(idx_array.begin());
    operand->set_type(var_type_array);
    operand->set_array_index(idx_array);
    expressions_stack.push(operand);
}


void C_Tree_visitor::enterInitializerList(C_parser::C_grammarParser::InitializerListContext *ctx) {
    in_initializer_list = true;
    initializer_array_level++;
}

void C_Tree_visitor::exitInitializerList(C_parser::C_grammarParser::InitializerListContext *ctx) {
    if(initializer_array_level==1) in_initializer_list = false;
    initializer_array_level--;
}



void C_Tree_visitor::exitInitializer(C_parser::C_grammarParser::InitializerContext *ctx) {
    if(ctx->assignmentExpression() != nullptr && !in_initializer_list){
        current_initializer = expressions_stack.top();
        expressions_stack.pop();
    }
}



void C_Tree_visitor::exitCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) {
    in_function_body = false;

}

void C_Tree_visitor::exitUnaryExpression(C_parser::C_grammarParser::UnaryExpressionContext *ctx) {
    std::shared_ptr<hl_expression_node> expression;
    expression_type_t expr;
    if(ctx->unaryExpression() != nullptr|| !ctx->PlusPlus().empty() || !ctx->MinusMinus().empty()){

        if( !ctx->PlusPlus().empty()){
            expr = expr_incr_pre;
        } else if(!ctx->MinusMinus().empty()){
            expr = expr_decr_pre;
        } else if(ctx->unaryOperator()->getText() == "!"){
            expr = expr_not_l;
        } else if(ctx->unaryOperator()->getText() == "~"){
            expr = expr_not_b;
        } else if(ctx->unaryOperator()->getText() == "-"){
            expr = expr_neg;
        }

        expression = std::make_shared<hl_expression_node>( expr);
        expression->set_rhs(expressions_stack.top());
        expressions_stack.pop();
        expressions_stack.push(expression);

    }

}

void C_Tree_visitor::exitPrimaryExpression(C_parser::C_grammarParser::PrimaryExpressionContext *ctx) {
    std::shared_ptr<hl_ast_operand> operand;

    if(ctx->expression() != nullptr){
        return;
    } else if(ctx->Identifier() != nullptr){
        std::string var_name = ctx->Identifier()->getText();

        if(iom_map.count(var_name)>0){
            operand = std::make_shared<hl_ast_operand>(iom_map[var_name]);
        } else {
            std::shared_ptr<variable> var = std::make_shared<variable>(var_name);
            operand = std::make_shared<hl_ast_operand>(var);
        }


    } else if(ctx->constant() != nullptr){
        if(ctx->constant()->FloatingConstant() != nullptr){

            std::string constant = ctx->constant()->FloatingConstant()->getText();

            std::shared_ptr<variable> var = std::make_shared<variable>("constant",std::stof(constant));
            operand = std::make_shared<hl_ast_operand>( var);

        } else if(ctx->constant()->IntegerConstant() != nullptr){

            std::string constant = ctx->constant()->IntegerConstant()->getText();

            std::shared_ptr<variable> var = std::make_shared<variable>("constant", std::stoi(constant));
            operand = std::make_shared<hl_ast_operand>( var);

        } else if(ctx->constant()->CharacterConstant() != nullptr){
            throw std::runtime_error("character literals are not supported by the fCore toolchain");
        }
    } else { // string litteral
        throw std::runtime_error("Strings are not supported by the fCore toolchain");
    }

    if(in_initializer_list){
        array_initializer_data.push_back(operand);
    } else{
        expressions_stack.push(operand);
    }


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
    std::string dbg = ctx->getText();
    if(ctx->unaryExpression()!= nullptr){
        std::shared_ptr<hl_expression_node> value = std::static_pointer_cast<hl_expression_node>(expressions_stack.top());
        expressions_stack.pop();
        std::shared_ptr<hl_ast_operand> target = std::static_pointer_cast<hl_ast_operand>(expressions_stack.top());
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
    } else if(ctx->selectionStatement() != nullptr){
        current_block_item = conditional;
    } else if(ctx->returnStatement() != nullptr){
        if(!expressions_stack.empty()){
            current_function->set_return(expressions_stack.top());
            expressions_stack.pop();
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

    std::stack<std::string> operations;
    std::stack<std::shared_ptr<hl_ast_node>> reversed_operands;

    for(int i = 0; i <= expression_size; ++i){
        reversed_operands.push(expressions_stack.top());
        expressions_stack.pop();
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

    expressions_stack.push(expression);
}

void C_Tree_visitor::exitBlockItem(C_parser::C_grammarParser::BlockItemContext *ctx) {
    std::string test = ctx->getText();
    if(in_function_body){
        if(ctx->statement() != nullptr){
            if(ctx->statement()->returnStatement() != nullptr) return;
        }
        function_body.push_back(current_block_item);
    }
}

void C_Tree_visitor::exitFunctionCallExpression(C_parser::C_grammarParser::FunctionCallExpressionContext *ctx) {
    std::string name = ctx->typedefName()->getText();
    std::shared_ptr<hl_function_call_node> node = std::make_shared<hl_function_call_node>(name, argument_vector);
    argument_vector.clear();
    expressions_stack.push(node);

}

void C_Tree_visitor::exitArgumentExpression(C_parser::C_grammarParser::ArgumentExpressionContext *ctx) {
    argument_vector.push_back(expressions_stack.top());
    expressions_stack.pop();
}

void C_Tree_visitor::exitIfContent(C_parser::C_grammarParser::IfContentContext *ctx) {
    conditional->set_if_block(conditional_body);
    conditional_body.clear();
}

void C_Tree_visitor::exitConditionalBlockItem(C_parser::C_grammarParser::ConditionalBlockItemContext *ctx) {
    conditional_body.push_back(current_block_item);
}

void C_Tree_visitor::exitElseContent(C_parser::C_grammarParser::ElseContentContext *ctx) {
    conditional->set_else_block(conditional_body);
    conditional_body.clear();
}

void C_Tree_visitor::exitConditionContent(C_parser::C_grammarParser::ConditionContentContext *ctx) {
    conditional->set_condition(expressions_stack.top());
    expressions_stack.pop();
}

void C_Tree_visitor::enterSelectionStatement(C_parser::C_grammarParser::SelectionStatementContext *ctx) {
    save_current_block_context();
    conditional = std::make_shared<hl_ast_conditional_node>();
    in_conditional_block = true;
    in_foor_loop_block = false;
    in_function_body = false;
}

void C_Tree_visitor::exitSelectionStatement(C_parser::C_grammarParser::SelectionStatementContext *ctx) {
    restore_current_block_context();
}


void C_Tree_visitor::enterIterationStatement(C_parser::C_grammarParser::IterationStatementContext *ctx) {
    save_current_block_context();
    loop = std::make_shared<hl_ast_loop_node>();
    loop_body.clear();
    in_function_body = false;
    in_foor_loop_block = true;
    in_conditional_block = false;
}

void C_Tree_visitor::exitIterationStatement(C_parser::C_grammarParser::IterationStatementContext *ctx) {
    loop->set_loop_content(loop_body);
    current_block_item = loop;
    restore_current_block_context();
}

std::string C_Tree_visitor::restore_current_block_context() {
    std::string outer_type = outer_block_types.top();
    outer_block_types.pop();

    if(outer_type == "function"){
        in_foor_loop_block = false;
        in_conditional_block = false;
        in_function_body = true;
    } else if(outer_type == "loop"){
        in_foor_loop_block = true;
        in_conditional_block = false;
        in_function_body = false;
        loop = std::static_pointer_cast<hl_ast_loop_node>(outer_block_nodes.top());
        outer_block_nodes.pop();
        loop_body = outer_block_contents.top();
        outer_block_contents.pop();
    } else if(outer_type == "conditional"){
        in_foor_loop_block = false;
        in_conditional_block = true;
        in_function_body = false;
        conditional = std::static_pointer_cast<hl_ast_conditional_node>(outer_block_nodes.top());
        outer_block_nodes.pop();
        conditional_body = outer_block_contents.top();
        outer_block_contents.pop();
    }
    return outer_type;
}



void C_Tree_visitor::save_current_block_context() {
    if(in_conditional_block){
        outer_block_nodes.push(conditional);
        outer_block_contents.push(conditional_body);
        outer_block_types.push("conditional");
    } else if(in_foor_loop_block){
        outer_block_nodes.push(loop);
        outer_block_contents.push(loop_body);
        outer_block_types.push("loop");
    } else{
        outer_block_types.push("function");
    }
}

void C_Tree_visitor::exitForExitCondition(C_parser::C_grammarParser::ForExitConditionContext *ctx) {
    loop->set_condition(std::static_pointer_cast<hl_expression_node>(expressions_stack.top()));
    expressions_stack.pop();
}

void C_Tree_visitor::exitForDeclaration(C_parser::C_grammarParser::ForDeclarationContext *ctx) {
    loop->set_init_statement(std::static_pointer_cast<hl_definition_node>(current_block_item));
    ext_decl.clear();
}

void C_Tree_visitor::exitForIterationExpression(C_parser::C_grammarParser::ForIterationExpressionContext *ctx) {
    loop->set_iteration_expr(std::static_pointer_cast<hl_expression_node>(expressions_stack.top()));
    expressions_stack.pop();
}

void C_Tree_visitor::exitForBlockItem(C_parser::C_grammarParser::ForBlockItemContext *ctx) {
    loop_body.push_back(current_block_item);
}

void C_Tree_visitor::enterForContent(C_parser::C_grammarParser::ForContentContext *ctx) {
    in_foor_loop_block = true;
}

void C_Tree_visitor::exitForContent(C_parser::C_grammarParser::ForContentContext *ctx) {
    in_foor_loop_block = false;
}

void C_Tree_visitor::set_iom_map(std::unordered_map<std::string, std::shared_ptr<variable>> iom) {
    iom_map = std::move(iom);
}

