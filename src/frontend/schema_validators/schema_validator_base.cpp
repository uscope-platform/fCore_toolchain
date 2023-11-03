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


#include "frontend/schema_validators/schema_validator_base.h"

schema_validator_base::schema_validator_base(const std::string& schema_file) {
    std::string schemas_path = SCHEMAS_FOLDER;
    std::string full_schema_path = schemas_path  + "/" + schema_file;
    if(!std::filesystem::exists(full_schema_path)){
        std::string err_msg = "JSON schema file not found: " + full_schema_path;
        spdlog::critical(err_msg);
        throw std::invalid_argument(err_msg);
    }

    nlohmann::json chosen_schema_doc;
    if (!valijson::utils::loadDocument(full_schema_path, chosen_schema_doc)) {
        throw std::runtime_error("Failed to load schema document");
    }

     schema;
    valijson::SchemaParser parser;
    valijson::adapters::NlohmannJsonAdapter schema_adapter(chosen_schema_doc);
    parser.populateSchema(schema_adapter, schema);


}


void schema_validator_base::validate(nlohmann::json &spec_file) {
    valijson::Validator validator;
    valijson::ValidationResults results;
    valijson::adapters::NlohmannJsonAdapter myTargetAdapter(spec_file);
    if (!validator.validate(schema, myTargetAdapter, &results)) {
        valijson::ValidationResults::Error err;
        unsigned int errorNum = 1;
        while (results.popError(err)) {

            std::string context;
            auto itr = err.context.begin();
            for (; itr != err.context.end(); itr++) {
                context += *itr;
            }

            std::cerr << "Error #" << errorNum << std::endl
                      << "  context: " << context << std::endl
                      << "  desc:    " << err.description << std::endl;
            ++errorNum;
        }
        throw std::invalid_argument("");
    }
}
