// Copyright 2021 University of Nottingham Ningbo China
// Author: Filippo Savi <filssavi@gmail.com>
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

#include <fstream>

#include <gtest/gtest.h>
#include "fcore_cc.hpp"
#include "data_structures/instruction_stream.hpp"

using namespace fcore;

TEST(EndToEndC, fcore_cc) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        int a = 4.0*5.0+6.0;
        // b = 1.0*2.0+7.0;
    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result = compiler.get_executable();

    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x1000a, 0xc, 0x26, 1104150528, 0xc};
    ASSERT_EQ(result, gold_standard);
}

TEST(EndToEndC, end_to_end_intrinsics) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        float b = itf(a);
        float c = satp(a, 100.0);
        float d = popcnt(a);
        bset(a, r31, r1);
    }
    )""""};

    std::vector<std::string> includes;


    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result = compiler.get_executable();

    std::vector<uint32_t> gold_standard = {0x70002, 0xc, 0x1000A, 0xc, 0x1024,0x46,0x42C80000, 0x61030, 0x1033, 0x2f836, 0xc};
    ASSERT_EQ(result, gold_standard);
}

TEST(EndToEndC, exceptionHandling) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        float v_cells;
        float v_arms = 0;

        for(int i = 0; i<2; ++i){
            int idx_l = 10+i;
            v_arms += "v_cells[idx_l]";
        }
    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cells":{"type": "input","address":59},
                    "v_arms":{"type": "output","address":[60,61]}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::string result = compiler.get_errors();

    ASSERT_EQ(result, "Strings are not supported by the fCore toolchain");
}

TEST(EndToEndC, json_writing) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        float b = itf(a);
        float c = satp(a, 100.0);
        float d = popcnt(a);
        bset(a, r31, r1);
    }
    )""""};

    std::vector<std::string> includes;

    std::string test_json = "/tmp/e2e_c_json_test.json";

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    compiler.write_json(test_json);

    nlohmann::json out;
    std::ifstream check_stream(test_json);

    check_stream >> out;

    std::vector<uint32_t> compile_result = out["compiled_program"];

    std::vector<uint32_t> gold_standard = {0x70002, 0xc, 0x1000A, 0xc, 0x1024,0x46,0x42C80000, 0x61030, 0x1033, 0x2f836, 0xc};

    std::filesystem::remove(test_json);

    ASSERT_EQ(gold_standard, compile_result);
}

