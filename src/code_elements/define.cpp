//
// Created by fils on 29/06/2021.
//

#include "code_elements/define.h"

#include <utility>

define::define(int l, std::string n, std::string c) {
line = l;
name = std::move(n);
content = std::move(c);
}

bool operator==(const define &lhs, const define &rhs) {
    bool cond = lhs.name == rhs.name;
    cond &= lhs.line == rhs.line;
    cond &= lhs.content == rhs.content;
    return cond;
}
