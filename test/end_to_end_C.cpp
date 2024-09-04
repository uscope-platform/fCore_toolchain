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
#include "data_structures/instruction_stream/instruction_stream.hpp"

using namespace fcore;

TEST(EndToEndC, fcore_cc) {

    std::vector<std::string> file_content = {R""""(
    int main(){
        int a = 4.0*5.0+6.0;
        // b = 1.0*2.0+7.0;
    }
    )""""};

    std::vector<std::string> includes;

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_output, {10}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result = compiler.get_executable();

    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x1000a, 0xc, 0xc, 0x26, 1104150528, 0xc};
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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_output, {10}};
    
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result = compiler.get_executable();

    std::vector<uint32_t> gold_standard = {0x70002, 0xc, 0x1000A, 0xc, 0xc, 0x1024,0x46,0x42C80000, 0x61030, 0x1033, 0x2f836, 0xc};
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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["v_cells"] = {core_iom_input, {59}};
    dma_map["v_arms"] = {core_iom_output, {60,61}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_output, {10}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    compiler.write_json(test_json);

    nlohmann::json out;
    std::ifstream check_stream(test_json);

    check_stream >> out;

    std::vector<uint32_t> compile_result = out["compiled_program"];

    std::vector<uint32_t> gold_standard = {0x70002, 0xc, 0x1000A, 0xc, 0xc, 0x1024,0x46,0x42C80000, 0x61030, 0x1033, 0x2f836, 0xc};

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
    

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_memory, {1}};
    dma_map["b"] = {core_iom_input, {2}};
    dma_map["c"] = {core_iom_memory, {4}};
    dma_map["test"] = {core_iom_output, {10}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x80005, 0xc, 0x3e0001,0x10002, 0x3f0004, 0x3000A, 0xc, 0xc, 0x7e0fc1, 0x26, 0x40A00000, 0x40fe3, 0x26, 0x3e2aaaab, 0x60843, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["test"] = {core_iom_output, {7}};

    
    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x10007, 0xc, 0xc, 0x26, 0x40C00000, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["h"] = {core_iom_input, {1,2,3,4}};
    dma_map["k"] = {core_iom_input, {5,6,7,8}};
    dma_map["b"] = {core_iom_output, {9,10,11,12}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30007, 0xc, 0x30003, 0x10004, 0x20007,0x40008,  0x5000B, 0x2000c, 0xc, 0xc, 0xa1061, 0x42021, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["h"] = {core_iom_input, {1,2,3,4}};
    dma_map["a"] = {core_iom_input, {5,6,7,8}};
    dma_map["c"] = {core_iom_output, {9,10,11,12}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = { 0x50007, 0xc, 0x30003, 0x10004,0x20005, 0x40006, 0x5000B, 0x3000c, 0xc, 0xc, 0xa1061, 0xa2061, 0x61021, 0x62021, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["c"] = {core_iom_output, {7}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50002, 0xc,0x20007, 0xc, 0xc, 0x26, 0x41300000, 0x61023, 0x21063, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["c"] = {core_iom_output, {18}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x10012, 0xc, 0xc, 0x26, 0x40400000, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["c"] = {core_iom_output, {18}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x10012, 0xc, 0xc, 0x26, 0x40400000, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {4,7}};
    dma_map["b"] = {core_iom_output, {3}};
    dma_map["c"] = {core_iom_output, {8,9}};
    dma_map["d"] = {core_iom_memory, {10,11}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x60008, 0xc,0x30003,0x10004,0x20007,0x40008,0x50009,0x3e000A,0x3f000B,
                                           0xc, 0xc, 0x61021, 0x81021, 0xa1022, 0x7c1023, 0x7e1823, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {4,7}};
    dma_map["c"] = {core_iom_output, {8,9,10,11}};
    dma_map["d"] = {core_iom_memory, {12,13,16,18}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xA000B,  0xc, 0x10004, 0x20007, 0x40008, 0x60009, 0x5000A, 0x7000B,
                                           0x3d000C, 0x3E000D, 0x3c0010,0x3f0012,  0xc, 0xc, 0x61021, 0x81021, 0xa1022,
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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["c"] = {core_iom_output, {8,9,10,11}};
    dma_map["b"] = {core_iom_output, {20}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xb0006, 0xc, 0x10008, 0x20009, 0x3000A, 0x4000B, 0x50014, 0xc, 0xc, 0x26,0x3F800000,0x46, 0x40000000, 0x66, 0x40400000, 0x86, 0x40800000, 0xa6, 0x40800000, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {1}};
    dma_map["test"] = {core_iom_output, {10}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003, 0xc, 0x10001, 0x2000a, 0xc, 0xc, 0x4002e, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {1}};
    dma_map["b"] = {core_iom_input, {2}};
    dma_map["test"] = {core_iom_memory, {10}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x90004, 0xc, 0x20001,0x10002,0x3f000a, 0xc, 0xc, 0x66, 0x40A00000, 0x81821, 0x26, 0x41880000, 0x60843, 0x22063, 0x7e0fe1, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {1}};
    dma_map["test"] = {core_iom_memory, {10}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x40003, 0xc,0x10001,0x3f000a, 0xc, 0xc, 0x46, 0x41880000, 0x7e1023, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["test_in"] = {core_iom_input, {25}};
    dma_map["integ"] = {core_iom_memory, {6}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xF0003, 0xc,  0x3f0006, 0x10019, 0xc, 0xc, 0x46, 0x40A00000, 0x61023, 0x26,
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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["test_in"] = {core_iom_input, {25}};
    dma_map["test_out"] = {core_iom_output, {5}};
    dma_map["test_var"] = {core_iom_output, {7}};
    dma_map["factor_1"] = {core_iom_output, {6}};

    fcore_cc compiler(file_content, includes);
    compiler.set_dma_map(dma_map);
    compiler.enable_logging();
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();

    //TODO:test var viene caricato due volte
    std::vector<uint32_t> gold_standard = {0x80005, 0xc,0x10005,0x30006, 0x50007, 0x10019, 0xc, 0xc, 0x46, 0x3F800000,
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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {5}};
    dma_map["switching_cell"] = {core_iom_memory, {17,18}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50004, 0xc, 0x10005, 0x3e0011,0x3f0012,  0xc, 0xc,
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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {2}};
    dma_map["b"] = {core_iom_input, {3}};
    dma_map["c"] = {core_iom_output, {7}};


    std::vector<std::string> includes;

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30004, 0xc,0x20002,0x10003, 0x20007, 0xc, 0xc, 0x61002, 0x40863, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["b"] = {core_iom_input, {2}};
    dma_map["a"] = {core_iom_input, {1}};
    dma_map["c"] = {core_iom_output, {10}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = { 0x90004, 0xc,0x20001,  0x10002,0x3000A ,0xc, 0xc, 0x66, 4, 0x81823, 0x26, 2, 0x60843, 0x21881, 0x61021, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {10,11}};
    dma_map["b"] = {core_iom_output, {12,13}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50005, 0xc, 0x1000A,0x2000B,  0x4000C,  0x1000D, 0xc, 0xc, 0x66, 0x42340000,  0x81823, 0x21843, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {10}};
    dma_map["b"] = {core_iom_output, {12}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003, 0xc, 0x1000a, 0x2000c,0xc, 0xc, 0x40021, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["v_cells"] = {core_iom_input, {40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59}};
    dma_map["v_arms"] = {core_iom_output, {60,61}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70005, 0xc,0x20032,0x10033, 0x3003C, 0x5003d, 0xc,  0xc, 0x66, 0, 0x86, 0x0, 0xa1081, 0xa08a1, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["v_cells"] = {core_iom_input, {40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59}};
    dma_map["v_arms"] = {core_iom_output, {60,61}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70005, 0xc, 0x10031,0x20035, 0x3003c, 0x5003d, 0xc, 0xc, 0x66, 0, 0x86, 0x0, 0xa0881, 0xa10a1, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["c"] = {core_iom_input, {2}};
    dma_map["out_1"] = {core_iom_output, {7}};
    dma_map["out_2"] = {core_iom_output, {6}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x60004, 0xc,0x10002, 0x30006, 0x20007, 0xc, 0xc, 0x85855,0x40881, 0x26,0x2,0x608a1,0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["theta"] = {core_iom_input, {1}};
    dma_map["s_th"] = {core_iom_output, {15}};
    dma_map["c_th"] = {core_iom_output, {17}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xb0004, 0xc, 0x10001, 0x1000f, 0x20011,  0xc, 0xc, 0x6002e,
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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["theta"] = {core_iom_input, {1}};
    dma_map["s_th"] = {core_iom_output, {15}};
    dma_map["c_th"] = {core_iom_output, {17}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xF0004, 0xc, 0x10001, 0x2000f, 0x30011, 0xc, 0xc, 0x46, 0x0, 0x6002e, 0x81055,
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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["v_err"] = {core_iom_output, {2}};
    dma_map["v_err2"] = {core_iom_output, {3}};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50003, 0xC, 0x10002,0x20003,  0xC, 0xc, 0x26, 0x41700000, 0x46, 0xE, 0xC};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["dt"] = {core_iom_output, {5}};
    dma_map["dt2"] = {core_iom_output, {6}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x50003, 0xc,  0x10005,0x20006, 0xc, 0xc, 0x26, 0x37A7C5AC, 0x46, 0x2FDBE6FE ,0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["angle_test"] = {core_iom_output, {5}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x30002, 0xc, 0x10005,0xc, 0xc, 0x26, 0x43AC8622,0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["v_cap"] = {core_iom_memory, {63}};
    dma_map["v_cap_s"] = {core_iom_output, {22}};
    dma_map["v_out"] = {core_iom_output, {20}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70004, 0xc, 0x20014, 0x10016, 0x3F003F, 0xc, 0xc, 0x7e6, 0x4201999A, 0x26, 0x44EFA51D,  0x46, 2876 ,0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {3}};
    dma_map["c"] = {core_iom_output, {2}};


    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);

    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0xA0003, 0xc, 0x30002, 0x10003, 0xc, 0xc, 0x40028, 0x26, 0x43160000, 0x66,  0x43480000, 0x6085b, 0x26, 0x42000000,0x60842, 0xc};

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


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {3}};
    dma_map["b"] = {core_iom_input, {4}};
    dma_map["c"] = {core_iom_output, {2}};


    fcore_cc compiler(file_content, include_content);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);

    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20004, 0xc, 0x30002, 0x20003, 0x10004, 0xc, 0xc, 0x60841, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {3}};
    dma_map["b"] = {core_iom_output, {4}};

    fcore_cc compiler(file_content, include_content);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);

    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70003, 0xc, 0x10003, 0x20004, 0xc, 0xc, 0x40028, 0x26, 0x3f800000,0x66, 0xbf800000, 0x6085b, 0xc};

    ASSERT_EQ(gold_standard, result);

}

TEST(EndToEndC, common_io_space) {

    std::vector<std::string> file_content = {R""""(
        int main(){

            float a;
            float b;
            float c = a+b;
        }
    )""""};

    std::vector<std::string> includes;


    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {10}, true};
    dma_map["b"] = {core_iom_input, {12}, false};
    dma_map["c"] = {core_iom_output, {3}, false};

    fcore_cc compiler(file_content, includes);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map);
    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x20003, 0xc, 0x20003, 0x1000c, 0xc, 0x2000a, 0xc, 0x840841, 0xc};

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

    std::unordered_map<std::string, core_iom> dma_map;
    dma_map["a"] = {core_iom_input, {3}};
    dma_map["b"] = {core_iom_input, {4}};
    dma_map["c"] = {core_iom_memory, {5}};

    fcore_cc compiler(file_content, include_content);
    compiler.enable_logging();
    compiler.set_dma_map(dma_map)

    compiler.compile();
    std::vector<uint32_t> result =  compiler.get_executable();


    std::vector<uint32_t> gold_standard = {0x70003, 0xc, 0x10003, 0x20004, 0xc, 0x40028, 0x26, 0x3f800000,0x66, 0xbf800000, 0x6085b, 0xc};

    ASSERT_EQ(gold_standard, result);

}
 */