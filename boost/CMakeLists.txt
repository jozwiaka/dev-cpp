cmake_minimum_required(VERSION 3.16)
project(boost LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# apt install libboost-all-dev
# grep "#define BOOST_VERSION " /usr/include/boost/version.hpp
# #define BOOST_VERSION 107400
# 1.74.0 installed
find_package(Boost 1.70.0 REQUIRED system filesystem)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(exe ${SOURCES})

target_include_directories(exe PUBLIC "include")
target_compile_options(exe PRIVATE -O2)

target_link_libraries(exe PRIVATE Boost::headers Boost::system Boost::filesystem)
