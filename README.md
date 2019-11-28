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

## Assumption

1. Only one circular buffer per data type.
2. Tests need a get function. 
3. On an empty buffer get should not be used. 
3. Before using the get function the buffer has to be tested if empty. 
4. MISRA C++ compliance, common style guides and similar needs not to be focused. 

## Build

1. Use a Linux machine. 
2. Open a terminal.  
3. Go to the source directory "circular_buffer".
3. In the "circular_buffer" folder type "make".
5. Run the program "./testcb".
6. Final result printed in terminal should be "GHIJA".
7. You can use gdb for debugging if needed.
