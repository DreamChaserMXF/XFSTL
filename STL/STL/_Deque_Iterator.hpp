#ifndef XF_DEQUE_ITERATOR_HPP
#define XF_DEQUE_ITERATOR_HPP

#include "_Deque_Const_Iterator.hpp"
#include "_Deque_Common.hpp"

namespace xf
{
	template<class T>
	class _Deque_Iterator : public _Deque_Const_Iterator<T>
	{
	public:
		typedef T* pointer;
		typedef T& reference;
		typedef T value_type;
		typedef random_access_iterator_tag iterator_category;

		_Deque_Iterator();
		_Deque_Iterator(typename vector<pointer>::iterator map_iter, size_t item_index);

		const T& operator *() const;
		T& operator *();
		const T* operator ->() const;
		T* operator ->();
		_Deque_Iterator<T>& operator ++();
		_Deque_Iterator<T> operator ++(int);
		_Deque_Iterator<T>& operator --();
		_Deque_Iterator<T> operator --(int);
		_Deque_Iterator<T>& operator +=(int n);
		_Deque_Iterator<T> operator +(int n) const;
		_Deque_Iterator<T>& operator -=(int n);
		_Deque_Iterator<T> operator -(int n) const;
		int operator -(const _Deque_Const_Iterator<T> &iter) const;
	};

	template<class T>
	_Deque_Iterator<T>::_Deque_Iterator() : _Deque_Const_Iterator<T>()
	{
		;
	}

	template<class T>
	_Deque_Iterator<T>::_Deque_Iterator(typename vector<pointer>::iterator map_iter, size_t item_index) 
		: _Deque_Const_Iterator<T>(map_iter, item_index)
	{
		;
	}

	template<class T>
	const T& _Deque_Iterator<T>::operator *() const
	{
		return (*map_iter_)[item_index_];
	}
	template<class T>
	T& _Deque_Iterator<T>::operator *()
	{
		return (*map_iter_)[item_index_];
	}
	
	template<class T>
	const T* _Deque_Iterator<T>::operator ->() const
	{
		return *map_iter_ + item_index_;
	}
	template<class T>
	T* _Deque_Iterator<T>::operator ->()
	{
		return &(*map_iter_)[item_index_];
	}

	template<class T>
	_Deque_Iterator<T>& _Deque_Iterator<T>::operator ++()
	{
		++item_index_;
		if(SEGMENT_LENGTH == item_index_)
		{
			++map_iter_;
			item_index_ = 0;
		}
		return *this;
	}

	template<class T>
	_Deque_Iterator<T> _Deque_Iterator<T>::operator ++(int)
	{
		_Deque_Iterator<T> ret(*this);
		++(*this);
		return ret;
	}

	template<class T>
	_Deque_Iterator<T>& _Deque_Iterator<T>::operator --()
	{
		if(0 == item_index_)
		{
			item_index_ = SEGMENT_LENGTH - 1;
			--map_iter_;
		}
		else
		{
			--item_index_;
		}
		return *this;
	}

	template<class T>
	_Deque_Iterator<T> _Deque_Iterator<T>::operator --(int)
	{
		_Deque_Iterator<T> ret(*this);
		--(*this);
		return ret;
	}

	template<class T>
	_Deque_Iterator<T>& _Deque_Iterator<T>::operator +=(int n)
	{
		if(n < 0)
		{
			*this -= -n;
		}
		else
		{
			item_index_ += n;
			if(item_index_ >= SEGMENT_LENGTH)
			{
				map_iter_ += item_index_ / SEGMENT_LENGTH;
				item_index_ = item_index_ % SEGMENT_LENGTH;
			}
		}
		return *this;
	}

	template<class T>
	_Deque_Iterator<T> _Deque_Iterator<T>::operator +(int n) const
	{
		_Deque_Iterator<T> ret(*this);
		return ret += n;
	}

	template<class T>
	_Deque_Iterator<T>& _Deque_Iterator<T>::operator -=(int n)
	{
		if(n < 0)
		{
			*this += -n;
		}
		else if(item_index_ >= (size_t)n)
		{
			item_index_ -= n;
		}
		else
		{
			int remain_substraction = n - item_index_ - 1;	// remain_substraction相当于，把当前bin减掉之后，还要减多少
			map_iter_ -= 1 + remain_substraction / SEGMENT_LENGTH;
			item_index_ = SEGMENT_LENGTH - 1 - remain_substraction % SEGMENT_LENGTH;
		}
		return *this;
	}

	template<class T>
	_Deque_Iterator<T> _Deque_Iterator<T>::operator -(int n) const
	{
		_Deque_Iterator<T> ret(*this);
		return ret -= n;
	}

	template<class T>
	int _Deque_Iterator<T>::operator -(const _Deque_Const_Iterator<T> &right) const
	{
		return *static_cast<const _Deque_Const_Iterator<T>*>(this) - right;
	}

}

#endif