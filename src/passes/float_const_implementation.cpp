//
// Created by fils on 15/06/20.
//

#include "float_const_implementation.hpp"

#include <utility>

float_const_implementation::float_const_implementation(std::shared_ptr<variable_map> var_map) {
    vmap = std::move(var_map);
}

ast_t float_const_implementation::process_leaf(ast_t element) {
    bool float_present = false;
    std::shared_ptr<code_element> new_element;
    if(element->type == type_instr){
        instruction_t current_instr = element->inst.getStringInstr();
        for(auto &item:current_instr.arguments){
           if(item->is_float()){
               float_present = true;
               double desired_constant = std::stof(item->to_str());
               std::vector<int> fract = rationalize_constant(desired_constant);
               new_element = create_block(fract,current_instr.arguments);
           }
        }
    }
    if(float_present)
        return new_element;
    else
        return element;
}

std::shared_ptr<code_element> float_const_implementation::create_block(std::vector<int> frac, std::vector<std::shared_ptr<variable>> op_args) {
     std::shared_ptr<code_element> container = std::make_shared<code_element>(type_code_block);

    //ADD CONSTANT TO VARIABLE MAP
    for(auto item:frac){
        if(!vmap->count(std::to_string(item))){
            std::shared_ptr<variable> var = std::make_shared<variable>(true,std::to_string(item));
            vmap->insert(std::to_string(item),var);
        }
    }

    std::vector<std::shared_ptr<code_element>> block_content;

    //CREATE FRACT NUMERATOR MULTIPLICATION
    std::vector<std::shared_ptr<variable>>  mul_fract_args = {op_args[0], vmap->at(std::to_string(frac[1])), op_args[2]};
    instruction mul_fract_instr = instruction(ALU_IMMEDIATE_INSTRUCTION, "muli", mul_fract_args);
    std::shared_ptr<code_element> mul_fract = std::make_shared<code_element>(type_instr, mul_fract_instr);
    block_content.push_back(mul_fract);

    //CREATE FRACT NUMERATOR DIVISION
    std::vector<std::shared_ptr<variable>> shift_args = {op_args[2], vmap->at(std::to_string(frac[2])), op_args[2]};
    instruction shift_instr = instruction(ALU_IMMEDIATE_INSTRUCTION, "sari", shift_args);
    std::shared_ptr<code_element> shift = std::make_shared<code_element>(type_instr, shift_instr);
    block_content.push_back(shift);


    //CREATE INTEGER PART MULTIPLICATION IF NECESSARY
    if(frac[0]!=0){
        std::cout<<"multiplication by an immediate constant greater than 1 will require the use of an intermediate register"<<std::endl;
        std::cout<<"use the feature sparingly until lifetime tracking register allocation is implemented."<<std::endl;

        std::string target_var = "frac_impl"+std::to_string(rand()%100);
        std::shared_ptr<variable> var = std::make_shared<variable>(false,target_var);
        vmap->insert(target_var,var);

        std::vector<std::shared_ptr<variable>>  mul_int_args = {op_args[0], vmap->at(std::to_string(frac[0])), var};
        instruction mul_int_instr = instruction(ALU_IMMEDIATE_INSTRUCTION, "muli", mul_int_args);
        std::shared_ptr<code_element> mul_int = std::make_shared<code_element>(type_instr, mul_int_instr);
        block_content.push_back(mul_int);

        std::vector<std::shared_ptr<variable>>  final_add_args = {var, op_args[2], op_args[2]};
        instruction  final_add_instr = instruction(REGISTER_INSTRUCTION, "add", final_add_args);
        std::shared_ptr<code_element> final_add = std::make_shared<code_element>(type_instr, final_add_instr);
        block_content.push_back(final_add);
    }



    container->set_content(block_content);
    return container;
}

std::vector<int> float_const_implementation::rationalize_constant(double desired_constant) {
    double fractpart, intpart_d;
    fractpart = modf (desired_constant , &intpart_d);
    int intpart = (int) round(intpart_d);
    int den = (int) round(pow(2, MAX_ALLOWABLE_SHIFT));
    int num = (int) round(fractpart*den);
    double fitted_constant = (double)num/den;
    double error = (intpart+fitted_constant-desired_constant)/desired_constant*100;
    std::cout <<"The desired constant: "<< desired_constant <<" has been approximated with the following fraction ";
    std::cout<< num << "/"<< den<<"="<<intpart+fitted_constant <<  std::setprecision(2)<< " with a percentage error of: "<< error <<"%"<<std::endl;
    std::cout<< std::setprecision(5);
    std::vector<int> ret_val = {intpart, num, MAX_ALLOWABLE_SHIFT};
    return ret_val;
}



