cmake_minimum_required(VERSION 3.3)
project(ThaiEngine)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(src/libthaiengine)

find_package(Iconv REQUIRED)
include_directories(${ICONV_INCLUDE_DIR})

if(WIN32)
	find_library(PSAPI Psapi)
endif(WIN32)

add_executable(ThaiEngine src/rss.c src/main.cc)
target_compile_features(ThaiEngine PRIVATE cxx_auto_type)
target_compile_features(ThaiEngine PRIVATE cxx_nullptr)
target_link_libraries(ThaiEngine ${ICONV_LIBRARIES} thaiengine PSAPI)

include(CompileOption)
if(NOT CMAKE_BUILD_TYPE MATCHES DEBUG)
    COMPILE_OPTION(ThaiEngine -march=native)
endif(NOT CMAKE_BUILD_TYPE MATCHES DEBUG)

option(BUILD_BENCH "Build benchmark utilities" OFF)

if(BUILD_BENCH)
    set(BENCHMARK_ENABLE_LTO ON)
    add_subdirectory(lib/benchmark)

    add_executable(bench src/bench.cc)
    target_link_libraries(bench thaiengine benchmark)

    if(HAS_O3 AND NOT CMAKE_BUILD_TYPE MATCHES DEBUG)
        target_compile_options(bench PRIVATE -O3)
    endif(HAS_O3 AND NOT CMAKE_BUILD_TYPE MATCHES DEBUG)
    if(HAS_NATIVE_ARCH AND NOT CMAKE_BUILD_TYPE MATCHES DEBUG)
        target_compile_options(bench PRIVATE -march=native)
    endif(HAS_NATIVE_ARCH AND NOT CMAKE_BUILD_TYPE MATCHES DEBUG)
endif(BUILD_BENCH)
