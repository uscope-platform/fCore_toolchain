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


#include "emulator/emulator_manager.hpp"



fcore::emulator_manager::emulator_manager(nlohmann::json &spec, bool dbg, std::string s_f) {
    debug_autogen = dbg;

    spec_file = spec;
    schema_file = s_f + "/emulator_spec_schema.json";
    emu_length = 1;
}

void fcore::emulator_manager::process() {
    bus_map.clear();
    emulator_builder e_b(debug_autogen);

    try{
        fcore::schema_validator_base validator(schema_file);
        validator.validate(spec_file);
    } catch(std::invalid_argument &ex){
        throw std::runtime_error("Failed to validate emulator schema");
    }

    if(!spec_file.contains("cores")){
        throw std::runtime_error("No cores section found in the emulator specification file");
    }
    // Parse specification file;

    for(auto &item:spec_file["cores"]){
        std::string id = item["id"];
        try{
            std::set<io_map_entry> io_map;
            if(item["program"].contains("filename")){
                emulators[id] = e_b.load_json_program(item, {}, {}, io_map);
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
                emulators[id] = e_b.load_json_program(item, dst, src, io_map);
                cores_ordering = e_b.get_core_ordering();
            }

        } catch(std::runtime_error &e){
            throw std::runtime_error("CORE " + id + ": " + e.what());
        }

        emulators[id].input = load_input(item);
        emulators[id].output_specs = load_output_specs(item);
        emulators[id].memory_init = load_memory_init(item["memory_init"]);

        skipping_counters[id] = 0;
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
    check_bus_duplicates();
}

std::vector<fcore::program_bundle> fcore::emulator_manager::get_programs() {
    bus_map.clear();
    emulator_builder e_b(debug_autogen);
    std::vector<program_bundle> programs;

    // I do not need to load all this stuff, however since these functions run the duplication check it is worth doing
    // as the performance hit is not too bad.
    interconnects = load_interconnects(spec_file["interconnect"]);

    for(auto &item:spec_file["cores"]){
        std::string id = item["id"];

        //same as before, these are loaded just for the check
        auto output_specs = load_output_specs(item);
        auto memory_init = load_memory_init(item["memory_init"]);


        program_bundle b;
        b.name = id;
        try{
            std::vector<nlohmann::json> src = {};
            std::vector<nlohmann::json> dst = {};
            for(auto &ic:spec_file["interconnect"]){
                std::string source = ic["source"];
                if(id == source) src.push_back(ic);
                std::string destination = ic["destination"];
                if(id == destination) dst.push_back(ic);
            }
            b.program = e_b.compile_programs(item, dst, src, b.io);
            cores_ordering = e_b.get_core_ordering();
        } catch(std::runtime_error &e){
            errors[id] = e.what();
        }
        for(auto &mem:item["memory_init"]){
            int reg_idx = mem["reg_n"];
            if(mem["type"]== "float"){
                float flt_v = mem["value"];
                b.mem_init[reg_idx] = emulator::float_to_uint32(flt_v);
            } else {
                b.mem_init[reg_idx] = mem["value"];
            }
        }
        e_b.clear_dma_io();
        b.multirate_divisor = item["multirate_divisor"];
        programs.push_back(b);
    }
    check_bus_duplicates();
    return programs;
}


void fcore::emulator_manager::emulate() {
    output_repeater.clear();
    run_cores();
}

void fcore::emulator_manager::run_cores() {

    spdlog::info("EMULATION START");
    for(int i= 0; i<emu_length;i++){
        if(i%100000==0 && i != 0){
            spdlog::info("EMULATION PROGRESS: {0} cycles done out of {1}", i, emu_length);
        }
        for(auto &core_id:cores_ordering){
            inputs_phase(core_id.second, i);
            execution_phase(core_id.second, i);
            interconnects_phase(core_id.second);
            outputs_phase(core_id.second);

        }
    }
    spdlog::info("EMULATION DONE");
}


void fcore::emulator_manager::inputs_phase(const std::string& n, uint64_t round_n) {

    bool skipped_cycle = skipping_counters[n] != emulators[n].multirate_divisor;
    // APPLY INPUTS (ONLY WHEN THE EMULATOR IS RUN TO AVOID POTENTIALLY DESTROYING THE OUTPUTS IN MEMORY)
    if(!skipped_cycle){
        for(auto &in:emulators[n].input){
            uint32_t core_reg = 0;
            if(emulators[n].io_remapping_active){
                auto addr = in.second.get_address();
                if(emulators[n].io_map.contains(addr)){
                    core_reg = emulators[n].io_map.at(addr);
                }
            } else {
                core_reg = in.second.get_address();
            }
            if(core_reg != 0){
                emulators[n].emu->apply_inputs(core_reg, in.second.get_data(round_n), in.second.get_channel());
            }
        }
    }

}

void fcore::emulator_manager::execution_phase(const std::string& n, uint64_t round_n) {

    bool skipped_cycle = skipping_counters[n] != emulators[n].multirate_divisor;
    for(int j = 0; j<emulators[n].active_channels; ++j){
        if(!skipped_cycle){
            spdlog::trace("RUNNING ROUND " + std::to_string(round_n+1) + " of " + std::to_string(emu_length) + ": core ID = " + n + " (CH " + std::to_string(j) + ")");
            emulators[n].emu->run_round(j);
            skipping_status[n] = false;
            skipping_counters[n] = 0;
        } else {
            skipping_status[n] = true;
            skipping_counters[n]++;
        }

    }
}

void fcore::emulator_manager::interconnects_phase(const std::string& n) {

    for(auto &conn:interconnects){
        if(n == conn.source){

            auto src = emulators[conn.source].emu;
            auto dst = emulators[conn.destination].emu;
            for(auto &reg:conn.connections){
                auto src_id = src->get_name();
                uint32_t first_address, second_address;
                if(emulators[n].io_remapping_active){
                    first_address = emulators[src->get_name()].io_map[reg.first.address];
                    second_address = emulators[dst->get_name()].io_map[reg.second.address];
                } else {
                    first_address = reg.first.address;
                    second_address = reg.second.address;
                }


                if(!skipping_status[src_id]){
                    auto val = src->get_output(first_address, reg.first.channel);
                    output_repeater.add_output(src_id, first_address, val);
                    dst->apply_inputs(second_address, val, reg.second.channel);
                } else {
                    auto val = output_repeater.get_output(src_id, first_address);
                    dst->apply_inputs(second_address, val, reg.second.channel);
                }
            }
        }
    }
}

void fcore::emulator_manager::outputs_phase(std::string n) {

    bool skipped_cycle = skipping_counters[n] != emulators[n].multirate_divisor;
    for(int j = 0; j<emulators[n].active_channels; ++j){
        for (auto &out:emulators[n].output_specs) {
            uint32_t address;
            if(emulators[n].io_remapping_active){
                address = emulators[n].io_map[out.reg_n];
            } else {
                address = out.reg_n;
            }

            if(!skipped_cycle){
                auto value = emulators[n].emu->get_output(address, j);
                output_repeater.add_output(n, address, value);
                emulators[n].outputs[j][out.reg_n].push_back(value);
            } else {
                emulators[n].outputs[j][out.reg_n].push_back(output_repeater.get_output(n, address));
            }
        }
    }
}

std::unordered_map<std::string, fcore::emulator_input> fcore::emulator_manager::load_input(nlohmann::json &core) {
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

            for ([[maybe_unused]]                  auto &l: labels) {
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
            is_vect = false;
            working_addresses.push_back( (uint32_t) input_spec["reg_n"]);
            working_channels.push_back(input_spec["channel"]);
        }

        factory.new_input(name, is_vect);
        factory.set_labels(labels);
        factory.set_type(name, type.substr(0,1));
        factory.set_target_address(name, working_addresses);
        factory.set_target_channel(name, working_channels);
        if(input_spec["source"]["type"] == "constant"){
            if(type=="float") {
                factory.set_data(name,(float) input_spec["source"]["value"]);
            } else {
                factory.set_data_int(name, input_spec["source"]["value"]);
            }

        } else if(input_spec["source"]["type"] == "file"){
            if(input_spec["source"]["value"].is_array()){
                factory.set_data((std::vector<std::string>) input_spec["source"]["value"]);
            } else {
                std::string raw_name = input_spec["source"]["value"];
                std::string series_name  = raw_name.substr(raw_name.find('.')+1, raw_name.length()-raw_name.find('.'));
                factory.set_data(name,(std::string) series_name);
            }
        }
        factory.finalize_object();

    }
    auto dbg = factory.get_map();
    return dbg;
}

