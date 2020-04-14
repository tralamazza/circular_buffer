add_executable(cbtest cbtest.cpp main.cpp)
target_link_libraries(cbtest PRIVATE circularbuffer)

add_test(NAME circular_buffer COMMAND cbtest)
