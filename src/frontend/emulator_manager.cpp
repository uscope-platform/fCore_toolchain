// Copyright 2022 Filippo Savi <filssavi@gmail.com>
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


#include "frontend/emulator_manager.hpp"



emulator_manager::emulator_manager(nlohmann::json &spec_file, bool dbg) {
    debug_autogen = dbg;
    emulator_builder e_b(debug_autogen);
    try{
        emulator_schema_validator validator;
        validator.validate(spec_file);
    } catch(std::invalid_argument &ex){
        exit(-1);
    }

    if(!spec_file.contains("cores")){
        spdlog::critical("No cores section found in the emulator specification file");
        exit(-1);
    }
    // Parse specification file;
    for(auto &item:spec_file["cores"]){
        std::string id = item["id"];
        try{

            if(item["program"].contains("filename")){
                emulators[id] = e_b.load_json_program(item, {}, {});
                cores_ordering = e_b.get_core_ordering();
            } else {

                std::vector<nlohmann::json> src = {};
                std::vector<nlohmann::json> dst = {};
                for(auto &ic:spec_file["interconnect"]){
                    std::string source = ic["source"];
                    if(id == source) src.push_back(ic);
                    std::string destination = ic["destination"];
                    if(id == destination) dst.push_back(ic);
                }
                emulators[id] = e_b.load_json_program(item, dst, src);
                cores_ordering = e_b.get_core_ordering();
            }
        } catch(std::runtime_error &e){
            errors[id] = e.what();
        }

        emulators[id].input = load_input(item);
        emulators[id].output_specs = load_output_specs(item);
        emulators[id].memory_init = load_memory_init(item["memory_init"]);

    }
    interconnects = load_interconnects(spec_file["interconnect"]);
    if(spec_file.contains("n_cycles"))
        emu_length = spec_file["n_cycles"];
    // Setup emulators
    for(auto &item:emulators){
        auto emu = item.second.emu;
        emu->set_efi_selector(item.second.efi_implementation);
        if(item.second.io_remapping_active){
            emu->init_memory(io_remap_memory_init(item.second.memory_init, item.second.io_map));
        } else{
            emu->init_memory(item.second.memory_init);
        }
    }

}

void emulator_manager::emulate() {
    run_cores();
}

void emulator_manager::run_cores() {
    for(int i= 0; i<emu_length;i++){
        for(auto &core_id:cores_ordering){
            auto emu = emulators[core_id.second].emu;
            for(auto &in:emulators[core_id.second].input){
                uint32_t core_reg;
                if(emulators[core_id.second].io_remapping_active){
                    core_reg = emulators[core_id.second].io_map[in.second.get_address()];
                } else {
                    core_reg = in.second.get_address();
                }
                emu->apply_inputs(core_reg, in.second.get_data(i), in.second.get_channel());
            }
            for(int j = 0; j<emulators[core_id.second].active_channels; ++j){
                spdlog::info("RUNNING ROUND " + std::to_string(i+1) + " of " + std::to_string(emu_length) + ": core ID = " + core_id.second + " (CH " + std::to_string(j) + ")");
                emu->run_round(j);
            }

            for(auto &conn:interconnects){
                if(core_id.second == conn.source){

                    auto src = emulators[conn.source].emu;
                    auto dst = emulators[conn.destination].emu;
                    for(auto &reg:conn.connections){
                        uint32_t first_address, second_address;
                        if(emulators[core_id.second].io_remapping_active){
                            first_address = emulators[src->get_name()].io_map[reg.first.address];
                            second_address = emulators[dst->get_name()].io_map[reg.second.address];
                        } else {
                            first_address = reg.first.address;
                            second_address = reg.second.address;
                        }

                        auto val = src->get_output(first_address, reg.first.channel);
                        dst->apply_inputs(second_address, val, reg.second.channel);
                    }
                }
            }


            for(int j = 0; j<emulators[core_id.second].active_channels; ++j){
                for (auto &out:emulators[core_id.second].output_specs) {
                    uint32_t address;
                    if(emulators[core_id.second].io_remapping_active){
                        address = emulators[core_id.second].io_map[out.reg_n];
                    } else {
                        address = out.reg_n;
                    }
                    emulators[core_id.second].outputs[j][out.reg_n].push_back(emu->get_output(address, j));
                }
            }
        }
    }
}