TEST(EndToEndC, iom) {

    std::vector<std::string> file_content = {R""""(
        int main(int arg1, float arg2){

            int a;
            int b;
            int c;

            c = a + b;

            int test = c*5.0/6.0;
        }
    )""""};

    std::vector<std::string> includes;


    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "memory","address":1},
                    "b":{"type": "input","address":2},
                    "c":{"type": "memory","address":4},
                    "test":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x80005, 0xc, 0x3e0001,0x10002, 0x3f0004, 0x3000A, 0xc, 0x7e0fc1, 0x26, 0x40A00000, 0x40fe3, 0x26, 0x3e2aaaab, 0x60843, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, conditional) {
    std::vector<std::string> file_content = {R""""(
    int main(){
        int i = 3.0;


        if( i == 0){
            int a = 2.0;
        } else
            int a = 3.0;

        int test  = i + a;
    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test":{"type": "output","address":7}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x10007, 0xc, 0x26, 0x40C00000, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, loop) {
    std::vector<std::string> file_content = {R""""(
        int add (int a, int b){
            return a+b;
        }

        int main(){

            int h[4];

            int k[4];
            int b[4];
            int j;
            #pragma output(j, r15);

            for(int i = 0+2; i+1<5; ++i){
                if(3<5){
                    b[i] = add(h[i], k[i]);
                }
            }
        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "h":{"type": "input","address":[1,2,3,4]},
                    "k":{"type": "input","address":[5,6,7,8]},
                    "b":{"type": "output","address":[9,10,11,12]}
                }})"
    );
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30007, 0xc, 0x30003, 0x10004, 0x20007,0x40008,  0x5000B, 0x2000c, 0xc, 0xa1061, 0x42021, 0xc};

   ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, nested_loop) {

    std::vector<std::string> file_content = {R""""(
        int add (int a, int b){
            return a+b;
        }

        int main(){
            int h[4];
            int a[4];
            int c[4];

            for(int i = 2; i<4; ++i)
                for(int x = 0; x<2; ++x){
                    c[i] = h[i] + a[x];
                }
        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "h":{"type": "input","address":[1,2,3,4]},
                    "a":{"type": "input","address":[5,6,7,8]},
                    "c":{"type": "output","address":[9,10,11,12]}
                }})"
    );
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = { 0x50007, 0xc, 0x30003, 0x10004,0x20005, 0x40006, 0x5000B, 0x3000c, 0xc, 0xa1061, 0xa2061, 0x61021, 0x62021, 0xc};

     ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_initialization) {
    std::vector<std::string> file_content = {R""""(
    int main(){
        float c;
        int a[2][2][3] = {
                {
                    {0.0, 1.0, 2.0},
                    {3.0, 4.0, 5.0}
                },
                {
                    {6.0, 7.0, 8.0},
                    {9.0, 10.0, 11.0}
                }
        };
        int b[2] = {2.0, 2.0};
        a[1][0][0] = a[1][1][2]*c;
        b[1] = a[1][0][0]*c;

    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":7}
                }})"
    );
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50002, 0xc,0x20007, 0xc,0x26, 0x41300000, 0x61023, 0x21063, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_initialization_through_function) {

    std::vector<std::string> file_content = {R""""(
        float add_first(float mem_1[2][2][3], float mem_2[7]){
            return mem_1[0][0][1] + mem_2[1];
        }


        int main(){
            int a[2][2][3] = {{{0.0, 1.0, 2.0}, {3.0, 4.0, 5.0}},{{6.0, 7.0, 8.0}, {9.0, 10.0, 11.0}}};
            int b[7] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};

            float c = add_first(a, b);
        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":18}
                }})"
    );
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x10012, 0xc, 0x26, 0x40400000, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, constant_argument_inlining) {
    std::vector<std::string> file_content = {R""""(
        float add_first(float mem_1[2][2][3], float mem_2[7], int i){
            return mem_1[0][0][i] + mem_2[i];
        }


        int main(){
            int a[2][2][3] = {
                    {
                        {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0}
                    },
                    {
                        {6.0, 7.0, 8.0}, {9.0, 10.0, 11.0}
                    }
            };
            int b[7] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};


            float c = add_first(a, b, 1);
        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":18}
                }})"
    );
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x10012, 0xc, 0x26, 0x40400000, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, array_io_definition) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        float a[2];
        float b = a[0] + a[1];
        float c[2];
        c[0] = a[0] + a[1];
        c[1] = a[0] - a[1];
        float d[2];
        d[0] = a[0] * a[1];
        d[1] = a[0] * b;
    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":[4,7]},
                    "b":{"type": "output","address":3},
                    "c":{"type": "output","address":[8,9]},
                    "d":{"type": "memory","address":[10,11]}
                }})"
    );
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x60008, 0xc,0x30003,0x10004,0x20007,0x40008,0x50009,0x3e000A,0x3f000B,
                                           0xc, 0x61021, 0x81021, 0xa1022, 0x7c1023, 0x7e1823, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, multidimensional_array_io_definition) {
    std::vector<std::string> includes;

    std::vector<std::string> file_content = {R""""(
    int main(){

        float a[2];
        float b = a[0] + a[1];
        float c[2][2];
        c[0][0] = a[0] + a[1];
        c[1][0] = a[0] - a[1];
        c[0][1] =  a[0] + a[1];
        c[1][1] = a[0] - a[1];
        float d[2][2];
        d[0][0] = a[0] * a[1];
        d[1][0] = a[0] * b;
        d[0][1] = a[0] * a[1];
        d[1][1] = a[0] * b;
    }
    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":[4,7]},
                    "c":{"type": "output","address":[8,9,10,11]},
                    "d":{"type": "memory","address":[12,13,16,18]}
                }})"
    );
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xA000B,  0xc, 0x10004, 0x20007, 0x40008, 0x60009, 0x5000A, 0x7000B,
                                           0x3d000C, 0x3E000D, 0x3c0010,0x3f0012,  0xc, 0x61021, 0x81021, 0xa1022,
                                           0xc1021, 0xe1022, 0x7a1023, 0x781823, 0x7c1023, 0x7e1823, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, iom_initialization){

    std::vector<std::string> includes;

    std::vector<std::string> file_content = {R""""(
    int main(){
        float c[2][2] = {{1.0,2.0},{3.0,4.0}};
        float b = c[0][0] + c[1][0];
    }
    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "output","address":[8,9,10,11]},
                    "b":{"type": "output","address":20}
                }})"
    );
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xb0006, 0xc, 0x10008, 0x20009, 0x3000A, 0x4000B, 0x50014, 0xc, 0x26,0x3F800000,0x46, 0x40000000, 0x66, 0x40400000, 0x86, 0x40800000, 0xa6, 0x40800000, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, test_move){

    std::vector<std::string> includes;

    std::vector<std::string> file_content = {R""""(
    int main(int arg1, float arg2){

        int a;
        int test = a;
    }
    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":1},
                    "test":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003, 0xc, 0x10001, 0x2000a, 0xc, 0x4002e, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, test_complex_normalization){

    std::vector<std::string> includes;

    std::vector<std::string> file_content = {R""""(
        int main(int arg1, float arg2){

            int a;
            int b;
            int test;

            test += a*17.0*(b+5.0);

        }
    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":1},
                    "b":{"type": "input","address":2},
                    "test":{"type": "memory","address":10}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x90004, 0xc, 0x20001,0x10002,0x3f000a, 0xc, 0x66, 0x40A00000, 0x81821, 0x26, 0x41880000, 0x60843, 0x22063, 0x7e0fe1, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, register_allocation){

    std::vector<std::string> includes;

    std::vector<std::string> file_content = {R""""(
    int main(){
        int a;

        int test = a*17.0;
    }
    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":1},
                    "test":{"type": "memory","address":10}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x40003, 0xc,0x10001,0x3f000a, 0xc, 0x46, 0x41880000, 0x7e1023, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, function_inlining_expression) {

    std::vector<std::string> includes;

    std::vector<std::string> file_content = {R""""(
        float integrate(float in, float Ts, float memory) {
            float out = memory+Ts*in;

            out = satn(out, -150.0);
            out = satp(out, 150.0);
            return out;
        }

        int main(){
            int test_in;
            float in_1 = 5.0;
            float integ;
            float test_out = integrate(test_in*in_1, 1e-5, integ);
            return 0;
        }
    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test_in":{"type": "input","address":25},
                    "integ":{"type": "memory","address":6}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xF0003, 0xc,  0x3f0006, 0x10019, 0xc, 0x46, 0x40A00000, 0x61023, 0x26,
                                           0x3727C5AC, 0x41823, 0x217e1, 0x46, 0xC3160000, 0x21031, 0x46,
                                           0x43160000, 0x21030, 0x4002e, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, essential_variable_initialization) {

    std::vector<std::string> includes;

    std::vector<std::string> file_content = {R""""(
    int main(){

        int test_in;

        float test_out;


        float test_var = 1.0;
        int factor_1 = test_var <= test_in;

        test_var=test_var+test_in;

        test_out = test_var;
        return 0;
    }
    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "test_in":{"type": "input","address":25},
                    "test_out":{"type": "output","address":5},
                    "test_var":{"type": "output","address":7},
                    "factor_1":{"type": "output","address":6}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.enable_logging();
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();

    //TODO:test var viene caricato due volte
    std::vector<uint32_t> gold_standard = {0x80005, 0xc,0x10005,0x30006, 0x50007, 0x10019, 0xc, 0x46, 0x3F800000,
                                           0x60849,0x86, 0x3F800000, 0xa0881, 0x200ae, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, test_constant_propagation) {

    std::vector<std::string> includes;

    std::vector<std::string> file_content = {R""""(
    int main(){
        int a;
        float switching_cell[2] = {1.0, 1.0};


        switching_cell[0]=switching_cell[0]+a;

        switching_cell[0] = 1.0;
        switching_cell[1] = 1.0;

        switching_cell[1]=switching_cell[1]+a;

    }
    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":5},
                    "switching_cell":{"type": "memory","address":[17,18]}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50004, 0xc, 0x10005, 0x3e0011,0x3f0012,  0xc,
                                           0x7a6,0x3F800000, 0x7c0fa1, 0x7e0fa1, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, negative_leading_sum) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        float a;
        float b;
        float c;

        c = -a*b;
    }
    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":2},
                    "b":{"type": "input","address":3},
                    "c":{"type": "output","address":7}
                }})"
            );
    std::vector<std::string> includes;

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30004, 0xc,0x20002,0x10003, 0x20007, 0xc, 0x61002, 0x40863, 0xc};

    ASSERT_EQ(gold_standard, result);
}

