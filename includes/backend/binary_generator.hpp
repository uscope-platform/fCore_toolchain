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

#ifndef FCORE_TOOLCHAIN_BINARY_GENERATOR_HPP
#define FCORE_TOOLCHAIN_BINARY_GENERATOR_HPP

#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <memory>

#include "data_structures/executable.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"

namespace fcore{
    class binary_generator {

    public:
        binary_generator() = default;
        void process_stream(
                const instruction_stream& stream,
                const std::unordered_map<std::string, std::vector<uint32_t>>& dma_map,
                const std::shared_ptr<std::unordered_map<std::string, std::vector<io_map_entry>>>& allocation_map,
                bool debug_print);
        void process_stream(const instruction_stream& stream, bool debug_print);
        std::vector<uint32_t> get_executable();
        std::vector<uint32_t> get_code();
        uint32_t get_program_size();
        void write_hex_file(const std::string& filename);
        void write_mem_file(const std::string& filename);
        std::vector<uint32_t> generate_hex(bool endian_swap);
        std::vector<std::string> generate_mem();
        std::set<io_map_entry> get_io_mapping(){return io_mapping;};
    private:
        std::set<io_map_entry> io_mapping;
        std::set<io_map_entry> common_io_mapping;

        std::set<uint16_t, uint16_t> allocated_mapping;
        int progress_counter = 0;
        executable ex;
        static inline uint16_t Reverse16(uint16_t value)
        {
            return (((value & 0x00FFu) << 8u) |
                    ((value & 0xFF00u) >> 8u));
        }

        static inline uint32_t Reverse32(uint32_t value)
        {
            return (((value & 0x000000FFu) << 24u) |
                    ((value & 0x0000FF00u) <<  8u) |
                    ((value & 0x00FF0000u) >>  8u) |
                    ((value & 0xFF000000u) >> 24u));
        }

    };
}



#endif //FCORE_TOOLCHAIN_BINARY_GENERATOR_HPP
