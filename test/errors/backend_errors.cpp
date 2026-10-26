// Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#include "fcore_cc.hpp"
#include "data_structures/common/memory_tracker.hpp"
#include "data_structures/constants_tracker.h"
#include "passes/instruction_stream/stream_pass_manager.hpp"

using namespace fcore;

TEST(backend_errors, running_out_of_registers_is_an_error) {
    // more simultaneously live variables than the core has registers, this used to terminate the process.
    // The values depend on an input so that constant propagation can not remove them
    std::string body = "float main(){\n";
    constexpr int n_variables = 100;
    for (int i = 0; i < n_variables; ++i) {
        body += "float v" + std::to_string(i) + " = input_value * " + std::to_string(i + 1) + ".5;\n";
    }
    body += "float sum = v0";
    for (int i = 1; i < n_variables; ++i) body += " + v" + std::to_string(i);
    body += ";\nreturn sum;\n}\n";

    std::vector<std::string> input = {body};
    std::vector<std::string> includes;
    std::map<std::string, core_iom> dma_map;
    dma_map["input_value"] = {core_iom_input, {1}};

    fcore_cc compiler(input, includes);
    compiler.set_dma_map(dma_map);
    auto compilation = compiler.compile(1);
    ASSERT_FALSE(compilation);
    EXPECT_EQ(compilation.error().code, error_code::register_allocation);
    ASSERT_FALSE(compilation.error().context.empty());
    EXPECT_NE(compilation.error().context.front().find("register allocation"), std::string::npos);
}

TEST(backend_errors, use_before_initialization_has_a_semantic_code) {
    std::vector<std::string> input = {"float main(){ float a; float b = a + 1.0; return b; }"};
    std::vector<std::string> includes;
    fcore_cc compiler(input, includes);
    auto compilation = compiler.compile(1);
    ASSERT_FALSE(compilation);
    EXPECT_EQ(compilation.error().code, error_code::semantic_error);
    EXPECT_EQ(compilation.error().message, "ERROR: Variable 'a' is used before initialization");
}

TEST(backend_errors, stall_insertion_rejects_unbound_registers) {
    auto r3 = std::make_shared<variable>("r3");
    auto r4 = std::make_shared<variable>("r4");
    auto r5 = std::make_shared<variable>("r5");
    r3->set_bound_reg(3);
    r4->set_bound_reg(4);
    // r5 is left unbound

    instruction_stream program_stream;
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, r4, r5)));
    program_stream.push_back(instruction_variant(register_instruction(opcode_add, r5, r4, r3)));

    auto ic = std::make_shared<instrumentation_core>();
    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 1);
    auto outcome = sman.apply_pass(program_stream, std::make_shared<stall_insertion>(1));
    ASSERT_FALSE(outcome);
    EXPECT_EQ(outcome.error().code, error_code::pipeline_hazard);
}

TEST(backend_errors, stall_insertion_rejects_an_unbound_destination_for_every_instruction_kind) {
    auto bound = std::make_shared<variable>("r3");
    bound->set_bound_reg(3);
    auto bound_b = std::make_shared<variable>("r4");
    bound_b->set_bound_reg(4);
    auto unbound = std::make_shared<variable>("r7");

    auto ic = std::make_shared<instrumentation_core>();
    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 1);

    instruction_stream register_stream;
    register_stream.push_back(instruction_variant(register_instruction(opcode_add, bound, bound_b, unbound)));
    auto register_outcome = sman.apply_pass(register_stream, std::make_shared<stall_insertion>(1));
    ASSERT_FALSE(register_outcome);
    EXPECT_EQ(register_outcome.error().code, error_code::pipeline_hazard);

    instruction_stream constant_stream;
    constant_stream.push_back(instruction_variant(load_constant_instruction(opcode_ldc, unbound, std::make_shared<variable>("constant", 1.0f))));
    auto constant_outcome = sman.apply_pass(constant_stream, std::make_shared<stall_insertion>(1));
    ASSERT_FALSE(constant_outcome);
    EXPECT_EQ(constant_outcome.error().code, error_code::pipeline_hazard);

    instruction_stream conversion_stream;
    conversion_stream.push_back(instruction_variant(conversion_instruction(opcode_itf, bound, unbound)));
    auto conversion_outcome = sman.apply_pass(conversion_stream, std::make_shared<stall_insertion>(1));
    ASSERT_FALSE(conversion_outcome);
    EXPECT_EQ(conversion_outcome.error().code, error_code::pipeline_hazard);
}

TEST(backend_errors, failed_stream_pass_can_be_reused) {
    auto r3 = std::make_shared<variable>("r3");
    auto r4 = std::make_shared<variable>("r4");
    auto r6 = std::make_shared<variable>("r6");
    r3->set_bound_reg(3);
    r4->set_bound_reg(4);
    r6->set_bound_reg(6);
    auto unbound = std::make_shared<variable>("r7");

    instruction_stream failing_stream;
    failing_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, unbound, r6)));
    instruction_stream good_stream;
    good_stream.push_back(instruction_variant(register_instruction(opcode_add, r3, r4, r6)));

    auto ic = std::make_shared<instrumentation_core>();
    stream_pass_manager sman(ic, stream_pass_manager::asm_language, 1);
    // the same pass object runs a failing and then a valid stream
    auto shared_pass = std::make_shared<stall_insertion>(1);
    EXPECT_FALSE(sman.apply_pass(failing_stream, shared_pass));
    EXPECT_TRUE(sman.apply_pass(good_stream, shared_pass));
}

TEST(backend_errors, memory_tracker_runs_out_of_memory) {
    memory_tracker tracker({0, 4});

    auto too_big = tracker.get_free_memory_range(8);
    ASSERT_FALSE(too_big);
    EXPECT_EQ(too_big.error().code, error_code::register_allocation);

    auto fits = tracker.get_free_memory_range(3);
    ASSERT_TRUE(fits);
    EXPECT_EQ(fits.value(), memory_range_t(0, 3));

    auto cell = tracker.get_free_memory_cell();
    ASSERT_TRUE(cell);
    EXPECT_EQ(cell.value(), 3u);

    EXPECT_FALSE(tracker.get_free_memory_cell());
}

TEST(backend_errors, constants_tracker_reports_unknown_constants) {
    constants_tracker tracker;
    auto missing = tracker.get_constant("never_added", 0, {0});
    ASSERT_FALSE(missing);
    EXPECT_EQ(missing.error().code, error_code::internal_error);

    EXPECT_FALSE(tracker.terminate_constant_range("never_added", 3, {0}));
    EXPECT_FALSE(tracker.terminate_all_constant_ranges("never_added", 3));
}

TEST(backend_errors, constants_tracker_terminates_known_constants) {
    constants_tracker tracker;
    auto value = std::make_shared<ast_operand>(std::make_shared<variable>("constant", 5));
    tracker.add_constant("a", value, 0, {0});
    tracker.add_constant("b", value, 0, {0});

    EXPECT_TRUE(tracker.terminate_constant_range("a", 4, {0}));
    // used to fail even for a tracked constant
    EXPECT_TRUE(tracker.terminate_all_constant_ranges("b", 4));
    EXPECT_FALSE(tracker.is_constant("b", 5, {0}));
}
