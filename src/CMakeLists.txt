set(FCORE_LIB_SRCS code_elements/instruction.cpp code_elements/instruction.h
        frontend/Tree_visitor.cpp frontend/Tree_visitor.hpp ../include/fCore_isa.hpp
        frontend/file_parser.cpp frontend/file_parser.h backend/output_generator.cpp backend/output_generator.hpp
        code_elements/code_element.cpp code_elements/code_element.hpp passes/pass_manager.cpp passes/pass_manager.hpp
        passes/loop_implementation_pass.cpp passes/loop_implementation_pass.hpp
        code_elements/for_loop.cpp code_elements/for_loop.hpp passes/passes.hpp passes/pseudo_instructions_pass.cpp
        passes/pseudo_instructions_pass.hpp passes/instruction_counting_pass.cpp passes/instruction_counting_pass.hpp
        code_elements/variable.cpp code_elements/variable.hpp passes/register_allocation_pass.cpp
        passes/register_allocation_pass.hpp frontend/variable_map.cpp frontend/variable_map.hpp
        passes/variable_lifetime_mapping.cpp passes/variable_lifetime_mapping.hpp
        frontend/register_map.cpp frontend/register_map.hpp passes/load_intercalation_pass.cpp
        passes/load_intercalation_pass.hpp fcore_has.cpp fcore_has.hpp frontend/ErrorHandling.cpp frontend/ErrorHandling.hpp)

add_library(fCore_lib ${FCORE_LIB_SRCS})


add_library(fCore_lib_so SHARED ${FCORE_LIB_SRCS})
set_property(TARGET fCore_lib_so PROPERTY POSITION_INDEPENDENT_CODE 1)

target_link_libraries(fCore_lib fs_parser)
target_link_libraries(fCore_lib antlr4)


add_executable(fCore_has main.cpp)
target_link_libraries(fCore_has fCore_lib)