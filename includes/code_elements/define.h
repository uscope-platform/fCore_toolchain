//
// Created by fils on 29/06/2021.
//

#ifndef FCORE_HAS_DEFINE_H
#define FCORE_HAS_DEFINE_H

#include <string>

class define {
public:
    define(int l, std::string n, std::string c);
    friend bool operator==(const define& lhs, const define& rhs);
private:
    int line;
    std::string name;
    std::string content;
};


#endif //FCORE_HAS_DEFINE_H
