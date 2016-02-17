#ifndef _VECTOR_REVERSE_CONST_ITERATOR
#define _VECTOR_REVERSE_CONST_ITERATOR

namespace xf
{

	template<class T>
	class _Vector_reverse_const_iterator : public _Vector_const_iterator<T>
	{
	public:
		_Vector_reverse_const_iterator() throw();
		explicit _Vector_reverse_const_iterator(T *p) throw();
		//_Vector_reverse_const_iterator(const _Vector_reverse_const_iterator<T> &iter) throw();
		_Vector_const_iterator<T> base() throw();
		// Overwrite
		_Vector_reverse_const_iterator<T> operator ++() throw();
		_Vector_reverse_const_iterator<T> operator ++(int) throw();
		_Vector_reverse_const_iterator<T> operator --() throw();
		_Vector_reverse_const_iterator<T> operator --(int) throw();
		_Vector_reverse_const_iterator<T> operator +(int n) throw();
		_Vector_reverse_const_iterator<T> operator -(int n) throw();
	private:
	};

	template<class T>
	_Vector_reverse_const_iterator<T>::_Vector_reverse_const_iterator() throw() : _Vector_const_iterator()
	{
	}

	template<class T>
	_Vector_reverse_const_iterator<T>::_Vector_reverse_const_iterator(T *p) throw() : _Vector_const_iterator(p)
	{
	}

	//template<class T>
	//_Vector_reverse_const_iterator<T>::_Vector_reverse_const_iterator(const _Vector_reverse_const_iterator<T> &iter) throw() : _Vector_const_iterator(iter)
	//{
	//}

	template<class T>
	_Vector_const_iterator<T> _Vector_reverse_const_iterator<T>::base() throw()
	{
		return _Vector_const_iterator<T>(p_ + 1);
	}

	template<class T>
	_Vector_reverse_const_iterator<T> _Vector_reverse_const_iterator<T>::operator ++() throw()
	{
		--p_;
		return *this;
	}

	template<class T>
	_Vector_reverse_const_iterator<T> _Vector_reverse_const_iterator<T>::operator ++(int) throw()
	{
		_Vector_reverse_const_iterator iter(*this);
		--p_;
		return iter;
	}


	template<class T>
	_Vector_reverse_const_iterator<T> _Vector_reverse_const_iterator<T>::operator --() throw()
	{
		++p_;
		return *this;
	}

	template<class T>
	_Vector_reverse_const_iterator<T> _Vector_reverse_const_iterator<T>::operator --(int) throw()
	{
		_Vector_reverse_const_iterator iter(*this);
		++p_;
		return iter;
	}

	template<class T>
	_Vector_reverse_const_iterator<T> _Vector_reverse_const_iterator<T>::operator +(int n) throw()
	{
		p_ -= n;
		return *this;
	}

	template<class T>
	_Vector_reverse_const_iterator<T> _Vector_reverse_const_iterator<T>::operator -(int n) throw()
	{
		p_ += n;
		return *this;
	}

}
#endif