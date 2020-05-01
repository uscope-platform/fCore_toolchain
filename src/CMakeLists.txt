
add_executable(fCore_has main.cpp code_elements/instruction.cpp code_elements/instruction.h
        code_elements/immediate_instruction.cpp code_elements/immediate_instruction.h code_elements/register_operating_instruction.cpp
        code_elements/register_operating_instruction.h frontend/Tree_visitor.cpp frontend/Tree_visitor.hpp ../include/fCore_isa.hpp
        code_elements/independent_instruction.cpp code_elements/independent_instruction.hpp frontend/file_parser.cpp frontend/file_parser.h backend/output_writer.cpp backend/output_writer.hpp code_elements/code_element.cpp code_elements/code_element.hpp passes/pass_manager.cpp passes/pass_manager.hpp passes/loop_implementation_pass.cpp passes/loop_implementation_pass.hpp code_elements/for_loop.cpp code_elements/for_loop.hpp passes/passes.hpp)

target_link_libraries(fCore_has fs_parser)
target_link_libraries(fCore_has antlr4)