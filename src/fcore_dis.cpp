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

#include "fcore_dis.hpp"

namespace fcore{


    bool operator==(const disassembled_program& lhs, const disassembled_program& rhs){
        return lhs.translation_table == rhs.translation_table && lhs.program == rhs.program;
    }


    bool operator==(const translation_table_entry& lhs, const translation_table_entry& rhs){
        return lhs.address == rhs.address && lhs.name == rhs.name;
    }


    fcore_dis::fcore_dis(std::istream &input, bin_loader_input_type_t in_type) {
        binary_loader dis;
        finish_loading(dis.load_stream(input, in_type), dis);
    }


    fcore_dis::fcore_dis(const std::vector<uint32_t> &mem) {
        binary_loader dis;
        finish_loading(dis.load_program(mem), dis);
    }

    void fcore_dis::finish_loading(result<void> loaded, binary_loader &loader) {
        last_error.reset();
        if(!loaded){
            last_error = std::move(loaded).error();
            return;
        }

        // the stream passes and the generator still report failures by throwing
        auto disassembled = catching([&]{
            process_stream(loader.get_program_stream());
            gen->set_common_io_map(loader.get_common_io_mapping());
            gen->set_io_map(loader.get_io_mapping());
        });
        if(!disassembled) last_error = std::move(disassembled).error();
    }

    std::string fcore_dis::get_errors() {
        return last_error ? last_error->what() : "";
    }

    void fcore_dis::write_json(const std::string &output_file) {
        nlohmann::json j;
        j["error_code"] = get_errors();
        if(!last_error){
            j["disassembled_program"] = gen->get_program(true);
        } else{
            j["disassembled_program"] = "";
        }
        std::string str = j.dump();
        std::ofstream ss(output_file);
        ss<<str;
        ss.close();
    }

    std::string fcore_dis::get_disassembled_program_text() {
        return gen->get_program(true);
    }

    void fcore_dis::write_disassembled_program(const std::string &output_file) {
        gen->write_program(output_file);
    }

    void fcore_dis::process_stream(instruction_stream program_stream) {
        std::vector<int> io_res;

        std::shared_ptr<instrumentation_core> ic = nullptr;
        stream_pass_manager sman(io_res, ic,stream_pass_manager::asm_language);
        program_stream = sman.process_stream(program_stream);
        gen = std::make_unique<assembly_generator>(program_stream);

    }

    disassembled_program fcore_dis::get_diassembled_object() {
        disassembled_program dis;
        dis.program = gen->get_program(false);
        auto raw_translation_table = gen->get_io_map();
        auto raw_common_io_table =  gen->get_common_io_map();

        for(auto &[key, value]: raw_translation_table) {
            dis.translation_table[key] =  {"",value};
        }

        for(auto &[key, value]: raw_common_io_table) {
            dis.common_io_translation_table[key] =  {"",value};
        }

        return dis;
    }
}



