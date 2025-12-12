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

#include "fcore_cc.hpp"

using namespace fcore;

TEST(runtime_analysis, simple_program) {

std::vector<std::string> file_content = {R""""(

        int main(){
              float out[2] = {15.6, 17.2};
        }
    )""""};

std::vector<std::string> include_content;

std::map<std::string, core_iom> dma_map;
dma_map["out"] = {core_iom_output, {5,6}};

fcore_cc compiler(file_content, include_content);
compiler.enable_logging();
compiler.set_dma_map(dma_map);

compiler.compile();
auto exec = compiler.get_executable();

std::vector<uint32_t> reference_program = {
        0x60003,
        0xc,
        0x10005,
        0x20006,
        0xc,
        0xc,
        0x26,
        0x4179999a,
        0x46,
        0x4189999a,
        0x0,
        0xc
    };

    ASSERT_EQ(exec.size(), 12);
    ASSERT_EQ(exec, reference_program);


    auto info = compiler.get_program_info();
    ASSERT_EQ(info.fixed_portion, 9);
    ASSERT_EQ(info.per_channel_portion, 2);
}
