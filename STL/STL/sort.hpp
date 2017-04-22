#ifndef XF_SORT_HPP
#define XF_SORT_HPP

#include "_Iterator_Traits.hpp"
#include "heap_sort.hpp"
#include "quick_sort.hpp"

namespace xf
{
	template<class _Iter>
	void sort(_Iter first, _Iter last)
	{
		_sort(first, last, *(static_cast<_Iterator_Traits<_Iter>::pointer>(NULL)));
	}

	template<class _Iter, class _Comparer>
	void sort(_Iter first, _Iter last, const _Comparer &comparer)
	{
		_sort(first, last, comparer, *(static_cast<_Iterator_Traits<_Iter>::pointer>(NULL)));
	}

	template<class _Iter, class value_type>
	void _sort(_Iter first, _Iter last, const value_type &null_val)
	{
		//heapsort(first, last, null_val);
		quicksort(first, last, null_val);
	}

	template<class _Iter, class _Comparer, class value_type>
	void _sort(_Iter first, _Iter last, const _Comparer &comparer, const value_type &null_val)
	{
		//heapsort(first, last, comparer, null_val);
		quicksort(first, last, comparer, null_val);
	}


	

}

#endif