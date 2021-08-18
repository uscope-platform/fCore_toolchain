// Copyright (C) 2020 Filippo Savi - All Rights Reserved

// This file is part of fCore_toolchain.

// fCore_toolchain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License.

// fCore_toolchain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with fCore_toolchain.  If not, see <https://www.gnu.org/licenses/>.

#include "fcore_dis.hpp"

fcore_dis::fcore_dis(std::istream &input, disassembler_input_type_t in_type) {
    error_code = "";
    try{

        disassembler_testing dis(input, in_type);
        std::shared_ptr<ll_ast_node> ast = dis.get_ast();

    } catch(std::runtime_error &e){
        error_code = e.what();
        int i = 0;
    } catch (...) {
        throw std::runtime_error("OH SNAP!");
    }


}

std::string fcore_dis::get_errors() {
    return error_code;
}

void fcore_dis::write_json(const std::string &output_file) {

}
