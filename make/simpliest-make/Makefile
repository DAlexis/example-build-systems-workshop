program: library main.o
	g++ -Wall -g -O0 -pg -DDEBUG  build/main.o -o build/program -lexample-lib -lboost_program_options -L build

main.o: program/main.cpp
	g++ -Wall -g -O0 -pg -DDEBUG -std=gnu++11 -o build/main.o -c program/main.cpp -I lib

libsource.o: build_dir lib/libsource.cpp lib/libheader.hpp
	g++ -Wall -g -O0 -pg -DDEBUG -std=gnu++11 -o build/libsource.o -c lib/libsource.cpp

library: build_dir libsource.o
	ar qc build/libexample-lib.a  build/libsource.o

build_dir:
	mkdir -p build

clean:
	rm -rf build
