cmake_minimum_required(VERSION 3.20)
project(projectName LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES src/main.cpp)
add_executable(exe ${SOURCE_FILES})
target_include_directories(exe PRIVATE /usr/include/boost/)
# target_link_libraries(exe PRIVATE /usr/lib/x86_64-linux-gnu/)