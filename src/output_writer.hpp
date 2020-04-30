//
// Created by fils on 30/04/20.
//

#ifndef FCORE_HAS_OUTPUT_WRITER_HPP
#define FCORE_HAS_OUTPUT_WRITER_HPP

#include <string>
#include <vector>
#include <fstream>
class output_writer {

public:
    output_writer( const std::vector<uint32_t>&);
    void write_hex(const std::string& filename);
    void write_mem(const std::string& filename);
private:
    std::vector<uint32_t> program;
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
