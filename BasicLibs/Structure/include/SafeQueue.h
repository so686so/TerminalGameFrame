#pragma once

#include <deque>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <memory>

template <typename T>
class SafeQueue
{
public:
	explicit SafeQueue(void) noexcept
		: q()
		, m()
		, c()
	{}

	~SafeQueue(void)
	{}

	// Add an element to the queue.
	void enqueue(T t)
	{
		std::shared_ptr<T> ptr( std::make_shared<T>( std::move(t) ) );
		std::lock_guard<std::mutex> lock(m);
		q.push_back(ptr);
		c.notify_one();
	}

	void enqueue_move(T& t)
	{
		std::shared_ptr<T> ptr( std::make_shared<T>( std::move(t) ) );
		std::lock_guard<std::mutex> lock( m );
		q.push_back( ptr );
		c.notify_one();
	}

	// Get the "front"-element.
	// If the queue is empty, wait till a element is avaiable.
	T dequeue(void)
	{
		std::unique_lock<std::mutex> lock(m);
		while( q.empty() ) {
			// release lock as long as the wait and reaquire it afterwards.
			c.wait(lock);
		}
		T val = std::move( *( q.front() ) );
		q.pop_front();
		return val;
	}

	T dequeueWaitFor( const int millisec, const T& timeoutReturnT )
	{
		std::unique_lock<std::mutex> lock( m );
		while( q.empty() ) {
			if ( c.wait_for( lock, std::chrono::milliseconds( millisec ) ) == std::cv_status::timeout )
				return timeoutReturnT;
		}
		T val = std::move( *( q.front() ) );
		q.pop_front();
		return val;
	}
	
	const int size(void)
	{
		std::unique_lock<std::mutex> lock(m);
		int size = q.size();
		lock.unlock();
		return size;
	}

private:
	std::deque<std::shared_ptr<T>> q;
	mutable std::mutex m;
	std::condition_variable c;
};