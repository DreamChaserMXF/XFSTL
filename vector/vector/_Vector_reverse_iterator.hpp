#ifndef XF_REVERSE_ITER_H
#define XF_REVERSE_ITER_H

#include "_Vector_reverse_const_iterator.hpp"
namespace xf
{
	template<class T>
	class _Vector_reverse_iterator : public _Vector_reverse_const_iterator<T>
	{
	public:
		_Vector_reverse_iterator() throw();
		explicit _Vector_reverse_iterator(T *p) throw();	// 如果不加explicit，则_Vector_reverse_iterator就可以直接和指针对象相比较了
		_Vector_reverse_iterator(const _Vector_reverse_iterator<T> &iter) throw();
		T& operator *() const throw();
		T* operator ->() const throw();
	};

	template<class T>
	_Vector_reverse_iterator<T>::_Vector_reverse_iterator() throw() : _Vector_reverse_const_iterator()
	{
	}

	template<class T>
	_Vector_reverse_iterator<T>::_Vector_reverse_iterator(T *p) throw() : _Vector_reverse_const_iterator(p)
	{
	}

	template<class T>
	_Vector_reverse_iterator<T>::_Vector_reverse_iterator(const _Vector_reverse_iterator<T> &iter) throw() : _Vector_reverse_const_iterator(iter)
	{
	}

	template<class T>
	T& _Vector_reverse_iterator<T>::operator *() const throw()
	{
		return *p_;
	}

	template<class T>
	T* _Vector_reverse_iterator<T>::operator ->() const throw()
	{
		return p_;
	}

}
#endif