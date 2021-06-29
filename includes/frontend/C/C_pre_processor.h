//
// Created by fils on 29/06/2021.
//

#ifndef FCORE_HAS_C_PRE_PROCESSOR_H
#define FCORE_HAS_C_PRE_PROCESSOR_H

#include <istream>
#include <iostream>
#include <sstream>
#include <regex>

#include "code_elements/variable.hpp"
#include "code_elements/define.h"
#include "frontend/variable_map.hpp"
#include "frontend/define_map.h"

class C_pre_processor {
public:
    explicit C_pre_processor(std::istream &file,std::shared_ptr<variable_map> new_varmap,  std::shared_ptr<define_map> defmap);
    std::string get_preprocessed_file();
private:
    void remove_comments();
    void process_pragmas();
    void process_define();

    std::string working_content;
    std::shared_ptr<variable_map> vmap;
    std::shared_ptr<define_map> dmap;
};


#endif //FCORE_HAS_C_PRE_PROCESSOR_H
