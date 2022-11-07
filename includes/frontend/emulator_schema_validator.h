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

#ifndef FCORE_TOOLCHAIN_EMULATOR_SCHEMA_VALIDATOR_H
#define FCORE_TOOLCHAIN_EMULATOR_SCHEMA_VALIDATOR_H

#include <string>
#include <fstream>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>


class emulator_error_handler : public nlohmann::json_schema::basic_error_handler {
    void error(const nlohmann::json::json_pointer &ptr, const nlohmann::json &instance, const std::string &message) override {
        nlohmann::json_schema::basic_error_handler::error(ptr, instance, message);
        error_ptr = ptr;
        error_instance = instance;
        error_message = message;
    }
public:
    nlohmann::json::json_pointer error_ptr;
    nlohmann::json error_instance;
    std::string error_message;
};


class emulator_schema_validator {
    public:
        emulator_schema_validator();
        void validate(nlohmann::json &spec_file);
    private:
        nlohmann::json schema;
        emulator_error_handler err;
        std::string error;
};


#endif //FCORE_TOOLCHAIN_EMULATOR_SCHEMA_VALIDATOR_H
