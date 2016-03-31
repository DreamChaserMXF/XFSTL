#ifndef XF_VECTOR_CONST_ITERATOR_HPP
#define XF_VECTOR_CONST_ITERATOR_HPP


namespace xf
{
	template<class T>
	class _Vector_Const_Iterator
	{
	public:
		typedef const T& reference;
		typedef const T* pointer;
		typedef T value_type;

		_Vector_Const_Iterator() throw();
		explicit _Vector_Const_Iterator(const T *p) throw();

		const T& operator *() const throw();
		const T* operator ->() const throw();
		_Vector_Const_Iterator<T>& operator ++() throw();
		_Vector_Const_Iterator<T> operator ++(int) throw();
		_Vector_Const_Iterator<T>& operator --() throw();
		_Vector_Const_Iterator<T> operator --(int) throw();
		_Vector_Const_Iterator<T>& operator +=(int n) throw();
		_Vector_Const_Iterator<T> operator +(int n) const throw();
		_Vector_Const_Iterator<T>& operator -=(int n) throw();
		_Vector_Const_Iterator<T> operator -(int n) const throw();
		int operator -(const _Vector_Const_Iterator &right) throw();
		bool operator == (const _Vector_Const_Iterator<T> &iter) const throw();
		bool operator != (const _Vector_Const_Iterator<T> &iter) const throw();
		bool operator > (const _Vector_Const_Iterator<T> &iter) const throw();
		bool operator >= (const _Vector_Const_Iterator<T> &iter) const throw();
		bool operator < (const _Vector_Const_Iterator<T> &iter) const throw();
		bool operator <= (const _Vector_Const_Iterator<T> &iter) const throw();
		const T* p_;
	};

	template<class T>
	_Vector_Const_Iterator<T>::_Vector_Const_Iterator() throw() : p_(NULL)
	{
	}

	template<class T>
	_Vector_Const_Iterator<T>::_Vector_Const_Iterator(const T * p) throw() : p_(p)
	{
	}

	template<class T>
	const T& _Vector_Const_Iterator<T>::operator *() const throw()
	{
		return *p_;
	}

	template<class T>
	const T* _Vector_Const_Iterator<T>::operator ->() const throw()
	{
		return p_;
	}

	

	template<class T>
	_Vector_Const_Iterator<T>& _Vector_Const_Iterator<T>::operator ++() throw()
	{
		++p_;
		return *this;
	}

	template<class T>
	_Vector_Const_Iterator<T> _Vector_Const_Iterator<T>::operator ++(int) throw()
	{
		_Vector_Const_Iterator<T> iter(*this);
		++p_;
		return iter;
	}

	template<class T>
	_Vector_Const_Iterator<T>& _Vector_Const_Iterator<T>::operator --() throw()
	{
		--p_;
		return *this;
	}

	template<class T>
	_Vector_Const_Iterator<T> _Vector_Const_Iterator<T>::operator --(int) throw()
	{
		_Vector_Const_Iterator<T> iter(*this);
		--p_;
		return iter;
	}

	template<class T>
	_Vector_Const_Iterator<T>& _Vector_Const_Iterator<T>::operator +=(int n) throw()
	{
		p_ += n;
		return *this;
	}

	template<class T>
	_Vector_Const_Iterator<T> _Vector_Const_Iterator<T>::operator +(int n) const throw()
	{
		return _Vector_Const_Iterator<T>(p_ + n);
	}

	template<class T>
	_Vector_Const_Iterator<T>& _Vector_Const_Iterator<T>::operator -=(int n) throw()
	{
		p_ -= n;
		return *this;
	}

	template<class T>
	_Vector_Const_Iterator<T> _Vector_Const_Iterator<T>::operator -(int n) const throw()
	{
		return _Vector_Const_Iterator<T>(p_ - n);
	}

	template<class T>
	int _Vector_Const_Iterator<T>::operator -(const _Vector_Const_Iterator &right) throw()
	{
		return (p_ - right.p_);
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator == (const _Vector_Const_Iterator<T> &iter) const throw()
	{
		return p_ == iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator != (const _Vector_Const_Iterator<T> &iter) const throw()
	{
		return p_ != iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator > (const _Vector_Const_Iterator<T> &iter) const throw()
	{
		return p_ > iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator >= (const _Vector_Const_Iterator<T> &iter) const throw()
	{
		return p_ >= iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator < (const _Vector_Const_Iterator<T> &iter) const throw()
	{
		return p_ < iter.p_;
	}

	template<class T>
	bool _Vector_Const_Iterator<T>::operator <= (const _Vector_Const_Iterator<T> &iter) const throw()
	{
		return p_ <= iter.p_;
	}
}

#endif