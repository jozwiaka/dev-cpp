cmake_minimum_required(VERSION 3.16)
project(gtest LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(exe ${SOURCES})
target_include_directories(exe PUBLIC "include")

# target_compile_options(exe PRIVATE -lgtest -lgtest_main -pthred) #WRONG
# command is used set compiler options, not linker options
# linker options such as "-lgtest -lgtest_main -pthred" are used to specify external libraries that need to be linked with my executable during the linking phase.

target_link_libraries(exe PRIVATE GTest::GTest GTest::Main pthread)
# this command tells CMake to link the exe target with the specified libraries

