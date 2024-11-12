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
    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();
    auto res_obj = manager.get_results();

    std::vector<float>  result = std::vector<float>(res_obj["test"]["outputs"]["test_out"]["0"][0]);
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
            emulator_manager manager(specs, false);
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

    in["metadata"] = nlohmann::json();
    in["metadata"]["type"] = "float";
    in["metadata"]["width"] = 12;
    in["metadata"]["signed"] = true;
    in["metadata"]["common_io"] = false;
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
    in["metadata"]["type"] = "float";
    in["metadata"]["width"] = 12;
    in["metadata"]["signed"] = true;
    in["reg_n"] = 4;
    in["is_output"] = true;
    in["value"] = 0;
    spec["cores"][0]["memory_init"].push_back(in);


    spec["cores"][0]["program"]["build_settings"]["io"]["inputs"].push_back("input_1");
    spec["cores"][0]["program"]["build_settings"]["io"]["inputs"].push_back("input_2");
    spec["cores"][0]["program"]["build_settings"]["io"]["memories"].push_back("out");

    emulator_manager manager(spec, false);
    manager.process();
    manager.emulate();
    auto result = manager.get_memory_snapshot("test", 0);

    ASSERT_EQ(result->at(63), 0x42f070a4);

}

TEST(Emulator, emulator_outputs) {

    std::ifstream ifs("emu/test_inputs_spec.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();
    auto res = manager.get_results()["test"];

    std::vector<float> reference = {58.6199989, 120.220001};
    std::vector<float> test_out = res["outputs"]["test_out"]["0"][0];
    ASSERT_EQ(test_out, reference);

}

TEST(Emulator, emulator_inteconnect) {

    std::ifstream ifs("emu/test_interconnect_spec.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();
    auto res = manager.get_results()["test_consumer"];

    std::vector<uint32_t> reference = {0x426a7ae1, 0x42f070a4};
    ASSERT_EQ(res["outputs"]["consumer_out"]["0"][0], reference);

}

TEST(Emulator, emulator_compilation) {

    std::ifstream ifs("emu/test_compilation.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();
    auto res = manager.get_results()["test"];

    std::vector<uint32_t> reference = {59,62};
    std::vector<uint32_t> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
}





TEST(Emulator, emulator_compilation_interconnect) {

    std::ifstream ifs("emu/test_compilation_interconnect.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();
    auto res = manager.get_results();

    std::vector<uint32_t> reference = {59,62};
    std::vector<uint32_t> result = res["test"]["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
    reference = {60,63};
    std::vector<uint32_t> result2 = res["test_move"]["outputs"]["out"]["0"][0];
    ASSERT_EQ(result2, reference);
}


TEST(Emulator, emulator_compilation_memory) {

    std::ifstream ifs("emu/test_compilation_memory.json");
    nlohmann::json specs = nlohmann::json::parse(ifs);
    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();
    auto res = manager.get_results()["test"];

    std::vector<uint32_t> reference = {15,83};
    std::vector<uint32_t> result = res["outputs"]["out"]["0"][0];
    ASSERT_EQ(result, reference);
}


TEST(Emulator, emulator_header) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
    "cores": [
        {
            "id": "test",
            "order": 0,
            "input_data": [],
            "inputs": [
                {
                    "name": "input_1",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "source": {
                        "type": "constant",
                        "value": [5]
                    },
                    "reg_n": 3,
                    "channel": [0]
                },
                {
                    "name": "input_2",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "source": {
                        "type": "constant",
                        "value": [4]
                    },
                    "reg_n": 4,
                    "channel": [0]
                }
            ],
            "outputs": [
                {
                    "name": "out",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false
                    },
                    "reg_n": [5]
                }
            ],
            "memory_init": [],
            "channels": 1,
            "options": {
                "comparators": "reducing",
                "efi_implementation": "none"
            },
            "program": {
                "content": "int main(){\n  float input_1;\n  float input_2;\n  float out = add(input_1, input_2);\n}",
                "build_settings": {
                    "io": {
                        "inputs": [
                            "input_1",
                            "input_2"
                        ],
                        "memories": [],
                        "outputs": [
                            "out"
                        ]
                    }
                },
                "headers": ["float add(float input_1, float input_2) {return input_1 + input_2;};"]
            },
            "sampling_frequency": 1,
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
            }
        }
    ],
    "interconnect": [],
    "emulation_time": 1,
    "deployment_mode": false
})");


    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    std::vector<float> res = res_obj["test"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 9.0);

}



