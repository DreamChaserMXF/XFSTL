#ifndef XF_VECTOR_ITERATOR_HPP
#define XF_VECTOR_ITERATOR_HPP

#include "_Vector_Const_Iterator.hpp"

namespace xf
{

	template<class T>
	class _Vector_Iterator
	{
	public:
		typedef T* pointer;
		typedef T& reference;
		typedef T value_type;

		_Vector_Iterator() throw();
		explicit _Vector_Iterator(T *p) throw();	// 如果不加explicit，则_Vector_Iterator就可以直接和指针对象相比较了

		const T& operator *() const throw();
		T& operator *() throw();
		const T* operator ->() const throw();
		T* operator ->() throw();
		_Vector_Iterator<T>& operator ++() throw();
		_Vector_Iterator<T> operator ++(int) throw();
		_Vector_Iterator<T>& operator --() throw();
		_Vector_Iterator<T> operator --(int) throw();
		_Vector_Iterator<T>& operator +=(int n) throw();
		_Vector_Iterator<T> operator +(int n) const throw();
		_Vector_Iterator<T>& operator -=(int n) throw();
		_Vector_Iterator<T> operator -(int n) const throw();
		int operator -(const _Vector_Iterator<T> &iter) const throw();
		bool operator == (const _Vector_Iterator<T> &iter) const throw();
		bool operator != (const _Vector_Iterator<T> &iter) const throw();
		bool operator >  (const _Vector_Iterator<T> &iter) const throw();
		bool operator >= (const _Vector_Iterator<T> &iter) const throw();
		bool operator <  (const _Vector_Iterator<T> &iter) const throw();
		bool operator <= (const _Vector_Iterator<T> &iter) const throw();
		operator _Vector_Const_Iterator<T> () const throw();
	private:
		T *p_;
	};

	template<class T>
	_Vector_Iterator<T>::_Vector_Iterator() : _Vector_Const_Iterator() throw()
	{
	}

	template<class T>
	_Vector_Iterator<T>::_Vector_Iterator(T *p) throw() : p_(p)
	{
	}

	template<class T>
	const T& _Vector_Iterator<T>::operator *() const throw()
	{
		return *p_;
	}
	template<class T>
	T& _Vector_Iterator<T>::operator *() throw()
	{
		return (*p_);
	}

	template<class T>
	const T* _Vector_Iterator<T>::operator ->() const throw()
	{
		return p_;
	}
	template<class T>
	T* _Vector_Iterator<T>::operator ->() throw()
	{
		return p_;
	}

	template<class T>
	_Vector_Iterator<T>& _Vector_Iterator<T>::operator ++() throw()
	{
		++p_;
		return *this;
	}

	template<class T>
	_Vector_Iterator<T> _Vector_Iterator<T>::operator ++(int) throw()
	{
		T *tmp = p_++;
		return _Vector_Iterator<T>(tmp);
	}

	template<class T>
	_Vector_Iterator<T>& _Vector_Iterator<T>::operator --() throw()
	{
		--p_;
		return *this;
	}

	template<class T>
	_Vector_Iterator<T> _Vector_Iterator<T>::operator --(int) throw()
	{
		T *tmp = p_--;
		return _Vector_Iterator<T>(tmp);
	}

	template<class T>
	_Vector_Iterator<T>& _Vector_Iterator<T>::operator +=(int n) throw()
	{
		p_ += n;
		return *this;
	}

	template<class T>
	_Vector_Iterator<T> _Vector_Iterator<T>::operator +(int n) const throw()
	{
		return _Vector_Iterator<T>((p_ + n));
	}

	template<class T>
	_Vector_Iterator<T>& _Vector_Iterator<T>::operator -=(int n) throw()
	{
		p_ -= n;
		return *this;
	}

	template<class T>
	_Vector_Iterator<T> _Vector_Iterator<T>::operator -(int n) const throw()
	{
		return _Vector_Iterator<T>(p_ - n);
	}

	template<class T>
	int _Vector_Iterator<T>::operator -(const _Vector_Iterator<T> &iter) const throw()
	{
		return p_ - iter.p_;
	}

	template<class T>
	bool _Vector_Iterator<T>::operator == (const _Vector_Iterator<T> &iter) const throw()
	{
		return (p_ == iter.p_);
	}

	template<class T>
	bool _Vector_Iterator<T>::operator != (const _Vector_Iterator<T> &iter) const throw()
	{	
		return (p_ != iter.p_);
	}

	template<class T>
	bool _Vector_Iterator<T>::operator > (const _Vector_Iterator<T> &iter) const throw()
	{
		return (p_ > iter.p_);
	}

	template<class T>
	bool _Vector_Iterator<T>::operator >= (const _Vector_Iterator<T> &iter) const throw()
	{	
		return (p_ >= iter.p_);
	}

	template<class T>
	bool _Vector_Iterator<T>::operator < (const _Vector_Iterator<T> &iter) const throw()
	{
		return (p_ < iter.p_);
	}

	template<class T>
	bool _Vector_Iterator<T>::operator <= (const _Vector_Iterator<T> &iter) const throw()
	{	
		return (p_ <= iter.p_);
	}

	template<class T>
	_Vector_Iterator<T>::operator _Vector_Const_Iterator<T>() const throw()
	{
		return _Vector_Const_Iterator<T>(p_);
	}
}

#endif