std::unordered_map<std::string, emulator_input> emulator_manager::load_input(nlohmann::json &core) {
    emulator_input_factory factory(core["input_data"]);
    if(core["inputs"].empty()){
        return {};
    }

    bool is_vect;
    for (auto &input_spec: core["inputs"]) {

        std::string name = input_spec["name"];

        std::string type = input_spec["type"];
        std::vector<std::string> labels;
        std::string register_type = input_spec["register_type"];
        std::vector<uint32_t> working_addresses;
        std::vector<uint32_t> working_channels;
        if(register_type == "vector" || register_type == "explicit_vector") {
            is_vect = true;
            labels = input_spec["vector_labels"];
            uint32_t channel_progressive = register_type == "vector" ? (uint32_t)input_spec["channel"] : 0;

            for (auto &l: labels) {
                if(register_type == "vector"){
                    working_addresses.push_back(input_spec["reg_n"]);
                    working_channels.push_back(channel_progressive);
                }else{
                    working_addresses.push_back((uint32_t) input_spec["reg_n"] + channel_progressive);
                    working_channels.push_back(input_spec["channel"]);
                }
                channel_progressive++;
            }
        } else {
            working_addresses.push_back( (uint32_t) input_spec["reg_n"]);
            working_channels.push_back(input_spec["channel"]);
        }

        factory.new_input(name, is_vect);
        factory.set_labels(name, labels);
        factory.set_type(name, type.substr(0,1));
        factory.set_target_address(name, working_addresses);
        factory.set_target_channel(name, working_channels);
        if(input_spec["source"]["type"] == "constant"){
            factory.set_data(name,(float) input_spec["source"]["value"]);
        } else if(input_spec["source"]["type"] == "file"){
            if(input_spec["source"]["value"].is_array()){
                factory.set_data(name,(std::vector<std::string>) input_spec["source"]["value"]);
            } else {
                factory.set_data(name,(std::string) input_spec["source"]["value"]);
            }
        }
        factory.finalize_object();

    }

    return factory.get_map();
}

std::vector<emulator_output_t> emulator_manager:: load_output_specs(nlohmann::json &core) {
    std::vector<emulator_output_t> out_specs;
    for(auto &item: core["outputs"]){
        emulator_output_t out;
        std::string type = item["type"];
        if(type =="float"){
            out.type = type_float;
        } else if(type=="integer"){
            out.type = type_uint32;
        }
        if(item["register_type"] == "vector"){
            uint32_t register_progressive = 0;
            for(auto &o:item["reg_n"]){
                out.reg_n = o;
                std::string out_name = item["name"];
                out.name = out_name + "["+ std::to_string(register_progressive) + "]";
                out_specs.push_back(out);
                register_progressive++;
            }
        } else {
            out.reg_n = item["reg_n"];
            out.name = item["name"];
            out_specs.push_back(out);
        }

    }

    for(auto &mem: core["memory_init"]){

       if(mem["is_output"]){
           auto dbg = mem.dump();
           emulator_output_t out;
           if(mem["reg_n"].is_array()){
               for(int i = 0; i< mem["reg_n"].size();i++){
                   out.type = type_float;
                   int addr = mem["reg_n"];
                   std::string name = mem["name"];
                   out.reg_n = addr;
                   out.name = name + "[" + std::to_string(addr) + "]";
                   out_specs.push_back(out);
               }
           } else {
               out.type = type_float;
               out.reg_n = mem["reg_n"];
               out.name = mem["name"];
               out_specs.push_back(out);
           }
       }

    }
    return out_specs;
}

