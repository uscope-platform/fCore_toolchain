//
// Created by fils on 01/05/20.
//

#include "loop_implementation_pass.hpp"








std::shared_ptr<code_element> loop_implementation_pass::process_element_enter(std::shared_ptr<code_element> element) {
    bool unroll_mode = false;
    std::vector<std::shared_ptr<code_element>> loop_content;
    if(element->type == type_for_block){
        std::vector<std::shared_ptr<code_element>> test = element->get_content();
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
            if(end_obj.condition == "<=")
                loop_end_val--;
            else if(end_obj.condition == ">=")
                loop_end_val++;
            std::vector<std::shared_ptr<code_element>> new_loop_content;
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
            element->set_content(new_loop_content);
        } else{
            throw std::runtime_error("Standard loop are not supported yet");
        }

    }

    return element;
}


std::shared_ptr<code_element> loop_implementation_pass::process_element_exit(std::shared_ptr<code_element> element) {

    return element;
}

std::shared_ptr<code_element> loop_implementation_pass::deep_copy_element(std::shared_ptr<code_element> element) {
    code_element copied_elem;
    if(element->has_content()){
        std::vector<std::shared_ptr<code_element>> childs;
        for(auto &item:element->get_content()){
            childs.push_back(deep_copy_element(item));
        }
        copied_elem.set_content(childs);
    }
    copied_elem.type = element->type;
    copied_elem.loop = element->loop;
    copied_elem.inst = element->inst;
    copied_elem.directive = element->directive;

    return std::make_shared<code_element>(copied_elem);
}
