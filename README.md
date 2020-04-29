# Circular buffer

## Prerequisites

1. Complete this README.md by documenting how to build and run.
2. Use any build tool (e.g. make).
3. The code should compile cleanly, no errors/warnings.
4. Static memory only, no malloc()/new.
5. Open a pull request with your changes.
6. Use C++

## Coding task

1. Write a circular buffer class with the following features:
    1. Compile time fixed size
    2. Static memory allocation only
    3. Generic data type (e.g. uint8_t)
    4. Two put(data) overflow behaviors: overwrite and discard data.
2. Write tests showing your circular buffer in action.

## Install CMake and GTest
### CMake
https://cmake.org/install/

### GTest
Linux:
https://github.com/smistad/GTest
Windows:
https://github.com/iat-cener/tonatiuh/wiki/Installing-Google-Test-For-Windows

Note: Compiler used to compiling GTest and this Circular buffer project needs to be same

Use clang(clang 6) or gcc(gcc8) which supports C++17

## Build
Go to circular_buffer path. Execute the following commands.
1. cmake CMakeLists.txt
2. make

CircularBuffer is built and run, an executable 'CircularBuffer' will be created.

CMakeLists.txt has command to run the CircularBuffer Testcases for each build to encourage Test driven development.

## Run

In the circular_buffer path, 'CircularBuffer' executable will be created after successful build.

Execute the following command to run the testcases.
./CircularBuffer