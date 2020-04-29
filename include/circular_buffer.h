#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <cstddef>
#include <mutex>
namespace Circular {
namespace Buffer {

constexpr auto kMaxBufferSize{50};
constexpr auto kOverRide{true};
template <typename T>
class CircularBuffer {
 public:
  CircularBuffer() = default;
  CircularBuffer(const CircularBuffer&) = delete;
  CircularBuffer(CircularBuffer&&) = delete;
  CircularBuffer& operator=(CircularBuffer&&) = delete;
  CircularBuffer& operator=(const CircularBuffer&) = delete;
  constexpr auto Capacity() const { return kMaxBufferSize; }
  constexpr auto Empty() const { return (!full_ && (head_ == tail_)); }
  constexpr auto Full() const { return full_; }
  constexpr auto Size() const {
    size_t buffer_size{kMaxBufferSize};
    if (full_) {
      buffer_size = kMaxBufferSize + head_ - tail_;
    } else {
      buffer_size = head_ - tail_;
    }
    return buffer_size;
  }
  constexpr void PushBack(const T& data, bool override = kOverRide) {
    std::lock_guard<std::mutex> lock(circular_buffer_mutex_);
    if (full_) {
      if (override) {
        PutDataFull(data);
      }
    } else {
      PutData(data);
    }
    full_ = head_ == tail_;
  }
  constexpr T operator[](const size_t& index) const { return buffer_[index]; }

 private:
  constexpr void PutData(const T& data) {
    buffer_[head_] = data;
    head_ = (head_ + 1) % kMaxBufferSize;
  }
  constexpr void PutDataFull(const T& data) {
    PutData(data);
    tail_ = (tail_ + 1) % kMaxBufferSize;
  }
  T buffer_[kMaxBufferSize];
  std::mutex circular_buffer_mutex_;
  size_t head_{0};
  size_t tail_{0};
  bool full_{false};
};
}  // namespace Buffer
}  // namespace Circular
#endif