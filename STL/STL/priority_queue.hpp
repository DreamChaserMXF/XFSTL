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
		priority_queue();
		priority_queue(const _Container &container);
		bool empty() const;
		size_t size() const;
		void push(const T &val);
		void pop();
		const T& top() const;
		T& top();

	//protected:
	private:
		void max_heapify();
		void max_heapify_descending(int index);
		void max_heapify_ascending(int index);
		_Container heap_;
		_Comparer comparer_;
	};

	template<class T, class _Container, class _Comparer>
	priority_queue<T, _Container, _Comparer>::priority_queue() : heap_(), comparer_()
	{
		;
	}
	template<class T, class _Container, class _Comparer>
	priority_queue<T, _Container, _Comparer>::priority_queue(const _Container &container) : heap_(container), comparer_()
	{
		max_heapify();
	}

	template<class T, class _Container, class _Comparer>
	bool priority_queue<T, _Container, _Comparer>::empty() const
	{
		return heap_.empty();
	}

	template<class T, class _Container, class _Comparer>
	size_t priority_queue<T, _Container, _Comparer>::size() const
	{
		return heap_.size();
	}

	template<class T, class _Container, class _Comparer>
	void priority_queue<T, _Container, _Comparer>::push(const T &val)
	{
		heap_.push_back(val);
		max_heapify_ascending(heap_.size() - 1);
	}

	template<class T, class _Container, class _Comparer>
	void priority_queue<T, _Container, _Comparer>::pop()
	{
		heap_.front() = heap_.back();
		heap_.pop_back();
		max_heapify_descending(0);
	}

	template<class T, class _Container, class _Comparer>
	const T& priority_queue<T, _Container, _Comparer>::top() const
	{
		return heap_.front();
	}

	template<class T, class _Container, class _Comparer>
	T& priority_queue<T, _Container, _Comparer>::top()
	{
		return heap_.front();
	}

	template<class T, class _Container, class _Comparer>
	void priority_queue<T, _Container, _Comparer>::max_heapify()
	{
		for(int i = static_cast<int>(heap_.size() / 2) - 1; i >= 0; --i)	// last node's index = length-1，its parent's index = (length-1-1)/2
		{
			max_heapify_descending(i);
		}
	}

	template<class T, class _Container, class _Comparer>
	void priority_queue<T, _Container, _Comparer>::max_heapify_descending(int index)
	{
		while(index >= 0)	// 用index来指示是否退出循环
		{
			size_t left_child = index * 2 + 1;
			size_t right_child = (index + 1) * 2;
			if(right_child < heap_.size() && comparer_(heap_[left_child], heap_[right_child]))
			{
				// right is larger than left
				// test if right is larger than index
				if(comparer_(heap_[index], heap_[right_child]))
				{
					// exchange the object pointed by index and right_child
					T tmp(heap_[index]);
					heap_[index] = heap_[right_child];
					heap_[right_child] = tmp;
					
					//max_heapify_descending(right_child);
					index = right_child;
				}
				else
				{
					index = -1;
				}
			}
			else if(left_child < heap_.size() && comparer_(heap_[index], heap_[left_child]))
			{
				// exchange the object pointed by index and left_child
				T tmp(heap_[index]);
				heap_[index] = heap_[left_child];
				heap_[left_child] = tmp;
				
				//max_heapify_descending(left_child);
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
			if(comparer_(heap_[parent], heap_[index]))
			{
				T tmp(heap_[index]);
				heap_[index] = heap_[parent];
				heap_[parent] = tmp;

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