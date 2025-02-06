
@echo off

set CXXFLAGS=-std=c++14

:: Run CMake to configure the build
cmake %*

cmake --build . --config Release

ctest --output-on-failure

