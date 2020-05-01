//
// Created by fils on 01/05/20.
//

#ifndef FCORE_HAS_FOR_LOOP_HPP
#define FCORE_HAS_FOR_LOOP_HPP

#include "code_element.hpp"
#include <string>



class for_loop : public code_element{

public:
    for_loop(element_type_t block_type, std::shared_ptr<code_element>parent_element);
    bool is_terminal() override { return false;};
    void set_loop_start(loop_start_t start) override;
    void set_loop_end(loop_end_t end) override;
    void set_advance(loop_advance_t adv) override;
    loop_start_t get_loop_start() override;
    loop_end_t get_loop_end() override;
    loop_advance_t get_advance() override;
private:
    loop_start_t loop_start;
    loop_end_t end_condition{};
    loop_advance_t loop_advance{};
};


#endif //FCORE_HAS_FOR_LOOP_HPP
