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
#include "emulator/emulator_manager.hpp"

using namespace fcore;

struct input_struct{
    std::string name;
    float value;
    std::string type;
};


struct output_struct{
    std::string name;
    std::string type;
};

struct memory_struct{
    std::string name;
    float value;
    std::string type;
};

nlohmann::json prepare_spec_file(const std::string &file, int run_length){
    nlohmann::json spec;
    spec["cores"] = std::vector<nlohmann::json>();
    spec["n_cycles"] = run_length;
    spec["cores"][0]["order"] = 0;
    spec["cores"][0]["id"] = "test";
    spec["cores"][0]["program"] = std::unordered_map<std::string, std::string>({{"type", "mem"}, { "filename", file}});
    spec["cores"][0]["channels"] = 1;
    spec["cores"][0]["options"] = nlohmann::json();
    spec["cores"][0]["options"]["comparators"] = "full";
    spec["cores"][0]["options"]["efi_implementation"] = "none";
    spec["cores"][0]["sampling_frequency"] =1000;
    return spec;
}

nlohmann::json prepare_spec(
        const std::string &content,
        int run_length,
        std::vector<input_struct>inputs,
        std::vector<output_struct> outputs,
        std::vector<memory_struct> memories
){
    nlohmann::json spec;
    spec["cores"] = std::vector<nlohmann::json>();
    spec["n_cycles"] = run_length;

    auto cs = nlohmann::json();

    cs["order"] = 0;
    cs["id"] = "test";

    cs["program"] = nlohmann::json();
    cs["program"]["content"] = content;
    cs["channels"] = 1;
    cs["options"] = nlohmann::json();
    cs["options"]["comparators"] = "full";
    cs["options"]["efi_implementation"] = "none";
    cs["sampling_frequency"] =1000;
    cs["inputs"]= std::vector<nlohmann::json>();

    cs["program"]["build_settings"] = nlohmann::json();
    cs["program"]["build_settings"]["io"] = nlohmann::json();

    cs["program"]["build_settings"]["io"]["inputs"] = std::vector<std::string>();
    cs["program"]["build_settings"]["io"]["outputs"] = std::vector<std::string>();
    cs["program"]["build_settings"]["io"]["memories"] = std::vector<std::string>();

    for(int i = 0; i<inputs.size(); i++){
        nlohmann::json in_obj;
        in_obj["name"] = inputs[i].name;
        in_obj["type"] = inputs[i].type;
        in_obj["reg_n"] = i;
        in_obj["register_type"] = "scalar";
        in_obj["channel"] = 0;
        in_obj["source"] = nlohmann::json();
        in_obj["source"]["type"] = "constant";
        in_obj["source"]["value"] = inputs[i].value;
        cs["inputs"].push_back(in_obj);
        cs["program"]["build_settings"]["io"]["inputs"].push_back(inputs[i].name);
    }

    cs["outputs"]= std::vector<nlohmann::json>();
    for(int i = 0; i<outputs.size(); i++){
        nlohmann::json out_obj;
        out_obj["name"] = outputs[i].name;
        out_obj["type"] = outputs[i].type;
        out_obj["reg_n"] = 10+i;
        out_obj["register_type"] = "scalar";
        cs["program"]["build_settings"]["io"]["outputs"].push_back(outputs[i].name);
        cs["outputs"].push_back(out_obj);
    }
    cs["memory_init"]= std::vector<nlohmann::json>();

    for(int i = 0; i<memories.size(); i++){
        nlohmann::json mem_obj;
        mem_obj["name"] = memories[i].name;
        mem_obj["type"] = memories[i].type;
        mem_obj["reg_n"] = 20+i;
        mem_obj["is_output"] = false;
        mem_obj["value"] = memories[i].value;
        cs["program"]["build_settings"]["io"]["memories"].push_back(memories[i].name);
        cs["memory_init"].push_back(mem_obj);
    }



    spec["cores"].push_back(cs);
    return spec;
}

