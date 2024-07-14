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

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>

#include "emulator_test_helpers.hpp"
#include "emulator/emulator_manager.hpp"

using namespace fcore;

TEST(Emulator, emulator_executable_format) {

    std::ifstream ifs("emu/test_exec_format.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false, SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res_obj = nlohmann::json::parse(manager.get_results());

    std::vector<float>  result = std::vector<float>(res_obj["test"]["outputs"]["test_out"][0]);
    std::vector<float> reference = {58.62, 61.6};
    for(int i = 0; i<result.size(); ++i){
        ASSERT_FLOAT_EQ(result[i], reference[i]);
    }

}

TEST(Emulator, emulator_compile_error) {

    std::ifstream ifs("emu/test_exec_format_error.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);

    EXPECT_THROW({
        try{
            emulator_manager manager(specs, false, SCHEMAS_FOLDER);
            manager.process();
        }
        catch( const std::runtime_error& e ) {

         EXPECT_STREQ( "CORE test: Function UNDEFINED is not defined", e.what() );
         throw;
        }
    }, std::runtime_error );
}




TEST(Emulator, emulator_inputs) {


    auto program = "int main(){float input_1;float input_2;float internal = input_1 + input_2;float out =  internal + out;}";


    auto spec = prepare_spec(program, 2,
                             {}, {},{});


    spec["cores"][0]["efi_implementation"] = "efi_sort";
    spec["cores"][0]["input_data"] = std::vector<nlohmann::json>();
    spec["cores"][0]["input_data"].push_back(nlohmann::json());
    spec["cores"][0]["input_data"][0]["name"] = "data_file_1";
    spec["cores"][0]["input_data"][0]["data"] = nlohmann::json();
    spec["cores"][0]["input_data"][0]["data"]["input_1"] = {15.7,67.4};
    spec["cores"][0]["input_data"][0]["data"]["input_2"] = {42.92,-5.8};
    spec["cores"][0]["inputs"] = std::vector<nlohmann::json>();

    auto in = nlohmann::json();
    in["name"] = "input_1";
    in["type"] = "float";
    in["register_type"] = "scalar";
    in["reg_n"] = 1;
    in["source"] = nlohmann::json();
    in["source"]["type"] = "file";
    in["source"]["file"] = "data_file_1";
    in["source"]["series"] = "input_1";
    in["channel"] = 0;
    spec["cores"][0]["inputs"].push_back(in);

    in["name"] = "input_2";
    in["reg_n"] = 2;
    in["source"] = nlohmann::json();
    in["source"]["type"] = "file";
    in["source"]["file"] = "data_file_1";
    in["source"]["series"] = "input_2";
    spec["cores"][0]["inputs"].push_back(in);

    auto MEM = nlohmann::json();
    in["name"] = "out";
    in["type"] = "float";
    in["reg_n"] = 4;
    in["is_output"] = true;
    in["value"] = 0;
    spec["cores"][0]["memory_init"].push_back(in);


    spec["cores"][0]["program"]["build_settings"]["io"]["inputs"].push_back("input_1");
    spec["cores"][0]["program"]["build_settings"]["io"]["inputs"].push_back("input_2");
    spec["cores"][0]["program"]["build_settings"]["io"]["memories"].push_back("out");


    emulator_manager manager(spec, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);

    ASSERT_EQ(result->at(63), 0x42f070a4);

}

TEST(Emulator, emulator_outputs) {

    std::ifstream ifs("emu/test_inputs_spec.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test"];

    std::vector<float> reference = {58.6199989, 120.220001};
    std::vector<float> test_out = res["outputs"]["test_out"][0];
    ASSERT_EQ(test_out, reference);

}

TEST(Emulator, emulator_inteconnect) {

    std::ifstream ifs("emu/test_interconnect_spec.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test_consumer"];

    auto s = res.dump();
    std::vector<uint32_t> reference = {0x426a7ae1, 0x42f070a4};
    ASSERT_EQ(res["outputs"]["consumer_out"][0], reference);

}

TEST(Emulator, emulator_compilation) {

    std::ifstream ifs("emu/test_compilation.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test"];

    std::vector<uint32_t> reference = {59,62};
    std::vector<uint32_t> result = res["outputs"]["out"][0];
    ASSERT_EQ(result, reference);
}

TEST(Emulator, emulator_compilation_interconnect) {

    std::ifstream ifs("emu/test_compilation_interconnect.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results());

    std::vector<uint32_t> reference = {59,62};
    std::vector<uint32_t> result = res["test"]["outputs"]["out"][0];
    ASSERT_EQ(result, reference);
    reference = {60,63};
    std::vector<uint32_t> result2 = res["test_move"]["outputs"]["out"][0];
    ASSERT_EQ(result2, reference);
}


TEST(Emulator, emulator_compilation_memory) {

    std::ifstream ifs("emu/test_compilation_memory.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();
    auto res = nlohmann::json::parse(manager.get_results())["test"];

    std::vector<uint32_t> reference = {15,83};
    std::vector<uint32_t> result = res["outputs"]["out"][0];
    ASSERT_EQ(result, reference);
}


TEST(Emulator, emulator_multichannel) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
    "cores": [
        {
            "order": 0,
            "id": "test",
            "channels":4,
            "options":{
                "comparators": "full",
                "efi_implementation":"none"
            },
            "sampling_frequency":1,
            "input_data":[],
            "inputs":[
                {
                    "name": "input_1",
                    "type": "float",
                    "reg_n": 3,
                    "channel":[0,1,2,3],
                    "register_type": "scalar",
                    "source":{
                        "type": "constant",
                        "value": [31.2, 32.7, 62.1, 64.0]
                    }
                },
                {
                    "name": "input_2",
                    "type": "float",
                    "reg_n": 4,
                    "channel":[0,1,2,3],
                    "register_type": "scalar",
                    "source":{
                        "type": "constant",
                        "value": [4.0, 2.0, 6.0, 12.0]
                    }
                }
            ],
            "outputs":[
                {
                    "name":"out",
                    "type":"float",
                    "reg_n":5,
                    "register_type":"scalar"
                }
            ],
            "memory_init":[],
            "program": {
                "content": "int main(){float input_1;float input_2;float out = input_1 + input_2;}",
                "build_settings":{
                    "io":{
                        "inputs":["input_1", "input_2"],
                        "outputs":["out"],
                        "memories":[]
                    }
                }
            }
        }
    ],
    "interconnect": [],
    "emulation_time": 2
})");


    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();

    auto res_obj = nlohmann::json::parse(manager.get_results());
    std::vector<float> res = res_obj["test"]["outputs"]["out"][0];
    ASSERT_FLOAT_EQ(res[0], 35.2);
    ASSERT_FLOAT_EQ(res[1], 35.2);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"][1];
    ASSERT_FLOAT_EQ(res[0], 34.7);
    ASSERT_FLOAT_EQ(res[1], 34.7);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"][2];
    ASSERT_FLOAT_EQ(res[0], 68.1);
    ASSERT_FLOAT_EQ(res[1], 68.1);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"][3];
    ASSERT_FLOAT_EQ(res[0], 76.0);
    ASSERT_FLOAT_EQ(res[1], 76.0);
}



TEST(Emulator, emulator_multichannel_input_file) {


    nlohmann::json specs = nlohmann::json::parse(
            R"(
{
    "cores": [
        {
            "order": 0,
            "id": "test",
            "channels":4,
            "options":{
                "comparators": "full",
                "efi_implementation":"none"
            },
            "sampling_frequency":1,
            "input_data":[{
                "name": "test_data",
                    "data": {
                        "input_a": [
                            31.2,
                            31.3
                        ],
                        "input_b": [
                            32.7,
                            32.8
                        ],
                        "input_c":[
                            62.1,
                            62.2
                        ],
                        "input_d":[
                            64.0,
                            64.1
                        ]
                    }
            }],
            "inputs":[
                {
                    "name": "input_1",
                    "type": "float",
                    "reg_n": 3,
                    "channel":[0,1,2,3],
                    "register_type": "scalar",
                    "source":{
                        "type": "file",
                        "file": ["test_data", "test_data", "test_data", "test_data"],
                        "series": ["input_a", "input_b", "input_c", "input_d"]
                    }
                },
                {
                    "name": "input_2",
                    "type": "float",
                    "reg_n": 4,
                    "channel":[0,1,2,3],
                    "register_type": "scalar",
                    "source":{
                        "type": "constant",
                        "value": [4.0, 2.0, 6.0, 12.0]
                    }
                }
            ],
            "outputs":[
                {
                    "name":"out",
                    "type":"float",
                    "reg_n":5,
                    "register_type":"scalar"
                }
            ],
            "memory_init":[],
            "program": {
                "content": "int main(){float input_1;float input_2;float out = input_1 + input_2;}",
                "build_settings":{
                    "io":{
                        "inputs":["input_1", "input_2"],
                        "outputs":["out"],
                        "memories":[]
                    }
                }
            }
        }
    ],
    "interconnect": [],
    "emulation_time": 2
}
)");


    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();

    auto res_obj = nlohmann::json::parse(manager.get_results());
    std::vector<float> res = res_obj["test"]["outputs"]["out"][0];
    ASSERT_FLOAT_EQ(res[0], 35.2);
    ASSERT_FLOAT_EQ(res[1], 35.3);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"][1];
    ASSERT_FLOAT_EQ(res[0], 34.7);
    ASSERT_FLOAT_EQ(res[1], 34.8);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"][2];
    ASSERT_FLOAT_EQ(res[0], 68.1);
    ASSERT_FLOAT_EQ(res[1], 68.2);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"][3];
    ASSERT_FLOAT_EQ(res[0], 76.0);
    ASSERT_FLOAT_EQ(res[1], 76.1);
}




TEST(Emulator, emulator_multichannel_gather_transfer) {


    nlohmann::json specs = nlohmann::json::parse(
            R"(
{
    "cores": [
        {
            "order": 0,
            "id": "test_producer",
            "channels":2,
            "options":{
                "comparators": "full",
                "efi_implementation":"none"
            },
            "sampling_frequency":1,
            "input_data":[],
            "inputs":[
                {
                    "name": "input_1",
                    "type": "float",
                    "reg_n": 3,
                    "channel":[0,1,2,3],
                    "register_type": "scalar",
                    "source":{"type": "constant","value": [31.2, 32.7]}
                },
                {
                    "name": "input_2",
                    "type": "float",
                    "reg_n": 4,
                    "channel":[0,1,2,3],
                    "register_type": "scalar",
                    "source":{"type": "constant","value": [31.2, 32.7]}
                }
            ],
            "outputs":[ { "name":"out", "type":"float", "reg_n":5, "register_type":"scalar"}],
            "memory_init":[],
            "program": {
                "content": "int main(){float input_1;float input_2;float out = input_1 + input_2;}",
                "build_settings":{"io":{"inputs":["input_1", "input_2"],"outputs":["out"],"memories":[]}}
            }
        },
{
            "order": 1,
            "id": "test_reducer",
            "channels":1,
            "options":{
                "comparators": "full",
                "efi_implementation":"none"
            },
            "sampling_frequency":1,
            "input_data":[],
            "inputs":[],
            "outputs":[ { "name":"out", "type":"float", "reg_n":5, "register_type":"scalar"}],
            "memory_init":[],
            "program": {
                "content": "int main(){float input_data[2];float out = input_data[0] + input_data[1];}",
                "build_settings":{"io":{"inputs":["input_1", "input_2"],"outputs":["out"],"memories":[]}}
            }
        }
    ],
    "interconnect": [
        {
            "source": "test_producer",
            "destination": "test_reducer",
            "channels": [
                {
                    "name": "test_channel",
                    "type": "gather_transfer",
                    "source": {
                        "channel": 0,
                        "register": 5
                    },
                    "source_output": "out",
                    "destination": {
                        "channel": 0,
                        "register": 1
                    },
                    "destination_input": "input_data",
                    "length": 2
                }
            ]
        }
],
    "emulation_time": 1
})");


    emulator_manager manager(specs, false,SCHEMAS_FOLDER);
    manager.process();
    manager.emulate();

    auto res_obj = nlohmann::json::parse(manager.get_results());
    auto dbg = res_obj.dump();
    std::vector<float> res = res_obj["test_producer"]["outputs"]["out"][0];
    ASSERT_FLOAT_EQ(res[0], 62.4);
    res = (std::vector<float>) res_obj["test_producer"]["outputs"]["out"][1];
    ASSERT_FLOAT_EQ(res[0], 65.4);
    res = (std::vector<float>) res_obj["test_reducer"]["outputs"]["out"][0];
    ASSERT_FLOAT_EQ(res[0], 127.8);
}


TEST(Emulator, emulator_multichannel_scatter_transfer) {


}