#!/bin/bash

export CXXFLAGS="-std=c++11"

# if you encounter with an error about libudev undefined reference:
# sudo ln -s /lib/x86_64-linux-gnu/libudev.so.1 /lib/x86_64-linux-gnu/libudev.so.0 
cmake ${CMAKE_ARGS} .

make -j ${CPU_COUNT}

make test
