#ifndef XF_ITERATOR_TRAITS_HPP
#define XF_ITERATOR_TRAITS_HPP

namespace xf
{

	template<class _Iter>
	struct _Iterator_Traits
	{
		typedef typename _Iter::pointer pointer;
		typedef typename _Iter::reference reference;
		typedef typename _Iter::value_type value_type;
	};

	template<class _Iter>
	struct _Iterator_Traits<_Iter*>
	{
		typedef typename _Iter* pointer;
		typedef typename _Iter& reference;
		typedef typename _Iter value_type;
	};

}
#endif