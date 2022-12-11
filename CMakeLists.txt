cmake_minimum_required(VERSION 3.10)
project(libstreamvbyte VERSION 0.2.1)

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
endif()

option(BUILD_SHARED_LIBS "Build shared libraries." ON)
option(BUILD_PYBIND11 "Build pybind11." OFF)
option(BUILD_TESTS "Build tests." OFF)

if (BUILD_PYBIND11 AND BUILD_SHARED_LIBS)
    message(FATAL_ERROR "BUILD_PYBIND11 and BUILD_SHARED_LIBS are mutually exclusive.")
endif()

set(CMAKE_CXX_FLAGS "-Wall -std=c++17 -O3 ${ARCH_EXTENSION}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

if (BUILD_SHARED_LIBS)    
    add_library(streamvbyte ./src/encode/encode_streamvbyte.cpp ./src/decode/decode_streamvbyte.cpp ./src/encode/encode_zigzag.cpp ./src/decode/decode_zigzag.cpp)
    target_compile_definitions(streamvbyte PRIVATE VERSION_INFO=${PROJECT_VERSION})

    target_include_directories(streamvbyte PRIVATE ./include ./src)

    set_property(TARGET streamvbyte PROPERTY POSITION_INDEPENDENT_CODE ON)

    install(TARGETS streamvbyte DESTINATION lib)
    install(FILES ./include/streamvbyte.h DESTINATION include)

    add_custom_target(
        uninstall
        COMMAND rm -f ${CMAKE_INSTALL_PREFIX}/lib/libstreamvbyte.so
        COMMAND rm -f ${CMAKE_INSTALL_PREFIX}/include/streamvbyte.h
    )
elseif (BUILD_PYBIND11)
    add_subdirectory(pybind11)
    pybind11_add_module(libstreamvbyte ./src/streamvbyte.cpp)
    target_compile_definitions(libstreamvbyte PRIVATE VERSION_INFO=${PROJECT_VERSION})

    target_include_directories(libstreamvbyte PRIVATE ./include ./src)
    target_sources(libstreamvbyte PRIVATE ./src/encode/encode_streamvbyte.cpp ./src/decode/decode_streamvbyte.cpp ./src/encode/encode_zigzag.cpp ./src/decode/decode_zigzag.cpp)

    set_property(TARGET libstreamvbyte PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if (BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    add_executable(libstreamvbyte_tests ./tests/test.cpp)
    target_include_directories(libstreamvbyte_tests PRIVATE ./include ./src)
    target_sources(libstreamvbyte_tests PRIVATE ./src/encode/encode_streamvbyte.cpp ./src/decode/decode_streamvbyte.cpp ./src/encode/encode_zigzag.cpp ./src/decode/decode_zigzag.cpp)

    target_link_libraries(
        libstreamvbyte_tests
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(libstreamvbyte_tests)
endif()
