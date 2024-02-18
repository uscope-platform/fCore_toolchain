//  Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.05/07/2021.

#ifndef FCORE_TOOLCHAIN_EMULATOR_INPUT_FACTORY_HPP
#define FCORE_TOOLCHAIN_EMULATOR_INPUT_FACTORY_HPP

#include <utility>
#include <vector>
#include <string>
#include "emulator_input.hpp"
#include <nlohmann/json.hpp>

namespace fcore{
    class emulator_input_factory {
    public:
        emulator_input_factory() = default;
        emulator_input_factory(emulator_input_factory &em);
        explicit emulator_input_factory(nlohmann::json &id);
        void new_input(std::string &str, bool v);
        void set_target_address(const std::string& s, std::vector<uint32_t> a);
        void set_target_channel(const std::string& s, std::vector<uint32_t> c);
        void set_data(const std::string& s, const std::string& series_name);
        void set_data(const std::vector<std::string>& vn);
        void set_data(const std::string& s, float f);
        void set_data_int(const std::string& s, uint32_t f);
        void set_type(const std::string& s, std::string t);
        void set_labels(std::vector<std::string> l) {labels = std::move(l);};
        void finalize_object();
        std::unordered_map<std::string, emulator_input> get_map(){return inputs;};
    private:

        std::unordered_map<std::string, emulator_input> inputs;
        // HELPER METHODS
        std::vector<uint32_t> vect_fti(std::vector<float> v);
        uint32_t fti(float f);
        // CONSTRUCTION DATA;
        nlohmann::json data_file;
        bool is_vector = false;
        std::vector<std::string> labels;
        std::vector<uint32_t> addresses;
        std::vector<uint32_t> channels;
        std::vector<std::string> vector_names;
        std::string type;

    };
}



#endif //FCORE_TOOLCHAIN_EMULATOR_INPUT_FACTORY_HPP
