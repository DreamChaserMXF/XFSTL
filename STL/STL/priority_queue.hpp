#ifndef XF_PRIORITY_QUEUE_HPP
#define XF_PRIORITY_QUEUE_HPP

#include "vector.hpp"

namespace xf
{
	template<class T>
	class _LessThan
	{
	public:
		bool operator () (const T &lhs, const T &rhs) const
		{
			return lhs < rhs;
		}
	};

	template<class T, class _Container = vector<T>, class _Comparer = _LessThan<T>>
	class priority_queue
	{
	public:
		//typedef T value_type;
		bool empty() const;
		size_t size() const;
		void push(const T &val);
		void pop();
		const T& top() const;
		T& top();

	protected:
		void max_heapify_descending(int index);
		void max_heapify_ascending(int index);
		_Container arr_;
		_Comparer comparer_;
	};

	template<class T, class _Container, class _Comparer>
	bool priority_queue<T, _Container, _Comparer>::empty() const
	{
		return arr_.empty();
	}

	template<class T, class _Container, class _Comparer>
	size_t priority_queue<T, _Container, _Comparer>::size() const
	{
		return arr_.size();
	}

	template<class T, class _Container, class _Comparer>
	void priority_queue<T, _Container, _Comparer>::push(const T &val)
	{
		arr_.push_back(val);
		max_heapify_ascending(arr_.size() - 1);
	}

	template<class T, class _Container, class _Comparer>
	void priority_queue<T, _Container, _Comparer>::pop()
	{
		arr_.front() = arr_.back();
		arr_.pop_back();
		max_heapify_descending(0);
	}

	template<class T, class _Container, class _Comparer>
	const T& priority_queue<T, _Container, _Comparer>::top() const
	{
		return arr_.front();
	}

	template<class T, class _Container, class _Comparer>
	T& priority_queue<T, _Container, _Comparer>::top()
	{
		return arr_.front();
	}

	template<class T, class _Container, class _Comparer>
	void priority_queue<T, _Container, _Comparer>::max_heapify_descending(int index)
	{
		while(index >= 0)	// 用index来指示是否退出循环
		{
			size_t left_child = index * 2 + 1;
			size_t right_child = (index + 1) * 2;
			if(right_child < arr_.size() && comparer_(arr_[left_child], arr_[right_child]))
			{
				// right is larger than left
				// test if right is larger than index
				if(comparer_(arr_[index], arr_[right_child]))
				{
					// exchange the object pointed by index and right_child
					T tmp(arr_[index]);
					arr_[index] = arr_[right_child];
					arr_[right_child] = tmp;
					
					//max_heapify(right_child);
					index = right_child;
				}
				else
				{
					index = -1;
				}
			}
			else if(left_child < arr_.size() && comparer_(arr_[index], arr_[left_child]))
			{
				// exchange the object pointed by index and left_child
				T tmp(arr_[index]);
				arr_[index] = arr_[left_child];
				arr_[left_child] = tmp;
				
				//max_heapify(left_child);
				index = left_child;
			}
			else
			{
				index = -1;
			}
		}
	}

	template<class T, class _Container, class _Comparer>
	void priority_queue<T, _Container, _Comparer>::max_heapify_ascending(int index)
	{
		while(index > 0)
		{
			int parent = (index - 1) / 2;
			if(comparer_(arr_[parent], arr_[index]))
			{
				T tmp(arr_[index]);
				arr_[index] = arr_[parent];
				arr_[parent] = tmp;

				index = parent;
			}
			else
			{
				//index = -1;
				break;
			}
		}
	}
}

#endif