#ifndef circularBuffer_
#define circularBuffer_

//**********************************************************************************
// Author: Sascha Heinisch
// Date:   28.11.2019
// 
// Class: Declarartion of circular buffer class. 
//
//**********************************************************************************
template <class T, uint32_t BufferSize> class circularBuffer
{
  public:

    static T buffer[BufferSize];
    static size_t head;              //head of circular buffer
    static size_t tail;              //tail of circular buffer
    static bool   full;              //buffer full if true

  public:
  
    static void put_overwrite(T item);  
    static void put_discard(T item);
    static bool get(T &item);
    static bool notEmpty();
};

template <class T, uint32_t BufferSize> T      circularBuffer<T, BufferSize>::buffer[BufferSize] = {};
template <class T, uint32_t BufferSize> size_t circularBuffer<T, BufferSize>::head =                0;
template <class T, uint32_t BufferSize> size_t circularBuffer<T, BufferSize>::tail =                0;
template <class T, uint32_t BufferSize> bool   circularBuffer<T, BufferSize>::full =            false;

//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     put_overwrite
// 
// Function: Stores item in the circular buffer. If full it overwrites oldest value. 
//
// Param:    T item
// Return:   void
//
//**********************************************************************************
template <class T, uint32_t BufferSize> void circularBuffer<T, BufferSize>::put_overwrite(T item)
{
  buffer[head] = item;               //store item
  if (true == full)                  //if full tail++ to become equal with head
  {
    tail = (tail + 1) % BufferSize;
  }
  head = (head + 1) % BufferSize;    
  full = (head == tail);
  return;  
}
//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     put_discard
// 
// Function: Stores item in the circular buffer. If full it does stop writing value. 
//
// Param:    T item
// Return:   void
//
//**********************************************************************************
template <class T, uint32_t BufferSize> void circularBuffer<T, BufferSize>::put_discard(T item)
{
  if (false == full)                 //don't write item if full
  {
    buffer[head] = item;
    head = (head + 1) % BufferSize;
    full = (head == tail);
  }
  return;
}
//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     get
// 
// Function: Returns item from circular buffer. If empty it returns the oldest value. 
//
// Param:    void
// Return:   template <class T> T
//
//**********************************************************************************
template <class T, uint32_t BufferSize> bool circularBuffer<T, BufferSize>::get(T &item)
{  
  bool returnValue = false;
  item = buffer[tail];               //get oldest item
  if (notEmpty())                    //not empty
  {
    tail = (tail + 1) % BufferSize;
    returnValue = true;
  } 
  full = false;                      //after read buffer cannot be full
  return returnValue;
}
//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     notEmpty 
//
// Function: Returns true if buffer is not empty else false.
//
// Param:    void
// Return:   boolean
//
//**********************************************************************************
template <class T, uint32_t BufferSize> bool circularBuffer<T, BufferSize>::notEmpty(void)
{
  return (full || (head != tail));
}
#endif