std::vector<fcore::emulator_output_t> fcore::emulator_manager:: load_output_specs(nlohmann::json &core) {
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
            for(int o:item["reg_n"]){
                out.reg_n = o;
                std::string out_name = item["name"];
                out.name = out_name + "["+ std::to_string(register_progressive) + "]";
                out_specs.push_back(out);
                bus_map.add_entry(core["id"], "standalone_output", o, out_name);
                register_progressive++;
            }
        } else {
            out.reg_n = item["reg_n"];
            out.name = item["name"];
            bus_map.add_entry(core["id"], "standalone_output", item["reg_n"], item["name"]);
            out_specs.push_back(out);
        }
    }

    for(auto &mem: core["memory_init"]){

       if(mem["is_output"]){
           emulator_output_t out;
           if(mem["reg_n"].is_array()){
               for(uint32_t  i = 0; i< mem["reg_n"].size();i++){
                   out.type = type_float;
                   int addr = mem["reg_n"];
                   std::string name = mem["name"];
                   out.reg_n = addr;
                   out.name = name + "[" + std::to_string(addr) + "]";
                   bus_map.add_entry(core["id"], "memory_as_output", addr,mem["name"]);
                   out_specs.push_back(out);
               }
           } else {
               out.type = type_float;
               out.reg_n = mem["reg_n"];
               out.name = mem["name"];
               bus_map.add_entry(core["id"], "memory_as_output", mem["reg_n"],mem["name"]);
               out_specs.push_back(out);
           }
       }

    }
    return out_specs;
}

