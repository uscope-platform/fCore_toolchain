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

#include "dev_server/rest_handler.hpp"

void rest_handler::handle_get(const web::http::http_request& message) {

    auto ep = message.relative_uri().to_string();

    message.reply(web::http::status_codes::OK);

}

void rest_handler::handle_post(const web::http::http_request& message) {

    auto ep = message.relative_uri().to_string();

    auto body = get_request_body(message);

    message.reply(web::http::status_codes::OK);
}

void rest_handler::handle_compile_request(std::string file_path) {
    std::vector<std::string> include_files = {""};
    fcore_cc cc_engine(file_path, include_files, false, 2);

}

web::json::value rest_handler::get_request_body(const web::http::http_request& message) {
    web::json::value jsonObject;
    try{
        message.extract_json()
                .then([&jsonObject](web::json::value jo){
                    std::cout<<"Val:"<<jo.serialize() << std::endl;
                    jsonObject = jo;
                })
                .wait();
    }
    catch (const std::exception & e) {
        printf("Error exception:%s\n", e.what());
    }
    return jsonObject;
}
