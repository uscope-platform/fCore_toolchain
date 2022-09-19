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
// limitations under the License.05/07/2021.
//

#include "frontend/emulator_manager.hpp"



emulator_manager::emulator_manager(nlohmann::json &spec_file) {
    if(!spec_file.contains("cores")){
        throw std::runtime_error("ERROR: No cores section found in the emulator specification file");
    }
    // Parse specification file;
    for(auto &item:spec_file["cores"]){
        auto id = item["id"];
        emulators[id] = load_program(item);
        emulators[id].input = load_input(item);
        emulators[id].output_specs = load_output_specs(item);
        emulators[id].memory_init = load_memory_init(item["memory_init"]);
    }
    interconnects = load_interconnects(spec_file["interconnect"]);
    if(spec_file.contains("run_length"))
        emu_length = spec_file["run_length"];
    // Setup emulators
    for(auto &item:emulators){
        auto emu = item.second.emu;
        emu->set_efi_selector(item.second.efi_implementation);
        emu->init_memory(item.second.memory_init);
    }
}

void emulator_manager::emulate() {
    if(emu_length==-1){
        throw std::runtime_error("ERROR: Unspecified emulation length (at least one non empty input file should be present)");
    }
    run_cores();
}

void emulator_manager::run_cores() {
    for(int i= 0; i<emu_length;i++){
        for(auto &conn:interconnects){
            auto src = emulators[conn.source].emu;
            auto dst = emulators[conn.destination].emu;
            for(auto &reg:conn.connections){
                auto val = src->get_output(reg.first.address, reg.first.channel);
                dst->apply_inputs(reg.second.address, val, reg.second.channel);
            }
        }
        for(auto &item:emulators){
            auto emu = item.second.emu;
            for(auto &in:item.second.input){
                emu->apply_inputs(in.reg_n, in.data[i], in.channel);
            }
            for(int j = 0; j<item.second.active_channels; ++j){
                emu->run_round(j);

                for (auto &out:item.second.output_specs) {
                    item.second.outputs[j][out.reg_n].push_back(emu->get_output(out.reg_n, j));
                }
            }
        }
    }
}

emulator_metadata emulator_manager::load_program(nlohmann::json &core) {
    auto program = core["program"];
    emulator_metadata metadata;
    std::ifstream stream;
    bin_loader_input_type_t in_type;
    if(program["type"] == "mem") {
        stream.open(program["file"]);
        in_type = bin_loader_mem_input;
    } else if(program["type"] == "hex") {
        stream.open(program["file"], std::ifstream::binary);
        in_type = bin_loader_hex_input;
    }

    try{
        binary_loader dis(stream, in_type);
        std::shared_ptr<ll_ast_node> ast = dis.get_ast();

        instruction_stream program_stream = instruction_stream_builder::build_stream(ast);

        std::unordered_map<std::string, std::shared_ptr<variable>> iom;
        stream_pass_manager sman(iom,0);
        sman.set_enabled_passes({false, true, true, true,false});
        program_stream = sman.process_stream(program_stream);

        auto ch = core["channels"];
        metadata.active_channels = ch;

        metadata.emu = std::make_shared<emulator>(program_stream, ch);

        if(core.contains("efi_implementation")){
            metadata.efi_implementation = core["efi_implementation"];
        } else {
            metadata.efi_implementation = "";
        }

    } catch(std::runtime_error &e){
        errors[core["id"]] = e.what();
    }
    return metadata;
}

std::vector<inputs_t> emulator_manager::load_input(nlohmann::json &core) {
    std::vector<inputs_t> inputs;
    if(core["inputs"].empty()){
        return inputs;
    }
    std::string file_path = core["inputs"]["file"];
    csv::CSVReader reader(file_path);
    auto column_names = reader.get_col_names();

    std::unordered_map<std::string, std::string> types = core["inputs"]["types"];
    std::unordered_map<std::string, int> regs = core["inputs"]["registers"];
    std::unordered_map<std::string, unsigned int> channels;

    if(core["inputs"].contains("channels")){
        std::unordered_map<std::string, unsigned int> raw_ch = core["inputs"]["channels"];
        channels = raw_ch;
    } else {
        for(auto &col :column_names){
            channels[col] = 0;
        }
    }

    std::unordered_map<std::string, std::vector<uint32_t>> inputs_vect;

    for (csv::CSVRow& row: reader) { // Input iterator
        for(auto &col:column_names){
            uint32_t val;
            if(types[col] =="i"){
                inputs_vect[col].push_back(row[col].get<uint32_t>());
            } else if(types[col]=="f") {
                inputs_vect[col].push_back(emulator::float_to_uint32(row[col].get<float>()));
            } else{
                throw std::runtime_error("ERROR: unknown type: " + types[col] + " for input " + col);
            }
        }
    }
    for(auto &col:column_names){
        if(regs.contains(col)){
            inputs_t  in;
            in.reg_n = regs[col];
            in.data = inputs_vect[col];
            in.channel = channels[col];
            in.name = col;
            inputs.emplace_back(in);
        }
    }


    emu_length = -1;
    for(auto &item:inputs){
        if(emu_length<0){
            emu_length = item.data.size();
        } else{
            if(emu_length != item.data.size()){
                throw std::runtime_error("ERROR: All input files must have the same length");
            }
        }
    }
    return inputs;
}

std::vector<emulator_output_t> emulator_manager:: load_output_specs(nlohmann::json &core) {
    std::vector<emulator_output_t> outputs;
    for(auto &item: core["outputs"]){
        emulator_output_t out;
        if(item["type"] =="f"){
            out.type = type_float;
        } else if(item["type"] =="i"){
            out.type = type_uint32;
        }
        out.reg_n = item["reg_n"];
        out.name = item["name"];
        outputs.push_back(out);
    }
    return outputs;
}

std::unordered_map<unsigned int, uint32_t> emulator_manager::load_memory_init(nlohmann::json &mem_init) {

    std::unordered_map<unsigned int, uint32_t> init_map;

    for(int i = 0; i<mem_init["index"].size(); i++){
        auto idx =  mem_init["index"][i];
        if(mem_init["type"][i] == "f"){
            init_map[idx] = emulator::float_to_uint32(mem_init["values"][i]);
        } else {
            init_map[idx] = mem_init["values"][i];
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
        nlohmann::json registers = item["registers"];
        for(auto &regs: registers){
            register_spec_t rs_s;
            rs_s.channel = regs["source"][0];
            rs_s.address = regs["source"][1];
            register_spec_t rs_d;
            rs_d.channel = regs["destination"][0];
            rs_d.address = regs["destination"][1];
            i.connections.emplace_back(rs_s,rs_d);
        }
        res.push_back(i);
    }
    return res;
}

std::shared_ptr<std::vector<uint32_t>> emulator_manager::get_memory_snapshot(const std::string &core_id, int channel) {
    return emulators[core_id].emu->get_memory(channel);
}


