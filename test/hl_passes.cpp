//
// Created by fils on 05/07/2021.
//

#include <gtest/gtest.h>
#include "code_elements/hl_ast/hl_ast_node.h"
#include "code_elements/hl_ast/hl_ast_operand.h"
#include "code_elements/hl_ast/hl_expression_node.h"
#include "frontend/variable_map.hpp"
#include "frontend/define_map.h"
#include "frontend/C/C_language_parser.h"
#include "passes/hl_passes.hpp"
#include "passes/hl_ast/function_mapping.h"
#include "passes/hl_ast/hl_pass_manager.h"
#include "passes/hl_ast/normalization_pass.h"


#include <memory>
#include <fstream>


TEST(HlPassesTest, divisionImplementation) {


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> lvl_1 = std::make_shared<hl_expression_node>(expr_mult);
    lvl_1->set_lhs(op_1);
    lvl_1->set_rhs(op_2);

    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(7);

    std::shared_ptr<hl_expression_node> lvl_2 = std::make_shared<hl_expression_node>(expr_div);
    lvl_2->set_lhs(lvl_1);
    lvl_2->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");
    std::shared_ptr<hl_expression_node> lvl_3 = std::make_shared<hl_expression_node>(expr_assign);
    lvl_3->set_lhs(op_3);
    lvl_3->set_rhs(lvl_2);

    std::shared_ptr<hl_ast_node> ast = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    ast->add_content(lvl_3);


    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep);

    manager.run_morphing_passes(ast);



    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_mult);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(7);

    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_reciprocal);
    gs_2->set_rhs(op_2);


    std::shared_ptr<hl_expression_node> gs_3 = std::make_shared<hl_expression_node>(expr_mult);
    gs_3->set_lhs(gs_1);
    gs_3->set_rhs(gs_2);

    op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");

    std::shared_ptr<hl_expression_node> gs_4 = std::make_shared<hl_expression_node>(expr_assign);
    gs_4->set_lhs(op_3);
    gs_4->set_rhs(gs_3);

    std::shared_ptr<hl_ast_node> result = ast->get_content()[0];


    EXPECT_EQ( *gs_4, *result);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << std::static_pointer_cast<hl_expression_node>(ast->get_content()[0])->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << std::static_pointer_cast<hl_expression_node>(result)->pretty_print()<< std::endl;
    }
}



TEST(HlPassesTest, functionMapping) {


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> lvl_1 = std::make_shared<hl_expression_node>(expr_mult);
    lvl_1->set_lhs(op_1);
    lvl_1->set_rhs(op_2);

    std::shared_ptr<hl_function_def_node> func_1 = std::make_shared<hl_function_def_node>();
    std::string fn = "test_1";
    func_1->set_name(fn);
    func_1->add_content(lvl_1);

    std::shared_ptr<hl_function_def_node> func_2 = std::make_shared<hl_function_def_node>();
    fn = "test_2";
    func_2->set_name(fn);
    func_2->add_content(lvl_1);


    std::shared_ptr<hl_ast_node> ast = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    ast->add_content(func_1);
    ast->add_content(func_2);




    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep);

    manager.run_morphing_passes(ast);

    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<hl_function_def_node>>> pass = std::static_pointer_cast<function_mapping>(manager.morphing_passes[0])->get_map_ref();

    EXPECT_EQ( *func_1, *pass->at("test_1"));
    EXPECT_EQ( *func_2, *pass->at("test_2"));

}

