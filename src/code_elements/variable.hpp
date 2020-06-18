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
    variable(bool const_status, std::string text, bool is_float);
    static bool is_terminal() { return true;};
    [[nodiscard]] bool is_constant() const { return constant;};
    [[nodiscard]] unsigned int get_identifier() const {return identifier;};
    void set_used(bool status);
    [[nodiscard]] bool is_used() const;
    [[nodiscard]] bool is_float() const {return float_const;};
    [[nodiscard]] std::string to_str() const { return name;};
    [[nodiscard]] uint32_t get_value() const;
    int type;
    unsigned int first_occurrence;
    unsigned int last_occurrence;

private:
    unsigned int identifier;
    std::string name;
    bool float_const;
    bool constant;
    bool used;
};


#endif //FCORE_HAS_VARIABLE_HPP
