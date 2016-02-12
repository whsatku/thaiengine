cmake_minimum_required(VERSION 3.3)
project(libthaiengine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -funroll-loops")

set(SOURCE_FILES loader.cc database.cc farmhash.cc)
add_library(thaiengine SHARED ${SOURCE_FILES})
