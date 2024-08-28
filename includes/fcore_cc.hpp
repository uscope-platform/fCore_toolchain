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

#ifndef FCORE_TOOLCHAIN_FCORE_CC_HPP
#define FCORE_TOOLCHAIN_FCORE_CC_HPP

#include <istream>
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "tools/variable_map.hpp"
#include "tools/define_map.hpp"
#include "frontend/C/C_language_parser.hpp"
#include "backend/binary_generator.hpp"
#include "passes/hl_passes.hpp"
#include "passes/high_level/hl_pass_manager.hpp"
#include "tools/high_level_ast_lowering.hpp"
#include "data_structures/instruction_stream/instruction_stream.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "instrumentation/instrumentation_core.hpp"

namespace fcore {

    struct core_info {
        uint32_t n_channels = 11;
        uint32_t efi_lenght = 13;
        uint32_t load_overhead = 2;
        uint32_t stop_duration = 1;
        uint32_t fixed_core_overhead = 4;
    };

    struct program_info {
        uint32_t fixed_portion;
        uint32_t per_channel_portion;
    };

    typedef enum {
        core_iom_input = 0,
        core_iom_output = 1,
        core_iom_memory = 2
    } core_iom_type;

    static std::unordered_map<std::string, core_iom_type> core_iom_type_translator = {
            {"input", core_iom_input},
            {"output", core_iom_output},
            {"memory", core_iom_memory}
    };

    struct core_iom {
        core_iom_type type;
        std::vector<uint32_t> address;
    };


    typedef std::unordered_map<std::string, std::vector<io_map_entry>> io_map;

    class fcore_cc {
    public:
        fcore_cc(std::string &path, std::vector<std::string> &inc, bool print_debug);
        explicit fcore_cc(std::vector<std::string> &contents, std::vector<std::string> &inc);
        void set_profiler(const std::shared_ptr<instrumentation_core> &ic){profiling_core = ic;};
        void enable_logging(){logging = true;};
        void parse_dma_spec();
        bool compile();
        std::set<io_map_entry>  get_io_map();
        std::vector<uint32_t> get_raw_code();
        std::vector<uint32_t> get_executable();
        std::string get_errors();
        void write_hexfile(const std::string& ouput_file);
        void write_verilog_memfile(const std::string& ouput_file);
        void write_json(const std::string& output_file);
        nlohmann::json get_dump() {return dump;};

        void set_dma_map(std::unordered_map<std::string, core_iom> &map){dma_spec = map;};
        void set_core_info(struct core_info &i) {info = i;};
        struct program_info get_program_info() { return length_info;}

        static nlohmann::json dump_iom_map(std::unordered_map<std::string, core_iom> &map);
        static std::unordered_map<std::string, core_iom> load_iom_map(const nlohmann::json &raw_map);
    private:
        void merge_includes(const std::vector<std::shared_ptr<hl_ast_node>>& i);
        std::shared_ptr<hl_ast_node>  parse_include(std::istream &file, std::shared_ptr<define_map> def_map);
        void parse(std::unordered_map<std::string, variable_class_t> dma_specs, std::shared_ptr<define_map> def_map);
        void optimize(std::unordered_map<std::string, std::vector<uint32_t >> &dma_map);
        void analyze_program_length(std::shared_ptr<struct instruction_count> c);
        std::ifstream input_file_stream;
        std::istringstream input_string_stream;
        std::string type;
        std::vector<std::string> includes;
        bool include_is_paths;
        bool logging;

        std::unordered_map<std::string, core_iom> dma_spec;

        std::shared_ptr<hl_ast_root> hl_ast;
        binary_generator writer;
        hl_pass_manager  hl_manager;
        std::string error_code;
        nlohmann::json dump;

        std::unordered_map<std::string, std::vector<uint32_t >> dma_io_map;
        std::unordered_map<std::string, variable_class_t> dma_io_spec;
        std::shared_ptr<io_map> allocation_map;

        struct core_info info;
        struct program_info length_info;

        std::shared_ptr<instrumentation_core> profiling_core;

    };
}




#endif //FCORE_TOOLCHAIN_FCORE_CC_HPP
