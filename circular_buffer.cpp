#include <memory>
#include <iostream>
#include <mutex>

namespace cb_defines
{
	constexpr size_t cb_size = 4;
}


/**
 * Universal circual buffer implementation for different data types and
 * structures. Type and size solved in compile time
 *
 *  @tparam T the type of data stored in buffer
 *  @tparam size Size of the buffer
 */
template <typename T, int size>
class CircularBuffer
{
public:

	/**
	 * Class contstructor, always call default without any arguments as size is
	 * resolved in compile time
	 */
	CircularBuffer() = default;
	~CircularBuffer() = default;


	CircularBuffer(const CircularBuffer &) = delete;
    CircularBuffer &operator=(const CircularBuffer &) = delete;
    CircularBuffer(CircularBuffer &&) = delete;
    CircularBuffer &operator=(CircularBuffer &&) = delete;

	/**
	 * @brief Get buffer element from circular buffer
	 *
	 * @return item from head of buffer
	 */
	T dequeue()
	{
		// local lock_guard to lock mtx for guaranted destruction/exception
        std::lock_guard<std::mutex> lock(mtx);

		if (is_empty())
		{
			throw std::runtime_error("Buffer is empty");
		}

		T item = m_cb_data[head];

		T tmp;
		m_cb_data[head] = tmp;

		head = (head + 1) % m_cb_size;

		num_of_elements--;

		return item;
	}

	/**
	 * @brief Put data element into circular buffer
	 *
	 * @param item new data inserted into buffer
	 */
	void enqueue(T item)
	{
		// local lock_guard to lock mtx for guaranted destruction/exception
        std::lock_guard<std::mutex> lock(mtx);

		if (is_full())
		{
			if (overwrite)
			{
				m_cb_data[(head + head_overwrite) % m_cb_size] = item;
				head_overwrite = (head_overwrite + 1) % m_cb_size;
				//std::cout << "Overwrite" << std::endl;
			}
			else
			{
				//std::cout << "Data discarded due cb full" << std::endl;
			}
		}
		else
		{
			m_cb_data[tail] = item;
			tail = (tail + 1) % m_cb_size;
			head_overwrite = 0;
			num_of_elements++;
		}
	}
	/**
	 * Print current content of data and relevent infomations
	 */
	void print_buffer()
	{
		std::cout << "Current head " << head << ", tail " << tail << std::endl;
		for (auto x : m_cb_data)
			std::cout << x << " ";

		std::cout << std::endl;
	}


	/**
	 * Get item from front of buffer pointed by head
	 *
	 * @return buffer element from front
	 */
	T front()
    {
		// local lock_guard to lock mtx for guaranted destruction/exception
        std::lock_guard<std::mutex> lock(mtx);

        if (not is_empty())
        {
            return m_cb_data[head];
        }
    }

	/**
	 * Get item from back of buffer pointed by tail
	 *
	 * @return buffer element from back
	 */
	T back()
    {
        // local lock_guard to lock mtx for guaranted destruction/exception
        std::lock_guard<std::mutex> lock(mtx);

        if (not is_empty())
        {
            return m_cb_data[tail];
        }
    }

	/**
	 * Check if buffer is full
	 *
	 * @return true if buffer is full, false if not
	 */
	bool is_full()
	{
		return (num_of_elements >= m_cb_size);
	}

	/**
	 * Check if buffer is empty
	 *
	 * @return true if buffer is empty, false if not
	 */
	bool is_empty()
	{
		return (num_of_elements == 0);
	}

	/**
	 * Get current buffer size
	 *
	 * @return size of buffer
	 */
	size_t cb_size()
	{
		if (tail >= head)
			return tail - head;

		return this->cb_size - head - tail;
	}

private:
	CircularBuffer(uint32_t cb_size) = delete;
	//CircularBuffer(CircBuf&&) = delete;

	/** If overwrite mode is used set to true, if discard data is required
	 * after buffer is full set overwrite to false
	*/
	bool overwrite = true;

	int m_cb_size = size;
	int num_of_elements = 0;

	std::array<T, size> m_cb_data;

	int head = 0;
	int head_overwrite = 0;
	int tail = 0;

	std::mutex mtx;

};

int main()
{
	CircularBuffer<int, 4> cb;

	try
	{
		cb.enqueue(1);
		cb.print_buffer();
		cb.enqueue(2);
		cb.print_buffer();
		cb.enqueue(3);
		cb.print_buffer();
		cb.enqueue(4);
		cb.print_buffer();
		cb.enqueue(5);
		cb.print_buffer();
		cb.enqueue(6);
		cb.print_buffer();
		cb.enqueue(7);
		cb.print_buffer();
		cb.enqueue(8);
		cb.print_buffer();
		cb.enqueue(9);
		cb.print_buffer();

		std::cout << cb.dequeue() << std::endl;
		cb.enqueue(1);
		cb.print_buffer();
		std::cout << cb.dequeue() << std::endl;
		cb.enqueue(2);
		cb.print_buffer();
		std::cout << cb.dequeue() << std::endl;
		cb.enqueue(3);
		cb.print_buffer();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << '\n';
	}

	return 0;
}
