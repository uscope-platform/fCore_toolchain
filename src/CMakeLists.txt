
add_executable(fCore_has main.cpp instruction.cpp instruction.h
        immediate_instruction.cpp immediate_instruction.h register_operating_instruction.cpp
        register_operating_instruction.h Tree_visitor.cpp Tree_visitor.hpp ../include/fCore_isa.hpp
        independent_instruction.cpp independent_instruction.hpp file_parser.cpp file_parser.h output_writer.cpp output_writer.hpp code_element.cpp code_element.hpp)

target_link_libraries(fCore_has fs_parser)
target_link_libraries(fCore_has antlr4)