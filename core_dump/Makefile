.PHONY: prepare configure build test run all

prepare:
	rm -rf /mnt/wslg/dumps/*
	rm -rf build
	mkdir build
configure: prepare
	cd build && cmake ..
build: configure
	ulimit -c unlimited
	cd build && cmake --build . -j
run:
	cd build && ulimit -c unlimited && ./exe
read_core_dump:
	gdb build/exe -c /mnt/wslg/dumps/core.exe.*
	# Then in gdb mode run:
	# list
	# list #use it once more if there is a need to get more code
	# bt
	# p i
	# x/s i
	# q

all: prepare configure build test run