std::unordered_map<unsigned int, uint32_t> emulator_manager::load_memory_init(nlohmann::json &mem_init) {

    std::unordered_map<unsigned int, uint32_t> init_map;

    for(auto &mem:mem_init){
        if(mem["reg_n"].is_array()){
            for(int i = 0; i< mem["reg_n"].size();i++){
                if(mem["type"] == "float") {
                    init_map[mem["reg_n"][i]] = emulator::float_to_uint32(mem["value"][i]);
                } else {
                    init_map[mem["reg_n"][i]] = mem["value"][i];
                }
            }
        } else {
            if(mem["type"] == "float") {
                init_map[mem["reg_n"]] = emulator::float_to_uint32(mem["value"]);
            } else {
                init_map[mem["reg_n"]] = mem["value"];
            }
        }

    }

    return init_map;

}



std::string emulator_manager::get_results() {
    nlohmann::json res;
    for(auto &item:emulators){
        nlohmann::json j;
        nlohmann::json outputs_json;
        j["outputs"] = get_channel_outputs(item.second.output_specs, item.second.active_channels, item.second.outputs);
        j["error_code"] = errors[item.first];
        res[item.first] = j;
    }


    return res.dump(4);
}

nlohmann::json emulator_manager::get_channel_outputs(std::vector<emulator_output_t> specs, int ch, std::unordered_map<int, std::unordered_map<int, std::vector<uint32_t>>> outs) {
    nlohmann::json res;

    for(auto &s: specs){
        nlohmann::json output_obj;
        if(s.type == type_uint32){
            for(int i = 0; i<ch; ++i){
                output_obj[i] = outs[i][s.reg_n];
            }
        } else if(s.type == type_float){
            for(int i = 0; i<ch; ++i){
                output_obj[i] = uint32_to_float(outs[i][s.reg_n]);
            }
        }
        res[s.name] = output_obj;
    }

    return res;
}


std::vector<float> emulator_manager::uint32_to_float(std::vector<uint32_t> &vect) {
    std::vector<float> cast_vect;
    for(auto &item:vect)
        cast_vect.push_back(emulator::uint32_to_float(item));
    return cast_vect;
}

std::vector<interconnect_t> emulator_manager::load_interconnects(nlohmann::json &itc) {
    std::vector<interconnect_t> res;
    for(auto &item:itc){
        interconnect_t i;
        i.source = item["source"];
        i.destination = item["destination"];
        nlohmann::json channels = item["channels"];
        for(auto &ch: channels){
            register_spec_t rs_s;
            register_spec_t rs_d;
            std::string transfer_type;
            uint32_t transfer_length;
            if(!ch.contains("type")){
                transfer_type = "regular_transfer";
            } else {
                transfer_type = ch["type"];
                if(transfer_type != "regular_transfer" && transfer_type != "scalar_transfer"){
                    transfer_length = ch["length"];
                }
            }


            uint32_t source_ch = ch["source"]["channel"];
            uint32_t source_addr= ch["source"]["register"];
            uint32_t dest_ch = ch["destination"]["channel"];
            uint32_t dest_addr = ch["destination"]["register"];

            if(transfer_type == "scatter_transfer"){
                for(int j = 0; j<transfer_length; j++){
                    rs_s.channel = source_ch+j;
                    rs_s.address = source_addr;
                    rs_d.channel = dest_ch;
                    rs_d.address = dest_addr+j;
                    i.connections.emplace_back(rs_s,rs_d);
                }
            } else if(transfer_type == "vector_transfer"){
                for(int j = 0; j<transfer_length; j++){
                    rs_s.channel = source_ch+j;
                    rs_s.address = source_addr;
                    rs_d.channel = dest_ch+j;
                    rs_d.address = dest_addr;
                    i.connections.emplace_back(rs_s,rs_d);
                }
            } else if(transfer_type == "gather_transfer"){
                for(int j = 0; j<transfer_length; j++){
                    rs_s.channel = source_ch;
                    rs_s.address = source_addr+j;
                    rs_d.channel = dest_ch+j;
                    rs_d.address = dest_addr;
                    i.connections.emplace_back(rs_s,rs_d);
                }
            } else if(transfer_type == "regular_transfer" || transfer_type == "scalar_transfer" ){
                rs_s.channel = source_ch;
                rs_s.address = source_addr;
                rs_d.channel = dest_ch;
                rs_d.address = dest_addr;
                i.connections.emplace_back(rs_s,rs_d);
            } else if(transfer_type == "2d_vector_transfer"){

                uint32_t transfer_stride = ch["stride"];
                for (int k = 0; k < transfer_stride; k++) {
                    for(int j = 0; j<transfer_length; j++) {
                        rs_s.channel = source_ch + j;
                        rs_s.address = source_addr + k;
                        rs_d.channel = dest_ch + j;
                        rs_d.address = dest_addr + k;
                        i.connections.emplace_back(rs_s, rs_d);
                    }
                }
            }

        }
        res.push_back(i);
    }
    return res;
}

