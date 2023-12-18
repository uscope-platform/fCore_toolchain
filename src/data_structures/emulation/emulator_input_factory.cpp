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


#include "data_structures/emulation/emulator_input_factory.hpp"


void emulator_input_factory::new_input(std::string &str, bool v) {
    emulator_input ei;
    if(!is_vector){
        ei.set_name(str);
        inputs[str] = ei;
    }
    is_vector = v;
}

void emulator_input_factory::set_target_address(const std::string& s, std::vector<uint32_t> a) {
    if(is_vector)
        addresses = std::move(a);
    else
        inputs[s].set_target_address(a[0]);
}

void emulator_input_factory::set_target_channel(const std::string& s, std::vector<uint32_t> c) {
    if(is_vector)
        channels = std::move(c);
    else
        inputs[s].set_target_channel(c[0]);
}

void emulator_input_factory::set_data(const std::vector<std::string>& vn) {
    vector_names = vn;
}

void emulator_input_factory::set_data(const std::string& s, const std::string& series_name) {
    auto col = data_file[series_name];

    if(inputs[s].get_type()=="f"){
        inputs[s].set_data(vect_fti(col));
    } else {
        inputs[s].set_data((std::vector<uint32_t>)col);
    }
}

void emulator_input_factory::set_data(const std::string& s, float d) {
    inputs[s].set_data(fti(d));
}

void emulator_input_factory::set_type(const std::string& s, std::string t) {
    type = t;
    inputs[s].set_type(std::move(t));
}

emulator_input_factory::emulator_input_factory(emulator_input_factory &im) {
    inputs = im.inputs;
}

emulator_input_factory::emulator_input_factory(nlohmann::json &id) {
    data_file = id;
}

uint32_t emulator_input_factory::fti(float f) {
    uint32_t i;
    memcpy(&i, &f, sizeof(f));
    return i;
}

std::vector<uint32_t> emulator_input_factory::vect_fti(std::vector<float> v) {
    std::vector<uint32_t> dv;
    for(float f:v){
        dv.push_back(fti(f));
    }
    return dv;
}

void emulator_input_factory::finalize_object() {
    if(is_vector){
        for(uint32_t i = 0; i< labels.size();i++){
            emulator_input ei;
            ei.set_name(labels[i]);
            ei.set_target_channel(channels[i]);
            ei.set_target_address(addresses[i]);
            ei.set_type(type);
            if(type=="f"){
                ei.set_data(vect_fti( data_file[vector_names[i]]));
            } else {
                ei.set_data((std::vector<uint32_t>) data_file[vector_names[i]]);
            }
        }
    }
}

