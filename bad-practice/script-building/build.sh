#!/bin/bash

mkdir -p build

# Creating static library
g++ -Wall -g -O0 -pg -DDEBUG -std=gnu++11 -o build/libsource.cpp.o -c lib/libsource.cpp
ar qc build/libexample-lib.a  build/libsource.cpp.o
# Compiling program
g++ -Wall -g -O0 -pg -DDEBUG -std=gnu++11 -o build/main.cpp.o -c program/main.cpp -I lib
# Linking
g++ -Wall -g -O0 -pg -DDEBUG  build/main.cpp.o -o build/program -lexample-lib -lboost_program_options -L build
