cmake_minimum_required(VERSION 3.3)
project(libthaiengine)

add_library(thaiengine SHARED loader.cc database.cc farmhash.cc)
target_compile_features(thaiengine PRIVATE cxx_auto_type)
target_compile_features(thaiengine PUBLIC cxx_nullptr)

include(CompileOption)
if(NOT CMAKE_BUILD_TYPE MATCHES DEBUG)
    COMPILE_OPTION(thaiengine -march=native)
endif(NOT CMAKE_BUILD_TYPE MATCHES DEBUG)
