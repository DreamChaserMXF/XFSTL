#ifndef XF_REVERSE_ITERATOR_HPP
#define XF_REVERSE_ITERATOR_HPP

#include "_Iterator_Traits.hpp"

namespace xf
{
	template<class T>
	class _Reverse_Iterator
	{
	public:
		typedef typename T::reference reference;
		typedef typename T::pointer pointer;
		typedef typename T::value_type value_type;
		typedef typename T::iterator_category iterator_category;

		_Reverse_Iterator();
		explicit _Reverse_Iterator(T right);
		// 用于类型转换的构造函数
		template<class Other>
		_Reverse_Iterator(const _Reverse_Iterator<Other> &right);

		T base() const;
		const reference operator *() const;
		reference operator *();
		const pointer operator ->() const;
		pointer operator ->();
		_Reverse_Iterator<T>& operator ++();
		_Reverse_Iterator<T> operator ++(int);
		_Reverse_Iterator<T>& operator --();
		_Reverse_Iterator<T> operator --(int);
		_Reverse_Iterator<T>& operator +=(int n);
		_Reverse_Iterator<T> operator +(int n) const;
		_Reverse_Iterator<T>& operator -=(int n);
		_Reverse_Iterator<T> operator -(int n) const;
		int operator -(const _Reverse_Iterator &right) const;

		bool operator == (const _Reverse_Iterator &right) const;
		bool operator != (const _Reverse_Iterator &right) const;
		bool operator < (const _Reverse_Iterator &right) const;
		bool operator <= (const _Reverse_Iterator &right) const;
		bool operator > (const _Reverse_Iterator &right) const;
		bool operator >= (const _Reverse_Iterator &right) const;
	//private:
		// 设计为public变量，为了便于类型转换（否则在list实现时，将指向tail_的reverse_iterator转换为const_reverse_iterator时会有空指针错误）
		T iter_;
	};

	template<class T>
	_Reverse_Iterator<T>::_Reverse_Iterator() : iter_()
	{
		;
	}

	template<class T>
	_Reverse_Iterator<T>::_Reverse_Iterator(T right) : iter_(--right)
	{
		;
	}

	template<class T> template<class Other>
	_Reverse_Iterator<T>::_Reverse_Iterator(const _Reverse_Iterator<Other> &right) : iter_(right.iter_)
	{
		;
	}

	template<class T>
	T _Reverse_Iterator<T>::base() const
	{
		//return iter_ + 1;	// 原实现，但不适用与list，因为list不允许加法
		T ret_val = iter_;
		return ++ret_val;
	}

	template<class T>
	typename const _Reverse_Iterator<T>::reference _Reverse_Iterator<T>::operator*() const
	{
		return *iter_;
	}
	template<class T>
	typename _Reverse_Iterator<T>::reference _Reverse_Iterator<T>::operator*()
	{
		return *iter_;
	}

	template<class T>
	typename const _Reverse_Iterator<T>::pointer _Reverse_Iterator<T>::operator ->() const
	{
		return &(*iter_);
	}
	template<class T>
	typename _Reverse_Iterator<T>::pointer _Reverse_Iterator<T>::operator ->()
	{
		return &(*iter_);
	}

	template<class T>
	_Reverse_Iterator<T>& _Reverse_Iterator<T>::operator ++()
	{
		--iter_;
		return *this;
	}

	template<class T>
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator ++(int)
	{
		_Reverse_Iterator<T> tmp(*this);
		--iter_;
		return tmp;
	}

	template<class T>
	_Reverse_Iterator<T>& _Reverse_Iterator<T>::operator --()
	{
		++iter_;
		return *this;
	}

	template<class T>
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator --(int)
	{
		_Reverse_Iterator<T> tmp(*this);
		++iter_;
		return tmp;
	}

	template<class T>
	_Reverse_Iterator<T>& _Reverse_Iterator<T>::operator +=(int n)
	{
		iter_ -= n;
		return *this;
	}

	template<class T>
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator +(int n) const
	{
		_Reverse_Iterator<T> tmp = *this;
		return (tmp += n);
	}

	template<class T>
	_Reverse_Iterator<T>& _Reverse_Iterator<T>::operator -=(int n)
	{
		iter_ += n;
		return *this;
	}

	template<class T>
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator -(int n) const
	{
		_Reverse_Iterator<T> tmp = *this;
		return (tmp -= n);
	}

	template<class T>
	int _Reverse_Iterator<T>::operator -(const _Reverse_Iterator &right) const
	{
		return right.iter_ - iter_;
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator == (const _Reverse_Iterator<T> &right) const
	{
		return (iter_ == right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator != (const _Reverse_Iterator<T> &right) const
	{
		return (iter_ != right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator < (const _Reverse_Iterator<T> &right) const
	{
		return (iter_ > right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator <= (const _Reverse_Iterator<T> &right) const
	{
		return (iter_ >= right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator > (const _Reverse_Iterator<T> &right) const
	{
		return (iter_ < right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator >= (const _Reverse_Iterator<T> &right) const
	{
		return (iter_ <= right.iter_);
	}
}
#endif