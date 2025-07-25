// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "frontend/C/C_Tree_visitor.hpp"

#include <utility>
#include <data_structures/high_level_ast/ast_struct.hpp>

namespace fcore{

    C_Tree_visitor::C_Tree_visitor() {
        in_function_declaration = false;
        in_function_body = false;
        in_foor_loop_block = false;
        in_conditional_block = false;
        in_array_declaration = false;
        in_array_access = false;
        in_initializer_list = false;
        initializer_array_level = 0;
        current_block_item = std::vector<std::shared_ptr<ast_node>>(1000, nullptr);
    }



    void C_Tree_visitor::enterFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *) {
        in_function_declaration = true;
        current_function = std::make_shared<ast_function_def>();
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

        current_function->set_return_type(ast_node::string_to_type(type));
        current_function->set_name(func_name);
        current_function->set_parameters_list(parameters_list);
        current_function->set_body(function_body);
        function_body.clear();
        parameters_list.clear();
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
            id_name = ctx->declarator()->directDeclarator()->directDeclarator()->Identifier()->getText();
            n_dimensions = ctx->declarator()->directDeclarator()->arrayDeclarator().size();
        }

        std::shared_ptr<ast_definition> identifier;

        if(ctx->typeSpecifier()->structSpecifier() != nullptr) {
            auto struct_def = std::make_shared<ast_struct>(ctx->typeSpecifier()->structSpecifier()->Identifier()->getText());
            identifier = std::make_shared<ast_definition>(id_name, struct_def);
        }else {

            std::string type = ctx->typeSpecifier()->getText();

            std::shared_ptr<variable> var = std::make_shared<variable>(id_name);

            if(dma_specs.contains(id_name)){
                var->set_variable_class(dma_specs[id_name]);
            }

            identifier = std::make_shared<ast_definition>(id_name, ast_node::string_to_type(type), var);
            if(n_dimensions>0){
                std::vector<int> shape;

                std::vector<std::shared_ptr<ast_node>> idx_array;
                for(unsigned int i = 0; i< n_dimensions; ++i){
                    shape.insert(shape.begin(), std::static_pointer_cast<ast_operand>(expressions_stack.top())->get_int_value());
                    idx_array.insert(idx_array.begin(), expressions_stack.top());
                    expressions_stack.pop();
                }

                identifier->set_array_shape(shape);
                identifier->set_array_index(idx_array);
            }
        }


        if(in_function_declaration) {
            parameters_list.push_back(identifier);
        }
        current_block_item[0] = current_initializer;
    }

    void C_Tree_visitor::enterCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *) {
        in_function_body = true;
    }


    void C_Tree_visitor::exitDeclaration(C_parser::C_grammarParser::DeclarationContext *ctx) {

        bool is_const = ctx->Const() != nullptr;
        std::string type_name = ctx->typeSpecifier()->getText();

        std::shared_ptr<ast_definition> node;
        std::vector<std::shared_ptr<ast_node>> multi_initialization_nodes;
        if(ctx->typeSpecifier()->structSpecifier() == nullptr) {
            if(ctx->initDeclaratorList()->initDeclarator().size() > 1) {
                for(int i = 0; i< ctx->initDeclaratorList()->initDeclarator().size(); ++i) {
                    std::string raw_name = ctx->initDeclaratorList()->initDeclarator()[i]->declarator()->directDeclarator()->getText();
                    std::string name = raw_name.substr(0, raw_name.find('['));

                    auto var = std::make_shared<variable>(name);

                    if(dma_specs.contains(name)){
                        var->set_variable_class(dma_specs[name]);
                    }

                    std::shared_ptr<ast_definition> n = std::make_shared<
                        ast_definition>(name, ast_node::string_to_type(type_name), var);
                    n->set_constant(is_const);
                    multi_initialization_nodes.push_back(n);
                }


            } else {

                std::string raw_name = ctx->initDeclaratorList()->initDeclarator()[0]->declarator()->directDeclarator()->getText();
                std::string name = raw_name.substr(0, raw_name.find('['));

                std::shared_ptr<variable> var = std::make_shared<variable>(name);

                if(dma_specs.contains(name)){
                    var->set_variable_class(dma_specs[name]);
                }

                if(in_array_declaration)
                    var->set_type(var_type_array);
                node = std::make_shared<ast_definition>(name, ast_node::string_to_type(type_name), var);
                node->set_constant(is_const);

                if(in_array_declaration){

                    in_array_declaration = false;
                    unsigned int d = ctx->initDeclaratorList()->initDeclarator()[0]->declarator()->directDeclarator()->arrayDeclarator().size();
                    std::vector<int> shape;

                    std::vector<std::shared_ptr<ast_node>> idx_array;
                    for(unsigned int i = 0; i< d; ++i){
                        shape.insert(shape.begin(), std::static_pointer_cast<ast_operand>(expressions_stack.top())->get_int_value());
                        idx_array.insert(idx_array.begin(), expressions_stack.top());
                        expressions_stack.pop();
                    }

                    node->set_array_shape(shape);
                    array_shapes_map[name] = shape;
                    node->set_array_index(idx_array);
                    node->set_array_initializer(array_initializer_data);
                    array_initializer_data.clear();
                } else{
                    if(current_initializer != nullptr){
                        node->set_scalar_initializer(current_initializer);
                        current_initializer = nullptr;
                    }
                }

            }



        } else if(ctx->initDeclaratorList() == nullptr) {
            return;
        } else{

            auto rest = ctx->initDeclaratorList()->initDeclarator();
            std::string name = ctx->initDeclaratorList()->initDeclarator()[0]->declarator()->directDeclarator()->getText();

            std::string type = ctx->typeSpecifier()->structSpecifier()->Identifier()->getText();
            auto struct_def = std::make_shared<ast_struct>(type);
            struct_def->add_initializers(array_initializer_data);
            node = std::make_shared<ast_definition>(name, struct_def);
            array_initializer_data.clear();
        }
        if(in_function_body | in_conditional_block | in_foor_loop_block){
            if(multi_initialization_nodes.empty()) {
                current_block_item[0] = node;
            }else {
                current_block_item.insert(current_block_item.begin(), multi_initialization_nodes.begin(), multi_initialization_nodes.end());
            }
        } else {
            globals.push_back(node);
        }
    }

    void C_Tree_visitor::enterArrayAccessExpression(C_parser::C_grammarParser::ArrayAccessExpressionContext *) {
        in_array_access = true;
    }

    void C_Tree_visitor::exitArrayAccessExpression(C_parser::C_grammarParser::ArrayAccessExpressionContext *ctx) {

        std::vector<std::shared_ptr<ast_node>> idx_array;
        for(unsigned int i = 0; i< ctx->primaryExpression().size(); ++i){
            idx_array.insert(idx_array.begin(), expressions_stack.top());
            expressions_stack.pop();
        }
        std::shared_ptr<ast_operand> operand = std::static_pointer_cast<ast_operand>(idx_array[0]);
        idx_array.erase(idx_array.begin());
        operand->set_type(var_type_array);
        operand->set_array_index(idx_array);
        expressions_stack.push(operand);
    }


    void C_Tree_visitor::enterInitializerList(C_parser::C_grammarParser::InitializerListContext *) {
        in_initializer_list = true;
        initializer_array_level++;
    }

    void C_Tree_visitor::exitInitializerList(C_parser::C_grammarParser::InitializerListContext *) {
        if(initializer_array_level==1) in_initializer_list = false;
        initializer_array_level--;
    }



    void C_Tree_visitor::exitInitializer(C_parser::C_grammarParser::InitializerContext *ctx) {
        if(ctx->assignmentExpression() != nullptr && !in_initializer_list){
            current_initializer = expressions_stack.top();
            expressions_stack.pop();
        }
    }



    void C_Tree_visitor::exitCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *) {
        in_function_body = false;

    }

    void C_Tree_visitor::exitUnaryExpression(C_parser::C_grammarParser::UnaryExpressionContext *ctx) {
        if(ctx->unaryExpression() != nullptr|| !ctx->PlusPlus().empty() || !ctx->MinusMinus().empty()){
            ast_expression::expression_type expr;

            if( !ctx->PlusPlus().empty()){
                expr = ast_expression::PRE_INCR;
            } else if(!ctx->MinusMinus().empty()){
                expr =ast_expression:: PRE_DECR;
            } else if(ctx->unaryOperator()->getText() == "!"){
                expr = ast_expression::NOT_L;
            } else if(ctx->unaryOperator()->getText() == "~"){
                expr = ast_expression::NOT_B;
            } else if(ctx->unaryOperator()->getText() == "-"){
                expr = ast_expression::NEG;
            }

            const auto expression = std::make_shared<ast_expression>(expr);
            expression->set_rhs(expressions_stack.top());
            expressions_stack.pop();
            expressions_stack.push(expression);

        }

    }

    void C_Tree_visitor::exitPrimaryExpression(C_parser::C_grammarParser::PrimaryExpressionContext *ctx) {
        std::shared_ptr<ast_operand> operand;

        if(ctx->expression() != nullptr){
            return;
        }
        if(ctx->Identifier() != nullptr){
            std::string var_name = ctx->Identifier()->getText();

            std::shared_ptr<variable> var = std::make_shared<variable>(var_name);
            if(dma_specs.contains(var_name)){
                var->set_variable_class(dma_specs[var_name]);
            }

            operand = std::make_shared<ast_operand>(var);
            operand->get_variable()->set_array_shape(array_shapes_map[var_name]);



        } else if(ctx->constant() != nullptr){
            if(ctx->constant()->FloatingConstant() != nullptr){

                std::string constant = ctx->constant()->FloatingConstant()->getText();
                float const_value = std::stof(constant);
                if(ctx->constant()->Minus() != nullptr){
                    const_value = -const_value;
                }
                std::shared_ptr<variable> var = std::make_shared<variable>("constant",const_value);
                operand = std::make_shared<ast_operand>( var);

            } else if(ctx->constant()->IntegerConstant() != nullptr){

                std::string constant = ctx->constant()->IntegerConstant()->getText();

                int const_value;
                if(constant.starts_with("0x")){
                    const_value = std::stoi(constant, nullptr, 16);
                } else if(constant.starts_with("0b")){
                    const_value = std::stoi(constant, nullptr, 2);
                } else if(constant.starts_with("0")){
                    const_value = std::stoi(constant, nullptr, 8);
                } else {
                    const_value = std::stoi(constant, nullptr, 10);
                }

                if(ctx->constant()->Minus() != nullptr){
                    const_value = -const_value;
                }
                std::shared_ptr<variable> var = std::make_shared<variable>("constant", const_value);
                operand = std::make_shared<ast_operand>( var);

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

        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"*", ast_expression::MULT},
                {"/", ast_expression::DIV},
                {"%", ast_expression::MODULO}
        };

        if(ctx->unaryExpression().size()>1){
            processExpression(ctx->multiplicativeOperator().size(), ctx->multiplicativeOperator(), expr_map);
        }

    }

    void C_Tree_visitor::exitAdditiveExpression(C_parser::C_grammarParser::AdditiveExpressionContext *ctx) {

        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"+", ast_expression::ADD},
                {"-", ast_expression::SUB}
        };

        if(ctx->multiplicativeExpression().size()>1){
            processExpression(ctx->additiveOperator().size(), ctx->additiveOperator(), expr_map);
        }
    }

    void C_Tree_visitor::exitShiftExpression(C_parser::C_grammarParser::ShiftExpressionContext *ctx) {
        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"<<", ast_expression::LSH},
                {">>", ast_expression::RSH}
        };

        if(ctx->additiveExpression().size()>1){
            processExpression(ctx->shiftOperator().size(), ctx->shiftOperator(), expr_map);
        }
    }

    void C_Tree_visitor::exitEqualityExpression(C_parser::C_grammarParser::EqualityExpressionContext *ctx) {
        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"==", ast_expression::EQ},
                {"!=", ast_expression::NEQ}
        };

        if(ctx->relationalExpression().size()>1){
            processExpression(ctx->equalityOperator().size(), ctx->equalityOperator(), expr_map);
        }
    }

    void C_Tree_visitor::exitRelationalExpression(C_parser::C_grammarParser::RelationalExpressionContext *ctx) {
        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"<", ast_expression::LT},
                {">", ast_expression::GT},
                {"<=", ast_expression::LTE},
                {">=", ast_expression::GTE}
        };

        if(ctx->shiftExpression().size()>1){
            processExpression(ctx->relationalOperator().size(), ctx->relationalOperator(), expr_map);
        }
    }


    void C_Tree_visitor::exitInclusiveOrExpression(C_parser::C_grammarParser::InclusiveOrExpressionContext *ctx) {
        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"|", ast_expression::OR_B},
        };

        if(ctx->exclusiveOrExpression().size()>1){
            processExpression(ctx->Or().size(), ctx->Or(), expr_map);
        }
    }

    void C_Tree_visitor::exitExclusiveOrExpression(C_parser::C_grammarParser::ExclusiveOrExpressionContext *ctx) {
        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"^", ast_expression::XOR_B},
        };

        if(ctx->andExpression().size()>1){
            processExpression(ctx->Caret().size(), ctx->Caret(), expr_map);
        }
    }

    void C_Tree_visitor::exitAndExpression(C_parser::C_grammarParser::AndExpressionContext *ctx) {
        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"&", ast_expression::AND_B},
        };

        if(ctx->equalityExpression().size()>1){
            processExpression(ctx->And().size(), ctx->And(), expr_map);
        }
    }

    void C_Tree_visitor::exitLogicalOrExpression(C_parser::C_grammarParser::LogicalOrExpressionContext *ctx) {
        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"||", ast_expression::OR_L},
        };

        if(ctx->logicalAndExpression().size()>1){
            processExpression(ctx->OrOr().size(), ctx->OrOr(), expr_map);
        }
    }

    void C_Tree_visitor::exitLogicalAndExpression(C_parser::C_grammarParser::LogicalAndExpressionContext *ctx) {
        std::shared_ptr<ast_expression> expression;

        std::map<std::string, ast_expression::expression_type> expr_map = {
                {"&&", ast_expression::AND_L},
        };

        if(ctx->inclusiveOrExpression().size()>1){
            processExpression(ctx->AndAnd().size(), ctx->AndAnd(), expr_map);
        }
    }


    void C_Tree_visitor::exitConditionalExpression(C_parser::C_grammarParser::ConditionalExpressionContext *ctx) {

        if(ctx->Question() != nullptr){
            auto c = std::make_shared<ast_conditional>();
            c->set_else_block({expressions_stack.top()});
            expressions_stack.pop();
            c->set_if_block({expressions_stack.top()});
            expressions_stack.pop();
            c->set_condition(expressions_stack.top());
            expressions_stack.pop();
            c->set_ternary(true);
            expressions_stack.push(c);
        }
    }



    void C_Tree_visitor::exitAssignmentExpression(C_parser::C_grammarParser::AssignmentExpressionContext *ctx) {
        std::string dbg = ctx->getText();
        if(ctx->unaryExpression()!= nullptr){
            ast_expression::assignment_type operator_type;
            if(ctx->assignmentOperator()!= nullptr){
                std::string raw_operator = ctx->assignmentOperator()->getText();
                if(raw_operator.size()==1)
                    operator_type = ast_expression::regular_assignment;
                else{
                    char assignment_qualifier = raw_operator.at(0);
                    switch (assignment_qualifier) {
                        case '+':
                            operator_type = ast_expression::addition_assignment;
                            break;
                        case '-':
                            operator_type = ast_expression::subtraction_assignment;
                            break;
                        case '*':
                            operator_type = ast_expression::multiplication_assignment;
                            break;
                        case '/':
                            operator_type = ast_expression::division_assignment;
                            break;
                        case '%':
                            operator_type = ast_expression::modulo_assignment;
                            break;
                        case '&':
                            operator_type = ast_expression::and_assignment;
                            break;
                        case '|':
                            operator_type = ast_expression::or_assignment;
                            break;
                        case '^':
                            operator_type = ast_expression::xor_assignment;
                            break;
                        case '<':
                            operator_type = ast_expression::lsh_assignment;
                            break;
                        case '>':
                            operator_type = ast_expression::rsh_assignment;
                            break;
                        default:
                            throw std::runtime_error("ERORR: unknown assignment qualifier.");
                    }
                }
            }
            std::shared_ptr<ast_node> value = expressions_stack.top();
            expressions_stack.pop();
            std::shared_ptr<ast_node> target = expressions_stack.top();
            expressions_stack.pop();
            std::shared_ptr<ast_expression> assignment = std::make_shared<ast_expression>(ast_expression::ASSIGN);
            assignment->set_lhs(target);
            assignment->set_rhs(value);
            assignment->set_assignment_type(operator_type);
            expressions_stack.push(assignment);
        }
    }


    void C_Tree_visitor::exitStatement(C_parser::C_grammarParser::StatementContext *ctx) {
        if (ctx->expressionStatement() != nullptr){
            if(!expressions_stack.empty()){
                current_block_item[0] = expressions_stack.top();
                expressions_stack.pop();
            } else{
                std::string erorr_line = ctx->getText();
                throw std::runtime_error("internal error, this condition should never happen, contact development team");
            }
        } else if (ctx->iterationStatement() != nullptr) {
        } else if(ctx->selectionStatement() != nullptr){
            current_block_item[0] = conditional;
        } else if(ctx->returnStatement() != nullptr){
            if(!expressions_stack.empty()){
                current_function->set_return(expressions_stack.top());
                expressions_stack.pop();
            }

        } else {
            throw std::runtime_error("The following statement is not supported: " + ctx->getText()+"\n");
        }
    }

    void C_Tree_visitor::exitCompilationUnit(C_parser::C_grammarParser::CompilationUnitContext *) {
        root = std::make_shared<ast_code_block>();

        root->set_content(functions);

    }

    void C_Tree_visitor::exitStructDeclaration(C_parser::C_grammarParser::StructDeclarationContext *ctx) {
        auto type = ctx->specifierQualifierList()->typeSpecifier()->getText();
        auto name = ctx->structDeclaratorList()->structDeclarator()[0]->getText();
        struct_fields.emplace_back(type, name);
    }

    void C_Tree_visitor::exitStructSpecifier(C_parser::C_grammarParser::StructSpecifierContext *ctx) {
        auto struct_name = ctx->Identifier()->getText();
        auto struct_def = std::make_shared<ast_struct>(struct_name);

        for(auto &[field_type, field_name]:struct_fields) {
            auto var = std::make_shared<variable>(field_name);
            auto def = std::make_shared<ast_definition>(field_name, ast_node::string_to_type(field_type), var);
            struct_def->add_definition(def);
        }
        auto def = std::make_shared<ast_definition>(struct_name, struct_def);

        if(in_function_body | in_conditional_block | in_foor_loop_block){
            current_block_item[0] = def;
        } else {
            if(!in_function_declaration) globals.push_back(def);
        }

        struct_fields.clear();
    }

    void C_Tree_visitor::exitStructExpression(C_parser::C_grammarParser::StructExpressionContext *ctx) {
        std::vector<std::string> accessors;
        for(const auto &item: ctx->Identifier()) {
            auto id = item->getText();
            accessors.push_back(id);
        }
        const auto base_expr = std::static_pointer_cast<ast_operand>(expressions_stack.top());
        base_expr->get_variable()->add_struct_accessors(accessors);


    }

    template<typename T>
    void C_Tree_visitor::processExpression(unsigned int expression_size, const T& operands_array,
                                                  std::map<std::string, ast_expression::expression_type> &expr_map) {
        std::shared_ptr<ast_expression> expression;

        std::stack<std::string> operations;
        std::stack<std::shared_ptr<ast_node>> reversed_operands;

        for(uint32_t i = 0; i <= expression_size; ++i){
            reversed_operands.push(expressions_stack.top());
            expressions_stack.pop();
        }

        bool first_op = true;
        for(auto item: operands_array){
            ast_expression::expression_type type = expr_map[item->getText()];
            std::shared_ptr<ast_expression> ex = std::make_shared<ast_expression>(type);
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
            for(int i = 0; i < current_block_item.size(); ++i) {
                if(current_block_item[i] == nullptr) break;
                function_body.push_back(current_block_item[i]);
                current_block_item[i] = nullptr;
            }
        }
    }

    void C_Tree_visitor::exitFunctionCallExpression(C_parser::C_grammarParser::FunctionCallExpressionContext *ctx) {
        std::string name = ctx->typedefName()->getText();
        std::shared_ptr<ast_call> node = std::make_shared<ast_call>(name, argument_vector);
        argument_vector.clear();
        expressions_stack.push(node);

    }

    void C_Tree_visitor::exitArgumentExpression(C_parser::C_grammarParser::ArgumentExpressionContext *) {
        argument_vector.push_back(expressions_stack.top());
        expressions_stack.pop();
    }


    void C_Tree_visitor::exitIfContent(C_parser::C_grammarParser::IfContentContext *) {
        conditional->set_if_block(conditional_body);
        conditional_body.clear();
    }

    void C_Tree_visitor::exitConditionalBlockItem(C_parser::C_grammarParser::ConditionalBlockItemContext *) {
        conditional_body.push_back(current_block_item[0]);
    }

    void C_Tree_visitor::exitElseContent(C_parser::C_grammarParser::ElseContentContext *) {
        conditional->set_else_block(conditional_body);
        conditional_body.clear();
    }

    void C_Tree_visitor::exitConditionContent(C_parser::C_grammarParser::ConditionContentContext *) {
        conditional->set_condition(expressions_stack.top());
        expressions_stack.pop();
    }

    void C_Tree_visitor::enterSelectionStatement(C_parser::C_grammarParser::SelectionStatementContext *) {
        save_current_block_context();
        conditional = std::make_shared<ast_conditional>();
        in_conditional_block = true;
        in_foor_loop_block = false;
        in_function_body = false;
    }

    void C_Tree_visitor::exitSelectionStatement(C_parser::C_grammarParser::SelectionStatementContext *) {
        restore_current_block_context();
    }


    void C_Tree_visitor::enterIterationStatement(C_parser::C_grammarParser::IterationStatementContext *) {
        save_current_block_context();
        loop = std::make_shared<ast_loop>();
        loop_body.clear();
        in_function_body = false;
        in_foor_loop_block = true;
        in_conditional_block = false;
    }

    void C_Tree_visitor::exitIterationStatement(C_parser::C_grammarParser::IterationStatementContext *) {
        loop->set_loop_content(loop_body);
        current_block_item[0] = loop;
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
            loop = std::static_pointer_cast<ast_loop>(outer_block_nodes.top());
            outer_block_nodes.pop();
            loop_body = outer_block_contents.top();
            outer_block_contents.pop();
        } else if(outer_type == "conditional"){
            in_foor_loop_block = false;
            in_conditional_block = true;
            in_function_body = false;
            conditional = std::static_pointer_cast<ast_conditional>(outer_block_nodes.top());
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
            outer_block_types.emplace("conditional");
        } else if(in_foor_loop_block){
            outer_block_nodes.push(loop);
            outer_block_contents.push(loop_body);
            outer_block_types.emplace("loop");
        } else{
            outer_block_types.emplace("function");
        }
    }

    void C_Tree_visitor::exitForExitCondition(C_parser::C_grammarParser::ForExitConditionContext *) {
        loop->set_condition(std::static_pointer_cast<ast_expression>(expressions_stack.top()));
        expressions_stack.pop();
    }

    void C_Tree_visitor::exitForDeclaration(C_parser::C_grammarParser::ForDeclarationContext *) {
        loop->set_init_statement(std::static_pointer_cast<ast_definition>(current_block_item[0]));
        globals.clear();
    }

    void C_Tree_visitor::exitForIterationExpression(C_parser::C_grammarParser::ForIterationExpressionContext *) {
        loop->set_iteration_expr(std::static_pointer_cast<ast_expression>(expressions_stack.top()));
        expressions_stack.pop();
    }

    void C_Tree_visitor::exitForBlockItem(C_parser::C_grammarParser::ForBlockItemContext *) {
        loop_body.push_back(current_block_item[0]);
    }

    void C_Tree_visitor::enterForContent(C_parser::C_grammarParser::ForContentContext *) {
        in_foor_loop_block = true;
    }

    void C_Tree_visitor::exitForContent(C_parser::C_grammarParser::ForContentContext *) {
        in_foor_loop_block = false;
    }

}
