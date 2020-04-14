cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(CircularBuffer CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(circularbuffer INTERFACE)
target_include_directories(circularbuffer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)
