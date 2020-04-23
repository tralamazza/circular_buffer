/*
 * Copyright 2020 by Alexander Dahmen
 */
#include <circularbuffer/circular_buffer.hpp>
#include <gtest/gtest.h>

using circularbuffer::CircularBuffer;

TEST(CircularBufferTest, overwriteTest) {
  CircularBuffer<std::uint8_t, 3> circular_buffer{};

  // check if buffer is empty
  ASSERT_TRUE(circular_buffer.empty());
  ASSERT_FALSE(circular_buffer.full());

  // fill the buffer with data till it is full
  circular_buffer.putOverwrite(10);
  circular_buffer.putOverwrite(8);
  circular_buffer.putOverwrite(6);

  // check if full and empty are set correctly
  ASSERT_TRUE(circular_buffer.full());
  ASSERT_FALSE(circular_buffer.empty());

  circular_buffer.putOverwrite(4);

  uint8_t read_item;
  bool result = circular_buffer.get(&read_item);
  ASSERT_EQ(read_item, 4);
  ASSERT_FALSE(circular_buffer.full());
  ASSERT_FALSE(circular_buffer.empty());
}

TEST(CircularBufferTest, discardTest) {
  CircularBuffer<std::uint8_t, 3> circular_buffer{};

  // check if buffer is empty
  ASSERT_TRUE(circular_buffer.empty());
  ASSERT_FALSE(circular_buffer.full());

  // fill the buffer with data till it is full
  circular_buffer.putDiscard(10);
  circular_buffer.putDiscard(8);
  circular_buffer.putDiscard(6);

  // check if full and empty are set correctly
  ASSERT_TRUE(circular_buffer.full());
  ASSERT_FALSE(circular_buffer.empty());

  circular_buffer.putDiscard(4);

  // read first item
  uint8_t read_item;
  bool result = circular_buffer.get(&read_item);
  ASSERT_EQ(read_item, 10);
  ASSERT_FALSE(circular_buffer.full());
  ASSERT_FALSE(circular_buffer.empty());
}

TEST(CircularBufferTest, getTest) {
  CircularBuffer<std::uint8_t, 3> circular_buffer{};

  // check if buffer is empty
  ASSERT_TRUE(circular_buffer.empty());
  ASSERT_FALSE(circular_buffer.full());

  uint8_t read_value;
  // try to read from an empty buffer
  bool result = circular_buffer.get(&read_value);
  ASSERT_FALSE(result);

  // fill buffer with data
  for (int i = 0; i < 3; ++i) {
    circular_buffer.putDiscard(i);
  }

  // check if buffer is full
  ASSERT_FALSE(circular_buffer.empty());
  ASSERT_TRUE(circular_buffer.full());

  // read from buffer
  for (int i = 0; i < 3; ++i) {
    bool result = circular_buffer.get(&read_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(read_value, i) << "read item differs at " << i;
  }

  // now buffer should be empty
  ASSERT_TRUE(circular_buffer.empty());
  ASSERT_FALSE(circular_buffer.full());
}