TEST(Emulator, emulator_disassemble) {


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
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "reg_n": 3,
                    "channel":[0,1],
                    "source":{"type": "constant","value": [31.2, 32.7]}
                },
                {
                    "name": "input_2",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "reg_n": 4,
                    "channel":[0,1],
                    "source":{"type": "constant","value": [31.2, 32.7]}
                }
            ],
            "outputs":[
                {
                    "name":"out",
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false
                    },
                    "reg_n":[5]
                }
            ],
            "memory_init":[],
            "program": {
                "content": "int main(){\n  float input_1;\n  float input_2;\n  float out = input_1 + input_2;\n}",
                "build_settings":{"io":{"inputs":["input_1", "input_2"],"outputs":["out"],"memories":[]}},
                "headers": []
            },
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
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
            "outputs":[
                {
                    "name":"out",
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false
                    },
                    "reg_n":[5]
                }
            ],
            "memory_init":[],
            "program": {
                "content": "int main(){\n    float input_data[2];\n    float out = input_data[0] * input_data[1];\n}\n",
                "build_settings":{"io":{"inputs":["input_data", "input_data"],"outputs":["out"],"memories":[]}},
                "headers": []
            },
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
            }
        }
    ],
    "interconnect": [],
    "emulation_time": 1,
    "deployment_mode": false
})");


    emulator_manager manager(specs, false);
    auto res = manager.disassemble();
    std::unordered_map<std::string, std::string> expected = {
            {"test_producer", R"("///////////////////////////////////////////\n//               IO MAPPING              //\n//    io address <---> core address      //\n///////////////////////////////////////////\n//    5  <--->  3      //\n//    4  <--->  1      //\n//    3  <--->  2      //\n///////////////////////////////////////////\nadd r2, r1, r3\nstop\n")"},
            {"test_reducer", R"("///////////////////////////////////////////\n//               IO MAPPING              //\n//    io address <---> core address      //\n///////////////////////////////////////////\n//    5  <--->  3      //\n///////////////////////////////////////////\nmul r1, r2, r3\nstop\n")"}
    };

    EXPECT_EQ(res["test_producer"], res["test_producer"]);
    EXPECT_EQ(res["test_reducer"], res["test_reducer"]);

}

TEST(Emulator, emulator_multichannel) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
    "cores": [
        {
            "id": "test",
            "order": 0,
            "input_data": [],
            "inputs": [
                {
                    "name": "input_1",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io":false
                    },
                    "source": {
                        "type": "constant",
                        "value": [
                            31.2,
                            32.7,
                            62.1,
                            64
                        ]
                    },
                    "reg_n": 3,
                    "channel": [
                        0,
                        1,
                        2,
                        3
                    ]
                },
                {
                    "name": "input_2",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io":false
                    },
                    "source": {
                        "type": "constant",
                        "value": [
                            4,
                            2,
                            6,
                            12
                        ]
                    },
                    "reg_n": 4,
                    "channel": [
                        0,
                        1,
                        2,
                        3
                    ]
                }
            ],
            "outputs": [
                {
                    "name": "out",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false
                    },
                    "reg_n": [
                        5
                    ]
                }
            ],
            "memory_init": [],
            "channels": 4,
            "options": {
                "comparators": "reducing",
                "efi_implementation": "none"
            },
            "program": {
                "content": "int main(){\n  float input_1;\n  float input_2;\n  float out = input_1 + input_2;\n}",
                "build_settings": {
                    "io": {
                        "inputs": [
                            "input_1",
                            "input_2"
                        ],
                        "memories": [],
                        "outputs": [
                            "out"
                        ]
                    }
                },
                "headers": []
            },
            "sampling_frequency": 1,
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
            }
        }
    ],
    "interconnect": [],
    "emulation_time": 2,
    "deployment_mode": false
})");


    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    std::vector<float> res = res_obj["test"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 35.2);
    ASSERT_FLOAT_EQ(res[1], 35.2);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 34.7);
    ASSERT_FLOAT_EQ(res[1], 34.7);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["2"][0];
    ASSERT_FLOAT_EQ(res[0], 68.1);
    ASSERT_FLOAT_EQ(res[1], 68.1);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["3"][0];
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
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "reg_n": 3,
                    "channel":[0,1,2,3],
                    "source":{
                        "type": "file",
                        "file": ["test_data", "test_data", "test_data", "test_data"],
                        "series": ["input_a", "input_b", "input_c", "input_d"]
                    }
                },
                {
                    "name": "input_2",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "reg_n": 4,
                    "channel":[0,1,2,3],
                    "source":{
                        "type": "constant",
                        "value": [4.0, 2.0, 6.0, 12.0]
                    }
                }
            ],
            "outputs":[
                {
                    "name":"out",
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false
                    },
                    "reg_n":[5]
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
                },
                "headers": []
            },
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
            }
        }
    ],
    "interconnect": [],
    "emulation_time": 2,
    "deployment_mode": false
}
)");


    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();


    std::vector<float> res = res_obj["test"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 35.2);
    ASSERT_FLOAT_EQ(res[1], 35.3);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 34.7);
    ASSERT_FLOAT_EQ(res[1], 34.8);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["2"][0];
    ASSERT_FLOAT_EQ(res[0], 68.1);
    ASSERT_FLOAT_EQ(res[1], 68.2);
    res = (std::vector<float>) res_obj["test"]["outputs"]["out"]["3"][0];
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
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "reg_n": 3,
                    "channel":[0,1],
                    "source":{"type": "constant","value": [31.2, 32.7]}
                },
                {
                    "name": "input_2",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "reg_n": 4,
                    "channel":[0,1],
                    "source":{"type": "constant","value": [31.2, 32.7]}
                }
            ],
            "outputs":[
                {
                    "name":"out",
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false
                    },
                    "reg_n":[5]
                }
            ],
            "memory_init":[],
            "program": {
                "content": "int main(){\n  float input_1;\n  float input_2;\n  float out = input_1 + input_2;\n}",
                "build_settings":{"io":{"inputs":["input_data"],"outputs":["out"],"memories":[]}},
                "headers": []
            },
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
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
            "outputs":[
                {
                    "name":"out",
                    "metadata": {
                        "type": "float",
                        "width": 32,
                        "signed": false
                    },
                    "reg_n":[5]
                }
            ],
            "memory_init":[],
            "program": {
                "content": "int main(){\n    float input_data[2];\n    float out = input_data[0] + input_data[1];\n}\n",
                "build_settings":{"io":{"inputs":["input_1", "input_2"],"outputs":["out"],"memories":[]}},
                "headers": []
            },
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
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
    "emulation_time": 1,
    "deployment_mode": false
})");


    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    std::vector<float> res = res_obj["test_producer"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 62.4);
    res = (std::vector<float>) res_obj["test_producer"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 65.4);
    res = (std::vector<float>) res_obj["test_reducer"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 127.8);
}


