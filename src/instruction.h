//
// Created by fils on 29/04/20.
//

#ifndef FCORE_HAS_INSTRUCTION_H
#define FCORE_HAS_INSTRUCTION_H


#include <cstdint>

class instruction {

    public:
        virtual uint32_t emit();
        virtual void print();

};


#endif //FCORE_HAS_INSTRUCTION_H
