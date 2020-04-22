#include "buffer.h"

/**
 * Since the std::array is created on compile time, here only setting of 
 * limitations for array is done
 */
Buffer::Buffer(int size) : storageSize(size)
{
    assert((storageSize > 1 && "size must be greater than 1") && (storageSize < ARRAY_MAX_SIZE && "size must be less then ARRAY_MAX_SIZE"));    
}

/**
 * Add item to the back of the ring buffer
 */
void Buffer::pushBack(int item)
{
    if(static_cast<size_t>(0) == itemsNum)
    {
        /**
         * No items in ring buffer, h = t = 0;
         */
        storage.at(tail) = static_cast<uint8_t>(item);
        ++itemsNum;
    }
    else
    {
        /**
         * There is already items in array, it != 0;
         */
        if(itemsNum < storageSize)
        {
            /**
             * But it is not full;
             */
            ++tail;
            storage.at(tail) = static_cast<uint8_t>(item);
            ++itemsNum;
        }
        else if (static_cast<uint8_t>(0) == storagePolicy)
        {
            /**
             * It is full;
             */
            std::cout<<"Full";
            tail = (tail == static_cast<size_t>(storageSize-1)) ? static_cast<size_t>(0) : (tail+1);
            head = (head == static_cast<size_t>(storageSize-1)) ? static_cast<size_t>(0) : (head+1);
            storage.at(tail) = static_cast<uint8_t>(item);
        }
        else
        {
            std::cout << "Discarded items";
        }
        
    }
}

/**
 * Return last item in the buffer
 */
uint8_t Buffer::popBack()
{
    uint8_t temp{storage[tail]};
    
    tail = (tail == static_cast<size_t>(0)) ? static_cast<size_t>(storageSize-1) : (tail-1);
    --itemsNum;

    head = (itemsNum == static_cast<size_t>(0)) ? 0 : head;
    tail = (itemsNum == static_cast<size_t>(0)) ? 0 : tail;
    
    return temp;
}

/**
 * Print out whole buffer
 */
void Buffer::readBuffer()
{
    for(uint8_t it = 0; it < itemsNum; it++)
    {
        std::cout << static_cast<int>(storage.at(it)) << ", ";
    }
    std::cout << std::endl;
}

/**
 * Set policy for adding items in buffer
 * 0 - overwrite, 1 - discard
 */
void Buffer::setPolicy(uint8_t pol)
{
    storagePolicy = pol;
}

Buffer::~Buffer()
{
    std::cout << "In desctructor" << std::endl;
}