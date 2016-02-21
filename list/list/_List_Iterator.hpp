#ifndef _VECTOR_ITERATOR
#define _VECTOR_ITERATOR
#include "list_item.hpp"
#include "_List_Const_Iterator.hpp"

namespace xf
{

	template<class T>
	class _List_Iterator
	{
	public:
		typedef T* pointer;
		typedef T& reference;

		_List_Iterator() throw();
		_List_Iterator(list_item<T> *_Ptr, enum PTR_POS _Prev_Index, enum PTR_POS _Next_Index) throw();

		const T& operator *() const throw();
		T& operator *() throw();
		const T* operator ->() const throw();
		T* operator ->() throw();
		_List_Iterator<T>& operator ++() throw();
		_List_Iterator<T> operator ++(int) throw();
		_List_Iterator<T>& operator --() throw();
		_List_Iterator<T> operator --(int) throw();
		bool operator == (const _List_Iterator<T> &iter) const throw();
		bool operator != (const _List_Iterator<T> &iter) const throw();

		operator _List_Const_Iterator<T> () const throw();

		list_item<T> *p_;
		enum PTR_POS prev_index_;
		enum PTR_POS next_index_;
	};

	template<class T>
	_List_Iterator<T>::_List_Iterator() throw() : p_(NULL), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		;
	}

	template<class T>
	_List_Iterator<T>::_List_Iterator(list_item<T> *_Ptr, enum PTR_POS _Prev_Index, enum PTR_POS _Next_Index) throw()
		: p_(_Ptr), prev_index_(_Prev_Index), next_index_(_Next_Index)
	{
		;
	}

	template<class T>
	const T& _List_Iterator<T>::operator *() const throw()
	{
		return p_->val_;
	}
	template<class T>
	T& _List_Iterator<T>::operator *() throw()
	{
		return p_->val_;
	}

	template<class T>
	const T* _List_Iterator<T>::operator ->() const throw()
	{
		return &(p_->val_);
	}
	template<class T>
	T* _List_Iterator<T>::operator ->() throw()
	{
		return &(p_->val_);
	}

	template<class T>
	_List_Iterator<T>& _List_Iterator<T>::operator ++() throw()
	{
		p_ = p_->item_ptr_[next_index_];
		return *this;
	}

	template<class T>
	_List_Iterator<T> _List_Iterator<T>::operator ++(int) throw()
	{
		_List_Iterator<T> iter(*this);
		p_ = p_->item_ptr_[next_index_];
		return iter;
	}

	template<class T>
	_List_Iterator<T>& _List_Iterator<T>::operator --() throw()
	{
		p_ = p_->item_ptr_[prev_index_];
		return *this;
	}

	template<class T>
	_List_Iterator<T> _List_Iterator<T>::operator --(int) throw()
	{
		_List_Iterator<T> iter(*this);
		p_ = p_->item_ptr_[prev_index_];
		return iter;
	}

	
	template<class T>
	bool _List_Iterator<T>::operator == (const _List_Iterator<T> &iter) const throw()
	{
		return p_ == iter.p_;
	}

	template<class T>
	bool _List_Iterator<T>::operator != (const _List_Iterator<T> &iter) const throw()
	{
		return p_ != iter.p_;
	}

	template<class T>
	_List_Iterator<T>::operator _List_Const_Iterator<T> () const throw()
	{
		return _List_Const_Iterator<T>(p_, prev_index_, next_index_);
	}
}

#endif