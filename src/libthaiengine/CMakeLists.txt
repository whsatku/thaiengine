cmake_minimum_required(VERSION 3.3)
project(libthaiengine)

find_package(Iconv REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3")

set(SOURCE_FILES loader.cc)
add_library(thaiengine SHARED ${SOURCE_FILES})
target_link_libraries(thaiengine ${ICONV_LIBRARIES})