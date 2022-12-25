cmake_minimum_required(VERSION 3.10)
project(libstreamvbyte VERSION 0.3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ARCH_EXTENSION "")
set(__NEON__ OFF)

message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")

if (APPLE)
    # for macOS, check ARCHFLAGS
    message(STATUS "ARCHFLAGS: $ENV{ARCHFLAGS}")
    if (NOT DEFINED ENV{ARCHFLAGS})
        message(FATAL_ERROR "ARCHFLAGS is not defined.")
    endif()
    if ($ENV{ARCHFLAGS} MATCHES "x86_64")
        set(ARCH_EXTENSION "-mssse3")
    elseif ($ENV{ARCHFLAGS} MATCHES "arm64")
        set(ARCH_EXTENSION "-march=armv8-a+fp+simd")
        set(__NEON__ ON)
    endif()
else()
    # for windows
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64")
        set(ARCH_EXTENSION "-mssse3")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM64")
        set(ARCH_EXTENSION "-march=armv8-a+fp+simd")
        set(__NEON__ ON)
    # for other linux
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(ARCH_EXTENSION "-mssse3")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
        set(ARCH_EXTENSION "-march=armv8-a+fp+simd")
        set(__NEON__ ON)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "armv8")
        set(ARCH_EXTENSION "-march=armv8-a+fp+simd")
        set(__NEON__ ON)
    endif()
endif()

message(STATUS "ARCH_EXTENSION: ${ARCH_EXTENSION}")
message(STATUS "__NEON__: ${__NEON__}")

option(BUILD_SHARED_LIBS "Build shared libraries." ON)
option(BUILD_PYBIND11 "Build pybind11." OFF)
option(PRINT_BENCHMARK "Print benchmark." OFF)
option(BUILD_TESTS "Build tests." OFF)
option(BUILD_BENCHMARKS "Build benchmark." OFF)

if (BUILD_PYBIND11 AND BUILD_SHARED_LIBS)
    message(FATAL_ERROR "BUILD_PYBIND11 and BUILD_SHARED_LIBS are mutually exclusive.")
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/config.h)

set(CMAKE_CXX_FLAGS "-Wall -std=c++17 -O3 ${ARCH_EXTENSION}")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

if (BUILD_SHARED_LIBS)    
    add_library(streamvbyte ${CMAKE_CURRENT_SOURCE_DIR}/src/encode/streamvbyte_encode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/decode/streamvbyte_decode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/encode/zigzag_encode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/decode/zigzag_decode.cpp)
    target_compile_definitions(streamvbyte PRIVATE VERSION_INFO=${PROJECT_VERSION})

    target_include_directories(streamvbyte PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/sse2neon)

    set_property(TARGET streamvbyte PROPERTY POSITION_INDEPENDENT_CODE ON)

    install(TARGETS streamvbyte DESTINATION lib)
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/streamvbyte.h DESTINATION include)

    add_custom_target(
        uninstall
        COMMAND rm -f ${CMAKE_INSTALL_PREFIX}/lib/libstreamvbyte.so
        COMMAND rm -f ${CMAKE_INSTALL_PREFIX}/include/streamvbyte.h
    )
elseif (BUILD_PYBIND11)
    add_subdirectory(pybind11)
    pybind11_add_module(libstreamvbyte ${CMAKE_CURRENT_SOURCE_DIR}/src/streamvbyte.cpp)
    target_compile_definitions(libstreamvbyte PRIVATE VERSION_INFO=${PROJECT_VERSION})

    target_include_directories(libstreamvbyte PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/sse2neon)
    target_sources(libstreamvbyte PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/encode/streamvbyte_encode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/decode/streamvbyte_decode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/encode/zigzag_encode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/decode/zigzag_decode.cpp)

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
    
    add_executable(libstreamvbyte_tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)
    target_include_directories(libstreamvbyte_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/sse2neon)
    target_sources(libstreamvbyte_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/encode/streamvbyte_encode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/decode/streamvbyte_decode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/encode/zigzag_encode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/decode/zigzag_decode.cpp)

    target_link_libraries(
        libstreamvbyte_tests
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(libstreamvbyte_tests)
endif()

if (NOT BUILD_TESTS AND BUILD_BENCHMARKS)
    message(FATAL_ERROR "BUILD_TESTS must be enabled to build benchmarks.")
endif()

if (BUILD_BENCHMARKS)
    include(FetchContent)
    FetchContent_Declare(
    googlebenchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.7.1.zip
    )

    FetchContent_MakeAvailable(googlebenchmark)

    add_executable(libstreamvbyte_benchmarks ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/benchmark.cpp)
    target_include_directories(libstreamvbyte_benchmarks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/sse2neon)
    target_sources(libstreamvbyte_benchmarks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/encode/streamvbyte_encode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/decode/streamvbyte_decode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/encode/zigzag_encode.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/decode/zigzag_decode.cpp)

    target_link_libraries(
        libstreamvbyte_benchmarks
        benchmark::benchmark
    )
endif()