TEST(Emulator, emulator_multichannel_scatter_transfer) {


    nlohmann::json specs = nlohmann::json::parse(
            R"(
    {
        "cores": [
            {
                "order": 0,
                "id": "test_producer",
                "channels":1,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "input_data":[],
                "inputs":[],
                "outputs":[],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float out[2] = {15.6, 17.2};\n}",
                    "build_settings":{"io":{"inputs":[],"outputs":["out"],"memories":[]}},
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            },
            {
                "order": 1,
                "id": "test_consumer",
                "channels":2,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "input_data":[],
                "inputs":[],
                "outputs":[
                    {
                        "name":"out",
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": false
                        },
                        "reg_n":[5]
                    }
                ],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float input;float out = input*3.5;\n}",
                    "build_settings":{"io":{"inputs":["input"],"outputs":["out"],"memories":[]}},
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            }
        ],
        "interconnect": [
            {
                "source": "test_producer",
                "destination": "test_consumer",
                "channels": [
                    {
                        "name": "test_channel",
                        "type": "scatter_transfer",
                        "source": {
                            "channel": 0,
                            "register": 5
                        },
                        "source_output": "out",
                        "destination": {
                            "channel": 0,
                            "register": 1
                        },
                        "destination_input": "input",
                        "length": 2
                    }
                ]
            }
    ],
        "emulation_time": 1,
    "deployment_mode": false
    })");


    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    auto res = (std::vector<float>) res_obj["test_consumer"]["outputs"]["out"]["0"][0];

    ASSERT_FLOAT_EQ(res[0], 54.6);
    res = (std::vector<float>) res_obj["test_consumer"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 60.2);
}


