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



emulator_manager::emulator_manager(nlohmann::json &spec_file) {
    ordering_style = no_ordering;
    implicit_order_idx = 0;
    emulator_builder e_b;
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
        auto id = item["id"];
        if(item["program"].contains("filename")){
            emulators[id] = load_program(item);

        } else {

            nlohmann::json src;
            nlohmann::json dst;
            for(auto &ic:spec_file["interconnect"]){
                if(id == ic["source"]) src = ic;
                if(id == ic["destination"]) dst = ic;
            }
            emulators[id] = e_b.load_program(item, dst, src);
            cores_ordering = e_b.get_core_ordering();
        }
        emulators[id].input = load_input(item);
        emulators[id].output_specs = load_output_specs(item);
        if(emulators[id].io_remapping_active){
            emulators[id].memory_init = load_memory_init(item["memory_init"], emulators[id].io_map);
        } else{
            emulators[id].memory_init = load_memory_init(item["memory_init"]);
        }

    }
    interconnects = load_interconnects(spec_file["interconnect"]);
    if(spec_file.contains("run_length"))
        emu_length = spec_file["run_length"];
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
    if(emu_length==-1){
        spdlog::critical("Unspecified emulation length (at least one non empty input file should be present)");
        exit(-1);
    }
    run_cores();
}

void emulator_manager::run_cores() {
    for(int i= 0; i<emu_length;i++){
        for(auto &core_id:cores_ordering){
            auto emu = emulators[core_id.second].emu;
            for(auto &in:emulators[core_id.second].input){
                uint32_t core_reg;
                if(emulators[core_id.second].io_remapping_active){
                    core_reg = emulators[core_id.second].io_map[in.reg_n];
                } else {
                    core_reg = in.reg_n;
                }
                emu->apply_inputs(core_reg, in.data[i], in.channel);
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

emulator_metadata emulator_manager::load_program(nlohmann::json &core) {
    auto program = core["program"];
    emulator_metadata metadata;
    std::ifstream stream;

    bin_loader_input_type_t in_type;
    std::string file_path = program["filename"];
    if(!std::filesystem::is_regular_file(file_path)){
        std::string core_id = core["id"];
        spdlog::critical("Invalid program file for core: " + core_id);
        exit(-1);
    }
    if(program["type"] == "mem") {
        stream.open(file_path);
        in_type = bin_loader_mem_input;
    } else if(program["type"] == "hex") {
        stream.open(file_path, std::ifstream::binary);
        in_type = bin_loader_hex_input;
    } else{
        spdlog::critical("Unknown program type for core: " + nlohmann::to_string(core["id"]));
        exit(2);
    }

    try{
        binary_loader dis(stream, in_type);
        metadata.io_map = dis.get_io_mapping();
        metadata.io_remapping_active = dis.is_io_mapped();
        std::shared_ptr<ll_ast_node> ast = dis.get_ast();

        instruction_stream program_stream = instruction_stream_builder::build_stream(ast);

        std::vector<int> io_res;
        stream_pass_manager sman(io_res,0);
        sman.set_enabled_passes({false, false, true, true, true,false, true});
        program_stream = sman.process_stream(program_stream);

        auto ch = core["channels"];
        metadata.active_channels = ch;

        metadata.emu = std::make_shared<emulator>(program_stream, ch, core["id"]);

        if(core.contains("options")){
            auto opt = core["options"];
            metadata.efi_implementation = opt["efi_implementation"];
            metadata.comparator_type = opt["comparators"];
            metadata.emu->set_comparator_type(metadata.comparator_type);
        }

        if(core.contains("order")){
            if(ordering_style==implicit_ordering){
                spdlog::critical("Mixing of explicit and implicit cores ordering is not allowed");
                exit(-1);
            }
                cores_ordering[core["order"]] = core["id"];
                ordering_style = explicit_ordering;
        } else {
            if(ordering_style==explicit_ordering){
                spdlog::critical("Mixing of explicit and implicit cores ordering is not allowed");
                exit(-1);
            }
            ordering_style = implicit_ordering;

            cores_ordering[implicit_order_idx] =  core["id"];
            implicit_order_idx++;
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
    std::string file_path = core["input_file"];
    csv::CSVReader reader(file_path);
    auto column_names = reader.get_col_names();

    std::unordered_map<std::string, std::string> types;
    std::unordered_map<std::string, int> regs;
    std::unordered_map<std::string, unsigned int> channels;

    for (auto &input_spec: core["inputs"]) {
        std::string name = input_spec["name"];

        std::string type = input_spec["type"];
        types[name] = type[0];

        regs[name] = input_spec["reg_n"];

        uint32_t c =  input_spec["channel"];
        channels[name] = c;
    }


    std::unordered_map<std::string, std::vector<uint32_t>> inputs_vect;

    for (csv::CSVRow& row: reader) { // Input iterator
        for(auto &col:column_names){
            if(!types.contains(col) && !regs.contains(col)){
                continue; //In this case the column in the input file is spurious and can be ignored
            }
            if(types[col] =="i"){
                inputs_vect[col].push_back(row[col].get<uint32_t>());
            } else if(types[col]=="f") {
                inputs_vect[col].push_back(emulator::float_to_uint32(row[col].get<float>()));
            } else{
                spdlog::critical("unknown type: " + types[col] + " for input " + col);
                exit(-1);
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
                spdlog::critical("All input files must have the same length");
                exit(-1);
            }
        }
    }
    return inputs;
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
        } else {
            spdlog::critical("Unknown output type.");
            exit(-1);
        }
        out.reg_n = item["reg_n"];
        out.name = item["name"];
        out_specs.push_back(out);
    }
    return out_specs;
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


std::unordered_map<unsigned int, uint32_t>
emulator_manager::load_memory_init(nlohmann::json &mem_init, std::unordered_map<uint16_t, uint16_t> io_map) {

    std::unordered_map<unsigned int, uint32_t> init_map;

    for(auto &mem:mem_init){
        if(mem["type"] == "float") {
            init_map[mem["reg_n"]] = emulator::float_to_uint32(mem["value"]);
        } else {
            init_map[mem["reg_n"]] = mem["value"];
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
                transfer_length = ch["length"];
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
            } else if(transfer_type == "regular_transfer"){
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

