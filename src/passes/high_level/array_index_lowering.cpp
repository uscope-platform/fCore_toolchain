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


#include "passes/high_level/array_index_lowering.hpp"

array_index_lowering::array_index_lowering() : pass_base<hl_ast_node>("array index lowering"){

}

std::shared_ptr<hl_ast_node> array_index_lowering::process_leaf(std::shared_ptr<hl_ast_node> element) {
    std::shared_ptr<hl_ast_node> ret_val = element;
    if(element->node_type==hl_ast_node_type_operand){
        std::shared_ptr<hl_ast_operand> op = std::static_pointer_cast<hl_ast_operand>(element);
        if(op->get_type()==var_type_array){
            int i = 0;
        }
    }
    return ret_val;
}
