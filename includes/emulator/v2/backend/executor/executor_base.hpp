//  Copyright 2025 Filippo Savi <filssavi@gmail.com>
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

#ifndef FCORE_TOOLCHAIN_EXECUTOR_BASE_HPP
#define FCORE_TOOLCHAIN_EXECUTOR_BASE_HPP

namespace fcore {
    class executor_base{
    public:
        virtual uint32_t execute_add(uint32_t a, uint32_t b){ return 0;}
        virtual uint32_t execute_sub(uint32_t a, uint32_t b){ return 0;}
        virtual uint32_t execute_mul(uint32_t a, uint32_t b){ return 0;}
        virtual uint32_t execute_rec(uint32_t a){ return 0;}
        virtual uint32_t execute_fti(uint32_t a){ return 0;}
        virtual uint32_t execute_itf(uint32_t a){ return 0;}
    private:
    };
}


#endif //FCORE_TOOLCHAIN_EXECUTOR_BASE_HPP