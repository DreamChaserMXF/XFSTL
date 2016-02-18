#ifndef _VECTOR_CONST_ITERATOR
#define _VECTOR_CONST_ITERATOR

namespace xf
{
	template<class T>
	class _Vector_const_iterator
	{
	public:
		typedef const T& reference;
		typedef const T* pointer;

		_Vector_const_iterator() throw();
		explicit _Vector_const_iterator(T *p) throw();

		const T& operator *() const throw();
		const T* operator ->() const throw();
		_Vector_const_iterator<T>& operator ++() throw();
		_Vector_const_iterator<T> operator ++(int) throw();
		_Vector_const_iterator<T>& operator --() throw();
		_Vector_const_iterator<T> operator --(int) throw();
		_Vector_const_iterator<T>& operator +=(int n) throw();
		_Vector_const_iterator<T> operator +(int n) const throw();
		_Vector_const_iterator<T>& operator -=(int n) throw();
		_Vector_const_iterator<T> operator -(int n) const throw();
		int operator -(const _Vector_const_iterator &right) throw();
		bool operator == (const _Vector_const_iterator<T> &iter) const throw();
		bool operator != (const _Vector_const_iterator<T> &iter) const throw();
	protected:
		T* p_;
	};

	template<class T>
	_Vector_const_iterator<T>::_Vector_const_iterator() throw() : p_(NULL)
	{
	}

	template<class T>
	_Vector_const_iterator<T>::_Vector_const_iterator(T *p) throw() : p_(p)
	{
	}

	template<class T>
	const T& _Vector_const_iterator<T>::operator *() const throw()
	{
		return *p_;
	}

	template<class T>
	const T* _Vector_const_iterator<T>::operator ->() const throw()
	{
		return p_;
	}

	

	template<class T>
	_Vector_const_iterator<T>& _Vector_const_iterator<T>::operator ++() throw()
	{
		++p_;
		return *this;
	}

	template<class T>
	_Vector_const_iterator<T> _Vector_const_iterator<T>::operator ++(int) throw()
	{
		_Vector_const_iterator<T> iter(*this);
		++p_;
		return iter;
	}

	template<class T>
	_Vector_const_iterator<T>& _Vector_const_iterator<T>::operator --() throw()
	{
		--p_;
		return *this;
	}

	template<class T>
	_Vector_const_iterator<T> _Vector_const_iterator<T>::operator --(int) throw()
	{
		_Vector_const_iterator<T> iter(*this);
		--p_;
		return iter;
	}

	template<class T>
	_Vector_const_iterator<T>& _Vector_const_iterator<T>::operator +=(int n) throw()
	{
		p_ += n;
		return *this;
	}

	template<class T>
	_Vector_const_iterator<T> _Vector_const_iterator<T>::operator +(int n) const throw()
	{
		return _Vector_const_iterator<T>(p_ + n);
	}

	template<class T>
	_Vector_const_iterator<T>& _Vector_const_iterator<T>::operator -=(int n) throw()
	{
		p_ -= n;
		return *this;
	}

	template<class T>
	_Vector_const_iterator<T> _Vector_const_iterator<T>::operator -(int n) const throw()
	{
		return _Vector_const_iterator<T>(p_ - n);
	}

	template<class T>
	int _Vector_const_iterator<T>::operator -(const _Vector_const_iterator &right) throw()
	{
		return (p_ - right.p_);
	}

	template<class T>
	bool _Vector_const_iterator<T>::operator == (const _Vector_const_iterator<T> &iter) const throw()
	{
		return p_ == iter.p_;
	}

	template<class T>
	bool _Vector_const_iterator<T>::operator != (const _Vector_const_iterator<T> &iter) const throw()
	{
		return p_ != iter.p_;
	}

}

#endif