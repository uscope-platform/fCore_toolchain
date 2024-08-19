

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

#include "data_structures/emulation/specs/emulator_specs.hpp"

namespace fcore::emulator {
    emulator_specs::emulator_specs(const nlohmann::json &spec_obj) {

        try{
            fcore::schema_validator_base validator(emulator_input);
            validator.validate(spec_obj);
        } catch(std::invalid_argument &ex){
            throw std::runtime_error("Failed to validate emulator schema");
        }

        for(auto &is: spec_obj["interconnect"]){
            auto i = process_interconnect(is);
            interconnects.push_back(i);
        }

        for(const auto &cs:spec_obj["cores"]){
            auto c = process_core(cs);
            cores.push_back(c);
        }


        emulation_time = spec_obj["emulation_time"];
        custom_deploy_mode = spec_obj["deployment_mode"];
    }

    emulator_core emulator::emulator_specs::get_core_by_id(const std::string &id) {
        for(auto &c: cores){
            if(c.id == id) return c;
        }
        throw std::runtime_error("core with ID: " + id + " not found");
    }

    emulator_output_specs emulator_specs::process_output(const nlohmann::json &o) {
        emulator_output_specs out;
        out.data_type = data_type_map[o["type"]];
        out.name = o["name"];
        std::vector<uint32_t> addrs =  o["reg_n"];
        out.address = addrs;
        return out;
    }

    emulator_input_specs emulator_specs::process_input(const nlohmann::json &i, const nlohmann::json &in_data) {
        emulator_input_specs in;


        in.name = i["name"];
        in.data_type = data_type_map[i["type"]];
        in.source_type = input_type_map[i["source"]["type"]];
        if(in.source_type == external_input) {
            in.data = {};
        } else if(in.source_type == time_series_input){
            std::vector<std::string> series;
            std::vector<std::string> files;
            if(i["source"]["series"].size() != i["source"]["file"].size()){
                throw std::runtime_error("source.series and source.file fields need to have the same dimensions for input "+ in.name);
            }
            if(i["source"]["series"].is_array()) {
                series = i["source"]["series"];
                files = i["source"]["file"];
            } else {
                series = {i["source"]["series"]};
                files = {i["source"]["file"]};
            }
            for(int j = 0; j<files.size(); j++){
                auto sel_series =get_input_series(in_data, files[j], series[j]);
                auto dbg = sel_series.dump();
                if(in.data_type== type_float){
                    std::vector<float> ds = sel_series;
                    in.data.emplace_back(ds);
                } else {
                    std::vector<uint32_t> ds = sel_series;
                    in.data.emplace_back(ds);
                }
            }
        } else {
            std::vector<std::variant<std::vector<unsigned int>, std::vector<float>>> ds;
            if(in.data_type== type_float){
                if(i["source"]["value"].is_array()){
                    std::vector<float> v = i["source"]["value"];
                    for(auto &item:v){
                        ds.emplace_back(std::vector<float>({item}));
                    }
                } else {
                    std::vector<float> v = {i["source"]["value"]};
                    ds.emplace_back(v);
                }
            } else {
                if(i["source"]["value"].is_array()){
                    std::vector<uint32_t> v = i["source"]["value"];
                    for(auto &item:v){
                        ds.emplace_back(std::vector<uint32_t>({item}));
                    }
                } else {
                    std::vector<uint32_t> v = {i["source"]["value"]};
                    ds.emplace_back(v);
                }
            }
            in.data = ds;
        }


        if(i["reg_n"].is_array()){
            std::vector<uint32_t> addresses = i["reg_n"];
            in.address = addresses;
        } else {
            in.address = {i["reg_n"]};
        }

        if(i["channel"].is_array()){
            std::vector<uint32_t> ch = i["channel"];
            in.channel = ch;
        } else {
            in.channel = {i["channel"]};
        }

        return in;
    }