TEST(EndToEndC, function_vars_mangling) {

    std::vector<std::string> file_content = {R""""(
        int add(int in_1, int in_2){
            int a = in_1*4;
            int b = in_2*2;

            return a+b+in_2;
        }

        int main(){
            int a;
            int b;
            int c = add(b,a);

        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "b":{"type": "input","address":2},
                    "a":{"type": "input","address":1},
                    "c":{"type": "output","address":10}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = { 0x90004, 0xc,0x20001,  0x10002,0x3000A ,0xc, 0x66, 4, 0x81823, 0x26, 2, 0x60843, 0x21881, 0x61021, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, constant_merging) {

    std::vector<std::string> file_content = {R""""(
        int main(){

            float a[2];

            float b[2];

            float c = 45.0;
            for(int i =0; i<2; ++i){
                b[i] = a[i]*c;
            }


        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":[10,11]},
                    "b":{"type": "output","address":[12,13]}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50005, 0xc, 0x1000A,0x2000B,  0x4000C,  0x1000D, 0xc, 0x66, 0x42340000,  0x81823, 0x21843, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, zero_assignment_removal) {

    std::vector<std::string> file_content = {R""""(
        int main(){

            float a;
            float b;
            float c = 0;
            b= a+c;

        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"type": "input","address":10},
                    "b":{"type": "output","address":12}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003, 0xc, 0x1000a, 0x2000c,0xc,0x40021, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, loop_index_expression) {

    std::vector<std::string> file_content = {R""""(
        int main(){


            float v_cells[20];
            float v_arms[2] = {0.0, 0.0};


            v_arms[1] = 0.0;

            for(int i = 0; i<2; ++i){
                int idx_l = 10+i;
                v_arms[1] += v_cells[idx_l];
            }
        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cells":{"type": "input","address":[40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59]},
                    "v_arms":{"type": "output","address":[60,61]}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70005, 0xc,0x20032,0x10033, 0x3003C, 0x5003d, 0xc, 0x66, 0, 0x86, 0x0, 0xa1081, 0xa08a1, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, loop_index_expression_multidim) {

    std::vector<std::string> file_content = {R""""(
        int main(){

            float v_cells[5][4];
            float v_arms[2] = {0.0, 0.0};


            v_arms[1] = 0.0; // THESE ARE NOT WORKING WHEN THE LOOP IS USED

            for(int i = 0; i<2; ++i){
                int idx_l = 2+i;
                v_arms[1] += v_cells[idx_l][1];
            }
        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cells":{"type": "input","address":[40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59]},
                    "v_arms":{"type": "output","address":[60,61]}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70005, 0xc, 0x10031,0x20035, 0x3003c, 0x5003d, 0xc, 0x66, 0, 0x86, 0x0, 0xa0881, 0xa10a1, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, contiguos_array_allocation) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        float out_1;
        float out_2;

        float index[2];

        int c;
        int a[2];
        a = efi(index, 11);
        out_1 = a[0] + c;
        out_2 = a[1] + 2;
    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "c":{"type": "input","address":2},
                    "out_1":{"type": "output","address":7},
                    "out_2":{"type": "output","address":6}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x60004, 0xc,0x10002, 0x30006, 0x20007, 0xc, 0x85855,0x40881, 0x26,0x2,0x608a1,0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, efi_load_elimination) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        float theta;

        float s_th;
        float c_th;


        float trig_in[2];

        trig_in[1] = theta;
        trig_in[0] = 0;
        s_th = efi(trig_in, 2);
        s_th = 0.000030518*s_th;
        trig_in[0] = 1;
        c_th = efi(trig_in, 2);
    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "theta":{"type": "input","address":1},
                    "s_th":{"type": "output","address":15},
                    "c_th":{"type": "output","address":17}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xb0004, 0xc, 0x10001, 0x1000f, 0x20011,  0xc, 0x6002e,
                                           0x46, 0x0, 0x21055, 0x46,0x38000074,0x20843, 0x46, 0x1, 0x41055,0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, efi_load_elimination_in_func) {

    std::vector<std::string> file_content = {R""""(

        float sin(float theta){
            float efi_in[2];

            efi_in[0] = 0;
            efi_in[1] = theta;

            float sin_theta = efi(efi_in, 2);
            sin_theta = itf(sin_theta);
            sin_theta = 0.000030518*sin_theta;

            return sin_theta;
        }

        float cos(float theta){

            float efi_in[2];

            efi_in[0] = 1;
            efi_in[1] = theta;

            float cos_theta = efi(efi_in, 2);
            return cos_theta;
        }


        int main(){
            float theta;

            float s_th = sin(theta);
            float c_th = cos(theta);

        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "theta":{"type": "input","address":1},
                    "s_th":{"type": "output","address":15},
                    "c_th":{"type": "output","address":17}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xF0004, 0xc, 0x10001, 0x2000f, 0x30011, 0xc, 0x46, 0x0, 0x6002e, 0x81055,
                                           0x2084, 0x46,0x38000074, 0x82043, 0x4008e,
                                           0x66,1,0x8002e,0x21075, 0x6002e, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, constant_conversion) {

    std::vector<std::string> file_content = {R""""(
        int main(){

            float v_ref=15;
            float v_ref2=14.0;

            float v_err = itf(v_ref);
            float v_err2=fti(v_ref2);
            return 0;
        }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_err":{"type": "output","address":2},
                    "v_err2":{"type": "output","address":3}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50003, 0xC, 0x10002,0x20003,  0xC, 0x26, 0x41700000, 0x46, 0xE, 0xC};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, constant_squaring) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        float Ts  = 2e-5;

        float dt = Ts;
        float dt2 = Ts*Ts;
    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "dt":{"type": "output","address":5},
                    "dt2":{"type": "output","address":6}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50003, 0xc,  0x10005,0x20006, 0xc, 0x26, 0x37A7C5AC, 0x46, 0x2FDBE6FE ,0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, test_multiple_constant_op) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        float angle_n = 542.0;
        float angle_test = 4.0*angle_n*0.15915494309;
    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "angle_test":{"type": "output","address":5}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x10005,0xc, 0x26, 0x43AC8622,0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, test_constant_expression_output) {

    std::vector<std::string> file_content = {R""""(
    int main(){

        float v_cap = 32.4;
        float v_cap_s =v_cap*59.1715976331;

        float v_out = fti( v_cap_s*1.5);

    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "v_cap":{"address":[63],"type":"memory"},
                    "v_cap_s":{"address":[22],"type":"output"},
                    "v_out":{"address":[20],"type":"output"}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70004, 0xc, 0x20014, 0x10016, 0x3F003F, 0xc, 0x7e6, 0x4201999A, 0x26, 0x44EFA51D,  0x46, 2876 ,0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, test_ternary_operator) {

    std::vector<std::string> file_content = {R""""(
    int main(){

        float a;
        int test = a>0? 150.0: 200.0;
        float c = test - 32.0;
    }
    )""""};

    std::vector<std::string> includes;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"address":3,"type":"input"},
                    "c":{"address":2,"type":"output"}
                }})"
    );

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);

    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xA0003, 0xc, 0x30002, 0x10003, 0xc, 0x40028, 0x26, 0x43160000, 0x66,  0x43480000, 0x6085b, 0x26, 0x42000000,0x60842, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, test_include) {

    std::vector<std::string> file_content = {R""""(
        int main(){
            float a, b;
            float c = add(a,b);
        }
    )""""};

    std::vector<std::string> include_content = {R""""(
        float add_nested(float a, float b){
            return a + b;
        }


        float add(float a, float b){
            return add_nested(a, b);
        }

    )""""};

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"address":3,"type":"input"},
                    "b":{"address":4,"type":"input"},
                    "c":{"address":2,"type":"output"}
                }})"
    );

    fcore_cc compiler(file_content, include_content);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);

    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20004, 0xc, 0x30002, 0x20003, 0x10004, 0xc,  0x60841, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, test_ternary_return) {

    std::vector<std::string> file_content = {R""""(

        float sign(float in){
            return in>0.0 ? 1.0: -1.0;
        }

        int main(){
            float a;
            float b = sign(a);
        }
    )""""};

    std::vector<std::string> include_content;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"address":3,"type":"input"},
                    "b":{"address":4,"type":"output"}
                }})"
    );

    fcore_cc compiler(file_content, include_content);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);

    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70003, 0xc, 0x10003, 0x20004, 0xc, 0x40028, 0x26, 0x3f800000,0x66, 0xbf800000, 0x6085b, 0xc};

    ASSERT_EQ(gold_standard, result);

}


/*
TEST(EndToEndC, test_ternary_mem_self_assign) {

    std::vector<std::string> file_content = {R""""(

        int main(){
            float a;
            float b;
            float c;

                c = a>0.0 ? b : c ;
        }
    )""""};

    std::vector<std::string> include_content;

    nlohmann::json dma_map = nlohmann::json::parse(
            R"({"dma_io":{
                    "a":{"address":3,"type":"input"},
                    "b":{"address":4,"type":"input"},
                    "c":{"address":5,"type":"memory"}
                }})"
    );

    fcore_cc compiler(file_content, include_content);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map["dma_io"]);

    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70003, 0xc, 0x10003, 0x20004, 0xc, 0x40028, 0x26, 0x3f800000,0x66, 0xbf800000, 0x6085b, 0xc};

    ASSERT_EQ(gold_standard, result);

}
 */