TEST(Emulator_execution, emulator_load) {

    auto program = "int main(){int test = 5.0;}";

    auto spec = prepare_spec(program, 1,
                             {}, {{"test", "float"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 5.0, 1e-6);
}


TEST(Emulator_execution, emulator_add) {

    auto program = "int main(){float a,b;int test = a+b;}";

    auto spec = prepare_spec(program, 1,
     {{"a", 2.3,"float"},{"b", 1.5, "float"}}, {{"test", "float"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 3.8, 1e-6);

}


TEST(Emulator_execution, emulator_sub) {
    auto program = "int main(){float a,b;int test = a-b;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 2.3,"float"},{"b", 1.5, "float"}}, {{"test", "float"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 0.8, 1e-6);
}

TEST(Emulator_execution, emulator_mul) {
    auto program = "int main(){float a,b;int test = a*b;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 2.3,"float"},{"b", 1.5, "float"}}, {{"test", "float"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 3.45, 1e-6);
}

TEST(Emulator_execution, emulator_rec) {

    auto program = "int main(){float a,b;int test = 1.0/a;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 2,"float"}}, {{"test", "float"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 0.5, 1e-6);
}

TEST(Emulator_execution, emulator_itf) {
    auto program = "int main(){float a;int test = itf(a);}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 2,"integer"}}, {{"test", "float"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 2, 1e-6);
}

TEST(Emulator_execution, emulator_fti) {

    auto program = "int main(){float a;int test = fti(a);}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 2.3,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 2, 1e-6);
}

TEST(Emulator_execution, emulator_and) {

    auto program = "int main(){int a,b;int test = a&b;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 0x5,"integer"}, {"b", 0xd,"integer"}}, {{"test", "integer"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    int result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 5);
}

TEST(Emulator_execution, emulator_or) {

    auto program = "int main(){int a,b;int test = a|b;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 0x5,"integer"}, {"b", 0xA,"integer"}}, {{"test", "integer"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    int result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 15);
}

TEST(Emulator_execution, emulator_not) {

    auto program = "int main(){int a;int test = ~a;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 0x210C,"integer"}}, {{"test", "integer"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    int result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0xFFFFDEF3);
}


TEST(Emulator_execution, emulator_satn) {


    auto program = "int main(){float a;int test = satn(a, -5.0);}";

    auto spec = prepare_spec(program, 1,
                             {{"a", -10,"float"}}, {{"test", "float"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, -5, 1e-6);

    spec = prepare_spec(program, 1,
                             {{"a", -3,"float"}}, {{"test", "float"}}, {});
    manager = emulator_manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    res_obj = nlohmann::json::parse(manager.get_results());
    result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, -3, 1e-6);
}


TEST(Emulator_execution, emulator_satp) {

    auto program = "int main(){float a;int test = satp(a, 5.0);}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 10,"float"}}, {{"test", "float"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 5, 1e-6);
    spec = prepare_spec(program, 1,
                        {{"a", 3,"float"}}, {{"test", "float"}}, {});
    manager = emulator_manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    res_obj = nlohmann::json::parse(manager.get_results());
    result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 3, 1e-6);
}

TEST(Emulator_execution, emulator_beq) {

    auto program = "int main(){float a, b;int test = a==b;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 10.0,"float"}, {"b", 10.0,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    uint32_t result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    spec = prepare_spec(program, 1,
                        {{"a", 10.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    res_obj = nlohmann::json::parse(manager.get_results());
    result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0);

}

TEST(Emulator_execution, emulator_bne) {


    auto program = "int main(){float a, b;int test = a!=b;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 15.0,"float"}, {"b", 10.0,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    uint32_t result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    spec = prepare_spec(program, 1,
                        {{"a", 5.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    res_obj = nlohmann::json::parse(manager.get_results());
    result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0);

}


TEST(Emulator_execution, emulator_bgt) {

    auto program = "int main(){float a, b;int test = a>b;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 15.0,"float"}, {"b", 10.0,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    uint32_t result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    spec = prepare_spec(program, 1,
                        {{"a", 5.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    res_obj = nlohmann::json::parse(manager.get_results());
    result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0);

}

TEST(Emulator_execution, emulator_ble) {

    auto program = "int main(){float a, b;int test = a<=b;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 5.0,"float"}, {"b", 10.0,"float"}}, {{"test", "integer"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    uint32_t result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    spec = prepare_spec(program, 1,
                        {{"a", 5.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    res_obj = nlohmann::json::parse(manager.get_results());
    result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0xffffffff);

    spec = prepare_spec(program, 1,
                        {{"a", 15.0,"float"}, {"b", 5.0,"float"}}, {{"test", "integer"}}, {});
    manager = emulator_manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    res_obj = nlohmann::json::parse(manager.get_results());
    result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0);



}

TEST(Emulator_execution, emulator_stop) {
    nlohmann::json spec = prepare_spec_file("emu/test_stop.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(1), 0xc3fa8000);
}



TEST(Emulator_execution, emulator_efi) {

    nlohmann::json spec = prepare_spec_file("emu/test_efi.mem", 1);
    spec["cores"][0]["options"]["efi_implementation"] = "efi_sort";
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(7), 1);
    ASSERT_EQ(result->at(8), 0);
    ASSERT_EQ(result->at(9), 2);
}


TEST(Emulator_execution, emulator_bset) {
    auto program = "int main(){float a; bset(a, 3, 1); test = a;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 5,"integer"}}, {{"test", "integer"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    uint32_t result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0xd);

    program = "int main(){float a; bset(a, 2, 0); test = a;}";

    spec = prepare_spec(program, 1,
                             {{"a", 5,"integer"}}, {{"test", "integer"}}, {});
    manager = emulator_manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    res_obj = nlohmann::json::parse(manager.get_results());
    result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_EQ(result, 0x1);
}


TEST(Emulator_execution, emulator_csel) {

    auto program = "int main(){float a;int test = a>0? 150.0: 200.0;}";

    auto spec = prepare_spec(program, 1,
                             {{"a", 2,"float"}}, {{"test", "float"}}, {});
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());
    float result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 150.0, 1e-6);

    spec = prepare_spec(program, 1,
                        {{"a", -1,"float"}}, {{"test", "float"}}, {});
    manager = emulator_manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    res_obj = nlohmann::json::parse(manager.get_results());
    result = res_obj["test"]["outputs"]["test"][0][0];
    EXPECT_NEAR(result, 200.0, 1e-6);
}



TEST(Emulator_execution, emulator_inputs) {

    nlohmann::json spec = prepare_spec_file("emu/test_inputs.mem", 2);

    spec["cores"][0]["efi_implementation"] = "efi_sort";
    spec["cores"][0]["input_data"] = nlohmann::json();
    spec["cores"][0]["input_data"]["input_1"] = {15.7,67.4};
    spec["cores"][0]["input_data"]["input_2"] = {42.92,-5.8};
    spec["cores"][0]["inputs"] = std::vector<nlohmann::json>();
    auto in = nlohmann::json();
    in["name"] = "input_1";
    in["type"] = "float";
    in["register_type"] = "scalar";
    in["reg_n"] = 1;
    in["source"] = nlohmann::json();
    in["source"]["type"] = "file",
    in["source"]["value"] = "input_1",
    in["channel"] = 0;

    spec["cores"][0]["inputs"].push_back(in);
    in["name"] = "input_2";
    in["reg_n"] = 2;
    in["source"] = nlohmann::json();
    in["source"]["type"] = "file",
    in["source"]["value"] = "input_2",
    spec["cores"][0]["inputs"].push_back(in);

    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);

    ASSERT_EQ(result->at(4), 0x42f070a4);

}

TEST(Emulator_execution, emulator_outputs) {

    std::ifstream ifs("emu/test_inputs_spec.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test"];

    std::vector<float> reference = {58.6199989, 120.220001};
    std::vector<float> test_out = res["outputs"]["test_out"][0];
    ASSERT_EQ(test_out, reference);

}

TEST(Emulator_execution, emulator_inteconnect) {

    std::ifstream ifs("emu/test_interconnect_spec.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test_consumer"];

    auto s = res.dump();
    std::vector<uint32_t> reference = {0x426a7ae1, 0x42f070a4};
    ASSERT_EQ(res["outputs"]["consumer_out"][0], reference);

}

TEST(Emulator_execution, emulator_compilation) {

    std::ifstream ifs("emu/test_compilation.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test"];

    std::vector<uint32_t> reference = {59,62};
    std::vector<uint32_t> result = res["outputs"]["out"][0];
    ASSERT_EQ(result, reference);
}

TEST(Emulator_execution, emulator_compilation_interconnect) {

    std::ifstream ifs("emu/test_compilation_interconnect.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results());

    std::vector<uint32_t> reference = {59,62};
    std::vector<uint32_t> result = res["test"]["outputs"]["out"][0];
    ASSERT_EQ(result, reference);
    reference = {60,63};
    std::vector<uint32_t> result2 = res["test_move"]["outputs"]["out"][0];
    ASSERT_EQ(result2, reference);
}


TEST(Emulator_execution, emulator_compilation_memory) {

    std::ifstream ifs("emu/test_compilation_memory.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test"];

    std::vector<uint32_t> reference = {15,83};
    std::vector<uint32_t> result = res["outputs"]["out"][0];
    ASSERT_EQ(result, reference);
}

