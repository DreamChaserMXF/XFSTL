#ifndef XF_VECTOR_ITERATOR_HPP
#define XF_VECTOR_ITERATOR_HPP
#include <stdio.h>	// for NULL
#include "_Vector_Const_Iterator.hpp"
#include "_Iterator_Traits.hpp"

namespace xf
{

	template<class T>
	class _Vector_Iterator : public _Vector_Const_Iterator<T>
	{
	public:
		typedef T* pointer;
		typedef T& reference;
		typedef T value_type;
		typedef random_access_iterator_tag iterator_category;

		_Vector_Iterator();
		explicit _Vector_Iterator(T *p);	// 如果不加explicit，则_Vector_Iterator就可以直接和指针对象相比较了

		const T& operator *() const;	// 由于非const的*会把_Vector_Const_Iterator的cosnt类型的*覆盖，故这里还要重新定义
		T& operator *();
		const T* operator ->() const;
		T* operator ->();
		_Vector_Iterator<T>& operator ++();
		_Vector_Iterator<T> operator ++(int);
		_Vector_Iterator<T>& operator --();
		_Vector_Iterator<T> operator --(int);
		_Vector_Iterator<T>& operator +=(int n);
		_Vector_Iterator<T> operator +(int n) const;
		_Vector_Iterator<T>& operator -=(int n);
		_Vector_Iterator<T> operator -(int n) const;
		int operator -(const _Vector_Const_Iterator<T> &right) const;
	};

	template<class T>
	_Vector_Iterator<T>::_Vector_Iterator() : p_(NULL)
	{
	}

	template<class T>
	_Vector_Iterator<T>::_Vector_Iterator(T *p) : _Vector_Const_Iterator<T>(p)
	{
	}

	template<class T>
	const T& _Vector_Iterator<T>::operator *() const
	{
		return (*p_);
	}

	template<class T>
	T& _Vector_Iterator<T>::operator *()
	{
		return (*p_);
	}

	template<class T>
	const T* _Vector_Iterator<T>::operator ->() const
	{
		return p_;
	}

	template<class T>
	T* _Vector_Iterator<T>::operator ->()
	{
		return p_;
	}

	template<class T>
	_Vector_Iterator<T>& _Vector_Iterator<T>::operator ++()
	{
		++p_;
		return *this;
	}

	template<class T>
	_Vector_Iterator<T> _Vector_Iterator<T>::operator ++(int)
	{
		T *tmp = p_++;
		return _Vector_Iterator<T>(tmp);
	}

	template<class T>
	_Vector_Iterator<T>& _Vector_Iterator<T>::operator --()
	{
		--p_;
		return *this;
	}

	template<class T>
	_Vector_Iterator<T> _Vector_Iterator<T>::operator --(int)
	{
		T *tmp = p_--;
		return _Vector_Iterator<T>(tmp);
	}

	template<class T>
	_Vector_Iterator<T>& _Vector_Iterator<T>::operator +=(int n)
	{
		p_ += n;
		return *this;
	}

	template<class T>
	_Vector_Iterator<T> _Vector_Iterator<T>::operator +(int n) const
	{
		return _Vector_Iterator<T>((p_ + n));
	}

	template<class T>
	_Vector_Iterator<T>& _Vector_Iterator<T>::operator -=(int n)
	{
		p_ -= n;
		return *this;
	}

	template<class T>
	_Vector_Iterator<T> _Vector_Iterator<T>::operator -(int n) const
	{
		return _Vector_Iterator<T>(p_ - n);
	}

	template<class T>
	int _Vector_Iterator<T>::operator -(const _Vector_Const_Iterator<T> &right) const
	{
		//return *(_Vector_Const_Iterator<T>*)this - right;
		return *static_cast<const _Vector_Const_Iterator<T>*>(this) - right;
	}
}

#endif