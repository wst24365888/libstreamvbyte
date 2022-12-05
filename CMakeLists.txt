cmake_minimum_required(VERSION 3.10)
project(streamvbyte VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(ARCH ssse3)
set(CMAKE_CXX_FLAGS "-Wall -std=c++17 -O3 -m${ARCH}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_subdirectory(pybind11)
pybind11_add_module(streamvbyte ./src/streamvbyte.cpp)
target_compile_definitions(streamvbyte PRIVATE VERSION_INFO=${PROJECT_VERSION})

target_include_directories(streamvbyte PRIVATE ./include ./src)
target_sources(streamvbyte PRIVATE ./src/encode/encode.cpp ./src/decode/decode.cpp)

set_property(TARGET streamvbyte PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(test ./tests/test.cpp)
target_include_directories(test PRIVATE ./include ./src)
target_sources(test PRIVATE ./src/encode/encode.cpp ./src/decode/decode.cpp)

add_custom_target(run
    COMMAND test
    DEPENDS test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)