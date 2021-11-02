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


#include "fcore_emu.hpp"

fcore_emu::fcore_emu(std::istream &input, bin_loader_input_type_t in_type) {
    error_code = "";
    try{
        binary_loader dis(input, in_type);
        std::shared_ptr<ll_ast_node> ast = dis.get_ast();

        program_stream = instruction_stream_builder::build_stream(ast);

        std::unordered_map<std::string, std::shared_ptr<variable>> iom;
        stream_pass_manager sman(iom,0);
        program_stream = sman.process_stream(program_stream);

    } catch(std::runtime_error &e){
        error_occurred = true;
        error_code = e.what();
    }
}

void fcore_emu::write_json(const std::string &output_file) {
    nlohmann::json j;
    std::vector<std::string> str_mem_f;
    std::vector<std::string> str_mem;
    for(int i = 0; i< memory.size(); ++i){
        float val;
        memcpy(&val, &memory[i], sizeof(float));
        str_mem_f.push_back("r"+std::to_string(i)+ ": " + std::to_string(val));
        str_mem.push_back("r"+std::to_string(i)+ ": " + std::to_string(memory[i]));
    }
    j["registers"] = str_mem;
    j["registers_f"] = str_mem_f;
    j["error_code"] = error_code;
    std::string str = j.dump(4);
    std::ofstream ss(output_file);
    ss<<str;
    ss.close();
}

void fcore_emu::emulate_program() {
    try{
        emulator backend(program_stream);
        backend.set_inputs(inputs);
        backend.run_program();
        memory = backend.get_memory();
    } catch(std::runtime_error &e){
        error_occurred = true;
        error_code = e.what();
    }
}

void fcore_emu::set_inputs(std::istream &input) {
    try{
        std::string line;
        std::vector<unsigned int> addresses;
        // PARSE HEADER
        std::getline(input, line);

        std::istringstream iss = std::istringstream{line};
        std::string str;

        while (iss >> str) {
            std::smatch s;
            if(!std::regex_match(str, s, std::regex("r\\d+"))){
                throw std::runtime_error("ERROR: malformed inputs file header");
            }
            addresses.push_back(std::stoul(str.substr(1, str.size()-1)));
        }

        std::vector<std::vector<float>> inputs_store(addresses.size(), std::vector<float>());
        // PARSE CONTENT
        while (std::getline(input, line)) {
            iss = std::istringstream{line};
            int idx = 0;
            while(iss>>str){
                inputs_store[idx].push_back(std::stof(str));
                ++idx;
            }
        }

        for(int i = 0; i<addresses.size(); i++){
            inputs.emplace_back(addresses[i], inputs_store[i]);
        }
    } catch(std::runtime_error &e){
        error_occurred = true;
        error_code = e.what();
    }
}
