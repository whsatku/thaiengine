cmake_minimum_required(VERSION 3.3)
project(ThaiEngine)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -O3")

add_subdirectory(src/libthaiengine)
add_subdirectory(lib/benchmark)

find_package(Iconv REQUIRED)
include_directories(${ICONV_INCLUDE_DIR})

add_executable(ThaiEngine src/rss.c src/main.cc)
set_property(TARGET ThaiEngine PROPERTY CXX_STANDARD 11)
set_property(TARGET ThaiEngine PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(ThaiEngine ${ICONV_LIBRARIES} thaiengine)

add_executable(bench src/bench.cc)
set_property(TARGET bench PROPERTY CXX_STANDARD 11)
set_property(TARGET bench PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(bench thaiengine benchmark)

