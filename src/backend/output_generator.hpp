//
// Created by fils on 30/04/20.
//

#ifndef FCORE_HAS_OUTPUT_GENERATOR_HPP
#define FCORE_HAS_OUTPUT_GENERATOR_HPP

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "../code_elements/code_element.hpp"
class output_generator {

public:
    explicit output_generator(const ast_t &AST, bool debug_print);
    void emit_program(ast_t &sub_program, bool debug_print);
    std::vector<uint32_t> get_raw_program();
    int get_program_size();
    void write_hex_file(const std::string& filename);
    void write_mem_file(const std::string& filename);
    std::vector<uint32_t> generate_hex(bool endian_swap);
    std::vector<std::string> generate_mem();
private:
    ast_t program;
    std::vector<uint32_t> raw_program;
    int progress_counter;
    static inline uint16_t Reverse16(uint16_t value)
    {
        return (((value & 0x00FFu) << 8u) |
                ((value & 0xFF00u) >> 8u));
    }

    static inline uint32_t Reverse32(uint32_t value)
    {
        return (((value & 0x000000FFu) << 24u) |
                ((value & 0x0000FF00u) <<  8u) |
                ((value & 0x00FF0000u) >>  8u) |
                ((value & 0xFF000000u) >> 24u));
    }
};


#endif //FCORE_HAS_OUTPUT_GENERATOR_HPP
