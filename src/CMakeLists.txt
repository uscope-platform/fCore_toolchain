set(FCORE_LIB_SRCS code_elements/instruction.cpp ../includes/fcore_has/code_elements/instruction.h
        frontend/Tree_visitor.cpp ../includes/fcore_has/frontend/Tree_visitor.hpp ../includes/fcore_has/fCore_isa.hpp
        frontend/file_parser.cpp ../includes/fcore_has/frontend/file_parser.h backend/output_generator.cpp ../includes/fcore_has/backend/output_generator.hpp
        code_elements/code_element.cpp ../includes/fcore_has/code_elements/code_element.hpp passes/pass_manager.cpp ../includes/fcore_has/passes/pass_manager.hpp
        passes/loop_implementation_pass.cpp ../includes/fcore_has/passes/loop_implementation_pass.hpp
        code_elements/for_loop.cpp ../includes/fcore_has/code_elements/for_loop.hpp ../includes/fcore_has/passes/passes.hpp passes/pseudo_instructions_pass.cpp
        ../includes/fcore_has/passes/pseudo_instructions_pass.hpp passes/instruction_counting_pass.cpp ../includes/fcore_has/passes/instruction_counting_pass.hpp
        code_elements/variable.cpp ../includes/fcore_has/code_elements/variable.hpp passes/register_allocation_pass.cpp
        ../includes/fcore_has/passes/register_allocation_pass.hpp frontend/variable_map.cpp ../includes/fcore_has/frontend/variable_map.hpp
        passes/variable_lifetime_mapping.cpp ../includes/fcore_has/passes/variable_lifetime_mapping.hpp
        frontend/register_map.cpp ../includes/fcore_has/frontend/register_map.hpp passes/load_intercalation_pass.cpp
        ../includes/fcore_has/passes/load_intercalation_pass.hpp fcore_has.cpp ../includes/fcore_has/fcore_has.hpp frontend/ErrorHandling.cpp ../includes/fcore_has/frontend/ErrorHandling.hpp)

add_library(fCore_lib_internal ${FCORE_LIB_SRCS})

target_link_libraries(fCore_lib_internal fs_parser)


add_executable(fCore_has main.cpp)
target_link_libraries(fCore_has fCore_lib_internal)

#make shared library for use with uscope server


add_library(fchas SHARED ${FCORE_LIB_SRCS})
target_link_libraries(fchas fcparser)
set_property(TARGET fchas PROPERTY POSITION_INDEPENDENT_CODE 1)

install(TARGETS fchas
        LIBRARY DESTINATION /usr/local/lib/fcore_has)

install(DIRECTORY ../includes/fcore_has # source directory
        DESTINATION /usr/local/include # target directory
        FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
        )

pybind11_add_module(fCore_has_py  ${FCORE_LIB_SRCS})
target_link_libraries(fCore_has_py PRIVATE fcparser)
target_link_libraries(fCore_has_py PRIVATE antlr4-runtime)