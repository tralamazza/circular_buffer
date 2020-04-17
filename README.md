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

## Solution

### Design rationale

Since empty and full ring buffers both have `readPos == writePos`,
implementations have to find a small tradeoff between space utilization and runtime efficiency.
To resolve the ambiguity, they can either store `size - 1` elements and therefore waste one entry,
or they introduce separate state tracking, which complicates the implementation.

Since no further constraints were given in the objectives, it was decided to prefer the first approach.
In situations where memory was severely constrained, this would not be the best solution.

### Building and running

CMake (https://cmake.org) is used for building.
Tests can be executed by running `ctest`.

On Unix machines,
the following commands are sufficient:

```
$ mkdir build
$ cd build
$ cmake ..
...
$ cmake --build .
$ ctest -V
```
