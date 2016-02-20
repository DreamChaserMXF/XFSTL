#ifndef _VECTOR_ITERATOR
#define _VECTOR_ITERATOR

#include "_Vector_const_iterator.hpp"

namespace xf
{

	template<class T>
	class _Vector_iterator
	{
	public:
		typedef T* pointer;
		typedef T& reference;

		_Vector_iterator() throw();
		explicit _Vector_iterator(T *p) throw();	// 如果不加explicit，则_Vector_iterator就可以直接和指针对象相比较了
		// overwrite
		const T& operator *() const throw();
		T& operator *() throw();
		const T* operator ->() const throw();
		T* operator ->() throw();
		_Vector_iterator<T>& operator ++() throw();
		_Vector_iterator<T> operator ++(int) throw();
		_Vector_iterator<T>& operator --() throw();
		_Vector_iterator<T> operator --(int) throw();
		_Vector_iterator<T>& operator +=(int n) throw();
		_Vector_iterator<T> operator +(int n) const throw();
		_Vector_iterator<T>& operator -=(int n) throw();
		_Vector_iterator<T> operator -(int n) const throw();
		bool operator == (const _Vector_iterator<T> &iter) const throw();
		bool operator != (const _Vector_iterator<T> &iter) const throw();
		bool operator >  (const _Vector_iterator<T> &iter) const throw();
		bool operator >= (const _Vector_iterator<T> &iter) const throw();
		bool operator <  (const _Vector_iterator<T> &iter) const throw();
		bool operator <= (const _Vector_iterator<T> &iter) const throw();
		operator _Vector_const_iterator<T> () const throw();

		T *p_;
	};

	template<class T>
	_Vector_iterator<T>::_Vector_iterator() : _Vector_const_iterator() throw()
	{
	}

	template<class T>
	_Vector_iterator<T>::_Vector_iterator(T *p) throw() : p_(p)
	{
	}

	template<class T>
	const T& _Vector_iterator<T>::operator *() const throw()
	{
		return *p_;
	}
	template<class T>
	T& _Vector_iterator<T>::operator *() throw()
	{
		return (*p_);
	}

	template<class T>
	const T* _Vector_iterator<T>::operator ->() const throw()
	{
		return p_;
	}
	template<class T>
	T* _Vector_iterator<T>::operator ->() throw()
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
		return _Vector_iterator<T>((p_ + n));
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

	template<class T>
	bool _Vector_iterator<T>::operator == (const _Vector_iterator<T> &iter) const throw()
	{
		return (p_ == iter.p_);
	}

	template<class T>
	bool _Vector_iterator<T>::operator != (const _Vector_iterator<T> &iter) const throw()
	{	
		return (p_ != iter.p_);
	}

	template<class T>
	bool _Vector_iterator<T>::operator > (const _Vector_iterator<T> &iter) const throw()
	{
		return (p_ > iter.p_);
	}

	template<class T>
	bool _Vector_iterator<T>::operator >= (const _Vector_iterator<T> &iter) const throw()
	{	
		return (p_ >= iter.p_);
	}

	template<class T>
	bool _Vector_iterator<T>::operator < (const _Vector_iterator<T> &iter) const throw()
	{
		return (p_ < iter.p_);
	}

	template<class T>
	bool _Vector_iterator<T>::operator <= (const _Vector_iterator<T> &iter) const throw()
	{	
		return (p_ <= iter.p_);
	}

	template<class T>
	_Vector_iterator<T>::operator _Vector_const_iterator<T>() const throw()
	{
		return _Vector_const_iterator<T>(p_);
	}
}

#endif