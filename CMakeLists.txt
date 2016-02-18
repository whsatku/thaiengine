cmake_minimum_required(VERSION 3.3)
project(ThaiEngine)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -O3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -O3")

add_subdirectory(src/libthaiengine)
add_subdirectory(src/libcounter)

set(SOURCE_FILES src/main.cc)
add_executable(ThaiEngine ${SOURCE_FILES})
set_property(TARGET ThaiEngine PROPERTY CXX_STANDARD 11)
set_property(TARGET ThaiEngine PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(ThaiEngine thaiengine counter)
