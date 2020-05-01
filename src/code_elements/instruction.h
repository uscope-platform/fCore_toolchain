//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_INSTRUCTION_H
#define FCORE_HAS_INSTRUCTION_H


#include <cstdint>
#include "code_element.hpp"

class instruction : public code_element{

    public:
        virtual uint32_t emit();
        virtual void print();
        bool is_terminal() override { return true;};
};


#endif //FCORE_HAS_INSTRUCTION_H