std::shared_ptr<std::vector<uint32_t>> emulator_manager::get_memory_snapshot(const std::string &core_id, int channel) {
    return emulators[core_id].emu->get_memory(channel);
}

std::unordered_map<unsigned int, uint32_t>
emulator_manager::io_remap_memory_init(std::unordered_map<unsigned int, uint32_t> &map,
                                       std::unordered_map<uint16_t, uint16_t> &io_map) {
    std::unordered_map<unsigned int, uint32_t> ret;

    for(auto &item:map){
        uint32_t io_address = item.first;
        uint32_t core_address  = io_map[io_address];
        ret[core_address] = item.second;
    }

    return ret;
}

nlohmann::json emulator_manager::dump_core(const emulator_metadata &md) {
    nlohmann::json ret;
    ret["inputs"] = nlohmann::json();
    for(const auto &in:md.input){
        nlohmann::json i;
        i["reg_n"] = in.second.get_address();
        i["data"] = in.second.get_data();
        i["channel"] = in.second.get_channel();
        i["name"] = in.second.get_name();
        ret["inputs"].push_back(i);
    }

    ret["outputs"] = nlohmann::json();
    for(const auto &out:md.output_specs){
        nlohmann::json o;
        o["reg_n"] = out.reg_n;
        o["name"] = out.name;
        if(out.type == type_float){
            o["type"] = "float";
        } else{
            o["type"] = "integer";
        }
        ret["outputs"].push_back(o);
    }
    ret["output_types"] = md.output_types;

    ret["memory_init"] = md.memory_init;

    //dump md.emu ?

    ret["active_channels"] = md.active_channels;
    ret["efi_implementation"] = md.efi_implementation;
    ret["comparator_type"] = md.comparator_type;
    ret["io_remapping_active"] = md.io_remapping_active;
    ret["io_map"] = md.io_map;
    ret["outputs"] = md.outputs;

    return ret;
}

nlohmann::json emulator_manager::dump_interconnects(const std::vector<interconnect_t> &ics) {

    nlohmann::json ret;
    for(auto &md:ics){
        nlohmann::json md_j;
        md_j["source"] = md.source;
        md_j["destination"] = md.destination;

        std::vector<nlohmann::json> conns;
        for(auto &c:md.connections){

            nlohmann::json c_j;
            c_j["first"] = nlohmann::json();
            c_j["first"]["address"] = c.first.address;
            c_j["first"]["channel"] = c.first.channel;
            c_j["second"] = nlohmann::json();
            c_j["second"]["address"] = c.first.address;
            c_j["second"]["channel"] = c.first.channel;
            conns.push_back(c_j);
        }
        md_j["connections"] = conns;
        ret.push_back(md_j);
    }

    return ret;
}

