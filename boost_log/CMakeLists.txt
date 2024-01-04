cmake_minimum_required(VERSION 3.16)
project(boost_log LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

find_package(Boost 1.70 REQUIRED log)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(exe ${SOURCES})
target_include_directories(exe PUBLIC "include")

target_compile_options(exe PRIVATE -O2)
target_link_libraries(exe PRIVATE Boost::headers Boost::log pthread)
