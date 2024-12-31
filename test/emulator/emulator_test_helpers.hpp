//  Copyright 2024 Filippo Savi <filssavi@gmail.com>
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
// limitations under the License.

#include <nlohmann/json.hpp>

struct input_struct{
    std::string name;
    float value;
    std::string type;
};


struct output_struct{
    std::string name;
    std::string type;
};

struct memory_struct{
    std::string name;
    float value;
    std::string type;
};


static nlohmann::json prepare_spec(
        const std::string &content,
        float emulation_time,
        uint32_t sampling_frequency,
        std::vector<input_struct>inputs,
        std::vector<output_struct> outputs,
        std::vector<memory_struct> memories
){
    nlohmann::json spec;
    spec["cores"] = std::vector<nlohmann::json>();
    spec["emulation_time"] = emulation_time;

    auto cs = nlohmann::json();

    cs["order"] = 1;
    cs["id"] = "test";

    cs["program"] = nlohmann::json();
    cs["program"]["headers"] = std::vector<std::string>();
    cs["program"]["content"] = content;
    cs["channels"] = 1;
    cs["options"] = nlohmann::json();
    cs["options"]["comparators"] = "full";
    cs["options"]["efi_implementation"] = "none";
    cs["sampling_frequency"] =sampling_frequency;
    cs["deployment"] = nlohmann::json();
    cs["deployment"]["control_address"] = 18316525568;
    cs["deployment"]["rom_address"] = 17179869184;
    cs["deployment"]["has_reciprocal"] = false;
    cs["input_data"] = std::vector<nlohmann::json>();
    cs["inputs"]= std::vector<nlohmann::json>();

    cs["program"]["build_settings"] = nlohmann::json();
    cs["program"]["build_settings"]["io"] = nlohmann::json();

    cs["program"]["build_settings"]["io"]["inputs"] = std::vector<std::string>();
    cs["program"]["build_settings"]["io"]["outputs"] = std::vector<std::string>();
    cs["program"]["build_settings"]["io"]["memories"] = std::vector<std::string>();

    for(int i = 0; i<inputs.size(); i++){
        nlohmann::json in_obj;
        in_obj["name"] = inputs[i].name;
        in_obj["metadata"] = nlohmann::json();
        in_obj["metadata"]["type"] = inputs[i].type;
        in_obj["metadata"]["width"] = 32;
        in_obj["metadata"]["signed"] = true;
        in_obj["metadata"]["common_io"] = false;
        in_obj["reg_n"] = i;
        in_obj["channel"] = 0;
        in_obj["source"] = nlohmann::json();
        in_obj["source"]["type"] = "constant";
        in_obj["source"]["value"] = inputs[i].value;
        cs["inputs"].push_back(in_obj);
        cs["program"]["build_settings"]["io"]["inputs"].push_back(inputs[i].name);
    }

    cs["outputs"]= std::vector<nlohmann::json>();
    for(int i = 0; i<outputs.size(); i++){
        nlohmann::json out_obj;
        out_obj["name"] = outputs[i].name;
        out_obj["metadata"] = nlohmann::json();
        out_obj["metadata"]["type"] = outputs[i].type;
        out_obj["metadata"]["width"] = 32;
        out_obj["metadata"]["signed"] = true;
        out_obj["type"] =  outputs[i].type;
        out_obj["reg_n"] = {10 + i};
        cs["program"]["build_settings"]["io"]["outputs"].push_back(outputs[i].name);
        cs["outputs"].push_back(out_obj);
    }

    cs["memory_init"]= std::vector<nlohmann::json>();

    for(int i = 0; i<memories.size(); i++){
        nlohmann::json mem_obj;
        mem_obj["name"] = memories[i].name;
        mem_obj["metadata"] = nlohmann::json();
        mem_obj["metadata"]["type"] = memories[i].type;
        mem_obj["metadata"]["width"] = 32;
        mem_obj["metadata"]["signed"] = true;
        mem_obj["reg_n"] = 20+i;
        mem_obj["is_output"] = false;
        mem_obj["value"] = memories[i].value;
        cs["program"]["build_settings"]["io"]["memories"].push_back(memories[i].name);
        cs["memory_init"].push_back(mem_obj);
    }



    spec["cores"].push_back(cs);
    spec["interconnect"] = std::vector<nlohmann::json>();
    spec["deployment_mode"] = false;
    return spec;
}