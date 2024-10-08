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

#include "tools/variable_map.hpp"

namespace fcore{

    variable_map::variable_map() {
        for(int i = 0; i<std::pow(2, fcore_register_address_width); i++){
            std::string reg_name = "r"+std::to_string(i);
            std::shared_ptr<variable> reg = std::make_shared<variable>(reg_name);
            map[reg_name] = reg;
        }
    }

    std::shared_ptr<variable> variable_map::operator[](const std::string& key) {
        return map[key];
    }

    void variable_map::insert(const std::string& key, std::shared_ptr<variable>item) {
        if(map.count(key)>0) return;
        switch (item->get_variable_class().iom_spec) {
            case variable_input_type:
                n_inputs_++;
                break;
            case variable_memory_type:
            case variable_regular_type:
                if(!variable::is_explicit_register(key))
                    n_variables_++;
                break;
            case variable_output_type:
                n_outputs_++;
                break;
        }
        map[key] = std::move(item);
    }

    unsigned int variable_map::count(const std::string &key) {
        return map.count(key);
    }

    std::shared_ptr<variable> variable_map::at(const std::string &key) {
        return map.at(key);
    }


    unsigned int variable_map::size() {
        return map.size();
    }
}
