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


#include <gtest/gtest.h>

#include "data_structures/low_level_ast/low_level_ast.hpp"
#include "backend/binary_generator.hpp"
#include "tools/instruction_stream_builder.hpp"
#include "data_structures/instruction_stream.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "fcore_cc.hpp"

using namespace fcore;

TEST(llPassesTest, pseudo_inst_pass) {


    std::shared_ptr<variable> op_a = std::make_shared<variable>("r3");
    std::shared_ptr<variable> op_b = std::make_shared<variable>("r4");
    std::vector<std::shared_ptr<variable>> args = {op_a, op_b};

    std::shared_ptr<ll_pseudo_instr_node> instr = std::make_shared<ll_pseudo_instr_node>("mov", args);


    binary_generator writer;

    instruction_stream program_stream;
    program_stream.push_back(instr);

    auto bindings_map = std::make_shared<std::unordered_map<std::string, memory_range_t>>();
    std::shared_ptr<io_map> allocation_map;

    stream_pass_manager sman(0, bindings_map, allocation_map);
    program_stream = sman.process_stream(program_stream);

    writer.process_stream(program_stream, false);

    std::vector<uint32_t> result = writer.get_code();
    std::vector<uint32_t> gold_standard = {0x8006E};
    ASSERT_EQ(result, gold_standard);
}


TEST(llPassesTest, deep_copy_element) {

    //TODO: Test a more realistic case
    std::shared_ptr<ll_independent_inst_node> level_2 = std::make_shared<ll_independent_inst_node>("nop");;

    std::shared_ptr<ll_ast_node> result = ll_ast_node::deep_copy_element(level_2);

    ASSERT_EQ(*result, *level_2);
}