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
#include "frontend/emulator_manager.hpp"

nlohmann::json prepare_spec(const std::string &file, int run_length){
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
    return spec;
}

TEST(Emulator_execution, emulator_load) {

    nlohmann::json spec = prepare_spec("emu/test_load.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(1), 0x3f47ae14);
    ASSERT_EQ(result->at(15), 0x4306b333);
}


TEST(Emulator_execution, emulator_add) {

    nlohmann::json spec = prepare_spec("emu/test_add.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(2), 0x43077ae1);
}


TEST(Emulator_execution, emulator_sub) {
    nlohmann::json spec = prepare_spec("emu/test_sub.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(2), 0xc305eb85);
}

TEST(Emulator_execution, emulator_mul) {

    nlohmann::json spec = prepare_spec("emu/test_mul.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(2), 0x42d221ca);
}

TEST(Emulator_execution, emulator_rec) {

    nlohmann::json spec = prepare_spec("emu/test_rec.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(1), 0x3fa41a42);
}

TEST(Emulator_execution, emulator_itf) {

    nlohmann::json spec = prepare_spec("emu/test_itf.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(1), 0x40400000);
}

TEST(Emulator_execution, emulator_fti) {

    nlohmann::json spec = prepare_spec("emu/test_fti.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(1), 15);
}

TEST(Emulator_execution, emulator_and) {

    nlohmann::json spec = prepare_spec("emu/test_and.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(3), 0x40000000);
}

TEST(Emulator_execution, emulator_or) {

    nlohmann::json spec = prepare_spec("emu/test_or.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(3), 0xC578D666);
}

TEST(Emulator_execution, emulator_nor) {

    nlohmann::json spec = prepare_spec("emu/test_not.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(1), 0x3BF72999);
}


TEST(Emulator_execution, emulator_satn) {

    nlohmann::json spec = prepare_spec("emu/test_satn.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(4), 0xc3fa0000);
    ASSERT_EQ(result->at(5), 0xc408d666);
}


TEST(Emulator_execution, emulator_satp) {

    nlohmann::json spec = prepare_spec("emu/test_satp.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(4), 0x43fa0000);
    ASSERT_EQ(result->at(5), 0x4408d666);
}

TEST(Emulator_execution, emulator_beq) {

    nlohmann::json spec = prepare_spec("emu/test_beq.mem", 1);

    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(4), 0xffffffff);
    ASSERT_EQ(result->at(5), 0x0);
}

TEST(Emulator_execution, emulator_bne) {

    nlohmann::json spec = prepare_spec("emu/test_bne.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(4), 0xffffffff);
    ASSERT_EQ(result->at(5), 0x0);
}


TEST(Emulator_execution, emulator_bgt) {
    nlohmann::json spec = prepare_spec("emu/test_bgt.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(4), 0xffffffff);
    ASSERT_EQ(result->at(5), 0x0);
}

TEST(Emulator_execution, emulator_ble) {
    nlohmann::json spec = prepare_spec("emu/test_ble.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(4), 0xffffffff);
    ASSERT_EQ(result->at(5), 0x0);
    ASSERT_EQ(result->at(6), 0xffffffff);
}

TEST(Emulator_execution, emulator_stop) {
    nlohmann::json spec = prepare_spec("emu/test_stop.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(1), 0xc3fa8000);
}



TEST(Emulator_execution, emulator_efi) {

    nlohmann::json spec = prepare_spec("emu/test_efi.mem", 1);
    spec["cores"][0]["options"]["efi_implementation"] = "efi_sort";
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(7), 1);
    ASSERT_EQ(result->at(8), 0);
    ASSERT_EQ(result->at(9), 2);
}


TEST(Emulator_execution, emulator_bset) {

    nlohmann::json spec = prepare_spec("emu/test_bset.mem", 1);
    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);
    ASSERT_EQ(result->at(56), 0x41b00000);
    ASSERT_EQ(result->at(55), 0xC1b00000);
}



TEST(Emulator_execution, emulator_inputs) {

    nlohmann::json spec = prepare_spec("emu/test_inputs.mem", 2);

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
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);

    ASSERT_EQ(result->at(4), 0x42f070a4);

}

TEST(Emulator_execution, emulator_outputs) {

    std::ifstream ifs("emu/test_inputs_spec.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test"];

    std::vector<uint32_t> reference = {0x426a7ae1, 0x42f070a4};
    ASSERT_EQ(res["outputs"]["test_out"][0], reference);

}

TEST(Emulator_execution, emulator_inteconnect) {

    std::ifstream ifs("emu/test_interconnect_spec.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test_consumer"];

    auto s = res.dump();
    std::vector<uint32_t> reference = {0x426a7ae1, 0x42f070a4};
    ASSERT_EQ(res["outputs"]["test_out"][0], reference);

}

TEST(Emulator_execution, emulator_compilation) {

    std::ifstream ifs("emu/test_compilation.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
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
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test"];

    std::vector<uint32_t> reference = {15,83};
    std::vector<uint32_t> result = res["outputs"]["out"][0];
    ASSERT_EQ(result, reference);
}

