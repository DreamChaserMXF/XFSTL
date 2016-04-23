#ifndef XF_QUICK_SORT_HPP
#define XF_QUICK_SORT_HPP

#include "common.hpp"

namespace xf
{
	template<class _Iter, class value_type>
	void quicksort(_Iter first, _Iter last, const value_type &null_val)
	{
		int length = 0;
		while((length = last - first) > 1)	// end of recursion
		//if((length = last - first) > 1)	// end of recursion
		{
			// select pivot
			int pivot_index = rand() % length;
			// move the pivot to the first index
			swap(*first, *(first + pivot_index));
			// do the exchange
			_Iter i = first + 1, j = first + 1;
			while(j != last)
			{
				// *j is the new item
				if(*j < *first)	// 这里到底要不要取<=呢？
				{
					if(j != i)
					{
						swap(*i, *j);
					}
					++i;
				}
				++j;
			}
			// left if less than or equal to the pivot
			// right is greater than or equal to the pivot
			// now call quicksort recursively
			quicksort(first, i, null_val);
		
			// tail recursion optimization
			//quicksort(i, last, null_val);
			first = i;
		}
	}

	template<class _Iter, class _Comparer, class value_type>
	void quicksort(_Iter first, _Iter last, const _Comparer &comparer, const value_type &null_val)
	{
		int length = 0;
		while((length = last - first) > 1)	// end of recursion
		//if((length = last - first) > 1)	// end of recursion
		{
			// select pivot
			int pivot_index = rand() % length;
			// move the pivot to the first index
			swap(*first, *(first + pivot_index));
			// do the exchange
			_Iter i = first + 1, j = first + 1;
			while(j != last)
			{
				// *j is the new item
				if(comparer(*j, *first))	// 这里到底要不要取<=呢？
				{
					if(j != i)
					{
						swap(*i, *j);
					}
					++i;
				}
				++j;
			}
			// left if less than or equal to the pivot
			// right is greater than or equal to the pivot
			// now call quicksort recursively
			quicksort(first, i, comparer, null_val);
		
			// tail recursion optimization
			//quicksort(i, last, comparer, null_val);
			first = i;
		}
	}

}

#endif