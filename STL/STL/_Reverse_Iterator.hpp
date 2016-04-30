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
		explicit _Reverse_Iterator(T right) throw();
		// ��������ת���Ĺ��캯��
		template<class Other>
		_Reverse_Iterator(const _Reverse_Iterator<Other> &right) throw();

		T base() const throw();
		const reference operator *() const throw();
		reference operator *() throw();
		const pointer operator ->() const throw();
		pointer operator ->() throw();
		_Reverse_Iterator<T>& operator ++() throw();
		_Reverse_Iterator<T> operator ++(int) throw();
		_Reverse_Iterator<T>& operator --() throw();
		_Reverse_Iterator<T> operator --(int) throw();
		_Reverse_Iterator<T>& operator +=(int n) throw();
		_Reverse_Iterator<T> operator +(int n) const throw();
		_Reverse_Iterator<T>& operator -=(int n) throw();
		_Reverse_Iterator<T> operator -(int n) const throw();
		int operator -(const _Reverse_Iterator &right) const throw();

		bool operator == (const _Reverse_Iterator &right) const throw();
		bool operator != (const _Reverse_Iterator &right) const throw();
		bool operator < (const _Reverse_Iterator &right) const throw();
		bool operator <= (const _Reverse_Iterator &right) const throw();
		bool operator > (const _Reverse_Iterator &right) const throw();
		bool operator >= (const _Reverse_Iterator &right) const throw();
	//private:
		// ���Ϊpublic������Ϊ�˱�������ת����������listʵ��ʱ����ָ��tail_��reverse_iteratorת��Ϊconst_reverse_iteratorʱ���п�ָ�����
		T iter_;
	};

	template<class T>
	_Reverse_Iterator<T>::_Reverse_Iterator() throw() : iter_()
	{
		;
	}

	template<class T>
	_Reverse_Iterator<T>::_Reverse_Iterator(T right) : iter_(--right)
	{
		;
	}

	template<class T> template<class Other>
	_Reverse_Iterator<T>::_Reverse_Iterator(const _Reverse_Iterator<Other> &right) throw() : iter_(right.iter_)
	{
		;
	}

	template<class T>
	T _Reverse_Iterator<T>::base() const throw()
	{
		//return iter_ + 1;	// ԭʵ�֣�����������list����Ϊlist������ӷ�
		T ret_val = iter_;
		return ++ret_val;
	}

	template<class T>
	typename const _Reverse_Iterator<T>::reference _Reverse_Iterator<T>::operator*() const throw()
	{
		return *iter_;
	}
	template<class T>
	typename _Reverse_Iterator<T>::reference _Reverse_Iterator<T>::operator*() throw()
	{
		return *iter_;
	}

	template<class T>
	typename const _Reverse_Iterator<T>::pointer _Reverse_Iterator<T>::operator ->() const throw()
	{
		return &(*iter_);
	}
	template<class T>
	typename _Reverse_Iterator<T>::pointer _Reverse_Iterator<T>::operator ->() throw()
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
		_Reverse_Iterator<T> tmp(*this);
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
		_Reverse_Iterator<T> tmp(*this);
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
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator +(int n) const throw()
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
	_Reverse_Iterator<T> _Reverse_Iterator<T>::operator -(int n) const throw()
	{
		_Reverse_Iterator<T> tmp = *this;
		return (tmp -= n);
	}

	template<class T>
	int _Reverse_Iterator<T>::operator -(const _Reverse_Iterator &right) const throw()
	{
		return right.iter_ - iter_;
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator == (const _Reverse_Iterator<T> &right) const throw()
	{
		return (iter_ == right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator != (const _Reverse_Iterator<T> &right) const throw()
	{
		return (iter_ != right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator < (const _Reverse_Iterator<T> &right) const throw()
	{
		return (iter_ > right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator <= (const _Reverse_Iterator<T> &right) const throw()
	{
		return (iter_ >= right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator > (const _Reverse_Iterator<T> &right) const throw()
	{
		return (iter_ < right.iter_);
	}

	template<class T>
	bool _Reverse_Iterator<T>::operator >= (const _Reverse_Iterator<T> &right) const throw()
	{
		return (iter_ <= right.iter_);
	}
}
#endif