#ifndef _REVERSE_ITERATOR_HPP
#define _REVERSE_ITERATOR_HPP

namespace xf
{
	template<class T>
	class _Reverse_Iterator
	{
	public:
		typedef typename T::reference reference;
		typedef typename T::pointer pointer;

		_Reverse_Iterator();
		explicit _Reverse_Iterator(const pointer right) throw();
		explicit _Reverse_Iterator(const T &right) throw();
		// 用于类型转换的构造函数
		template<class Other>
		_Reverse_Iterator(const _Reverse_Iterator<Other> &right) throw();

		T base() const throw();
		reference operator *() const throw();
		pointer operator ->() const throw();
		_Reverse_Iterator<T>& operator ++() throw();
		_Reverse_Iterator<T> operator ++(int) throw();
		_Reverse_Iterator<T>& operator --() throw();
		_Reverse_Iterator<T> operator --(int) throw();
		_Reverse_Iterator<T>& operator +=(int n) throw();
		_Reverse_Iterator<T> operator +(int n) throw();
		_Reverse_Iterator<T>& operator -=(int n) throw();
		_Reverse_Iterator<T> operator -(int n) throw();

		bool operator == (const _Reverse_Iterator &right) const throw();
		bool operator != (const _Reverse_Iterator &right) const throw();
	private:
		T iter_;
	};

	template<class T>
	_Reverse_Iterator<T>::_Reverse_Iterator() throw() : iter_()
	{
		;
	}

	template<class T>
	_Reverse_Iterator<T>::_Reverse_Iterator(const pointer right) throw() : iter_(right)
	{
		;
	}

	template<class T>
	_Reverse_Iterator<T>::_Reverse_Iterator(const T &right) : iter_(right - 1)
	{
		;
	}

	template<class T> template<class Other>
	_Reverse_Iterator<T>::_Reverse_Iterator(const _Reverse_Iterator<Other> &right) throw() : iter_(right.base() - 1)
	{
		;
	}

	template<class T>
	T _Reverse_Iterator<T>::base() const throw()
	{
		return iter_ + 1;
	}

	template<class T>
	typename _Reverse_Iterator<T>::reference _Reverse_Iterator<T>::operator*() const throw()
	{
		return *iter_;
	}

	template<class T>
	typename _Reverse_Iterator<T>::pointer _Reverse_Iterator<T>::operator ->() const throw()
	{
		return &(*iter_);
	}

	template<class T>
	_Reverse_Iterator<T>& _Reverse_Iterator<T>::operator ++() throw()
	{
		--iter_;
		return *this;
	}

	template<class T>
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator ++(int) throw()
	{
		T tmp = iter_;
		--iter_;
		return tmp;
	}

	template<class T>
	_Reverse_Iterator<T>& _Reverse_Iterator<T>::operator --() throw()
	{
		++iter_;
		return *this;
	}

	template<class T>
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator --(int) throw()
	{
		T tmp = iter_;
		++iter_;
		return tmp;
	}

	template<class T>
	_Reverse_Iterator<T>& _Reverse_Iterator<T>::operator +=(int n) throw()
	{
		iter_ -= n;
		return *this;
	}

	template<class T>
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator +(int n) throw()
	{
		_Reverse_Iterator<T> tmp = *this;
		return (tmp += n);
	}

	template<class T>
	_Reverse_Iterator<T>& _Reverse_Iterator<T>::operator -=(int n) throw()
	{
		iter_ += n;
		return *this;
	}

	template<class T>
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator -(int n) throw()
	{
		_Reverse_Iterator<T> tmp = *this;
		return (tmp -= n);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator == (const _Reverse_Iterator<T> &right) const throw()
	{
		return (iter_ == right.rev_iter);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator != (const _Reverse_Iterator<T> &right) const throw()
	{
		return (iter_ != right.iter_);
	}
}
#endif