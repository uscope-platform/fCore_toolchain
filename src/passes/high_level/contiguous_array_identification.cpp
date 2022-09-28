// Copyright 2022 Filippo Savi <filssavi@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.05/07/2021.
//

#include "passes/high_level/contiguous_array_identification.hpp"

contiguous_array_identification::contiguous_array_identification() : pass_base<hl_ast_node>("contiguous_array_identification"){
}

std::shared_ptr<hl_ast_node> contiguous_array_identification::process_leaf(std::shared_ptr<hl_ast_node> element) {
    return element;
}
