#ifndef CORE_CIRCULAR_BUFFER_HPP_
#define CORE_CIRCULAR_BUFFER_HPP_

#include <array>
#include <cstdint>

namespace core {

/*!
 * @brief Fixed size circular buffer.
 *
 * To simplify the implementation (and make it possible to change it to a * lock-free SPSC
 * implementation), the capacity is size - 1. This way, no * separate tracking of the full or empty
 * state is necessary.
 */
template<std::size_t Size>
class CircularBuffer
{
public:
    using size_type = std::size_t;
    using value_type = std::uint8_t;

    /*!
     * @brief Put a new element into the buffer, unless it is full.
     *
     * If the buffer is full, no other action is performed.
     *
     * @param value The element to put into the buffer.
     */
    void putDiscard(std::uint8_t value);

    /*!
     * @brief Put a new element into the buffer.
     *
     * If the buffer is full, the oldest entry is overwritten.
     *
     * @param value The element to put into the buffer.
     */
    void putOverwrite(std::uint8_t value);

    /*!
     * @brief Get the next element from the buffer.
     *
     * @param p Pointer to an element.
     * @return {@c True} if an element was written into {@c p}, {@c false} if the buffer was empty.
     */
    bool get(std::uint8_t *p);

    /*!
     * @brief Returns the number of elements currently in the buffer.
     *
     * @return The number of elements currently in the buffer.
     */
    std::size_t size() const;

    /*!
     * @brief Returns the pointer to the raw data.
     *
     * @return A pointer to the raw data.
     */
    constexpr std::uint8_t const *data() const { return m_data.data(); }

    /*!
     * @brief Returns the maximum number of elements that can be stored in the * buffer.
     *
     * @return The maximum number of elements.
     */
    constexpr std::size_t capacity() const { return m_data.size() - 1; }

    /*!
     * @brief Returns {@c true} if the buffer is empty.
     *
     * @return {@c True} if the buffer is empty.
     */
    constexpr bool empty() const { return m_readPos == m_writePos; }

private:
    void doPut(std::uint8_t value);

    std::array<std::uint8_t, Size> m_data {};
    std::size_t m_readPos { 0 };
    std::size_t m_writePos { 0 };
};

template<std::size_t Size>
std::size_t CircularBuffer<Size>::size() const
{
    if (empty()) {
        return 0;
    }
    if (m_writePos > m_readPos) {
        return m_writePos - m_readPos;
    }
    return m_writePos + Size - m_readPos;
}

template<std::size_t Size>
void CircularBuffer<Size>::putDiscard(std::uint8_t value)
{
    if (size() < capacity()) {
        doPut(value);
    }
}

template<std::size_t Size>
void CircularBuffer<Size>::putOverwrite(std::uint8_t value)
{
    if (size() == capacity()) {
        m_readPos = (m_readPos + 1) % Size;
    }
    doPut(value);
}

template<std::size_t Size>
bool CircularBuffer<Size>::get(std::uint8_t *p)
{
    if (empty()) {
        return false;
    }
    if (p != nullptr) {
        *p = m_data[m_readPos];
    }
    m_readPos = (m_readPos + 1) % Size;
    return true;
}

template<std::size_t Size>
void CircularBuffer<Size>::doPut(std::uint8_t value)
{
    m_data[m_writePos] = value;
    // might use '(m_writePos + 1) >> Size' if Size is a power of 2
    m_writePos = (m_writePos + 1) % Size;
}

} // namespace core

#endif // CORE_CIRCULAR_BUFFER_HPP_
