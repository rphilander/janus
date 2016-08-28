#include "semaphore.hpp"

Semaphore::Semaphore(unsigned int count)
	: m_count(count)
 {
 }

void Semaphore::notify()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_count++;
	m_condvar.notify_one();
}

void Semaphore::wait()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	while(m_count == 0)
	{
		m_condvar.wait(lock);
	}
	m_count--;
}
