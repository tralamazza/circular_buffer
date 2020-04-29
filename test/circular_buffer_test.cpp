#include "circular_buffer.h"
#include <gtest/gtest.h>
namespace Circular {
namespace Buffer {
namespace {
using Type = std::int64_t;
class CircularBufferTest : public ::testing::Test {
 public:
  void SetUp() override {}
  void TearDown() override {}
  CircularBuffer<Type> circular_buffer_;
};

TEST_F(CircularBufferTest, CapacityTest) {
  EXPECT_EQ(kMaxBufferSize, circular_buffer_.Capacity());
}

class BufferSizeTest : public ::testing::TestWithParam<Type> {
 public:
  void SetUp() override {
    result_size_ = GetParam() % kMaxBufferSize;
    for (auto index{0u}; index < result_size_; ++index) {
      circular_buffer_.PushBack(index);
    }
    if (0 == result_size_) {
      result_empty_ = true;
    }
    if (kMaxBufferSize == result_size_) {
      result_full_ = true;
    }
  }
  void TearDown() override {}
  size_t result_size_{0};
  bool result_empty_{false};
  bool result_full_{false};
  CircularBuffer<Type> circular_buffer_;
};

TEST_P(BufferSizeTest, SizeTest) {
  EXPECT_EQ(result_size_, circular_buffer_.Size());
}
TEST_P(BufferSizeTest, EmptyTest) {
  EXPECT_EQ(result_empty_, circular_buffer_.Empty());
}
TEST_P(BufferSizeTest, FullTest) {
  EXPECT_EQ(result_full_, circular_buffer_.Full());
}
INSTANTIATE_TEST_CASE_P(SizeParam, BufferSizeTest,
                        ::testing::Values(0, kMaxBufferSize + 1));

class BufferDataTest : public ::testing::TestWithParam<std::tuple<Type, bool>> {
 public:
  void SetUp() override {
    auto buffer_size = std::get<0>(GetParam());
    auto override_flag = std::get<1>(GetParam());
    for (auto index{0}; index < buffer_size; ++index) {
      circular_buffer_.PushBack(index, override_flag);
    }
    if (override_flag) {
      result_start_index_ = buffer_size - kMaxBufferSize;
      result_end_index_ = buffer_size;
    } else {
      result_end_index_ = buffer_size % kMaxBufferSize;
    }
  }
  void TearDown() override {}
  size_t result_start_index_{0};
  size_t result_end_index_{0};
  CircularBuffer<Type> circular_buffer_;
};

TEST_P(BufferDataTest, VerifyBuffer) {
  for (auto index{result_start_index_}; index < result_end_index_; ++index) {
    EXPECT_EQ(index, circular_buffer_[(index) % kMaxBufferSize]);
  }
}
INSTANTIATE_TEST_CASE_P(OverrideDiscardParam, BufferDataTest,
                        ::testing::Combine(::testing::Values(0, kMaxBufferSize +
                                                                    1),
                                           ::testing::Bool()));

}  // namespace
}  // namespace Buffer
}  // namespace Circular