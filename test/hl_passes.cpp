//
// Created by fils on 05/07/2021.
//

#include <gtest/gtest.h>
#include "code_elements/hl_ast/hl_ast_node.h"
#include "code_elements/hl_ast/hl_ast_operand.h"
#include "code_elements/hl_ast/hl_expression_node.h"
#include "frontend/variable_map.hpp"
#include "passes/hl_passes.hpp"
#include <memory>

TEST(HlPassesTest, divisionImplementation) {


    std::shared_ptr<hl_ast_operand> op_1 = std::make_shared<hl_ast_operand>(variable_operand);
    op_1->set_name("c");
    std::shared_ptr<hl_ast_operand> op_2= std::make_shared<hl_ast_operand>(integer_immediate_operand);
    op_2->set_immediate(5);

    std::shared_ptr<hl_expression_node> gs_1 = std::make_shared<hl_expression_node>(expr_div);
    gs_1->set_lhs(op_1);
    gs_1->set_rhs(op_2);

    std::shared_ptr<hl_ast_operand> op_3 = std::make_shared<hl_ast_operand>(variable_operand);
    op_3->set_name("test");
    std::shared_ptr<hl_expression_node> gs_2 = std::make_shared<hl_expression_node>(expr_assign);
    gs_2->set_lhs(op_3);
    gs_2->set_rhs(gs_1);

    std::shared_ptr<hl_ast_node> ast = std::make_shared<hl_ast_node>(hl_ast_node_type_program_root);
    ast->add_content(gs_2);

    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    pass_manager_base<hl_ast_node> manager = create_hl_pass_manager(variables_map);
    manager.run_morphing_passes(ast);

    std::cout << std::static_pointer_cast<hl_expression_node>(ast->get_content()[0])->pretty_print();
    int i = 0;

}
