#ifndef XF_MEMORY_HPP
#define XF_MEMORY_HPP

#include "_Iterator_Traits.hpp"

namespace xf
{

	template<class _Init_Iter, class _Fwd_Iter>
	void uninitialized_copy(_Init_Iter _First, _Init_Iter _Last, _Fwd_Iter _Dst)
	{
		while(_First != _Last)
		{
			new (&*_Dst) _Iterator_Traits<_Fwd_Iter>::value_type(*_First);
			++_First;
			++_Dst;
		}
	}

	template<class _Fwd_Iter, class _ValType>
	void uninitialized_fill(_Fwd_Iter _First, _Fwd_Iter _Last, _ValType Value)
	{
		while(_First != _Last)
		{
			new (&*_First) _ValType(Value);
			++_First;
		}
	}

}
#endif