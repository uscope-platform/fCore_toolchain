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

#ifndef FCORE_TOOLCHAIN_REST_HANDLER_HPP
#define FCORE_TOOLCHAIN_REST_HANDLER_HPP

#include "cpprest/http_listener.h"
#include "fcore_cc.hpp"


class rest_handler {
public:
    void handle_get(const web::http::http_request& message);
    void handle_post(const web::http::http_request& message);
    bool exit_requested = false;
private:
    web::json::value get_request_body(const web::http::http_request& message);
    void handle_compile_request(std::string file_path);
};


#endif //FCORE_TOOLCHAIN_REST_HANDLER_HPP
