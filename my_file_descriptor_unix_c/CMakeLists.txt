cmake_minimum_required(VERSION 3.16)
project(file_descriptor LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

configure_file(${CMAKE_SOURCE_DIR}/src/file.txt ${CMAKE_BINARY_DIR}/file.txt)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(exe ${SOURCES})

target_include_directories(exe PUBLIC "include")

target_compile_options(exe PRIVATE -O2)
target_link_libraries(exe PRIVATE pthread)

