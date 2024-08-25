

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

#include "data_structures/instruction_stream/instruction_variant.hpp"

namespace fcore{

    uint32_t fcore::instruction_variant::emit() const {
        return std::visit([this](auto &var) -> uint32_t {
            return var.emit();
        }, content);

    }

    void fcore::instruction_variant::print() const{
        std::visit([](auto &var) -> void {
            var.print();
        }, content);
    }

    std::string fcore::instruction_variant::disassemble() const {
        return std::visit([](auto &var) -> std::string {
            return var.disassemble();
        }, content);
    }

    int fcore::instruction_variant::instruction_count() const{
        return std::visit([](auto &var) -> int {
            return var.instruction_count();
        }, content);
    }

    std::vector<std::shared_ptr<variable>> fcore::instruction_variant::get_arguments() {
        return std::visit([](auto &var) -> std::vector<std::shared_ptr<variable>> {
            return var.get_arguments();
        }, content);
    }
    std::vector<std::shared_ptr<variable>> instruction_variant::get_arguments() const {
        return std::visit([](auto &var) -> std::vector<std::shared_ptr<variable>> {
            return var.get_arguments();
        }, content);
    }

    nlohmann::json instruction_variant::dump() {
        return std::visit([](auto &var) -> nlohmann::json {
            return var.dump();
        }, content);
    }

    nlohmann::json instruction_variant::dump_instruction(instruction_variant &node) {
        return std::visit([](auto &var) -> nlohmann::json {
            return var.dump();
        }, node.content);
    }



}
