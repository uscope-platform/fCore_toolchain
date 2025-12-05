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

#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#include "tools/variable_map.hpp"
#include "data_structures/common/io_map.hpp"
#include "tools/define_map.hpp"
#include "frontend/C/C_language_parser.hpp"
#include "backend/binary_generator.hpp"
#include "passes/high_level/infrastructure/hl_passes.hpp"
#include "passes/high_level/infrastructure/hl_pass_manager.hpp"
#include "tools/high_level_ast_lowering.hpp"
#include "passes/instruction_stream/stream_pass_manager.hpp"
#include "instrumentation/instrumentation_core.hpp"
#include "data_structures/common/program_metadata.hpp"

namespace fcore {


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

        std::pair<std::shared_ptr<ast_code_block>, std::vector<std::shared_ptr<ast_definition>>> get_hl_ast();

        void set_dma_map(std::map<std::string, core_iom> &map){dma_spec = map;};
        void set_core_info(core_info &i) {info = i;};
        program_info get_program_info() { return length_info;}

        static nlohmann::json dump_iom_map(std::map<std::string, core_iom> &map);
        static std::map<std::string, core_iom> load_iom_map(const nlohmann::json &raw_map);
    private:
        void merge_includes(const std::vector<std::shared_ptr<ast_code_block>>& i);
        std::shared_ptr<ast_code_block>  parse_include(std::istream &file, std::shared_ptr<define_map> def_map);
        void parse(std::map<std::string, variable_class_t> dma_specs, std::shared_ptr<define_map> def_map);
        void optimize(std::map<std::string, std::vector<uint32_t >> &dma_map);
        void analyze_program_length(std::shared_ptr<instruction_count> c);
        std::ifstream input_file_stream;
        std::istringstream input_string_stream;
        std::string type;
        std::vector<std::string> includes;
        bool include_is_paths;
        bool logging;

        std::map<std::string, core_iom> dma_spec;

        std::shared_ptr<ast_code_block> hl_ast;
        std::vector<std::shared_ptr<ast_definition>> globals;

        binary_generator writer;
        hl_pass_manager  hl_manager;
        std::string error_code;
        nlohmann::json dump;

        std::map<std::string, std::vector<uint32_t >> dma_io_map;
        std::map<std::string, variable_class_t> dma_io_spec;
        std::shared_ptr<io_map> allocation_map;

        core_info info;
        program_info length_info;

        std::shared_ptr<instrumentation_core> profiling_core;

    };
}




#endif //FCORE_TOOLCHAIN_FCORE_CC_HPP
