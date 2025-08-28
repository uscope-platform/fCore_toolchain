#   Copyright 2025 Filippo Savi <filssavi@gmail.com>
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.

import sys, json


print("Generating emulator schema v2")
schema_header_template = '''
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

#ifndef FCORE_TOOLCHAIN_EMULATOR_SCHEMA_V2_HPP
#define FCORE_TOOLCHAIN_EMULATOR_SCHEMA_V2_HPP


#include <string>


const std::string emulator_schema_v2 = R"~(
__SCHEMA_HERE__
)~";


#endif //FCORE_TOOLCHAIN_EMULATOR_SCHEMA_V2_HPP

'''

schemas_dir = sys.argv[1] + "/includes/schemas/v2/emulator"

with open(schemas_dir + "/emulator_spec_schema.json", "r") as f:
    schema_base = f.read()

with open(schemas_dir + "/cores_schema.json", "r") as f:
    cores_schema = f.read()

with open(schemas_dir + "/interconnect_schema.json", "r") as f:
    interconnect_schema = f.read()

with open(schemas_dir + "/core_input_schema.json", "r") as f:
    input_schema = f.read()


    schema_obj = json.loads(schema_base)
    schema_obj["$defs"]["cores"] = json.loads(cores_schema)
    schema_obj["$defs"]["input_source"] = json.loads(input_schema)
    schema_obj["$defs"]["interconnect"] = json.loads(interconnect_schema)
    schema_obj["properties"]["cores"] = {"$ref": "#/$defs/cores"}
    schema_obj["properties"]["interconnect"] = {"$ref": "#/$defs/interconnect"}

schema_string = schema_header_template.replace("__SCHEMA_HERE__", json.dumps(schema_obj, indent=4))
with(open(schemas_dir + "/emulator_schema_v2.hpp", "w")) as f:
    f.write(schema_string)
    f.close()