TEST(Emulator, emulator_multichannel_transfer_error) {


    nlohmann::json specs = nlohmann::json::parse(
            R"(
    {
        "cores": [
            {
                "order": 0,
                "id": "test_producer",
                "channels":1,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "input_data":[],
                "inputs":[],
                "outputs":[
                    {
                        "name":"out",
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": false
                        },
                        "reg_n":[5,6]
                    }
                ],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float out[2] = {15.6, 17.2};\n}",
                    "build_settings":{"io":{"inputs":[],"outputs":["out"],"memories":[]}},
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            },
            {
                "order": 1,
                "id": "test_consumer",
                "channels":1,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "input_data":[],
                "inputs":[],
                "outputs":[
                    {
                        "name":"out",
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": false
                        },
                        "reg_n":[5]
                    }
                ],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float input;float out = input*3.5;\n}",
                    "build_settings":{"io":{"inputs":["input"],"outputs":["out"],"memories":[]}},
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            }
        ],
        "interconnect": [
            {
                "source": "test_producer",
                "destination": "test_consumer",
                "channels": [
                    {
                        "name": "test_channel",
                        "type": "scatter_transfer",
                        "source": {
                            "channel": 0,
                            "register": 5
                        },
                        "source_output": "out",
                        "destination": {
                            "channel": 0,
                            "register": 1
                        },
                        "destination_input": "input",
                        "length": 2
                    }
                ]
            }
    ],
        "emulation_time": 1,
    "deployment_mode": false
    })");


    emulator_manager manager(specs, false);
    manager.process();


    try {
        manager.emulate();
        FAIL();
    } catch( const std::runtime_error& err ) {
        std::string msg = err.what();
        // check exception
        EXPECT_EQ( "Attempted write to unavailable channel: 1 of core: test_consumer",  msg);
    }
}


TEST(Emulator, emulator_multichannel_vector_transfer) {
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
                        "metadata":{
                            "type": "float",
                            "width": 24,
                            "signed":false,
                            "common_io": false
                        },
                        "reg_n": 3,
                        "channel":[0,1],
                        "source":{"type": "constant","value": [31.2, 32.7]}
                    },
                    {
                        "name": "input_2",
                        "metadata":{
                            "type": "float",
                            "width": 24,
                            "signed":false,
                            "common_io": false
                        },
                        "reg_n": 4,
                        "channel":[0,1],
                        "source":{"type": "constant","value": [31.2, 32.7]}
                    }
                ],
                "outputs":[],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float input_1;\n  float input_2;\n  float out = input_1 + input_2;\n}",
                    "build_settings":{"io":{"inputs":["input_1", "input_2"],"outputs":["out"],"memories":[]}},
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            },
            {
                "order": 1,
                "id": "test_consumer",
                "channels":2,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "input_data":[],
                "inputs":[],
                "outputs":[
                    {
                        "name":"out",
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": false
                        },
                        "reg_n":[7]
                    }
                ],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float input;float out = input*3.5;\n}",
                    "build_settings":{"io":{"inputs":["input"],"outputs":["out"],"memories":[]}},
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            }
        ],
        "interconnect": [
            {
                "source": "test_producer",
                "destination": "test_consumer",
                "channels": [
                    {
                        "name": "test_channel",
                        "type": "vector_transfer",
                        "source": {
                            "channel": 0,
                            "register": 5
                        },
                        "source_output": "out",
                        "destination": {
                            "channel": 0,
                            "register": 1
                        },
                        "destination_input": "input",
                        "length": 2
                    }
                ]
            }
        ],
        "emulation_time": 1,
    "deployment_mode": false
    })");


    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    auto res = (std::vector<float>) res_obj["test_consumer"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 218.4);
    res = (std::vector<float>) res_obj["test_consumer"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res[0], 228.9);

}


TEST(Emulator, emulator_multichannel_2d_vector_transfer) {
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
                "inputs":[],
                "outputs":[],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float out[2] = {15.6, 17.2};\n}",
                    "build_settings":{"io":{"inputs":[],"outputs":["out"],"memories":[]}},
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            },
            {
                "order": 1,
                "id": "test_consumer",
                "channels":2,
                "options":{
                    "comparators": "full",
                    "efi_implementation":"none"
                },
                "sampling_frequency":1,
                "input_data":[],
                "inputs":[],
                "outputs":[
                    {
                        "name":"consumer_out",
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": false
                        },
                        "reg_n":[7,8]
                    }
                ],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float input[2]; \n  float consumer_out[2]; \n  consumer_out[0] = input[0]*3.5; \n  consumer_out[1] = input[1]*3.5;\n}",
                    "build_settings":{"io":{"inputs":["input"],"outputs":["consumer_out"],"memories":[]}},
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            }
        ],
        "interconnect": [
            {
                "source": "test_producer",
                "destination": "test_consumer",
                "channels": [
                    {
                        "name": "test_channel",
                        "type": "2d_vector_transfer",
                        "source": {
                            "channel": 0,
                            "register": [5,6]
                        },
                        "source_output": "out",
                        "destination": {
                            "channel": 0,
                            "register": [1,2]
                        },
                        "destination_input": "input",
                        "length": 2,
                        "stride": 2
                    }
                ]
            }
        ],
        "emulation_time": 2,
    "deployment_mode": false
    })");


    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();


    std::vector<float> res = res_obj["test_consumer"]["outputs"]["consumer_out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 54.6);
    ASSERT_FLOAT_EQ(res[1], 54.6);
    std::vector<float> res2 = (std::vector<float>) res_obj["test_consumer"]["outputs"]["consumer_out"]["0"][1];
    ASSERT_FLOAT_EQ(res2[0], 60.2);
    ASSERT_FLOAT_EQ(res2[1], 60.2);
    std::vector<float> res3 = (std::vector<float>) res_obj["test_consumer"]["outputs"]["consumer_out"]["1"][0];
    ASSERT_FLOAT_EQ(res3[0], 54.6);
    ASSERT_FLOAT_EQ(res3[1], 54.6);
    std::vector<float> res4 = (std::vector<float>) res_obj["test_consumer"]["outputs"]["consumer_out"]["1"][1];
    ASSERT_FLOAT_EQ(res4[0], 60.2);
    ASSERT_FLOAT_EQ(res4[1], 60.2);
}