    emulator_core emulator_specs::process_core(const nlohmann::json &core_obj) {
        emulator_core c;
        c.id = core_obj["id"];
        c.order = core_obj["order"];
        c.sampling_frequency = core_obj["sampling_frequency"];
        c.channels = core_obj["channels"];
        c.options = core_obj["options"];
        c.program.content = core_obj["program"]["content"];
        c.program.headers = core_obj["program"]["headers"];

        for(auto &s:core_obj["program"]["build_settings"]["io"]["inputs"]){
            c.program.io.inputs.insert(s);
        }
        for(auto &s:core_obj["program"]["build_settings"]["io"]["outputs"]){
            c.program.io.outputs.insert(s);
        }
        for(auto &s:core_obj["program"]["build_settings"]["io"]["memories"]){
            c.program.io.memories.insert(s);
        }

        for(auto &o: core_obj["outputs"]){
            c.outputs.push_back(process_output(o));
        }

        for(auto &m: core_obj["memory_init"]){
            auto mem = process_memory(m);
            c.memories.push_back(mem);
            if(mem.is_output){
                emulator_output_specs os;
                os.name = mem.name;
                os.address = mem.address;
                os.data_type = mem.data_type;
                c.outputs.push_back(os);
            }
        }


        for(auto &i: core_obj["inputs"]){
            c.inputs.push_back(process_input(i, core_obj["input_data"]));
        }

        c.deployment.rom_address = core_obj["deployment"]["rom_address"];
        c.deployment.control_address = core_obj["deployment"]["control_address"];
        c.deployment.has_reciprocal =  core_obj["deployment"]["has_reciprocal"];

        return c;
    }

    emulator_interconnect emulator_specs::process_interconnect(const nlohmann::json &ic) {
        emulator_interconnect interconnect;

        interconnect.source_core_id = ic["source"];
        interconnect.destination_core_id = ic["destination"];


        for(auto &ch_obj:ic["channels"]){
            dma_channel ch;
            ch.name = ch_obj["name"];
            ch.source.io_name = ch_obj["source_output"];
            ch.destination.io_name = ch_obj["destination_input"];

            if(ch_obj["source"]["channel"].is_array()){
                for(auto &item:ch_obj["source"]["channel"]){
                    ch.source.channel.push_back(item);
                }
            } else {
                ch.source.channel = {ch_obj["source"]["channel"]};
            }

            if(ch_obj["source"]["register"].is_array()){
                for(auto &item:ch_obj["source"]["register"]){
                    ch.source.address.push_back(item);
                }
            } else {
                ch.source.address = {ch_obj["source"]["register"]};
            }

            if(ch_obj["destination"]["channel"].is_array()){
                for(auto &item:ch_obj["destination"]["channel"]){
                    ch.destination.channel.push_back(item);
                }
            } else {
                ch.destination.channel = { ch_obj["destination"]["channel"] };
            }

            if(ch_obj["destination"]["register"].is_array()){
                for(auto &item:ch_obj["destination"]["register"]){
                    ch.destination.address.push_back(item);
                }
            } else {
                ch.destination.address = {ch_obj["destination"]["register"]};
            }

            ch.length = ch_obj["length"];
            if(ch_obj.contains("stride")){
                ch.stride = ch_obj["stride"];
            }
            ch.type = interconnect_type_map[ch_obj["type"]];

            interconnect.channels.push_back(ch);
        }
        return interconnect;
    }

    emulator_memory_specs emulator_specs::process_memory(const nlohmann::json &m) {
        emulator_memory_specs mem;

        mem.name = m["name"];
        mem.data_type = data_type_map[m["type"]];
        mem.is_output = m["is_output"];
        if(m["reg_n"].is_array()){
            mem.address = static_cast<std::vector<uint32_t>>(m["reg_n"]);
        } else{
            mem.address = {m["reg_n"]};
        }

        if(mem.data_type == type_float){
            std::vector<float> value;
            if(m["value"].is_array()){
                value = static_cast<std::vector<float>>(m["value"]);
            } else {
                value = {m["value"]};
            }
            mem.value = value;
        } else {
            std::vector<uint32_t> value;
            if(m["value"].is_array()){
                value = static_cast<std::vector<uint32_t>>(m["value"]);
            } else {
                value = {m["value"]};
            }
            mem.value = value;
        }

        return mem;
    }

    nlohmann::json
    emulator_specs::get_input_series(const nlohmann::json &input_data_obj, const std::string& file, const std::string& series) {
        for(auto &d : input_data_obj){
            std::string name = d["name"];
            if(name == file){
                return d["data"][series];
            }
        }
        throw std::runtime_error("Data series not found: " + file + "." + series);
    }
} // fcore