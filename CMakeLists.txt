cmake_minimum_required(VERSION 3.3)
project(ThaiEngine)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Iconv REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(${ICONV_INCLUDE_DIR})

set(SOURCE_FILES src/main.cc src/loader.cc src/loader.h)
add_executable(ThaiEngine ${SOURCE_FILES})
target_link_libraries(ThaiEngine ${ICONV_LIBRARIES})