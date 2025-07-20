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

#include <fstream>
#include <gtest/gtest.h>

#include "emulator_test_helpers.hpp"
#include "emulator/v2/emulator_manager.hpp"

using namespace fcore::emulator_v2;


TEST(Emulator_execution, emulator_load) {

    auto program = "int main(){int test = 5.0;}";

    auto specs = prepare_spec(program, 1, 1,
                             {}, {{"test", "float"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    float result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 5.0, 1e-6);
}


TEST(Emulator_execution, emulator_add) {

    auto program = "int main(){float a,b;int test = a+b;}";

    auto specs = prepare_spec(program, 1, 1,
     {{"a", 2.3,"float"},{"b", 1.5, "float"}}, {{"test", "float"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    float result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 3.8, 1e-6);

}


TEST(Emulator_execution, emulator_sub) {
    auto program = "int main(){float a,b;int test = a-b;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 2.3,"float"},{"b", 1.5, "float"}}, {{"test", "float"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    float result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 0.8, 1e-6);
}

TEST(Emulator_execution, emulator_mul) {
    auto program = "int main(){float a,b;int test = a*b;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 2.3,"float"},{"b", 1.5, "float"}}, {{"test", "float"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    float result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 3.45, 1e-6);
}

TEST(Emulator_execution, emulator_rec) {

    auto program = "int main(){float a,b;int test = 1.0/a;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 2,"float"}}, {{"test", "float"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    float result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 0.5, 1e-6);
}

TEST(Emulator_execution, emulator_itf) {
    auto program = "int main(){float a;int test = itf(a);}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 2,"integer"}}, {{"test", "float"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    float result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 2, 1e-6);
}

TEST(Emulator_execution, emulator_fti) {

    auto program = "int main(){float a;int test = fti(a);}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 2.3,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    auto dbg = res_obj.dump();
    uint32_t result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 2);
}

TEST(Emulator_execution, emulator_and) {

    auto program = "int main(){int a,b;int test = a&b;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 0x5,"integer"}, {"b", 0xd,"integer"}}, {{"test", "integer"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    int result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 5);
}

TEST(Emulator_execution, emulator_or) {

    auto program = "int main(){int a,b;int test = a|b;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 0x5,"integer"}, {"b", 0xA,"integer"}}, {{"test", "integer"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    int result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 15);
}

TEST(Emulator_execution, emulator_not) {

    auto program = "int main(){int a;int test = ~a;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 0x210C,"integer"}}, {{"test", "integer"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    int result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0xFFFFDEF3);
}


TEST(Emulator_execution, emulator_satn) {


    auto program = "int main(){float a;int test = satn(a, -5.0);}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", -10,"float"}}, {{"test", "float"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    float result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, -5, 1e-6);

    specs = prepare_spec(program, 1, 1,
                             {{"a", -3,"float"}}, {{"test", "float"}}, {});
    manager = emulator_manager();
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    res_obj = manager.get_results();
    result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, -3, 1e-6);
}


TEST(Emulator_execution, emulator_satp) {

    auto program = "int main(){float a;int test = satp(a, 5.0);}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 10,"float"}}, {{"test", "float"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    float result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 5, 1e-6);
    specs = prepare_spec(program, 1, 1,
                        {{"a", 3,"float"}}, {{"test", "float"}}, {});
    manager = emulator_manager();
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    res_obj = manager.get_results();
    result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 3, 1e-6);
}

TEST(Emulator_execution, emulator_beq) {

    auto program = "int main(){float a, b;int test = a==b;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 10.0,"float"}, {"b", 10.0,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    uint32_t result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    specs = prepare_spec(program, 1, 1,
                        {{"a", 10.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager();
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    res_obj = manager.get_results();
    result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0);

}

TEST(Emulator_execution, emulator_bne) {


    auto program = "int main(){float a, b;int test = a!=b;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 15.0,"float"}, {"b", 10.0,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    uint32_t result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    specs = prepare_spec(program, 1, 1,
                        {{"a", 5.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager();
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    res_obj = manager.get_results();
    result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0);

}


TEST(Emulator_execution, emulator_bgt) {

    auto program = "int main(){float a, b;int test = a>b;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 15.0,"float"}, {"b", 10.0,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    uint32_t result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    specs = prepare_spec(program, 1, 1,
                        {{"a", 5.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager();
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    res_obj = manager.get_results();
    result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0);

}

TEST(Emulator_execution, emulator_ble) {

    auto program = "int main(){float a, b;int test = a<=b;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 5.0,"float"}, {"b", 10.0,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    uint32_t result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    specs = prepare_spec(program, 1, 1,
                        {{"a", 5.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager();
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    res_obj = manager.get_results();
    result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    specs = prepare_spec(program, 1, 1,
                        {{"a", 15.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager();
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    res_obj = manager.get_results();
    result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0);



}



TEST(Emulator_execution, emulator_efi) {
    auto program = "int main(){float sort_input[4] = {1, 5.0, 0.5, 50.0};float sort_output[4];sort_output = efi(sort_input, 4);}";

    auto specs = prepare_spec(program, 1, 1,
                             {}, {}, {});

    nlohmann::json out_obj;
    out_obj["name"] = "sort_output";
    out_obj["metadata"] = nlohmann::json();
    out_obj["metadata"]["type"] = "integer";
    out_obj["metadata"]["width"] = 12;
    out_obj["metadata"]["signed"] = true;
    out_obj["metadata"]["common_io"] = false;
    out_obj["is_vector"] = true;
    out_obj["vector_size"] = 4;
    out_obj["reg_n"] = {5, 6, 7};
    specs["cores"][0]["program"]["build_settings"]["io"]["outputs"].push_back("sort_output");
    specs["cores"][0]["outputs"].push_back(out_obj);

    specs["cores"][0]["options"]["efi_implementation"] = "efi_sort";

    std::string dbg = specs.dump();
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();

    auto  res_obj = manager.get_results()["test"]["outputs"]["sort_output"]["0"];

    ASSERT_EQ(res_obj[0][0], 1);
    ASSERT_EQ(res_obj[1][0], 0);
    ASSERT_EQ(res_obj[2][0], 2);
}


TEST(Emulator_execution, emulator_bset) {
    auto program = "int main(){float a; bset(a, 3, 1); test = a;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 5,"integer"}}, {{"test", "integer"}}, {});
    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    uint32_t result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0xd);

    program = "int main(){float a; bset(a, 2, 0); test = a;}";

    specs = prepare_spec(program, 1, 1,
                             {{"a", 5,"integer"}}, {{"test", "integer"}}, {});
    manager = emulator_manager();
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    res_obj = manager.get_results();
    result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_EQ(result, 0x1);
}


TEST(Emulator_execution, emulator_csel) {

    auto program = "int main(){float a;int test = a>0? 150.0: 200.0;}";

    auto specs = prepare_spec(program, 1, 1,
                             {{"a", 2,"float"}}, {{"test", "float"}}, {});

    emulator_manager manager;
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();
    float result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 150.0, 1e-6);

    specs = prepare_spec(program, 1, 1,
                        {{"a", -1,"float"}}, {{"test", "float"}}, {});
    manager = emulator_manager();
    manager.set_specs(specs);
    manager.process();
    manager.emulate();
    res_obj = manager.get_results();
    result = res_obj["test"]["outputs"]["test"]["0"][0][0];
    EXPECT_NEAR(result, 200.0, 1e-6);
}

