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

    auto ep = message.relative_uri().path();
    auto body = get_request_body(message);

    if(ep == "/dump"){
        message.reply(construct_response(web::http::status_codes::OK,to_string(dump)));
    } else {
        message.reply(construct_response(web::http::status_codes::InternalError,"Endpoint not found"));
    }

}

void rest_handler::handle_post(const web::http::http_request& message) {

    auto ep = message.relative_uri().path();
    auto body = get_request_body(message);

    std::string error = "Endpoint not found";
    web::http::status_code ret_code = web::http::status_codes::InternalError;
    if(ep == "/compile"){
        ret_code = handle_compile_request(body, error);
    }

    message.reply(construct_response(ret_code,error));
}

web::http::status_code rest_handler::handle_compile_request(const web::json::value &prog, std::string &error) {

    auto working_file = "/tmp/fcore_dev_server_wf";
    std::ofstream ofs(working_file);
    ofs << prog.at("content").as_string();
    ofs.flush();
    std::vector<std::string> include_files = {""};
    fcore_cc cc_engine(working_file, include_files, false, 2);
    error = cc_engine.get_errors();
    dump = cc_engine.get_dump();
    if(error.empty()){
        return web::http::status_codes::OK;
    }else{
        return web::http::status_codes::InternalError;
    }

}

web::json::value rest_handler::get_request_body(const web::http::http_request& message) {
    web::json::value jsonObject;
    try{
        message.extract_json()
                .then([&jsonObject](const web::json::value& jo){
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

web::http::http_response rest_handler::construct_response(const web::http::status_code &sc, const std::string &resp) {
    web::http::http_response response(sc);
    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    response.set_body(resp);
    return response;
}

void rest_handler::handle_option(const web::http::http_request &message) {
    web::http::http_response sp(web::http::status_codes::OK);
    sp.headers().add("Access-Control-Allow-Origin","*");
    sp.headers().add("Access-Control-Allow-Methods","*");
    sp.headers().add("Access-Control-Allow-Headers","*");
    sp.headers().add("Access-Control-Max-Age","6400");
    message.reply(sp);
}
