

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

#include "data_structures/emulation/emulator_output.hpp"
namespace fcore{

    emulator_output::emulator_output(const std::string& output_name, uint32_t size, uint32_t n_channels) {
        for(int i=0; i<n_channels; i++){
            if(size == 1){
                id[i] = {output_name};
                data[i].emplace_back();
            } else {
                for(int n = 0; n<size; n++){
                    id[i].push_back(output_name + std::to_string(n));
                    data[i].emplace_back();
                }
            }
            vector_size = size;
        }
    }

    void emulator_output::add_data_point(const std::vector<uint32_t>& dp, uint32_t channel) {
        if(dp.size()!=vector_size){
            auto message = "Wrong dimension for output data point";
            spdlog::critical(message);
            throw std::runtime_error(message);
        }
        for(int n = 0; n<vector_size; n++){
            data[channel][n].push_back(dp[n]);
        }
    }

    void emulator_output::add_data_point(uint32_t dp, uint32_t channel) {
        if(vector_size!=1){
            auto message = "Attempted to add a single value to an output vector";
            spdlog::critical(message);
            throw std::runtime_error(message);
        }
        data[channel][0].push_back(dp);
    }

    void emulator_output::repeat_last_data_point() {
        for(auto & item : data){
            for(int n = 0; n<vector_size; n++){
                item.second[n].push_back(item.second[n].back());
            }
        }

    }

    std::map<std::string, std::vector<std::vector<float>>> emulator_output::get_float_data() {
        std::map<std::string, std::vector<std::vector<float>>>  ret_val;
        for(int i = 0; i<data.size(); i++){
            ret_val[std::to_string(i)] =  std::vector<std::vector<float>>();
            for(const auto &vect:data[i]){
                std::vector<float> ds;
                for(const auto &item:vect){
                    ds.push_back(emulator_backend::uint32_to_float(item));
                }
                ret_val[std::to_string(i)].push_back(ds);
            }
        }

        return ret_val;
    }

    std::map<std::string, std::vector<std::vector<uint32_t>>> emulator_output::get_integer_data() {
        std::map<std::string, std::vector<std::vector<uint32_t>>>  ret_val;
        for(int i = 0; i<data.size(); i++){
            ret_val[std::to_string(i)] = data[i];
        }
        return ret_val;
    }

}