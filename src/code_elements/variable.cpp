//
// Created by fils on 11/06/20.
//

#include "variable.hpp"


variable::variable() {
    identifier = 0;
    name = "invalid-variable";
    constant = false;
    used = false;
    type = TYPE_REGULAR;
}

variable::variable(bool const_status, std::string text) {
    identifier = std::hash<std::string>{}(text);
    name = std::move(text);
    constant = const_status;
    used = false;
    type = TYPE_REGULAR;
}

void variable::set_used(bool status) {
    used = status;
}

void variable::set_type(int var_type) {
    type = var_type;
}

bool variable::is_used() const {
    return used;
}

uint32_t variable::get_value() const {
    if(fcore_registers.count(name)){
        return fcore_registers[name];
    }else if(constant){
        return std::stoi(name, nullptr, 0);
    }
    throw std::runtime_error("Invalid operation: the compiler tried to get the numeric value of a variable");
}
