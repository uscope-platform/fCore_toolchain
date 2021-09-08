// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#include <fstream>
#include <gtest/gtest.h>
#include "fcore_emu.hpp"

TEST(Emulator, emulator_load) {

    std::string input_file = "emu/test_load.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[1], 0x3f47ae14);
    ASSERT_EQ(memory[15], 0x4306b333);
}


TEST(Emulator, emulator_add) {

    std::string input_file = "emu/test_add.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[2], 0x43077ae1);
}


TEST(Emulator, emulator_sub) {

    std::string input_file = "emu/test_sub.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[2], 0xc305eb85);
}

TEST(Emulator, emulator_mul) {

    std::string input_file = "emu/test_mul.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[2], 0x42d221ca);
}

TEST(Emulator, emulator_rec) {

    std::string input_file = "emu/test_rec.mem";
    std::ifstream stream(input_file);
    fcore_emu emu_engine(stream, bin_loader_mem_input);
    std::vector<uint32_t> memory = emu_engine.get_memory_snapshot();
    ASSERT_EQ(memory[1], 0x3fa41a42);
}