TEST(Emulator, emulator_common_io) {


    nlohmann::json specs = nlohmann::json::parse(
            R"({
    "cores": [
        {
            "id": "test",
            "order": 0,
            "input_data": [],
            "inputs": [
                {
                    "name": "a",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": true
                    },
                    "source": {
                        "type": "constant",
                        "value": [5]
                    },
                    "reg_n": 3,
                    "channel": [0]
                },
                {
                    "name": "b",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false,
                        "common_io": false
                    },
                    "source": {
                        "type": "constant",
                        "value": [1]
                    },
                    "reg_n": 4,
                    "channel": [0]
                }
            ],
            "outputs": [
                {
                    "name": "c",
                    "metadata":{
                        "type": "float",
                        "width": 24,
                        "signed":false
                    },
                    "reg_n": [5]
                }
            ],
            "memory_init": [],
            "channels": 1,
            "options": {
                "comparators": "reducing",
                "efi_implementation": "none"
            },
            "program": {
                "content": "int main(){float a, b;float c = a + b;}",
                "build_settings": {
                    "io": {
                        "inputs": [
                            "a",
                            "b"
                        ],
                        "memories": [],
                        "outputs": [
                            "c"
                        ]
                    }
                },
                "headers": ["float add(float input_1, float input_2) {return input_1 + input_2;};"]
            },
            "sampling_frequency": 1,
            "deployment": {
                "has_reciprocal": false,
                "control_address": 18316525568,
                "rom_address": 17179869184
            }
        }
    ],
    "interconnect": [],
    "emulation_time": 1,
    "deployment_mode": false
})");


    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();

    std::vector<float> res = res_obj["test"]["outputs"]["c"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 6.0);

}

TEST(Emulator, emulator_multichannel_input) {
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
                        "name": "a",
                        "metadata":{
                            "type": "float",
                            "width": 24,
                            "signed":false,
                            "common_io": false
                        },
                        "source": {
                            "type": "constant",
                            "value": [5]
                        },
                        "reg_n": 3,
                        "channel": [0]
                    },
                    {
                        "name": "b",
                        "metadata":{
                            "type": "float",
                            "width": 24,
                            "signed":false,
                            "common_io": false
                        },
                        "source": {
                            "type": "constant",
                            "value": [1]
                        },
                        "reg_n": 4,
                        "channel": [0]
                    }
                ],
                "outputs":[
                    {
                        "name":"out",
                        "metadata": {
                            "type": "float",
                            "width": 32,
                            "signed": false
                        },
                        "reg_n":[7]
                    }
                ],
                "memory_init":[],
                "program": {
                    "content": "int main(){\n  float a,b,out; out = a + b;\n}",
                    "build_settings":{"io":{"inputs":["a", "b"],"outputs":["out"],"memories":[]}},
                    "headers": []
                },
                "deployment": {
                    "has_reciprocal": false,
                    "control_address": 18316525568,
                    "rom_address": 17179869184
                }
            }
        ],
        "interconnect": [],
        "emulation_time": 2,
    "deployment_mode": false
    })");


    emulator_manager manager(specs, false);
    manager.process();
    manager.emulate();

    auto res_obj = manager.get_results();


    std::vector<float> res = res_obj["test_producer"]["outputs"]["out"]["0"][0];
    ASSERT_FLOAT_EQ(res[0], 6);
    ASSERT_FLOAT_EQ(res[1], 6);
    std::vector<float> res2 = (std::vector<float>) res_obj["test_producer"]["outputs"]["out"]["1"][0];
    ASSERT_FLOAT_EQ(res2[0], 6);
    ASSERT_FLOAT_EQ(res2[1], 6);
}