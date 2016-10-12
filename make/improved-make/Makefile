CXXFLAGS += -Wall -g -O0 -pg -DDEBUG
LDFLAGS +=  -lboost_program_options

program: main.o library
	g++ main.o -o program -lexample-lib $(CXXFLAGS) $(LDFLAGS)

%.o: %.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

library: libsource.o build_dir 
	ar qc libexample-lib.a  libsource.o

build_dir:
	mkdir -p build

clean:
	rm *.o program *.a
