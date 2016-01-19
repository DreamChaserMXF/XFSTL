#ifndef XF_ITER_H
#define XF_ITER_H

#include "_Const_Iter.hpp"

template<class T>
class _Iter : public _Const_Iter<T>
{
public:
	_Iter();
	explicit _Iter(T *p);	// 如果不加explicit，则_Iter就可以直接和指针对象相比较了
	_Iter(const _Iter<T> &iter);
	T operator *() const;
	T* operator ->() const;
};

template<class T>
_Iter<T>::_Iter() : _Const_Iter()
{
}

template<class T>
_Iter<T>::_Iter(T *p) : _Const_Iter(p)
{
}
template<class T>
_Iter<T>::_Iter(const _Iter<T> &iter) : _Const_Iter(iter)
{
}

template<class T>
T _Iter<T>::operator *() const
{
	return *p_;
}

template<class T>
T* _Iter<T>::operator ->() const
{
	return p_;
}

#endif