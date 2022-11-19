CXX=g++
CXXFLAGS=-Wall -fPIC -std=c++17 -O3 -mssse3
LDFLAGS=-shared
VERSION=0.1.0
LIBNAME=libstreamvbyte.$(VERSION).so
LNLIBNAME=libstreamvbyte.so
INCLUDES=./include/streamvbyte.h ./include/branch_prediction.h ./include/length_table.h ./include/encode_shuffle_table.h
HPPS=./src/encode/encode_scalar.hpp ./src/encode/encode_ssse3.hpp
OBJECTS=encode.o

.PHONY: all test clean

all: $(LIBNAME)

test: ./tests/test.cpp $(INCLUDES) $(OBJECTS) $(HPPS)
	$(CXX) $(CXXFLAGS) -o test ./tests/test.cpp $(OBJECTS) -Iinclude
	./test
	rm ./test

clean:
	rm -f $(OBJECTS) $(LIBNAME) $(LNLIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(LIBNAME) $(OBJECTS)

$(LNLIBNAME): $(LIBNAME)
	ln -sf $(LIBNAME) $(LNLIBNAME)

encode.o: ./src/encode/encode.cpp $(INCLUDES) $(HPPS)
	$(CXX) $(CXXFLAGS) -c ./src/encode/encode.cpp -o encode.o -Iinclude
