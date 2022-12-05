ARCH=ssse3
CXX=g++
CXXFLAGS=-Wall -fPIC -shared -std=c++17 -O3 -m$(ARCH)
LDFLAGS=-shared
VERSION=0.1.0
OBJECTS=encode.o decode.o
PUBLIC_HEADERS=./include/streamvbyte.h
PRIVATE_ENCODE_HEADERS=./src/branch_prediction.h ./src/length_table.h ./src/encode_shuffle_table.h
PRIVATE_ENCODE_HPPS=./src/encode/encode_scalar.hpp ./src/encode/encode_ssse3.hpp
PRIVATE_DECODE_HEADERS=./src/branch_prediction.h ./src/length_table.h ./src/decode_shuffle_table.h
PRIVATE_DECODE_HPPS=./src/decode/decode_scalar.hpp ./src/decode/decode_ssse3.hpp
PYBIND_INCLUDE = $(shell python3 -m pybind11 --includes)
PYTHON_CONFIG = $(shell python3-config --includes)
LIBNAME = streamvbyte$(shell python3-config --extension-suffix)
ENTRYPOINT = ./src/streamvbyte.cpp

.PHONY: all test clean

all: $(LIBNAME)

test: ./tests/test.cpp $(OBJECTS)
	$(CXX) -Wall -std=c++17 -O3 -m$(ARCH) -g -o test ./tests/test.cpp $(OBJECTS) -Iinclude
	./test
	rm ./test

clean:
	rm -f $(OBJECTS) $(LIBNAME) $(LNLIBNAME)

$(LIBNAME): $(OBJECTS) $(PUBLIC_HEADERS) $(PRIVATE_ENCODE_HEADERS) $(PRIVATE_ENCODE_HPPS) $(PRIVATE_DECODE_HEADERS) $(PRIVATE_DECODE_HPPS) $(ENTRYPOINT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(LIBNAME) $(ENTRYPOINT) $(OBJECTS) $(PYBIND_INCLUDE) $(PYTHON_CONFIG) -Iinclude

encode.o: ./src/encode/encode.cpp $(PRIVATE_ENCODE_HEADERS) $(PUBLIC_HEADERS) $(PRIVATE_ENCODE_HPPS)
	$(CXX) $(CXXFLAGS) -c ./src/encode/encode.cpp -o encode.o -Iinclude -Isrc

decode.o: ./src/decode/decode.cpp $(PRIVATE_DECODE_HEADERS) $(PUBLIC_HEADERS) $(PRIVATE_DECODE_HPPS)
	$(CXX) $(CXXFLAGS) -c ./src/decode/decode.cpp -o decode.o -Iinclude -Isrc
