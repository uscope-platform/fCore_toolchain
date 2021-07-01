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


C_Tree_visitor::C_Tree_visitor(std::shared_ptr<variable_map> map) {
    varmap = std::move(map);
    in_function_declaration = false;
    in_function_body = false;
}



void C_Tree_visitor::enterFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) {
    in_function_declaration = true;
}


void C_Tree_visitor::exitFunctionDefinition(C_parser::C_grammarParser::FunctionDefinitionContext *ctx) {

    std::string func_name = ctx->declarator()->directDeclarator()->directDeclarator()->getText();

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
    std::shared_ptr<hl_function_node> node = std::make_shared<hl_function_node>(type_function, hl_ast_node::string_to_type(type), func_name);
    node->set_parameters_list(parameters_list);
    node->set_body(function_body);
    function_body.clear();
    in_function_declaration = false;
    functions.push_back(node);
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
    std::shared_ptr<hl_identifier_node> identifier = std::make_shared<hl_identifier_node>(type_identifier, id_name, hl_ast_node::string_to_type(type));
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

    std::shared_ptr<hl_identifier_node> identifier = std::make_shared<hl_identifier_node>(type_identifier, id_name, hl_ast_node::string_to_type(type));

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
        std::shared_ptr<hl_identifier_node> identifier = std::make_shared<hl_identifier_node>(type_identifier, id_name, hl_ast_node::string_to_type(type));
        if(in_function_body) {
            function_body.push_back(identifier);
        }
    }

}

void C_Tree_visitor::exitCompoundStatement(C_parser::C_grammarParser::CompoundStatementContext *ctx) {
    std::shared_ptr<hl_identifier_node> id = std::static_pointer_cast<hl_identifier_node>(function_body[0]);
    id = std::static_pointer_cast<hl_identifier_node>(function_body[1]);
    id = std::static_pointer_cast<hl_identifier_node>(function_body[2]);
    id = std::static_pointer_cast<hl_identifier_node>(function_body[3]);
    in_function_body = false;
}

