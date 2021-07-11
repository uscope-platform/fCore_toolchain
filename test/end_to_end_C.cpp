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

#include <fstream>

#include <gtest/gtest.h>
#include "passes/low_level/ll_pass_manager.hpp"
#include "passes/ll_passes.hpp"
#include "ast/transformations/high_level_ast_lowering.hpp"
#include "fcore_cc.hpp"


TEST(EndToEndC, minimal_c_end_to_end) {


    std::string input_file = "test_normalization.c";
    std::ifstream ifs(input_file);

    std::shared_ptr<variable_map> result_var = std::make_shared<variable_map>();
    std::shared_ptr<define_map> result_def = std::make_shared<define_map>();

    C_language_parser parser(ifs, result_var, result_def);
    parser.pre_process({}, {});
    parser.parse();

    std::string ep = "main";
    std::shared_ptr<variable_map> variables_map = std::make_shared<variable_map>();
    hl_pass_manager hl_manager = create_hl_pass_manager(ep, variables_map);
    hl_manager.run_morphing_passes(parser.AST);

    std::shared_ptr<hl_ast_node> normalized_ast = hl_manager.run_global_passes(parser.AST);

    high_level_ast_lowering tranlator(variables_map);

    tranlator.set_input_ast(normalized_ast);
    tranlator.translate();
    std::shared_ptr<ll_ast_node> ll_ast = tranlator.get_output_ast();

    ll_pass_manager ll_manager = create_ll_pass_manager(variables_map);
    ll_manager.run_morphing_passes(ll_ast);

    output_generator writer(ll_ast, true);
    std::vector<uint32_t> result = writer.get_raw_program();

    std::vector<uint32_t> gold_standard = {0x22883, 0x43021};
    ASSERT_EQ(result, gold_standard);
}

