cmake_minimum_required(VERSION 3.3)
project(ThaiEngine)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -O3")

add_subdirectory(src/libthaiengine)

find_package(Iconv REQUIRED)

set(SOURCE_FILES src/main.cc)
add_executable(ThaiEngine ${SOURCE_FILES})
include_directories(${ICONV_INCLUDE_DIR})
target_link_libraries(ThaiEngine ${ICONV_LIBRARIES} thaiengine)
