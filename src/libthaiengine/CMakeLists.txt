cmake_minimum_required(VERSION 3.3)
project(libthaiengine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -O3 -funroll-loops")

set(SOURCE_FILES loader.cc)
add_library(thaiengine STATIC ${SOURCE_FILES})
set_property(TARGET thaiengine PROPERTY CXX_STANDARD 11)
set_property(TARGET thaiengine PROPERTY CXX_STANDARD_REQUIRED ON)
