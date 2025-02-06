#!/bin/bash

export CXXFLAGS="-std=c++11"

cmake ${CMAKE_ARGS} .

make -j ${CPU_COUNT}

ctest --output-on-failure

