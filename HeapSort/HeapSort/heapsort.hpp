
template<class _Iter, class T>
void heapsort(_Iter first, _Iter last, bool *compare(const T &item1, const T &item2), bool descending = false)
{
	
}

template<class _Iter>
void heapsort(_Iter first, _Iter last, bool descending = false)
{
	if(descending)
	{
		heapsort_descending(first, last);
	}
	else
	{
		heapsort_ascending(first, last);
	}
}

template<class _Iter>
void heapsort_ascending(_Iter first, _Iter last)
{
	int length = last - first;
	build_max_heap(first, length);
	for(int i = length - 1; i >= 0; --i)
	{
		// exchange item[0] and item[i]
		
	}
}

template<class _Iter>
void heapsort_descending(_Iter first, _Iter last)
{

}