#ifndef XF_QUEUE_HPP
#define XF_QUEUE_HPP
#include "deque.hpp"
namespace xf
{
	template<class T, class _Container = deque<T>>
	class queue
	{
	public:
		queue();
		queue(const _Container &container);
		size_t size() const;
		bool empty() const;
		void clear();
		const T& front() const;
		T& front();
		void push(const T &_Value);
		void pop();
	private:
		_Container deque_;
	};

	template<class T, class _Container>
	queue<T, _Container>::queue() : deque_()
	{
		;
	}
	template<class T, class _Container>
	queue<T, _Container>::queue(const _Container &container) : deque_(container)
	{
		;
	}

	template<class T, class _Container>
	size_t queue<T, _Container>::size() const
	{
		return deque_.size();
	}

	template<class T, class _Container>
	bool queue<T, _Container>::empty() const
	{
		return deque_.empty();
	}

	template<class T, class _Container>
	void queue<T, _Container>::clear()
	{
		deque_.clear();
	}

	template<class T, class _Container>
	const T& queue<T, _Container>::front() const
	{
		return deque_.front();
	}
	template<class T, class _Container>
	T& queue<T, _Container>::front()
	{
		return deque_.front();
	}

	template<class T, class _Container>
	void queue<T, _Container>::push(const T &_Value)
	{
		deque_.push_back(_Value);
	}
	template<class T, class _Container>
	void queue<T, _Container>::pop()
	{
		deque_.pop_front();
	}
}

#endif