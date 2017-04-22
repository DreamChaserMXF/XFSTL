#ifndef XF_LIST_ITERATOR_HPP
#define XF_LIST_ITERATOR_HPP
#include "list_item.hpp"
#include "_List_Const_Iterator.hpp"
#include "_Iterator_Traits.hpp"

namespace xf
{

	template<class T>
	class _List_Iterator : public _List_Const_Iterator<T>
	{
	public:
		typedef T* pointer;
		typedef T& reference;
		typedef T value_type;
		typedef bi_directional_iterator_tag iterator_category;

		_List_Iterator();
		_List_Iterator(list_item<T> *_Ptr, enum PTR_POS _Prev_Index, enum PTR_POS _Next_Index);

		const T& operator *() const;
		T& operator *();
		const T* operator ->() const;
		T* operator ->();
		_List_Iterator<T>& operator ++();
		_List_Iterator<T> operator ++(int);
		_List_Iterator<T>& operator --();
		_List_Iterator<T> operator --(int);

		operator _List_Const_Iterator<T> () const;
	};

	template<class T>
	_List_Iterator<T>::_List_Iterator() : _List_Const_Iterator<T>()
	{
		;
	}

	template<class T>
	_List_Iterator<T>::_List_Iterator(list_item<T> *_Ptr, enum PTR_POS _Prev_Index, enum PTR_POS _Next_Index)
		: _List_Const_Iterator<T>(_Ptr, _Prev_Index, _Next_Index)
	{
		;
	}

	template<class T>
	const T& _List_Iterator<T>::operator *() const
	{
		return p_->val_;
	}
	template<class T>
	T& _List_Iterator<T>::operator *()
	{
		return p_->val_;
	}

	template<class T>
	const T* _List_Iterator<T>::operator ->() const
	{
		return &(p_->val_);
	}
	template<class T>
	T* _List_Iterator<T>::operator ->()
	{
		return &(p_->val_);
	}

	template<class T>
	_List_Iterator<T>& _List_Iterator<T>::operator ++()
	{
		p_ = p_->item_ptr_[next_index_];
		return *this;
	}

	template<class T>
	_List_Iterator<T> _List_Iterator<T>::operator ++(int)
	{
		_List_Iterator<T> iter(*this);
		p_ = p_->item_ptr_[next_index_];
		return iter;
	}

	template<class T>
	_List_Iterator<T>& _List_Iterator<T>::operator --()
	{
		p_ = p_->item_ptr_[prev_index_];
		return *this;
	}

	template<class T>
	_List_Iterator<T> _List_Iterator<T>::operator --(int)
	{
		_List_Iterator<T> iter(*this);
		p_ = p_->item_ptr_[prev_index_];
		return iter;
	}
}

#endif