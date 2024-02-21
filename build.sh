#!/bin/bash

print_instruction() {
    printf "Usage:\n"
    printf "./build.sh smart_logging -i\n"
    printf "./build.sh smart_logging -r\n"
    printf "./build.sh smart_logging -i -r\n"
}

ROOT_DIR=$(pwd)

project_name=$1
if [ -z "$project_name" ]; then
    print_instruction
    exit 1
fi
shift

init=false
run=false

for arg in "$@"; do
    case "$arg" in
    -i | --init)
        init=true
        ;;

    -r | --run)
        run=true
        ;;
    *)
        print_instruction
        exit 1
        ;;
    esac
done

if $init; then
    # rm -rf $project_name

    mkdir "$project_name" || exit
    cd "$project_name" || exit
    mkdir src
    mkdir include
    mkdir build

    cat >src/main.cpp <<EOF
#include <iostream>
#include <thread>
#include <string>
#include <future>
#include <vector>
#include <list>
#include <mutex>
#include <memory>

template <typename T>
void print(T &&t)
{
    std::cout << std::forward<T>(t) << std::endl;
}

int main()
{

}
EOF

    cat >CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.16)
project($project_name LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(exe \${SOURCES})
target_include_directories(exe PUBLIC "include")

target_compile_options(exe PRIVATE -O2)
target_link_libraries(exe PRIVATE pthread)
EOF

    cat >Makefile <<EOF
.PHONY: prepare configure build test run callgrind all

prepare:
	rm -rf build
	mkdir build
configure: prepare
	cd build && cmake ..
build: configure
	cd build && cmake --build . -j
test: build
	# cd build && make test
run:
	cd build && ./exe
callgrind:
	cd build && valgrind --tool=callgrind ./exe && kcachegrin callgrind.out.*
all: prepare configure build test run
EOF
fi

if $run; then
    rm -rf "$ROOT_DIR/$project_name/build"
    mkdir "$ROOT_DIR/$project_name/build"
    cd "$ROOT_DIR/$project_name/build" || (echo "Project does not exist" && exit 1)
    cmake .. || exit 1
    make || exit 1
    ./exe || ./app/exe
fi
exit 0
