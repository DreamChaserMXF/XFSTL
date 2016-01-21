#ifndef XF_CONST_ITER_H
#define XF_CONST_ITER_H

namespace xf
{

	template<class T>
	class _Vector_const_iterator
	{
	public:
		_Vector_const_iterator() throw();
		explicit _Vector_const_iterator(T *p) throw();
		_Vector_const_iterator(const _Vector_const_iterator<T> &iter) throw();

		const T& operator *() const throw();
		const T* operator ->() const throw();
		_Vector_const_iterator<T> operator ++() throw();
		_Vector_const_iterator<T> operator ++(int) throw();
		_Vector_const_iterator<T> operator --() throw();
		_Vector_const_iterator<T> operator --(int) throw();
		//TODO +n, -n
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
	_Vector_const_iterator<T>::_Vector_const_iterator(const _Vector_const_iterator<T> &iter) throw() : p_(iter.p_)
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
	_Vector_const_iterator<T> _Vector_const_iterator<T>::operator ++() throw()
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
	_Vector_const_iterator<T> _Vector_const_iterator<T>::operator --() throw()
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