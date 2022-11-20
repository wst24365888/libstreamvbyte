CXX=g++
CXXFLAGS=-Wall -fPIC -std=c++17 -O3 -mssse3
LDFLAGS=-shared
VERSION=0.1.0
LIBNAME=libstreamvbyte.$(VERSION).so
LNLIBNAME=libstreamvbyte.so
OBJECTS=encode.o decode.o
ENCODE_INCLUDES=./include/streamvbyte.h ./include/branch_prediction.h ./include/length_table.h ./include/encode_shuffle_table.h
ENCODE_HPPS=./src/encode/encode_scalar.hpp ./src/encode/encode_ssse3.hpp
DECODE_INCLUDES=./include/streamvbyte.h ./include/branch_prediction.h ./include/length_table.h ./include/decode_shuffle_table.h
DECODE_HPPS=./src/decode/decode_scalar.hpp ./src/decode/decode_ssse3.hpp

.PHONY: all test clean

all: $(LIBNAME)

test: ./tests/test.cpp $(ENCODE_INCLUDES) $(OBJECTS) $(ENCODE_HPPS)
	$(CXX) $(CXXFLAGS) -o test ./tests/test.cpp $(OBJECTS) -Iinclude
	./test
	rm ./test

clean:
	rm -f $(OBJECTS) $(LIBNAME) $(LNLIBNAME)

$(LIBNAME): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(LIBNAME) $(OBJECTS)

$(LNLIBNAME): $(LIBNAME)
	ln -sf $(LIBNAME) $(LNLIBNAME)

encode.o: ./src/encode/encode.cpp $(ENCODE_INCLUDES) $(ENCODE_HPPS)
	$(CXX) $(CXXFLAGS) -c ./src/encode/encode.cpp -o encode.o -Iinclude

decode.o: ./src/decode/decode.cpp $(DECODE_INCLUDES) $(DECODE_HPPS)
	$(CXX) $(CXXFLAGS) -c ./src/decode/decode.cpp -o decode.o -Iinclude
