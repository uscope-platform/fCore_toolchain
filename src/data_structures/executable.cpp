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

#include "data_structures/executable.hpp"



executable::executable() {
    sections["metadata"] = std::vector<uint32_t>();
    sections["io_remapping"] = std::vector<uint32_t>();
    sections["code"] = std::vector<uint32_t>();
}

void executable::add_code_section(std::vector<uint32_t> code) {
    sections["code"] = std::move(code);
}

void executable::add_io_mapping(std::vector<std::pair<uint16_t, uint16_t>> mapping) {
    for(auto pair:mapping){
        io_mapping_present = true;
        uint32_t raw_mapping = pair.first + (pair.second<<16);
        sections["io_remapping"].push_back(raw_mapping);
    }

}

void executable::generate_metadata() {
    if(io_mapping_present){
        sections["metadata"].push_back(3);
        sections["metadata"].push_back(sections["io_remapping"].size() + (sections["code"].size()<<16));
        sections["metadata"][0] += sections["metadata"].size()<<16;
    } else {
        sections["metadata"].push_back(2);
        sections["metadata"].push_back((sections["code"].size()));
        sections["metadata"][0] += sections["metadata"].size()<<16;
    }

}


std::vector<uint32_t> executable::get_executable() {
    std::vector<uint32_t> ret_exec;
    auto metadata_sect = sections["metadata"];
    auto io_remap_sect = sections["io_remapping"];
    auto code_sect = sections["code"];
    std::move(metadata_sect.begin(), metadata_sect.end(), std::back_inserter(ret_exec));
    std::move(io_remap_sect.begin(), io_remap_sect.end(), std::back_inserter(ret_exec));
    std::move(code_sect.begin(), code_sect.end(), std::back_inserter(ret_exec));
    return ret_exec;
}

std::vector<uint32_t> executable::get_code() {
    return sections["code"];
}

