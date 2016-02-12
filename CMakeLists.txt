cmake_minimum_required(VERSION 3.3)
project(ThaiEngine)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_subdirectory(src/libthaiengine)

set(SOURCE_FILES src/main.cc)
add_executable(ThaiEngine ${SOURCE_FILES})
target_link_libraries(ThaiEngine thaiengine)