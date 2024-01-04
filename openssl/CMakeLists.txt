cmake_minimum_required(VERSION 3.16)
project(openssl LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(OPENSSL_ROOT_DIR ${PROJECT_SOURCE_DIR}/vcpkg/packages/openssl_x64-linux/lib)
set(OPENSSL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vcpkg/packages/openssl_x64-linux/include)
file(GLOB_RECURSE SOURCES "src/*.cpp")

find_package(OpenSSL REQUIRED)

add_executable(exe ${SOURCES})

target_link_libraries(exe PRIVATE OpenSSL::Crypto pthread)
target_include_directories(exe PUBLIC "include")

target_compile_options(exe PRIVATE -O2)
