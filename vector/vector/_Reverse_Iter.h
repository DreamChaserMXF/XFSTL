#ifndef XF_REVERSE_ITER_H
#define XF_REVERSE_ITER_H

#include "_Reverse_Const_Iter.hpp"

template<class T>
class _Reverse_Iter : public _Reverse_Const_Iter<T>
{
public:
	_Reverse_Iter();
	explicit _Reverse_Iter(T *p);	// 如果不加explicit，则_Reverse_Iter就可以直接和指针对象相比较了
	_Reverse_Iter(const _Reverse_Iter<T> &iter);
	T operator *() const;
	T* operator ->() const;
};

template<class T>
_Reverse_Iter<T>::_Reverse_Iter() : _Reverse_Const_Iter()
{
}

template<class T>
_Reverse_Iter<T>::_Reverse_Iter(T *p) : _Reverse_Const_Iter(p)
{
}

template<class T>
_Reverse_Iter<T>::_Reverse_Iter(const _Reverse_Iter<T> &iter) : _Reverse_Const_Iter(iter)
{
}

template<class T>
T _Reverse_Iter<T>::operator *() const
{
	return *p_;
}

template<class T>
T* _Reverse_Iter<T>::operator ->() const
{
	return p_;
}

#endif