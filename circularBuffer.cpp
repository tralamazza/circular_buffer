#include <iostream>
#include "circularBuffer.hpp"

template <class T> T      circularBuffer<T>::buffer[BufferSize] = {};
template <class T> size_t circularBuffer<T>::head =                0;
template <class T> size_t circularBuffer<T>::tail =                0;
template <class T> bool   circularBuffer<T>::full =            false;

template <class T> void circularBuffer<T>::put_overwrite(T item)
{
  buffer[head] = item;
  if (true == full)
  {
    tail = (tail + 1) % BufferSize;
  }
  head = (head + 1) % BufferSize;
  full = (head == tail);
  return;  
}

template <class T> void circularBuffer<T>::put_discard(T item)
{
  if (false == full)
  {
    buffer[head] = item;
    head = (head + 1) % BufferSize;
    full = (head == tail);
  }
  return;
}

template <class T> T circularBuffer<T>::get()
{
  T returnValue;
 
  returnValue = buffer[tail];
  if (full || (head != tail))
  {
    tail = (tail + 1) % BufferSize;
  }
  full = false;
  return returnValue;
}