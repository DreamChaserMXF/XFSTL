#ifndef _VECTOR_ITERATOR
#define _VECTOR_ITERATOR

#include "_Vector_const_iterator.hpp"

namespace xf
{

	template<class T>
	class _Vector_iterator : public _Vector_const_iterator<T>
	{
	public:
		typedef T* pointer;
		typedef T& reference;
		//typedef T value_type;

		_Vector_iterator() throw();
		explicit _Vector_iterator(T *p) throw();	// 如果不加explicit，则_Vector_iterator就可以直接和指针对象相比较了
		// overwrite
		T& operator *() const throw();
		T* operator ->() const throw();
		_Vector_iterator<T>& operator ++() throw();
		_Vector_iterator<T> operator ++(int) throw();
		_Vector_iterator<T>& operator --() throw();
		_Vector_iterator<T> operator --(int) throw();
		_Vector_iterator<T>& operator +=(int n) throw();
		_Vector_iterator<T> operator +(int n) const throw();
		_Vector_iterator<T>& operator -=(int n) throw();
		_Vector_iterator<T> operator -(int n) const throw();
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
	T& _Vector_iterator<T>::operator *() const throw()
	{
		return *p_;
	}

	template<class T>
	T* _Vector_iterator<T>::operator ->() const throw()
	{
		return p_;
	}

	template<class T>
	_Vector_iterator<T>& _Vector_iterator<T>::operator ++() throw()
	{
		++p_;
		return *this;
	}

	template<class T>
	_Vector_iterator<T> _Vector_iterator<T>::operator ++(int) throw()
	{
		T *tmp = p_++;
		return _Vector_iterator<T>(tmp);
	}

	template<class T>
	_Vector_iterator<T>& _Vector_iterator<T>::operator --() throw()
	{
		--p_;
		return *this;
	}

	template<class T>
	_Vector_iterator<T> _Vector_iterator<T>::operator --(int) throw()
	{
		T *tmp = p_--;
		return _Vector_iterator<T>(tmp);
	}

	template<class T>
	_Vector_iterator<T>& _Vector_iterator<T>::operator +=(int n) throw()
	{
		p_ += n;
		return *this;
	}

	template<class T>
	_Vector_iterator<T> _Vector_iterator<T>::operator +(int n) const throw()
	{
		return _Vector_iterator<T>(p_ + n);
	}

	template<class T>
	_Vector_iterator<T>& _Vector_iterator<T>::operator -=(int n) throw()
	{
		p_ -= n;
		return *this;
	}

	template<class T>
	_Vector_iterator<T> _Vector_iterator<T>::operator -(int n) const throw()
	{
		return _Vector_iterator<T>(p_ - n);
	}
}

#endif