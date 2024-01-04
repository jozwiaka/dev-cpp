cmake_minimum_required(VERSION 3.16)
project(my_allocator LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(exe ${SOURCES})
target_include_directories(exe PUBLIC "include")

target_compile_options(exe PRIVATE -O2)
target_link_libraries(exe PRIVATE pthread)

enable_testing()
# include(CTest)

find_program(MEMORYCHECK_COMMAND valgrind)

if(MEMORYCHECK_COMMAND)
    set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes" "--leak-check=full")
    add_test(NAME ValgrindTest COMMAND ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} $<TARGET_FILE:exe>)
    set_tests_properties(ValgrindTest PROPERTIES PASS_REGULAR_EXPRESSION "ERROR SUMMARY: 0 errors from 0 contexts")
endif()

