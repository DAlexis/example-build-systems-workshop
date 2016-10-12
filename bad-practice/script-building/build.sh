#!/bin/bash

mkdir -p build

# Creating static library
g++ -Wall -g -O0 -g -D_DEBUG -std=gnu++11 -o build/libsource.cpp.o -c lib/libsource.cpp
ar qc build/libexample-lib.a  build/libsource.cpp.o 
g++ -Wall -g -O0 -g -D_DEBUG -std=gnu++11 -o build/main.cpp.o -c program/main.cpp -I lib
g++ -Wall -g -O0 -g -D_DEBUG  build/main.cpp.o -o build/program -lexample-lib -lboost_program_options -L build
