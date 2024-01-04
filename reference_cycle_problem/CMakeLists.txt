cmake_minimum_required(VERSION 3.20)
project(projectName LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_BUILD_TYPE "Debug")
# find_package(Boost 1.70.0 REQUIRED lexical_cast)

add_executable(exe main.cpp)

# target_include_directories(exe PRIVATE /usr/include/boost/)
target_link_libraries(exe PRIVATE pthread)
# target_link_libraries(exe PRIVATE Boost::headers Boost::lexical_cast)

enable_testing()
# include(CTest)

find_program(MEMORYCHECK_COMMAND valgrind)

if(MEMORYCHECK_COMMAND)
    set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes" "--leak-check=full")
    add_test(NAME ValgrindTest COMMAND ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} $<TARGET_FILE:exe>)
    set_tests_properties(ValgrindTest PROPERTIES PASS_REGULAR_EXPRESSION "ERROR SUMMARY: 0 errors from 0 contexts")
endif()
