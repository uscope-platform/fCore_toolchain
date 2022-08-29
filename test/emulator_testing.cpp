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
#include <filesystem>
#include <gtest/gtest.h>
#include "fcore_emu.hpp"

TEST(Emulator, emulator_load) {

    std::string input_file = "emu/test_load.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[1], 0x3f47ae14);
    ASSERT_EQ(memory[15], 0x4306b333);
}


TEST(Emulator, emulator_add) {

    std::string input_file = "emu/test_add.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[2], 0x43077ae1);
}


TEST(Emulator, emulator_sub) {

    std::string input_file = "emu/test_sub.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[2], 0xc305eb85);
}

TEST(Emulator, emulator_mul) {

    std::string input_file = "emu/test_mul.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[2], 0x42d221ca);
}

TEST(Emulator, emulator_rec) {

    std::string input_file = "emu/test_rec.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[1], 0x3fa41a42);
}

TEST(Emulator, emulator_itf) {

    std::string input_file = "emu/test_itf.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[1], 0x40400000);
}

TEST(Emulator, emulator_fti) {

    std::string input_file = "emu/test_fti.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[1], 15);
}

TEST(Emulator, emulator_and) {

    std::string input_file = "emu/test_and.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[3], 0x40000000);
}

TEST(Emulator, emulator_or) {

    std::string input_file = "emu/test_or.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[3], 0xC578D666);
}

TEST(Emulator, emulator_nor) {

    std::string input_file = "emu/test_not.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[1], 0x3BF72999);
}


TEST(Emulator, emulator_satn) {

    std::string input_file = "emu/test_satn.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();

    ASSERT_EQ(memory[4], 0xc3fa0000);
    ASSERT_EQ(memory[5], 0xc408d666);
}


TEST(Emulator, emulator_satp) {

    std::string input_file = "emu/test_satp.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[4], 0x43fa0000);
    ASSERT_EQ(memory[5], 0x4408d666);
}

TEST(Emulator, emulator_beq) {

    std::string input_file = "emu/test_beq.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[4], 0xffffffff);
    ASSERT_EQ(memory[5], 0x0);
}

TEST(Emulator, emulator_bne) {

    std::string input_file = "emu/test_bne.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[4], 0xffffffff);
    ASSERT_EQ(memory[5], 0x0);
}


TEST(Emulator, emulator_bgt) {

    std::string input_file = "emu/test_bgt.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[4], 0xffffffff);
    ASSERT_EQ(memory[5], 0x0);
}

TEST(Emulator, emulator_ble) {

    std::string input_file = "emu/test_ble.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[4], 0xffffffff);
    ASSERT_EQ(memory[5], 0x0);
    ASSERT_EQ(memory[6], 0xffffffff);
}

TEST(Emulator, emulator_stop) {

    std::string input_file = "emu/test_stop.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[1], 0xc3fa8000);
}



TEST(Emulator, emulator_efi) {

    nlohmann::json specs;
    specs["efi_implementation"] = "efi_sort";

    std::string input_file = "emu/test_efi.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.set_specs(specs);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[7], 1);
    ASSERT_EQ(memory[8], 0);
    ASSERT_EQ(memory[9], 2);
}



TEST(Emulator, emulator_inputs) {

    std::string input_program = "emu/test_inputs.mem";
    std::ifstream program_stream(input_program);
    fcore_emu emu_engine(program_stream, bin_loader_mem_input);
    std::string input_file = "emu/test_inputs.csv";
    std::ifstream inputs_stream(input_file);
    emu_engine.set_inputs(inputs_stream);
    emu_engine.emulate_program();

    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();

    ASSERT_EQ(memory[4], 0x42f070a4);

}

TEST(Emulator, emulator_bset) {

    std::string input_file = "emu/test_bset.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    emu_engine.emulate_program();
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[56], 0x41b00000);
    ASSERT_EQ(memory[55], 0xC1b00000);
}


TEST(Emulator, emulator_outputs) {

    std::string input_program = "emu/test_inputs.mem";
    std::ifstream program_stream(input_program);
    fcore_emu emu_engine(program_stream, bin_loader_mem_input);
    std::string input_file = "emu/test_inputs.csv";
    std::ifstream inputs_stream(input_file);
    emu_engine.set_inputs(inputs_stream);
    std::ifstream ifs("emu/test_spec.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);

    emu_engine.set_specs(specs);
    emu_engine.emulate_program();

    std::unordered_map<int, std::vector<uint32_t>> outputs = emu_engine.get_outputs();

    std::unordered_map<int, std::vector<uint32_t>> reference;
    reference[4] = {0x426a7ae1, 0x42f070a4};
    ASSERT_EQ(outputs, reference);

}


TEST(Emulator, emulator_error) {

    std::string input_program = "emu/test_inputs.mem";
    std::ifstream program_stream(input_program);
    fcore_emu emu_engine(program_stream, bin_loader_mem_input);
    std::string input_file = "asf 123e";
    std::istringstream inputs_stream(input_file);
    emu_engine.set_inputs(inputs_stream);


    unsigned int filename = rand();
    std::string outfile_name = std::filesystem::temp_directory_path().string() + "/" + std::to_string(filename);
    emu_engine.write_json(outfile_name);

    std::ifstream result_file(outfile_name);
    std::ostringstream sstr;
    sstr << result_file.rdbuf();

    auto result = nlohmann::json::parse(sstr.str());

    nlohmann::json gold_standard_j;
    gold_standard_j["error_code"] = "ERROR: malformed inputs file header";
    gold_standard_j["registers"] = result["registers"];
    gold_standard_j["registers_f"] = result["registers_f"];
    gold_standard_j["outputs"] = nlohmann::json();
    ASSERT_EQ(result, gold_standard_j);
}

