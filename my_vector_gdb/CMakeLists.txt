cmake_minimum_required(VERSION 3.16)
project(vector_my LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# To ensure that program is build with debugging information such as line numbers and to facilitate debugging with GDB.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") 

add_subdirectory(src)
add_subdirectory(app)