#ifndef _VECTOR_ITERATOR
#define _VECTOR_ITERATOR

#include "_Vector_const_iterator.hpp"

namespace xf
{

	template<class T>
	class _Vector_iterator : public _Vector_const_iterator<T>
	{
	public:
		_Vector_iterator() throw();
		explicit _Vector_iterator(T *p) throw();	// 如果不加explicit，则_Vector_iterator就可以直接和指针对象相比较了
		_Vector_iterator(const _Vector_iterator<T> &iter) throw();
		// overwrite
		T& operator *() const throw();
		T* operator ->() const throw();
	};

	template<class T>
	_Vector_iterator<T>::_Vector_iterator() : _Vector_const_iterator() throw()
	{
	}

	template<class T>
	_Vector_iterator<T>::_Vector_iterator(T *p) throw() : _Vector_const_iterator(p)
	{
	}
	template<class T>
	_Vector_iterator<T>::_Vector_iterator(const _Vector_iterator<T> &iter) throw() : _Vector_const_iterator(iter)
	{
	}

	template<class T>
	T& _Vector_iterator<T>::operator *() const throw()
	{
		return *p_;
	}

	template<class T>
	T* _Vector_iterator<T>::operator ->() const throw()
	{
		return p_;
	}

}

#endif