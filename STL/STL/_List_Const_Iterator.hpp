#ifndef XF_LIST_CONST_ITERATOR_HPP
#define XF_LIST_CONST_ITERATOR_HPP

#include "list_item.hpp"
#include "_Iterator_Traits.hpp"

namespace xf
{
	template<class T>
	class _List_Const_Iterator
	{
	public:
		typedef const T& reference;
		typedef const T* pointer;
		typedef T value_type;
		typedef bi_directional_iterator_tag iterator_category;

		_List_Const_Iterator();
		_List_Const_Iterator(const list_item<T> *_Ptr, enum PTR_POS _Prev_Index, enum PTR_POS _Next_Index);

		const T& operator *() const;
		const T* operator ->() const;
		_List_Const_Iterator<T>& operator ++();
		_List_Const_Iterator<T> operator ++(int);
		_List_Const_Iterator<T>& operator --();
		_List_Const_Iterator<T> operator --(int);

		bool operator == (const _List_Const_Iterator<T> &iter) const;
		bool operator != (const _List_Const_Iterator<T> &iter) const;

		//friend bool operator == (const _List_Const_Iterator<T> &left, const _List_Const_Iterator<T> &right);
		//friend bool operator != (const _List_Const_Iterator<T> &left, const _List_Const_Iterator<T> &right);

		const list_item<T> *p_;
		enum PTR_POS prev_index_;
		enum PTR_POS next_index_;
	};

	template<class T>
	_List_Const_Iterator<T>::_List_Const_Iterator() : p_(NULL), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		;
	}

	template<class T>
	_List_Const_Iterator<T>::_List_Const_Iterator(const list_item<T> *_Ptr, enum PTR_POS _Prev_Index, enum PTR_POS _Next_Index)
		: p_(_Ptr), prev_index_(_Prev_Index), next_index_(_Next_Index)
	{
		;
	}

	template<class T>
	const T& _List_Const_Iterator<T>::operator *() const
	{
		return p_->val_;
	}

	template<class T>
	const T* _List_Const_Iterator<T>::operator ->() const
	{
		return &(p_->val_);
	}


	template<class T>
	_List_Const_Iterator<T>& _List_Const_Iterator<T>::operator ++()
	{
		p_ = p_->item_ptr_[next_index_];
		return *this;
	}

	template<class T>
	_List_Const_Iterator<T> _List_Const_Iterator<T>::operator ++(int)
	{
		_List_Const_Iterator<T> iter(*this);
		p_ = p_->item_ptr_[next_index_];
		return iter;
	}

	template<class T>
	_List_Const_Iterator<T>& _List_Const_Iterator<T>::operator --()
	{
		p_ = p_->item_ptr_[prev_index_];
		return *this;
	}

	template<class T>
	_List_Const_Iterator<T> _List_Const_Iterator<T>::operator --(int)
	{
		_List_Const_Iterator<T> iter(*this);
		p_ = p_->item_ptr_[prev_index_];
		return iter;
	}

	
	template<class T>
	bool _List_Const_Iterator<T>::operator == (const _List_Const_Iterator<T> &iter) const
	{
		return p_ == iter.p_;
	}

	template<class T>
	bool _List_Const_Iterator<T>::operator != (const _List_Const_Iterator<T> &iter) const
	{
		return p_ != iter.p_;
	}

	//template<class T>
	//bool operator == (const _List_Const_Iterator<T> &left, const _List_Const_Iterator<T> &right)
	//{
	//	return left.p_ == right.p_;
	//}

	//template<class T>
	//bool operator != (const _List_Const_Iterator<T> &left, const _List_Const_Iterator<T> &right)
	//{
	//	return left.p_ != right.p_;
	//}
}

#endif