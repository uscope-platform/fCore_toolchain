//
// Created by fils on 01/05/20.
//

#include "loop_implementation_pass.hpp"

std::vector<ast_t> loop_implementation_pass::process_node(ast_t element) {
    bool unroll_mode = false;
    std::vector<ast_t> loop_content;
    std::vector<ast_t> new_loop_content;
    if(element->type == type_for_block){
        std::vector<ast_t> test = element->get_content();
        for(auto & item:element->get_content()){
            if(item->type == type_pragma)
                unroll_mode =  item->directive.get_directive() == "unroll";
            else{
                loop_content.push_back(item);
            }
        }
        if(unroll_mode){
            int loop_idx = 0;

            loop_end_t end_obj = element->loop.get_loop_end();
            int loop_end_val = end_obj.end_count;
            loop_advance_t advance = element->loop.get_advance();
            if(end_obj.condition == "<=" | end_obj.condition == ">=")
                loop_end_val--;

            if(advance.direction){

                for(loop_idx=element->loop.get_loop_start().starting_value; loop_idx<loop_end_val; loop_idx++){
                    for(auto&item:loop_content){
                        new_loop_content.push_back(item);
                    }
                }

            } else{
                for(loop_idx=element->loop.get_loop_start().starting_value; loop_idx>loop_end_val; loop_idx--){
                    for(auto&item:loop_content){
                        new_loop_content.push_back(item);
                    }
                }
            }
        } else{
            throw std::runtime_error("Standard loop are not supported yet");
        }

    } else{
        new_loop_content.push_back(element);
    }

    return new_loop_content;
}

