cmake_minimum_required(VERSION 3.16)
project(dead_lock LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(exe ${SOURCES})
target_include_directories(exe PUBLIC "include")

target_compile_options(exe PRIVATE -O2)
target_link_libraries(exe PRIVATE pthread)
