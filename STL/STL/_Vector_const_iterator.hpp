#ifndef XF_VECTOR_CONST_ITERATOR_HPP
#define XF_VECTOR_CONST_ITERATOR_HPP

#include "_Iterator_Traits.hpp"

namespace xf
{
	template<class T>
	class _Vector_Const_Iterator
	{
	public:
		typedef const T& reference;
		typedef const T* pointer;
		typedef T value_type;
		typedef random_access_iterator_tag iterator_category;

		_Vector_Const_Iterator();
		explicit _Vector_Const_Iterator(T *p);

		const T& operator *() const;
		const T* operator ->() const;
		_Vector_Const_Iterator<T>& operator ++();
		_Vector_Const_Iterator<T> operator ++(int);
		_Vector_Const_Iterator<T>& operator --();
		_Vector_Const_Iterator<T> operator --(int);
		_Vector_Const_Iterator<T>& operator +=(int n);
		_Vector_Const_Iterator<T> operator +(int n) const;
		_Vector_Const_Iterator<T>& operator -=(int n);
		_Vector_Const_Iterator<T> operator -(int n) const;
		int operator -(const _Vector_Const_Iterator<T> &right) const;
		bool operator == (const _Vector_Const_Iterator<T> &iter) const;
		bool operator != (const _Vector_Const_Iterator<T> &iter) const;
		bool operator > (const _Vector_Const_Iterator<T> &iter) const;
		bool operator >= (const _Vector_Const_Iterator<T> &iter) const;
		bool operator < (const _Vector_Const_Iterator<T> &iter) const;
		bool operator <= (const _Vector_Const_Iterator<T> &iter) const;
		T* p_;
	};

	template<class T>
	_Vector_Const_Iterator<T>::_Vector_Const_Iterator() : p_(NULL)
	{
	}

	template<class T>
	_Vector_Const_Iterator<T>::_Vector_Const_Iterator(T * p) : p_(p)
	{
	}

	template<class T>
	const T& _Vector_Const_Iterator<T>::operator *() const
	{
		return *p_;
	}

	template<class T>
	const T* _Vector_Const_Iterator<T>::operator ->() const
	{
		return p_;
	}

	

	template<class T>
	_Vector_Const_Iterator<T>& _Vector_Const_Iterator<T>::operator ++()
	{
		++p_;
		return *this;
	}

	template<class T>
	_Vector_Const_Iterator<T> _Vector_Const_Iterator<T>::operator ++(int)
	{
		_Vector_Const_Iterator<T> iter(*this);
		++p_;
		return iter;
	}

	template<class T>
	_Vector_Const_Iterator<T>& _Vector_Const_Iterator<T>::operator --()
	{
		--p_;
		return *this;
	}

	template<class T>
	_Vector_Const_Iterator<T> _Vector_Const_Iterator<T>::operator --(int)
	{
		_Vector_Const_Iterator<T> iter(*this);
		--p_;
		return iter;
	}

	template<class T>
	_Vector_Const_Iterator<T>& _Vector_Const_Iterator<T>::operator +=(int n)
	{
		p_ += n;
		return *this;
	}

	template<class T>
	_Vector_Const_Iterator<T> _Vector_Const_Iterator<T>::operator +(int n) const
	{
		return _Vector_Const_Iterator<T>(p_ + n);
	}

	template<class T>
	_Vector_Const_Iterator<T>& _Vector_Const_Iterator<T>::operator -=(int n)
	{
		p_ -= n;
		return *this;
	}

	template<class T>
	_Vector_Const_Iterator<T> _Vector_Const_Iterator<T>::operator -(int n) const
	{
		return _Vector_Const_Iterator<T>(p_ - n);
	}

	template<class T>
	int _Vector_Const_Iterator<T>::operator -(const _Vector_Const_Iterator<T> &right) const
	{
		return (p_ - right.p_);
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator == (const _Vector_Const_Iterator<T> &iter) const
	{
		return p_ == iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator != (const _Vector_Const_Iterator<T> &iter) const
	{
		return p_ != iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator > (const _Vector_Const_Iterator<T> &iter) const
	{
		return p_ > iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator >= (const _Vector_Const_Iterator<T> &iter) const
	{
		return p_ >= iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator < (const _Vector_Const_Iterator<T> &iter) const
	{
		return p_ < iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator <= (const _Vector_Const_Iterator<T> &iter) const
	{
		return p_ <= iter.p_;
	}
}

#endif