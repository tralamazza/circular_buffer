#include <core/CircularBuffer.hpp>

#include "catch.hpp"

using namespace core;

SCENARIO("circular buffer can put and get values", "[circularbuffer]")
{
    GIVEN("A circular buffer")
    {
        constexpr std::size_t Size = 4;
        CircularBuffer<std::uint8_t, Size> circularBuffer {};

        REQUIRE(circularBuffer.capacity() == Size - 1);
        REQUIRE(circularBuffer.size() == 0);

        WHEN("the buffer is filled in discard mode")
        {
            for (std::uint8_t i = 0; i < Size; ++i) {
                circularBuffer.putDiscard(i);
            }
            THEN("the last element is not written into the buffer")
            {
                std::uint8_t val = 0;
                REQUIRE(circularBuffer.get(&val));
                REQUIRE(val == 0);
                REQUIRE(circularBuffer.get(&val));
                REQUIRE(val == 1);
                REQUIRE(circularBuffer.get(&val));
                REQUIRE(val == 2);
                REQUIRE(circularBuffer.empty());
            }
        }

        WHEN("the buffer is filled in overwrite mode")
        {
            for (std::uint8_t i = 0; i < Size; ++i) {
                circularBuffer.putOverwrite(i);
            }
            THEN("the first entry is overwritten")
            {
                std::uint8_t val = 0;
                REQUIRE(circularBuffer.get(&val));
                REQUIRE(val == 1);
                REQUIRE(circularBuffer.get(&val));
                REQUIRE(val == 2);
                REQUIRE(circularBuffer.get(&val));
                REQUIRE(val == 3);
                REQUIRE(circularBuffer.empty());
            }
        }
    }
}
