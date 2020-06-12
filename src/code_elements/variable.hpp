//
// Created by fils on 11/06/20.
//

#ifndef FCORE_HAS_VARIABLE_HPP
#define FCORE_HAS_VARIABLE_HPP

#include <cstdint>
#include <string>

class variable {
public:
    variable();
    variable(bool const_status, std::string text);
    static bool is_terminal() { return true;};
    [[nodiscard]] bool is_constant() const { return constant;};
    [[nodiscard]] unsigned int get_identifier() const {return identifier;};
    void set_used(bool status);
    bool is_used() const;
private:
    unsigned int identifier;
    std::string name;
    bool constant;
    bool used;
};


#endif //FCORE_HAS_VARIABLE_HPP
