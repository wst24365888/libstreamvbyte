cmake_minimum_required(VERSION 3.10)
project(libstreamvbyte VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# for windows
if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64")
    set(ARCH_EXTENSION "-mssse3")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM64")
    set(ARCH_EXTENSION "-mssse3")
# for others
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(ARCH_EXTENSION "-mssse3")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
    set(ARCH_EXTENSION "-mfpu=neon")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(ARCH_EXTENSION "-mfpu=neon")
endif()

set(CMAKE_CXX_FLAGS "-Wall -std=c++17 -O3 ${ARCH_EXTENSION}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

add_subdirectory(pybind11)
pybind11_add_module(libstreamvbyte ./src/streamvbyte.cpp)
target_compile_definitions(libstreamvbyte PRIVATE VERSION_INFO=${PROJECT_VERSION})

target_include_directories(libstreamvbyte PRIVATE ./include ./src)
target_sources(libstreamvbyte PRIVATE ./src/encode/encode.cpp ./src/decode/decode.cpp)

set_property(TARGET libstreamvbyte PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(test ./tests/test.cpp)
target_include_directories(test PRIVATE ./include ./src)
target_sources(test PRIVATE ./src/encode/encode.cpp ./src/decode/decode.cpp)

add_custom_target(run
    COMMAND test
    DEPENDS test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)