std::unordered_map<unsigned int, uint32_t> fcore::emulator_manager::load_memory_init(nlohmann::json &mem_init) {

    std::unordered_map<unsigned int, uint32_t> init_map;

    for(auto &mem:mem_init){
        if(mem["reg_n"].is_array()){
            for(uint32_t i = 0; i< mem["reg_n"].size();i++){
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



std::string fcore::emulator_manager::get_results() {
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

nlohmann::json fcore::emulator_manager::get_channel_outputs(std::vector<emulator_output_t> specs, int ch, std::unordered_map<int, std::unordered_map<int, std::vector<uint32_t>>> outs) {
    nlohmann::json res;

    for(auto &s: specs){
        nlohmann::json output_obj;
        if(s.type == type_uint32){
            for(int i = 0; i<ch; ++i){
                output_obj[i] = outs[i][s.reg_n];
            }
        } else if(s.type == type_float){
            for(int i = 0; i<ch; ++i){
                std::vector<float> cast_vect;
                for(int j = 0; j<outs[i][s.reg_n].size(); ++j){
                    output_obj[i][j] = emulator::uint32_to_float(outs[i][s.reg_n][j]);
                }
            }
        }
        res[s.name] = output_obj;
    }

    return res;
}


std::vector<fcore::interconnect_t> fcore::emulator_manager::load_interconnects(nlohmann::json &itc) {
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
            uint32_t transfer_length = 0;
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
                for(uint32_t j = 0; j<transfer_length; j++){
                    rs_s.channel = source_ch+j;
                    rs_s.address = source_addr;
                    rs_d.channel = dest_ch;
                    rs_d.address = dest_addr+j;
                    bus_map.add_entry(item["source"], "interconnect", dest_addr, ch["name"]);
                    i.connections.emplace_back(rs_s,rs_d);
                }
            } else if(transfer_type == "vector_transfer"){
                for(uint32_t j = 0; j<transfer_length; j++){
                    rs_s.channel = source_ch+j;
                    rs_s.address = source_addr;
                    rs_d.channel = dest_ch+j;
                    rs_d.address = dest_addr;
                    bus_map.add_entry(item["source"], "interconnect", dest_addr, ch["name"]);
                    i.connections.emplace_back(rs_s,rs_d);
                }
            } else if(transfer_type == "gather_transfer"){
                for(uint32_t  j = 0; j<transfer_length; j++){
                    rs_s.channel = source_ch;
                    rs_s.address = source_addr+j;
                    rs_d.channel = dest_ch+j;
                    rs_d.address = dest_addr;
                    bus_map.add_entry(item["source"], "interconnect", dest_addr, ch["name"]);
                    i.connections.emplace_back(rs_s,rs_d);
                }
            } else if(transfer_type == "regular_transfer" || transfer_type == "scalar_transfer" ){
                rs_s.channel = source_ch;
                rs_s.address = source_addr;
                rs_d.channel = dest_ch;
                rs_d.address = dest_addr;
                bus_map.add_entry(item["source"], "interconnect", dest_addr, ch["name"]);
                i.connections.emplace_back(rs_s,rs_d);
            } else if(transfer_type == "2d_vector_transfer"){

                uint32_t transfer_stride = ch["stride"];
                for (uint32_t  k = 0; k < transfer_stride; k++) {
                    for(uint32_t  j = 0; j<transfer_length; j++) {
                        rs_s.channel = source_ch + j;
                        rs_s.address = source_addr + k;
                        rs_d.channel = dest_ch + j;
                        rs_d.address = dest_addr + k;
                        bus_map.add_entry(item["source"], "interconnect", dest_addr + k, ch["name"]);
                        i.connections.emplace_back(rs_s, rs_d);
                    }
                }
            }

        }
        res.push_back(i);
    }
    return res;
}

std::shared_ptr<std::vector<uint32_t>> fcore::emulator_manager::get_memory_snapshot(const std::string &core_id, int channel) {
    return emulators[core_id].emu->get_memory(channel);
}

std::unordered_map<unsigned int, uint32_t>
fcore::emulator_manager::io_remap_memory_init(std::unordered_map<unsigned int, uint32_t> &map,
                                       std::unordered_map<uint16_t, uint16_t> &io_map) {
    std::unordered_map<unsigned int, uint32_t> ret;

    for(auto &item:map){
        uint32_t io_address = item.first;
        uint32_t core_address  = io_map[io_address];
        ret[core_address] = item.second;
    }

    return ret;
}

void fcore::emulator_manager::check_bus_duplicates() {
    if(bus_map.check_duplicates()){
        auto duplicates = bus_map.get_duplicates().dump();
        throw std::domain_error(duplicates);
    }
}