TEST(HlPassesTest, functionInlining) {


    std::string input_file = "test_function_inlining.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep);

    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_function_def_node> res = std::static_pointer_cast<hl_function_def_node>(parser.AST->get_content()[0]);

    std::shared_ptr<hl_function_def_node> gold_standard = std::make_shared<hl_function_def_node>();
    gold_standard->set_name("main");
    // PARAMETERS
    std::shared_ptr<hl_definition_node> par_1 = std::make_shared<hl_definition_node>("a", c_type_int);
    std::shared_ptr<hl_definition_node> par_2 = std::make_shared<hl_definition_node>("b", c_type_int);
    gold_standard->set_parameters_list({par_1, par_2});
    // CALL EXPRESSION
    std::shared_ptr<hl_expression_node> ex_call = std::make_shared<hl_expression_node>(expr_call);
    // CALL NODE
    std::shared_ptr<hl_ast_operand> arg_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    arg_1->set_immediate(2);
    std::shared_ptr<hl_ast_operand> arg_2 = std::make_shared<hl_ast_operand>(variable_operand);
    arg_2->set_name("t");
    std::vector<std::shared_ptr<hl_ast_node>> arguments = {arg_1, arg_2};
    std::shared_ptr<hl_function_call_node> func = std::make_shared<hl_function_call_node>("add", arguments);
    // CALL BODY
    std::shared_ptr<hl_definition_node> def = std::make_shared<hl_definition_node>("c", c_type_int);
    std::shared_ptr<hl_expression_node> exadd = std::make_shared<hl_expression_node>(expr_add);
    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(2);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(variable_operand);
    op_2->set_name("t");
    exadd->set_rhs(op_2);
    exadd->set_lhs(op_1);
    def->set_initializer(exadd);
    func->set_body({def});
    exadd = std::make_shared<hl_expression_node>(expr_add);
    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    op_2 = std::make_shared<hl_ast_operand>(variable_operand);
    op_2->set_name("t");
    exadd->set_rhs(op_2);
    exadd->set_lhs(op_1);
    func->set_return(exadd);
    gold_standard->set_body({ex_call});
    gold_standard->set_return_type(c_type_int);
    EXPECT_EQ(*res, *gold_standard);

}



TEST(HlPassesTest, normalization) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep);
    manager.run_morphing_passes(parser.AST);

    normalization_pass p;
    std::shared_ptr<hl_ast_node> raw_result = p.process_global(parser.AST);


    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("intermediate_expr_0", c_type_int);

    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(4);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_mult);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_1->set_initializer(ex_1);

    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("a", c_type_int);

    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("intermediate_expr_0");
    op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);

    ex_1= std::make_shared<hl_expression_node>(expr_add);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_2->set_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_function_def_node> gold_standard = std::make_shared<hl_function_def_node>();
    gold_standard->set_name("main");
    gold_standard->set_return_type(c_type_int);
    gold_standard->set_body({def_1, def_2});

    std::shared_ptr<hl_function_def_node> result = std::static_pointer_cast<hl_function_def_node>(raw_result->get_content()[0]);

    EXPECT_EQ( *gold_standard, *result);
    if(Test::HasFailure()){
        std::cout << "TEST RESULT: " << result->pretty_print()<< std::endl;
        std::cout << "GOLD STANDARD: " << gold_standard->pretty_print()<< std::endl;
    }
}



TEST(HlPassesTest, function_elimination) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    hl_pass_manager manager = create_hl_pass_manager(ep);
    manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> raw_result = manager.run_global_passes(parser.AST);

    std::shared_ptr<hl_definition_node> def_1 = std::make_shared<hl_definition_node>("intermediate_expr_0", c_type_int);

    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_1->set_immediate(4);
    std::shared_ptr<hl_ast_operand> op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> ex_1= std::make_shared<hl_expression_node>(expr_mult);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_1->set_initializer(ex_1);

    std::shared_ptr<hl_definition_node> def_2 = std::make_shared<hl_definition_node>("a", c_type_int);

    op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("intermediate_expr_0");
    op_2 = std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(6);

    ex_1= std::make_shared<hl_expression_node>(expr_add);
    ex_1->set_lhs(op_1);
    ex_1->set_rhs(op_2);
    def_2->set_initializer(ex_1);

    std::vector<std::shared_ptr<hl_ast_node>> arguments = {};
    std::shared_ptr<hl_ast_node> gold_standard = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    gold_standard->set_content({def_1, def_2});

    EXPECT_EQ( *gold_standard, *raw_result);

}