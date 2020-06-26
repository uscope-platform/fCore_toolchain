//
// Created by fils on 26/06/2020.
//

#include "load_intercalation_pass.hpp"

ast_t load_intercalation_pass::process_leaf(ast_t element) {
    std::shared_ptr<code_element> container = std::make_shared<code_element>(type_code_block);



    bool float_present = false;
    if(element->type == type_instr){
        instruction_t current_instr = element->inst.getStringInstr();
        if(current_instr.opcode == "ldc"){
            float desired_constant = std::stof(current_instr.arguments[1]->to_str());

            std::vector<std::shared_ptr<code_element>> block_content;

            //CREATE FRACT NUMERATOR MULTIPLICATION
            instruction constant_inst = instruction(INTERCALATED_CONSTANT,desired_constant);
            std::shared_ptr<code_element> load_inst = std::make_shared<code_element>(type_instr, element->inst);
            std::shared_ptr<code_element> constant = std::make_shared<code_element>(type_instr, constant_inst);
            block_content.push_back(load_inst);
            block_content.push_back(constant);


            container->set_content(block_content);
            return container;
        }

    }
    return element;

}
