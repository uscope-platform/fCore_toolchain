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

#ifndef FCORE_TOOLCHAIN_SCHEMA_VALIDATOR_BASE_H
#define FCORE_TOOLCHAIN_SCHEMA_VALIDATOR_BASE_H

#include <string>
#include <nlohmann/json.hpp>

#include <valijson/adapters/nlohmann_json_adapter.hpp>
#include <valijson/utils/nlohmann_json_utils.hpp>
#include <valijson/schema.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>

#include "schemas/v1/compiler_schema.hpp"
#include "schemas/v1/emulator_schema.hpp"

#include "schemas/v2/compiler_schema.hpp"
#include "schemas/v2/emulator_schema.hpp"

namespace fcore{

    typedef enum{
        emulator_input=1,
        compiler_input=2
    }json_type;

    class schema_validator_base {
    public:
        schema_validator_base(const json_type& schema_file, int version );
        void validate(const nlohmann::json &spec_file);
    private:
        valijson::Schema schema;
        std::string error;
        std::string schema_name;
    };
}




#endif //FCORE_TOOLCHAIN_SCHEMA_VALIDATOR_BASE_H
