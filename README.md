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


## Circular buffer

Circular buffer for different data types created as a templated class with fixed-size buffer. Two different behaviour added for circular buffer:

1) Overwrite on full
2) Discard data when full

To choose overwrite set `bool overwrite = true`, for discard data set `bool overwrite = false`

Buffer instanced compile-time for fixed static size. Size of the buffer resolved
in compile time trough `int size` argument of templated class

### How to build

Dependencies:
	- Cmake
	- Ninja/make
	- gcc/g++ compiler

1) Clone this repository `cd <dir>`
2) Navigate to build directory `cd build`
3) Execute `cmake .. -G Ninja` or `cmake .. -G make`
4) In build directory run `ninja` or `make`
5) Run example with `./circ-buff`



