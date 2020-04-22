#ifndef __BUFFER_H__
#define __BUFFER_H__

#define ARRAY_MAX_SIZE 256

#include <iostream>
#include <array>
#include <cstdint>
#include <cassert>

/**
 * Class containing Circular buffer implementation
 * - fixed array, with max size predefined.
 * - user can select the size of an array, but not bigger than predefined max 
 * size
 * - storage policy can be chosen in run-time
 * - storage size cannot less than 1
 * - predefined storage type to uint8_t (be aware of type limitations)
 * improvements:
 * -> support more types
 * -> add multiple policies for item manipulation (push_front, pop_front, etc.)
 * -> add more policies for buffer
 * -> overload operators for operations with two buffers
 * -> add more functions for buffer usage
 */
class Buffer
{
        using storageType = std::array<uint8_t, (size_t)ARRAY_MAX_SIZE>;

        size_t storageSize{0};     // size of storage
        size_t head{0};            // pointer to head of ring buffer
        size_t tail{0};            // pointer to tail of ring buffer
        size_t itemsNum{0};        // number of elements inside

        storageType storage;    // storage for buffer

        uint8_t storagePolicy{0};      // policy for discard or overwrite data

    public:
        Buffer(int);                // constructor creating storage of fixed size 

        ~Buffer();                  // destroying the storage
        
        void pushBack(int);         // push item to back of buffer (after tail pointer)
        uint8_t popBack();         // pop item from back (tail pointer)

        void readBuffer();

        void setPolicy(uint8_t);    //setting policy for buffer (0 - overwrite, 1 - discard)
};

#endif