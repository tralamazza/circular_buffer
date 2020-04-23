/*
 * Copyright 2020 by Alexander Dahmen
 */
#ifndef CIRCULARBUFFER_CIRCULAR_BUFFER_HPP_
#define CIRCULARBUFFER_CIRCULAR_BUFFER_HPP_

#include <mutex>

namespace circularbuffer {

/**
 * CircularBuffer class
 *
 * Declaration and definition and of a ring buffer with a fixed size.
 *
 */
template <typename T, std::size_t buffer_size> class CircularBuffer {
 public:
  /**
   * Reads the next item from the buffer if not empty.
   * Returns true if successfully.
   *
   */
  bool get(T *item);
  /**
   * Method to write a new item into the buffer.
   * If the buffer is full the oldest item will be overwritten.
   *
   */
  void putOverwrite(T const &item);
  /**
   * Method to write a new item into the buffer.
   * If the buffer is full the new item won't be written.
   *
   */
  void putDiscard(T const &item);
  /**
   * Returns true if the buffer is full or false if not.
   *
   */
  bool full() const;
  /**
   * Returns true if the buffer is empty or false if not.
   */
  bool empty() const;

 private:
  void put(T const &item);

  size_t read_index_;
  size_t write_index_;
  size_t data_available_;
  std::array<T, buffer_size> buf_;
  std::mutex mutex_;
};

template <typename T, std::size_t buffer_size>
void CircularBuffer<T, buffer_size>::put(T const &item) {
  buf_[write_index_] = item;
  write_index_ = (write_index_ + 1) % buffer_size;
}

template <typename T, std::size_t buffer_size>
void CircularBuffer<T, buffer_size>::putOverwrite(T const &item) {
  std::lock_guard<std::mutex> lock(mutex_);

  put(item);
  // Since this method overrides existing data
  // the maximum data which can be available is buffer_size.
  // Only increase data_available_ when it is smaller than buffer_size.
  if (!full())
    data_available_++;
}

template <typename T, std::size_t buffer_size>
void CircularBuffer<T, buffer_size>::putDiscard(T const &item) {
  std::lock_guard<std::mutex> lock(mutex_);

  if (full())
    return;
  put(item);
  data_available_++;
}

template <typename T, std::size_t buffer_size>
bool CircularBuffer<T, buffer_size>::get(T *item) {
  std::lock_guard<std::mutex> lock(mutex_);

  if (empty())
    return false;
  // read one item, return it and move index
  *item = buf_[read_index_];
  read_index_ = (read_index_ + 1) % buffer_size;
  data_available_--;
  return true;
}

template <typename T, std::size_t buffer_size>
bool CircularBuffer<T, buffer_size>::full() const {
  return data_available_ == buffer_size;
}

template <typename T, std::size_t buffer_size>
bool CircularBuffer<T, buffer_size>::empty() const {
  return data_available_ == 0;
}

}  // namespace circularbuffer

#endif  // CIRCULARBUFFER_CIRCULAR_BUFFER_HPP_
