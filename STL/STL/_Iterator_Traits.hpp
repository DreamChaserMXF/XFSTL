#ifndef XF_ITERATOR_TRAITS_HPP
#define XF_ITERATOR_TRAITS_HPP

namespace xf
{

	class input_iterator_tag{};
	class output_iterator_tag{};
	class forward_iterator_tag : public input_iterator_tag, public output_iterator_tag
	{};
	class bi_directional_iterator_tag : public forward_iterator_tag
	{};
	class random_access_iterator_tag : public bi_directional_iterator_tag
	{};

	template<class _Iter>
	struct _Iterator_Traits
	{
		typedef typename _Iter::pointer pointer;
		typedef typename _Iter::reference reference;
		typedef typename _Iter::value_type value_type;
		typedef typename _Iter::iterator_category iterator_category;
	};

	template<class _Iter>
	struct _Iterator_Traits<_Iter*>
	{
		typedef typename _Iter* pointer;
		typedef typename _Iter& reference;
		typedef typename _Iter value_type;
		typedef typename random_access_iterator_tag iterator_category;
	};

	template<class _Iter>
	typename _Iterator_Traits<_Iter>::iterator_category _Get_Iter_Category_Var(_Iter)
	{
		typename _Iterator_Traits<_Iter>::iterator_category cat;
		return cat;
	}

	//template<class _Input_Iter>
	//int _distance(_Input_Iter _First, _Input_Iter _Last, input_iterator_tag)
	//{
	//	int diff = 0;
	//	for(; _First != _Last; ++_First)
	//	{
	//		++diff;
	//	}
	//	return diff;
	//}

	//template<class _Output_Iter>
	//int _distance(_Output_Iter _First, _Output_Iter _Last, output_iterator_tag)
	//{
	//	int diff = 0;
	//	for(; _First != _Last; ++_First)
	//	{
	//		++diff;
	//	}
	//	return diff;
	//}

	template<class _Fwd_Iter>
	int _distance(_Fwd_Iter _First, _Fwd_Iter _Last, forward_iterator_tag)
	{
		int diff = 0;
		for(; _First != _Last; ++_First)
		{
			++diff;
		}
		return diff;
	}

	template<class _Rnd_Iter>
	int _distance(_Rnd_Iter _First, _Rnd_Iter _Last, random_access_iterator_tag)
	{
		return _Last - _First;
	}

	template<class T>
	int distance(const T &_First, const T &_Last)
	{
		return _distance(_First, _Last, _Get_Iter_Category_Var(_First));
	}
}
#endif