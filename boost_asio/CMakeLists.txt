cmake_minimum_required(VERSION 3.20)
project(projectName LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES src/main.cpp)

find_package(Boost 1.70.0 REQUIRED lexical_cast)

add_executable(exe ${SOURCE_FILES})
target_include_directories(exe PRIVATE /usr/include/boost/)
# target_link_libraries(exe PRIVATE Boost::headers Boost::lexical_cast)