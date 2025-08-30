

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

#include "emulator/v2/input_waveform_generator.hpp"
#include "emulator/v2/backend/emulator_backend.hpp"

namespace fcore::emulator_v2 {

    void emulator_specs::parse(const nlohmann::json &spec_obj) {
        std::set<uint32_t> current_orders;

        interconnects.clear();
        cores.clear();

        try{
            schema_validator_base validator(emulator_input, 2);
            validator.validate(spec_obj);
        } catch(std::invalid_argument &ex){
            throw std::runtime_error("Failed to validate emulator schema");
        }

        if(spec_obj["version"] != 2) {
            throw std::runtime_error("Wrong emulator input schema version");
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

    deployment_options emulator_specs::get_deployment_options(const std::string &core_id) {
        for(auto &c: cores) {
            if(c.id == core_id) return c.deployment;
        }
        throw std::runtime_error("core with ID: " + core_id + " not found");
    }

    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<uint32_t>>> emulator_specs::
    get_outputs_initial_values() const {
        std::unordered_map<std::string,std::unordered_map<std::string, std::vector<uint32_t>>> output_ivs;

        std::unordered_map<std::string,std::unordered_map<std::string, std::vector<uint32_t>>> inputs_ivs;
        for(auto &c:cores) {
            for(auto &in: c.inputs) {
                std::vector<uint32_t> data;
                for(int j = 0; j < c.channels; j++) {
                    int idx = 0;
                    if(in.data.size() != 1) idx = j;
                    if(in.source_type == waveform_input) {
                        input_waveform_generator gen;
                        gen.set_sampling_frequency(c.sampling_frequency);
                        gen.add_waveform(in.name, in.waveform_parameters);
                        const auto val = gen.peek_value(in.name);
                        data.push_back(emulator_backend::float_to_uint32(val));
                    }else if(std::holds_alternative<std::vector<uint32_t>>(in.data[idx])) {
                        data.push_back(std::get<std::vector<uint32_t>>(in.data[idx])[0]);
                    } else {
                        data.push_back(emulator_backend::float_to_uint32(std::get<std::vector<float>>(in.data[idx])[0]));
                    }
                }
                inputs_ivs[c.id][in.name] = data;
            }
        }


        for(auto &c:cores) {
            for(auto &o: c.outputs) {
                output_ivs[c.id][o.name] = std::vector<uint32_t>(c.channels, 0);
            }
            for(auto &m:c.memories) {
                if(std::holds_alternative<std::vector<uint32_t>>(m.value)) {
                    output_ivs[c.id][m.name] = std::get<std::vector<uint32_t>>(m.value);
                } else {
                    output_ivs[c.id][m.name] = emulator_backend::float_to_uint32_v(std::get<std::vector<float>>(m.value));
                }
            }
        }

        for(auto &ic:interconnects) {
            auto source_id = ic.source_endpoint.substr(0, ic.source_endpoint.find("."));
            auto source_name = ic.source_endpoint.substr(ic.source_endpoint.find(".") + 1);

            auto dest_id = ic.destination_endpoint.substr(0, ic.destination_endpoint.find("."));
            auto dest_name = ic.destination_endpoint.substr(ic.destination_endpoint.find(".") + 1);
            output_ivs[source_id][source_name] = inputs_ivs[dest_id][dest_name];
        }

        return output_ivs;
    }

    emulator_output_specs emulator_specs::process_output(const nlohmann::json &o) {
        emulator_output_specs out;
        out.metadata.type = data_type_map[o["metadata"]["type"]];
        out.metadata.width = o["metadata"]["width"];
        out.metadata.is_signed = o["metadata"]["signed"];
        out.metadata.is_common_io = o["metadata"]["common_io"];
        out.name = o["name"];

        out.is_vector = o["is_vector"];
        if(!out.is_vector) {
            out.vector_size = 1;
        } else {
            out.vector_size = o["vector_size"];
        }

        if(o["metadata"].contains("io_address")) {
            if(o["metadata"]["io_address"].is_array()) {
                out.metadata.io_address = static_cast<std::vector<uint32_t>>(o["metadata"]["io_address"]);
            } else {
                out.metadata.io_address = {o["metadata"]["io_address"]};
            }
        } else if(out.is_vector) {
            out.metadata.io_address = std::vector<uint32_t>(out.vector_size, 0);
        }

        return out;
    }

    emulator_input_specs emulator_specs::process_input(const nlohmann::json &i) {
        emulator_input_specs in;


        in.name = i["name"];
        in.metadata.type = data_type_map[i["metadata"]["type"]];
        in.metadata.width = i["metadata"]["width"];
        in.metadata.is_signed = i["metadata"]["signed"];
        in.is_vector = i["is_vector"];
        if(!in.is_vector) {
            in.vector_size = 1;
        } else {
            in.vector_size = i["vector_size"];
        }
        if(i["metadata"].contains("io_address")) {
            if(i["metadata"]["io_address"].is_array()) {
                in.metadata.io_address =  static_cast<std::vector<uint32_t>>(i["metadata"]["io_address"]);
            } else {
                in.metadata.io_address = {i["metadata"]["io_address"]};
            }
        }else if(in.is_vector) {
            in.metadata.io_address =  std::vector<uint32_t>(in.vector_size, 0);;
        }
        in.metadata.is_common_io = i["metadata"]["common_io"];

        auto source_obj = i["source"];
        in.source_type = source_type_map[source_obj["type"]];

        if(in.source_type == time_series_input) {
            std::vector<std::string> series;
            if(in.metadata.type== type_float){
                if(source_obj["value"][0].is_array()) {
                    for(auto &item:source_obj["value"]) {
                        std::vector<float> ds = item;
                        in.data.emplace_back(ds);
                    }
                } else {
                    std::vector<float> ds = source_obj["value"];
                    in.data.emplace_back(ds);
                }
            } else {
                if(source_obj["value"][0].is_array()) {
                    for(auto &item:source_obj["value"]) {
                        std::vector<uint32_t> ds = item;
                        in.data.emplace_back(ds);
                    }
                } else {
                    std::vector<uint32_t> ds = source_obj["value"];
                    in.data.emplace_back(ds);
                }

            }
        } else if(in.source_type == waveform_input){
            if(source_obj["shape"] == "square") {
                square_wave_parameters p;
                p.v_off = source_obj["voff"];
                p.v_on = source_obj["von"];
                p.t_delay = source_obj["tdelay"];
                p.t_on = source_obj["ton"];
                p.period = source_obj["period"];
                in.waveform_parameters  = p;
            } else if(source_obj["shape"] == "sine") {
                sine_wave_parameters p;
                p.dc_offset = source_obj["dc_offset"];
                p.amplitude = source_obj["amplitude"];
                p.frequency = source_obj["frequency"];
                p.phase = source_obj["phase"];
                in.waveform_parameters  = p;
            } else if(source_obj["shape"] == "triangle") {

                triangle_wave_parameters p;
                p.dc_offset = source_obj["dc_offset"];
                p.amplitude = source_obj["amplitude"];
                p.frequency = source_obj["frequency"];
                p.phase = source_obj["phase"];
                p.duty = source_obj["duty"];
                in.waveform_parameters  = p;
            } else {
                throw std::runtime_error(fmt::format("Unsupported waveform shape ({0}) for input {1}", i["shape"].dump(), in.name));
            }
        } else {
            if(source_obj.contains("value")) {
                std::vector<std::variant<std::vector<unsigned int>, std::vector<float>>> ds;
                if(in.metadata.type== type_float){
                    if(source_obj["value"].is_array()){
                        std::vector<float> v = source_obj["value"];
                        for(auto &item:v){
                            ds.emplace_back(std::vector<float>({item}));
                        }
                    } else {
                        std::vector<float> v = {source_obj["value"]};
                        ds.emplace_back(v);
                    }
                } else {
                    if(source_obj["value"].is_array()){
                        std::vector<uint32_t> v = source_obj["value"];
                        for(auto &item:v){
                            ds.emplace_back(std::vector<uint32_t>({item}));
                        }
                    } else {
                        std::vector<uint32_t> v = {source_obj["value"]};
                        ds.emplace_back(v);
                    }
                }
                in.data = ds;
            } else {
                in.data = {};
            }
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

        for(auto &o: core_obj["outputs"]){
            c.outputs.push_back(process_output(o));
        }

        for(auto &m: core_obj["memory_init"]){
            auto mem = process_memory(m);
            c.memories.push_back(mem);
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

        interconnect.destination_endpoint = ic["destination"];
        interconnect.source_endpoint = ic["source"];
        if(ic.contains("source_channel") && !ic.contains("destination_channel"))
            throw std::runtime_error("Either both source and destination channels need to be specified or none of them");
        if(ic.contains("source_channel"))
            interconnect.source_channel = ic["source_channel"];
        else
            interconnect.source_channel = -1;
        if(ic.contains("destination_channel"))
            interconnect.destination_channel = ic["destination_channel"];
        else
            interconnect.destination_channel = -1;

        return interconnect;
    }

    emulator_memory_specs emulator_specs::process_memory(const nlohmann::json &m) {
        emulator_memory_specs mem;

        mem.name = m["name"];

        mem.metadata.type = data_type_map[m["metadata"]["type"]];
        mem.metadata.width = m["metadata"]["width"];
        mem.metadata.is_signed = m["metadata"]["signed"];
        mem.is_vector = m["is_vector"];
        if(!mem.is_vector) {
            mem.vector_size = 1;
        } else {
            mem.vector_size = m["vector_size"];
        }

        if(m["metadata"].contains("io_address")) {
            if(m["metadata"]["io_address"].is_array()) {
                mem.metadata.io_address = static_cast<std::vector<uint32_t>>(m["metadata"]["io_address"]);
            } else {
                mem.metadata.io_address ={m["metadata"]["io_address"]};
            }
        }else if(mem.is_vector) {
            mem.metadata.io_address =  std::vector<uint32_t>(mem.vector_size, 0);;
        }

        mem.is_output = m["is_output"];
        mem.is_input = m["is_input"];

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