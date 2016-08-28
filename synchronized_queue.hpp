#pragma once

#include <list>

#include "semaphore.hpp"

template <class T>
class SynchronizedQueue
{
public:
	SynchronizedQueue(unsigned int max_size);

	void push(const T &item)
	{
		m_semaphoreSpaces.wait();
		std::lock_guard<std::mutex> guard(m_mutex);
		m_list.push_back(item);
		m_semaphoreItems.notify();
	}

	const T& pop()
	{
		m_semaphoreItems.wait();
		std::lock_guard<std::mutex> guard(m_mutex);
		auto item = m_list.front();
		m_list.pop_front();
		m_semaphoreSpaces.notify();
		return item;
	}

private:
	std::list<T> m_list;
	Semaphore m_semaphoreSpaces, m_semaphoreItems;
	std::mutex m_mutex;
};

template <class T>
SynchronizedQueue<T>::SynchronizedQueue(unsigned int max_size) : m_semaphoreSpaces(max_size) {}