
add_executable(fCore_has main.cpp code_elements/instruction.cpp code_elements/instruction.h
         frontend/Tree_visitor.cpp frontend/Tree_visitor.hpp ../include/fCore_isa.hpp
         frontend/file_parser.cpp frontend/file_parser.h backend/output_writer.cpp backend/output_writer.hpp
        code_elements/code_element.cpp code_elements/code_element.hpp passes/pass_manager.cpp passes/pass_manager.hpp
        passes/loop_implementation_pass.cpp passes/loop_implementation_pass.hpp
        code_elements/for_loop.cpp code_elements/for_loop.hpp passes/passes.hpp passes/pseudo_instructions_pass.cpp passes/pseudo_instructions_pass.hpp passes/instruction_counting_pass.cpp passes/instruction_counting_pass.hpp code_elements/variable.cpp code_elements/variable.hpp)

target_link_libraries(fCore_has fs_parser)
target_link_libraries(fCore_has antlr4)