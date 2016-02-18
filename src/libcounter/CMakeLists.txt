cmake_minimum_required(VERSION 3.3)
project(libcounter)

set(SOURCE_FILES counter.cpp counter.h)
add_library(counter STATIC ${SOURCE_FILES})
set_property(TARGET counter PROPERTY CXX_STANDARD 11)
set_property(TARGET counter PROPERTY CXX_STANDARD_REQUIRED ON)
