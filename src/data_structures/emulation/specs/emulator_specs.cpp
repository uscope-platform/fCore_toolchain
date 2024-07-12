

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
    emulator_specs::emulator_specs(const nlohmann::json &spec_obj, const std::string& schema_path) {

        try{
            fcore::schema_validator_base validator(schema_path);
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
        int i = 0;
    }

    emulator_core emulator::emulator_specs::get_core_by_id(const std::string &id) {
        for(auto &c: cores){
            if(c.id == id) return c;
        }
        throw std::runtime_error("core with ID: " + id + " not found");
    }

    emulator_output_specs emulator_specs::process_outputs(const nlohmann::json &o) {
        emulator_output_specs out;
        out.type = endpoint_type_map[o["register_type"]];
        out.data_type = data_type_map[o["type"]];
        out.name = o["name"];
        if(out.type == vector_endpoint){
            std::vector<uint32_t> addrs =  o["reg_n"];
            out.address = addrs;
        } else {
            out.address = {o["reg_n"]};
        }
        return out;
    }

    emulator_input_specs emulator_specs::process_inputs(const nlohmann::json &i, const nlohmann::json &in_data) {
        emulator_input_specs in;


        in.name = i["name"];
        in.type = endpoint_type_map[i["register_type"]];
        in.data_type = data_type_map[i["type"]];
        in.source_type = input_type_map[i["source"]["type"]];

        if(in.source_type == time_series_input){
            for(auto &d : in_data){
                std::string series = i["source"]["series"];
                std::string file = i["source"]["file"];
                if(d["name"] == file){
                    if(in.data_type== type_float){
                        std::vector<float> ds = d["data"][series];
                        in.data = {ds};
                    } else {
                        std::vector<uint32_t> ds = d["data"][series];
                        in.data = {ds};
                    }

                }
            }
        } else {
            if(in.data_type== type_float){
                std::vector<float> ds = {i["source"]["value"]};
                in.data = {ds};
            } else {
                std::vector<uint32_t> ds = {i["source"]["value"]};
                in.data = {ds};
            }
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
        for(auto &s:core_obj["program"]["build_settings"]["io"]["inputs"]){
            c.program.io.inputs.push_back(s);
        }
        for(auto &s:core_obj["program"]["build_settings"]["io"]["outputs"]){
            c.program.io.outputs.push_back(s);
        }
        for(auto &s:core_obj["program"]["build_settings"]["io"]["memories"]){
            c.program.io.memories.push_back(s);
        }

        for(auto &o: core_obj["outputs"]){
            c.outputs.push_back(process_outputs(o));
        }

        for(auto &i: core_obj["inputs"]){
            c.inputs[i["name"]]= process_inputs(i, core_obj["input_data"]);
        }
        return c;
    }

    emulator_interconnect emulator_specs::process_interconnect(const nlohmann::json &ic) {
        emulator_interconnect interconnect;

        interconnect.source_core_id = ic["source"];
        interconnect.destination_core_id = ic["destination"];


        for(auto &ch_obj:ic["channels"]){
            dma_channel ch;
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
} // fcore