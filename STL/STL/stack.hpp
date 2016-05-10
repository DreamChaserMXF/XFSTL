#ifndef XF_STACK_HPP
#define XF_STACK_HPP
#include "deque.hpp"
namespace xf
{
	template<class T, class _Container = deque<T>>
	class stack
	{
	public:
		stack();
		stack(const _Container &container);
		size_t size() const;
		bool empty() const;
		void clear();
		const T& top() const;
		T& top();
		void push(const T &_Value);
		void pop();
	private:
		_Container array_;
	};

	template<class T, class _Container>
	stack<T, _Container>::stack() : array_()
	{
		;
	}
	template<class T, class _Container>
	stack<T, _Container>::stack(const _Container &container) : array_(container)
	{
		;
	}

	template<class T, class _Container>
	size_t stack<T, _Container>::size() const
	{
		return array_.size();
	}

	template<class T, class _Container>
	bool stack<T, _Container>::empty() const
	{
		return array_.empty();
	}

	template<class T, class _Container>
	void stack<T, _Container>::clear()
	{
		array_.clear();
	}

	template<class T, class _Container>
	const T& stack<T, _Container>::top() const
	{
		return array_.back();
	}
	template<class T, class _Container>
	T& stack<T, _Container>::top()
	{
		return array_.back();
	}

	template<class T, class _Container>
	void stack<T, _Container>::push(const T &_Value)
	{
		array_.push_back(_Value);
	}
	template<class T, class _Container>
	void stack<T, _Container>::pop()
	{
		array_.pop_back();
	}

	
}

#endif