

//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#include "data_structures/emulation/v2/specs/emulator_specs.hpp"

namespace fcore::emulator_v2 {

    void emulator_specs::set_specs(const nlohmann::json &spec_obj) {
        std::set<uint32_t> current_orders;

        interconnects.clear();
        cores.clear();

        try{
            schema_validator_base validator(emulator_input, 2);
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
            if(current_orders.contains(c.order)){
                throw std::runtime_error("Core ID: " + c.id + " has duplicate order field");
            }
            current_orders.insert(c.order);
        }


        emulation_time = spec_obj["emulation_time"];
        custom_deploy_mode = spec_obj["deployment_mode"];
    }

    emulator_core emulator_specs::get_core_by_id(const std::string &id) {
        for(auto &c: cores){
            if(c.id == id) return c;
        }
        throw std::runtime_error("core with ID: " + id + " not found");
    }

    emulator_output_specs emulator_specs::process_output(const nlohmann::json &o) {
        emulator_output_specs out;
        out.metadata.type = data_type_map[o["metadata"]["type"]];
        out.metadata.width = o["metadata"]["width"];
        out.metadata.is_signed = o["metadata"]["signed"];
        out.name = o["name"];
        out.output_type = data_type_map[o["type"]];
        std::vector<uint32_t> addrs =  o["reg_n"];
        out.address = addrs;
        return out;
    }

    emulator_input_specs emulator_specs::process_input(const nlohmann::json &i) {
        emulator_input_specs in;


        in.name = i["name"];
        in.metadata.type = data_type_map[i["metadata"]["type"]];
        in.metadata.width = i["metadata"]["width"];
        in.metadata.is_signed = i["metadata"]["signed"];
        in.source_type = input_type_map[i["source"]["type"]];
        if(in.source_type == external_input) {
            in.data = {};
        } else if(in.source_type == time_series_input){
            std::vector<std::string> series;
            if(in.metadata.type== type_float){
                if(i["source"]["value"][0].is_array()) {
                    for(auto &item:i["source"]["value"]) {
                        std::vector<float> ds = item;
                        in.data.emplace_back(ds);
                    }
                } else {
                    std::vector<float> ds = i["source"]["value"];
                    in.data.emplace_back(ds);
                }
            } else {
                std::vector<uint32_t> ds = i["source"]["value"];
                in.data.emplace_back(ds);
            }
        } else {
            std::vector<std::variant<std::vector<unsigned int>, std::vector<float>>> ds;
            if(in.metadata.type== type_float){
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
        if(core_obj["program"].contains("type")){
            if(core_obj["program"]["type"] == "asm"){
                c.program.type = prog_type_asm;
            } else {
                c.program.type = prog_type_c;
            }
        } else {
            c.program.type = prog_type_c;
        }
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
                os.metadata = mem.metadata;
                os.output_type = type_float;
                c.outputs.push_back(os);
            }
        }


        for(auto &i: core_obj["inputs"]){
            c.inputs.push_back(process_input(i));
        }

        double rom_address = core_obj["deployment"]["rom_address"];
        double control_address = core_obj["deployment"]["control_address"];

        if(!check_float_intness(rom_address) || !check_float_intness(control_address)){
            throw std::runtime_error("Both rom and control addresses for core " + c.id + " should be integer like numbers");
        }
        c.deployment.rom_address = rom_address;
        c.deployment.control_address = control_address;
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

        mem.metadata.type = data_type_map[m["metadata"]["type"]];
        mem.metadata.width = m["metadata"]["width"];
        mem.metadata.is_signed = m["metadata"]["signed"];

        mem.is_output = m["is_output"];
        if(m["reg_n"].is_array()){
            mem.address = static_cast<std::vector<uint32_t>>(m["reg_n"]);
        } else{
            mem.address = {m["reg_n"]};
        }

        if(mem.metadata.type == type_float){
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

} // fcore