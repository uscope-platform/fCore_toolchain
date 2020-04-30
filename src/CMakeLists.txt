
add_executable(fCore_has main.cpp frontend/instruction.cpp frontend/instruction.h
        frontend/immediate_instruction.cpp frontend/immediate_instruction.h frontend/register_operating_instruction.cpp
        frontend/register_operating_instruction.h frontend/Tree_visitor.cpp frontend/Tree_visitor.hpp ../include/fCore_isa.hpp
        frontend/independent_instruction.cpp frontend/independent_instruction.hpp file_parser.cpp file_parser.h backend/output_writer.cpp backend/output_writer.hpp frontend/code_element.cpp frontend/code_element.hpp)

target_link_libraries(fCore_has fs_parser)
target_link_libraries(fCore_has antlr4)