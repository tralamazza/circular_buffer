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

## Build instructions

This solution is using the googletest framework for C++ unit tests.

1. Clone googletest into the root folder of this project via
    `git clone https://github.com/google/googletest.git`
2. Run `make check` inside the `tests` folder in order to compile and run the tests.
