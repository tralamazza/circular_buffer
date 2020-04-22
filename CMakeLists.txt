cmake_minimum_required(VERSION 3.10)

project(circ-buff)

SET(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
  circular_buffer.cpp
)
