#ifndef XF_HEAP_SORT_HPP
#define XF_HEAP_SORT_HPP

namespace xf
{
	//template<class _Iter, class value_type>
	//void max_heapify(_Iter first, int length, int index, const value_type &null_val)
	//{
	//	int left_child = index * 2 + 1;
	//	int right_child = (index + 1) * 2;
	//	if(right_child < length && *(first + right_child) > *(first + left_child))
	//	{
	//		// right is larger than left
	//		// test if right is larger than index
	//		if(*(first + right_child) > *(first + index))
	//		{
	//			// exchange the object pointed by index and right_child
	//			value_type tmp(*(first + index));
	//			*(first + index) = *(first + right_child);
	//			*(first + right_child) = tmp;
	//			max_heapify(first, length, right_child, null_val);
	//		}
	//	}
	//	else if(left_child < length && *(first + left_child) > *(first + index))
	//	{
	//		// exchange the object pointed by index and left_child
	//		value_type tmp(*(first + index));
	//		*(first + index) = *(first + left_child);
	//		*(first + left_child) = tmp;
	//		max_heapify(first, length, left_child, null_val);
	//	}
	//}

	// 尾递归优化后的max_heapify
	// first： 数组首元素的迭代器
	// length：数组长度
	// index:  要最大化堆的节点序号
	// null_val: 空的数组元素值
	template<class _Iter, class value_type>
	void max_heapify(_Iter first, int length, int index, const value_type &null_val)
	{
		while(index >= 0)	// 用index来指示尾递归的结束条件
		{
			int left_child = index * 2 + 1;
			int right_child = (index + 1) * 2;
			if(right_child < length && *(first + right_child) > *(first + left_child))
			{
				// right is larger than left
				// test if right is larger than index
				if(*(first + right_child) > *(first + index))
				{
					// exchange the object pointed by index and right_child
					value_type tmp(*(first + index));
					*(first + index) = *(first + right_child);
					*(first + right_child) = tmp;
					
					//max_heapify(first, length, right_child, null_val);
					index = right_child;
				}
				else
				{
					index = -1;
				}
			}
			else if(left_child < length && *(first + left_child) > *(first + index))
			{
				// exchange the object pointed by index and left_child
				value_type tmp(*(first + index));
				*(first + index) = *(first + left_child);
				*(first + left_child) = tmp;
				
				//max_heapify(first, length, left_child, null_val);
				index = left_child;
			}
			else
			{
				index = -1;
			}
		}
	}

	template<class _Iter, class value_type>
	void build_max_heap(_Iter first, int length, const value_type &null_val)
	{
		for(int i = length / 2 - 1; i >= 0; --i)	// last node's index = length-1，its parent's index = (length-1-1)/2
		{
			max_heapify(first, length, i, null_val);
		}
	}

	template<class _Iter, class value_type>
	void heapsort(_Iter first, _Iter last, const value_type &null_val)
	{
		int length = last - first;
		// build max heap
		build_max_heap(first, length, null_val);
		// select max value successively
		// then max heapify the heap
		for(int i = length - 1; i > 0; --i)
		{
			// exchange item[0] and item[i]
			value_type tmp(*first);
			*first = *(first + i);
			*(first + i) = tmp;
			// max heapify
			max_heapify(first, i, 0, null_val);
		}
	}




	template<class _Iter, class _Comparer, class value_type>
	void max_heapify(_Iter first, int length, int index, const _Comparer &comparer, const value_type &null_val)
	{
		int left_child = index * 2 + 1;
		int right_child = (index + 1) * 2;
		if(right_child < length && comparer(*(first + left_child), *(first + right_child)))
		{
			// right is larger than left
			// test if right is larger than index
			if(comparer(*(first + index), *(first + right_child)))
			{
				// exchange the object pointed by index and right_child
				value_type tmp(*(first + index));
				*(first + index) = *(first + right_child);
				*(first + right_child) = tmp;
				max_heapify(first, length, right_child, comparer, null_val);
			}
		}
		else if(left_child < length && comparer(*(first + index), *(first + left_child)))
		{
			// exchange the object pointed by index and left_child
			value_type tmp(*(first + index));
			*(first + index) = *(first + left_child);
			*(first + left_child) = tmp;
			max_heapify(first, length, left_child, comparer, null_val);
		}
	}

	template<class _Iter, class _Comparer, class value_type>
	void build_max_heap(_Iter first, int length, const _Comparer &comparer, const value_type &null_val)
	{
		for(int i = length / 2 - 1; i >= 0; --i)	// last node's index = length-1，its parent's index = (length-1-1)/2
		{
			max_heapify(first, length, i, comparer, null_val);
		}
	}

	template<class _Iter, class _Comparer, class value_type>
	void heapsort(_Iter first, _Iter last, const _Comparer &comparer, const value_type &null_val)
	{
		int length = last - first;
		// build max heap
		build_max_heap(first, length, comparer, null_val);
		// select max value successively
		// then max heapify the heap
		for(int i = length - 1; i > 0; --i)
		{
			// exchange item[0] and item[i]
			value_type tmp(*first);
			*first = *(first + i);
			*(first + i) = tmp;
			// max heapify
			max_heapify(first, i, 0, comparer, null_val);
		}
	}



}

#endif