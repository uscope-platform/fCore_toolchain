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


#include "passes/high_level/optimizations/visitor_passes/array_index_lowering.hpp"

namespace fcore{

    array_index_lowering::array_index_lowering() : pass_base("array index lowering"){

    }


    std::shared_ptr<hl_code_block> array_index_lowering::process_global(std::shared_ptr<hl_code_block> element, const std::vector<std::shared_ptr<hl_definition_node>> &globals) {

        hl_acting_visitor_operations ops;
        hl_acting_visitor visitor;

        ops.visit_operand = process_operand;

        return visitor.visit(ops, element);
    }


    std::shared_ptr<hl_ast_node> array_index_lowering::process_operand(const std::shared_ptr<hl_ast_operand> &op) {
        if(op->get_type()==var_type_array){
            std::vector<int> array_idx;
            for(auto&item:op->get_array_index()){
                auto idx_op = std::static_pointer_cast<hl_ast_operand>(item);
                array_idx.push_back(idx_op->get_int_value());
            }
            op->get_variable()->set_array_index(array_idx);
            op->set_array_index({});
        }
        return op;
    }
}
