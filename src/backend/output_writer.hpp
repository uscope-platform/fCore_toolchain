//
// Created by fils on 30/04/20.
//

#ifndef FCORE_HAS_OUTPUT_WRITER_HPP
#define FCORE_HAS_OUTPUT_WRITER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "../code_elements/code_element.hpp"
class output_writer {

public:
    explicit output_writer( const std::shared_ptr<code_element> &AST);
    void emit_program(std::shared_ptr<code_element>& sub_program);
    std::vector<uint32_t> get_raw_program();
    void write_hex(const std::string& filename);
    void write_mem(const std::string& filename);
private:
    std::shared_ptr<code_element> program;
    std::vector<uint32_t> raw_program;
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


#endif //FCORE_HAS_OUTPUT_WRITER_HPP
