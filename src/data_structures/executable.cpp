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
// limitations under the License.

#include "data_structures/executable.hpp"


namespace fcore{

    executable::executable() {
        sections["metadata"] = std::vector<uint32_t>();
        sections["io_remapping"] = std::vector<uint32_t>();
        sections["common_io_map"] = std::vector<uint32_t>();
        sections["code"] = std::vector<uint32_t>();
    }

    executable::executable(std::vector<uint32_t> exec) {
        std::vector<uint32_t> executable = std::move(exec);
        sections["metadata"].push_back(executable[0]);

        uint16_t metadata[2];
        split_word(executable[0], metadata);

        executable.erase(executable.begin(), executable.begin()+2);
        for(int i = 0; i< metadata[0]-1; i++){
            sections["io_remapping"].push_back(executable[i]);
        }
        executable.erase(executable.begin(), executable.begin()+metadata[0]);
        for(auto &i:executable){
            if(i==0xC) break;
            else(sections["common_io_map"].push_back(i));
        }
        executable.erase(executable.begin(), executable.begin() + sections["common_io_map"].size() + 1);

        sections["code"].insert(sections["code"].end(),executable.begin(), executable.end());
    }


    void executable::add_code_section(std::vector<uint32_t> code) {
        sections["code"] = std::move(code);
    }

    void executable::add_io_mapping(const std::set<io_map_entry>&  mapping, const std::set<io_map_entry>&  common_io_mapping) {
        std::set<uint32_t>maps;
        for(const auto& pair:mapping){
            uint32_t raw_mapping = pair.io_addr+ (pair.core_addr<<16);
            if(!maps.contains(raw_mapping)){
                maps.insert(raw_mapping);
                sections["io_remapping"].push_back(raw_mapping);
            }
        }
        sections["io_remapping"].push_back(0xC);

        for(const auto& pair:common_io_mapping){
            uint32_t raw_mapping = pair.io_addr+ (pair.core_addr<<16);
            if(!maps.contains(raw_mapping)){
                maps.insert(raw_mapping);
                sections["common_io_remapping"].push_back(raw_mapping);
            }
        }
        sections["common_io_remapping"].push_back(0xC);
    }

    void executable::generate_metadata() {
        sections["metadata"].push_back(sections["io_remapping"].size() + (sections["code"].size()<<16));
        sections["metadata"].push_back(0xC);
    }


    std::vector<uint32_t> executable::get_executable() {
        std::vector<uint32_t> ret_exec;
        auto metadata_sect = sections["metadata"];
        auto io_remap_sect = sections["io_remapping"];
        auto common_io_remap_sect = sections["common_io_remapping"];
        auto code_sect = sections["code"];
        std::move(metadata_sect.begin(), metadata_sect.end(), std::back_inserter(ret_exec));
        std::move(io_remap_sect.begin(), io_remap_sect.end(), std::back_inserter(ret_exec));
        std::move(common_io_remap_sect.begin(), common_io_remap_sect.end(), std::back_inserter(ret_exec));
        std::move(code_sect.begin(), code_sect.end(), std::back_inserter(ret_exec));
        return ret_exec;
    }

    std::vector<uint32_t> executable::get_code() {
        return sections["code"];
    }

    std::set<std::pair<uint16_t, uint16_t>> executable::get_io_mapping() {
        std::set<std::pair<uint16_t, uint16_t>> ret_val;
        for(auto &item:sections["io_remapping"]){
            uint16_t pair[2];
            split_word(item, pair);
            ret_val.insert({pair[0], pair[1]});
        }
        return ret_val;
    }

    std::set<std::pair<uint16_t, uint16_t>> executable::get_common_io_mapping() {
        std::set<std::pair<uint16_t, uint16_t>> ret_val;
        for(auto &item:sections["common_io_map"]){
            uint16_t pair[2];
            split_word(item, pair);
            ret_val.insert({pair[0], pair[1]});
        }
        return ret_val;
    }
}


