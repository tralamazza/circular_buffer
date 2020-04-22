#include <iostream>
#include "buffer.h"

#define BUFFER_SIZE_1   10

#define BUFFER_TEST_1   30

int main() 
{
    Buffer buff = Buffer(BUFFER_SIZE_1);

    for(int it = 0; it < BUFFER_TEST_1; it++)
    {
        buff.pushBack(it);
        buff.readBuffer();
    }
    
    for(int it = 0; it < BUFFER_SIZE_1; it++)
    {
        int temp = static_cast<int>(buff.popBack());
        buff.readBuffer();
    }

    std::cout << "Different policy for ring buffer!" << std::endl;

    buff.setPolicy(static_cast<uint8_t>(1));

    for(int it = 0; it < BUFFER_TEST_1; it++)
    {
        buff.pushBack(it);
        buff.readBuffer();
    }
    
    for(int it = 0; it < BUFFER_SIZE_1; it++)
    {
        int temp = static_cast<int>(buff.popBack());
        buff.readBuffer();
    }
    
    std::cout << "Hello Easy C++ project! " << std::endl;
}