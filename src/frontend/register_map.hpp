//
// Created by fils on 18/06/20.
//

#ifndef FCORE_HAS_REGISTER_MAP_HPP
#define FCORE_HAS_REGISTER_MAP_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define N_REGISTERS 16

typedef struct{
    int start;
    int end;
} range_t;

class register_map {
public:
    register_map();
    bool is_used(int reg, int from_inst, int to_inst);
    void insert(const std::string& identifier,int reg, int from_inst, int to_inst);
private:

    std::vector<std::vector<range_t>> reg_map;
};


#endif //FCORE_HAS_REGISTER_MAP_HPP
