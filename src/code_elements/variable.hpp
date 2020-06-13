//
// Created by fils on 11/06/20.
//

#ifndef FCORE_HAS_VARIABLE_HPP
#define FCORE_HAS_VARIABLE_HPP

#include <cstdint>
#include <string>
#include <utility>
#include "../../include/fCore_isa.hpp"

class variable {
public:
    variable();
    variable(bool const_status, std::string text);
    static bool is_terminal() { return true;};
    [[nodiscard]] bool is_constant() const { return constant;};
    [[nodiscard]] unsigned int get_identifier() const {return identifier;};
    void set_used(bool status);
    [[nodiscard]] bool is_used() const;
    [[nodiscard]] std::string to_str() const { return name;};
    [[nodiscard]] uint32_t get_value() const;
private:
    unsigned int identifier;
    std::string name;
    bool constant;
    bool used;
};


#endif //FCORE_HAS_VARIABLE_HPP
