//
// Created by fils on 11/06/20.
//

#ifndef FCORE_HAS_VARIABLE_HPP
#define FCORE_HAS_VARIABLE_HPP

#include <cstdint>
#include <string>
#include <utility>
#include "../../include/fCore_isa.hpp"

#define TYPE_INPUT 0
#define TYPE_OUTPUT 1
#define TYPE_REGULAR 2

class variable {
public:
    variable();
    variable(bool const_status, std::string text);
    static bool is_terminal() { return true;};
    [[nodiscard]] bool is_constant() const { return constant;};
    [[nodiscard]] unsigned int get_identifier() const {return identifier;};
    void set_used(bool status);
    void set_type(int var_type);
    [[nodiscard]] bool is_used() const;
    [[nodiscard]] std::string to_str() const { return name;};
    [[nodiscard]] uint32_t get_value() const;
    int type;

private:
    unsigned int identifier;
    std::string name;
    bool constant;
    bool used;
};


#endif //FCORE_HAS_VARIABLE_HPP
