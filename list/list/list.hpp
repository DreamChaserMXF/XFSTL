#ifndef XF_VECTOR_H
#define XF_VECTOR_H

#pragma warning(disable:4290)	// for msvc's not fully supporting the exception specifications
#pragma warning(disable:4996)	// for msvc's safety concern about uninitialized_xxxx()

#include "_List_Iterator.hpp"
#include "_Reverse_Iterator.hpp"
#include "list_item.hpp"
#include <cassert>
#include <exception>
#include <stdexcept>
#include <memory>
namespace xf
{
	
	template<class T>
	class list
	{
		
	public:

		typedef _List_Iterator<T> iterator;
		typedef _List_Const_Iterator<T> const_iterator;
		typedef _Reverse_Iterator<iterator> reverse_iterator;
		typedef _Reverse_Iterator<const_iterator> const_reverse_iterator;

		list() throw(std::bad_alloc, std::bad_cast);
		list(const list<T> &right) throw(std::bad_alloc, std::bad_cast);
		list(size_t _Count) throw(std::bad_alloc, std::bad_cast, std::length_error);
		list(size_t _Count, const T &_Value) throw(std::bad_alloc, std::bad_cast, std::length_error);
		template<class _Iter> list(_Iter first, _Iter last) throw(std::bad_alloc, std::bad_cast, std::length_error);
		template<> list(int _Count, int _Value) throw(std::bad_alloc, std::bad_cast, std::length_error) : 
			head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(count), prev_index_(PREV_POS), next_index_(NEXT_POS)
		{
			if(_Count > max_size())
			{
				throw std::length_error("too much memory to allocate");
			}
			for(size_t i = 0; i < size_; ++i)
			{
				list_item<T> *new_item = new list_item<T>(static_cast<T>(_Value), prev_index_, tail_, next_index_, NULL);
				tail_->item_ptr_[next_index_] = new_item;
				tail_ = new_item;
			}
			// 最后再加一个尾巴
			list_item<T> *new_item = static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)));
			new_item->item_ptr_[prev_index_] = tail_;
			new_item->item_ptr_[next_index_] = NULL;
			tail_->item_ptr_[next_index_] = new_item;
			tail_ = new_item;
		}
		virtual ~list() throw();

		size_t size() const throw();
		bool empty() const throw();

		static size_t max_size()throw();

		void clear() throw();
		void assign(size_t count, const T &val) throw(std::length_error, std::bad_alloc);
		template<class _Iter> 
		void assign(_Iter first, _Iter last) throw(std::length_error, std::bad_alloc);
		// 这个模板的特化不能在类外定义，不知道为啥
		template<> void assign<int>(int _Count, int _Value) throw(std::bad_cast, std::length_error, std::bad_alloc)
		{
			assign_n(_Count, static_cast<T>(_Value));
		}

		void push_back(const T &item) throw(std::bad_alloc, std::length_error);
		void pop_back() throw(std::length_error);

		const T& front() const throw();
		T& front();
		const T& back() const throw();
		T& back();

		iterator insert(const const_iterator &_Where, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast);
		iterator insert(const const_iterator &_Where, size_t _Count, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast);
		template<class Iter>
		iterator insert(const const_iterator &_Where, Iter _First, Iter _Last) throw(std::bad_alloc, std::length_error, std::bad_cast);
		template<> iterator insert<int>(const const_iterator &_Where, int _Count, int _Value) throw(std::bad_alloc, std::length_error, std::bad_cast)
		{
			return insert_n(_Where, _Count, _Value);
		}


		iterator erase(const const_iterator &_First, const const_iterator &_Last) throw();
		iterator erase(const const_iterator &_Where) throw();

		const T& at(size_t index) const throw(std::out_of_range);	// 找出第index个元素，有越界检查
		T& at(size_t index) throw(std::out_of_range);				// 找出第index个元素，有越界检查
		
		const T& operator [](size_t index) const throw();			// 找出第index个元素，无越界检查
		T& operator [](size_t index) throw();						// 找出第index个元素，无越界检查

		const T* data() const throw();
		T* data() throw();

		const_iterator cbegin() const throw();
		const_iterator begin() const throw();
		iterator begin() throw();

		const_iterator cend() const throw();
		const_iterator end() const throw();
		iterator end() throw();

		const_reverse_iterator crbegin() const throw();
		const_reverse_iterator rbegin() const throw();
		reverse_iterator rbegin() throw();

		const_reverse_iterator crend() const throw();
		const_reverse_iterator rend() const throw();
		reverse_iterator rend() throw();

		list<T>& operator = (const list<T> &right);

	private:
		void assign_n(size_t count, const T &val) throw(std::length_error, std::bad_alloc);
		iterator insert_n(const const_iterator _Where, size_t _Count, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast);
		T *p_;
		size_t capacity_;

		list_item<T> *head_;
		list_item<T> *tail_;
		size_t size_;
		PTR_POS prev_index_;
		PTR_POS next_index_;
	};

	template<class T>
	list<T>::list() throw(std::bad_alloc, std::bad_cast) :
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), size_(0), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		head_->item_ptr_[prev_index_] = NULL;
		head_->item_ptr_[next_index_] = tail_;
		tail_->item_ptr_[prev_index_] = head_;
		tail_->item_ptr_[next_index_] = NULL;
	}

	template<class T>
	list<T>::list(const list<T> &right) throw(std::bad_alloc, std::bad_cast) : 
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(right.size_), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		// 逐个复制
		list_item<T> *p = right.head_->item_ptr_[right.next_index_];
		while(p)
		{
			list_item<T> *new_item = new list_item<T>(p->val_, prev_index_, tail_, next_index_, NULL);
			tail_->item_ptr_[next_index_] = new_item;
			tail_ = new_item;
			p = p->item_ptr_[right.next_index_];
		}
		// 最后再加一个尾巴
		list_item<T> *new_item = static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)));
		new_item->item_ptr_[prev_index_] = tail_;
		new_item->item_ptr_[next_index_] = NULL;
		tail_->item_ptr_[next_index_] = new_item;
		tail_ = new_item;
	}

	template<class T>
	list<T>::list(size_t _Count) throw(std::bad_alloc, std::bad_cast, std::length_error) : 
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(_Count), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		if(_Count > max_size())
		{
			throw std::length_error("too much memory to allocate");
		}
		for(size_t i = 0; i < size_; ++i)
		{
			list_item<T> *new_item = new list_item<T>(prev_index_, tail_, next_index_, NULL);
			tail_->item_ptr_[next_index_] = new_item;
			tail_ = new_item;
		}
		// 最后再加一个尾巴
		list_item<T> *new_item = static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)));
		new_item->item_ptr_[prev_index_] = tail_;
		new_item->item_ptr_[next_index_] = NULL;
		tail_->item_ptr_[next_index_] = new_item;
		tail_ = new_item;
	}


	template<class T>
	list<T>::list(size_t _Count, const T &_Value) throw(std::bad_alloc, std::bad_cast, std::length_error) : 
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(_Count), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		if(_Count > max_size())
		{
			throw std::length_error("too much memory to allocate");
		}
		for(size_t i = 0; i < size_; ++i)
		{
			list_item<T> *new_item = new list_item<T>(_Value, prev_index_, tail_, next_index_, NULL);
			tail_->item_ptr_[next_index_] = new_item;
			tail_ = new_item;
		}
		// 最后再加一个尾巴
		list_item<T> *new_item = static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)));
		new_item->item_ptr_[prev_index_] = tail_;
		new_item->item_ptr_[next_index_] = NULL;
		tail_->item_ptr_[next_index_] = new_item;
		tail_ = new_item;
	}

	template<class T>template<class _Iter>
	list<T>::list(_Iter first, _Iter last) throw(std::bad_alloc, std::bad_cast, std::length_error) : 
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(0U), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		while(first != last)
		{
			list_item<T> *new_item = new list_item<T>(*first++, prev_index_, tail_, next_index_, NULL);
			tail_->item_ptr_[next_index_] = new_item;
			tail_ = new_item;
			++size_;
		}
		// 最后再加一个尾巴
		list_item<T> *new_item = static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)));
		new_item->item_ptr_[prev_index_] = tail_;
		new_item->item_ptr_[next_index_] = NULL;
		tail_->item_ptr_[next_index_] = new_item;
		tail_ = new_item;
	}

	template<class T>
	list<T>::~list() throw()
	{
		const list_item<T> *tmp_tail = tail_;
		list_item<T> *p = tail_->item_ptr_[prev_index_];
		while(p)
		{
			if(tmp_tail == tail_)
			{
				operator delete(tail_);
			}
			else
			{
				delete tail_;
			}
			tail_ = p;
			p = p->item_ptr_[prev_index_];
		}
		operator delete(head_);
	}


	template<class T>
	size_t list<T>::size() const throw()
	{
		return size_;
	}

	template<class T>
	bool list<T>::empty() const throw()
	{
		return (size_ == 0);
	}


	template<class T>
	size_t list<T>::max_size() throw()
	{
		return static_cast<size_t>(-1) / sizeof(list_item<T>) - 1;	// 减1是减去头结点
	}

	template<class T>
	void list<T>::clear() throw()
	{
		for(size_t i = 0; i < size_; ++i)
		{
			(p_ + i)->~T();
		}
		size_ = 0;
	}

	template<class T>
	void list<T>::assign(size_t count, const T &val) throw()
	{
		assign_n(count, val);
	}

	template<class T>
	template<class _Iter>
	void list<T>::assign(_Iter first, _Iter last) throw()
	{
		clear();
		size_ = last - first;
		if(size_ > capacity_)
		{
			reserve(size_);
			capacity_ = size_;
		}
		std::uninitialized_copy(first, last, p_);
	}

	template<class T>
	void list<T>::push_back(const T &item) throw(std::bad_alloc, std::length_error)
	{
		// 添加新元素
		new (p_ + size_) T(item);
		++size_;
	}

	template<class T>
	void list<T>::pop_back() throw(std::length_error)
	{
		if(0 == size_)
		{
			throw std::length_error("invalid list<T> subscript");
		}
		else
		{
			--size_;
			(p_ + size_)->~T();
		}
	}

	template<class T>
	const T& list<T>::front() const throw()
	{
		return *p_;
	}
	template<class T>
	const T& list<T>::back() const throw()
	{
		return p_[size_ - 1];
	}
	template<class T>
	T& list<T>::front() throw()
	{
		return *p_;
	}
	template<class T>
	T& list<T>::back() throw()
	{
		return p_[size_ - 1];
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(const const_iterator &_Where, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast)
	{
		if(size_ == capacity_)	// 须要扩容
		{
			size_t offset = _Where.p_ - p_;	// 记录插入元素的偏移量
			// 新申请空间并分两段复制，空下需要插入的元素的位置
			size_t new_capacity = get_new_capacity();
			T * new_ptr = static_cast<T*>(operator new[] (new_capacity * sizeof(T)));
			std::uninitialized_copy(p_, p_ + offset, new_ptr);
			std::uninitialized_copy(p_ + offset, p_ + size_, new_ptr + offset + 1);
			// 插入新的元素
			new (new_ptr + offset) T(_Value);
			// 销毁原来的空间
			for(size_t i = 0; i < size_; ++i)
			{
				p_[i].~T();
			}
			operator delete[](p_);
			// 更新list的属性
			p_ = new_ptr;
			capacity_ = new_capacity;
			++size_;
			return iterator(p_ + offset);
		}
		else	// 不须扩容
		{
			T *cur = const_cast<T*>(_Where.p_);
			T *last = p_ + size_;
			new (last) T(*(last-1));
			while(--last > cur)
			{
				*last = *(last - 1);
			}
			*cur = _Value;
			++size_;
			return iterator(cur);
		}
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(const const_iterator &_Where, size_t _Count, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast)
	{
		insert_n(_Where, _Count, _Value);
	}

	template<class T>template<class Iter>
	typename list<T>::iterator list<T>::insert(const const_iterator &_Where, Iter _First, Iter _Last) throw(std::bad_alloc, std::length_error, std::bad_cast)
	{
		assert(_First < _Last);	// 这里要不要assert？万一_Iter没有定义小于号怎么办？
		size_t count = _Last - _First;
		if(size_ + count > capacity_)	// 须要扩容
		{
			size_t offset = _Where.p_ - p_;	// 记录插入元素的偏移量
			// 新申请空间并分两段复制，空下需要插入的元素的位置
			size_t new_capacity = get_new_capacity(size_ + count);
			T * new_ptr = static_cast<T*>(operator new[] (new_capacity * sizeof(T)));
			std::uninitialized_copy(p_, p_ + offset, new_ptr);
			std::uninitialized_copy(p_ + offset, p_ + size_, new_ptr + offset + count);
			// 插入新的元素
			for(size_t i = 0; i < count; ++i)
			{
				new (new_ptr + offset + i) T(*_First);
				++_First;
			}
			assert(_First == _Last);
			// 销毁原来的空间
			for(size_t i = 0; i < size_; ++i)
			{
				p_[i].~T();
			}
			operator delete[](p_);
			// 更新list的属性
			p_ = new_ptr;
			capacity_ = new_capacity;
			size_ += count;
			return iterator(p_ + offset);
		}
		else	// 不须扩容
		{
			T *cur = const_cast<T*>(_Where.p_);
			T *last = p_ + size_ + count - 1;
			// 须要构造的部分
			while(last >= p_ + size_)
			{
				new (last) T(*(last - count));	
				--last;
			}
			// 须要复制的部分
			while(last >= cur + count)
			{
				*last = *(last - count);
				--last;
			}
			// 需要插入的部分
			iterator ret_val = iterator(cur);
			while(cur <= last)
			{
				*cur = *_First;
				++cur;
				++_First;
			}
			size_ += count;
			return ret_val;
		}

		return iterator(const_cast<T*>(_First));
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(const const_iterator &_First, const const_iterator &_Last) throw()
	{
		assert(_First < _Last);
		T * index1 = const_cast<T*>(_First.p_);
		T * index2 = const_cast<T*>(_Last.p_);
		size_t difference = index2 - index1;
		while(index2 < p_ + size_)
		{
			*index1++ = *index2++;
		}
		while(index1 < p_ + size_)
		{
			index1->~T();
			++index1;
		}
		size_ -= difference;
		return iterator(const_cast<T*>(_First.p_));
	}
	template<class T>
	typename list<T>::iterator list<T>::erase(const const_iterator &_Where) throw()
	{
		T * cur = const_cast<T*>(_Where.p_);
		while(++cur < p_ + size_)
		{
			*(cur - 1) = *cur;
		}
		cur->~T();
		--size_;
		return iterator(const_cast<T*>(_Where.p_));
	}


	template<class T>
	const T& list<T>::at(size_t index) const throw(std::out_of_range)
	{
		if(index < 0 || index >= size_)
		{
			throw std::out_of_range("invalid list<T> subscript");
		}
		else
		{
			return p_[index];
		}
	}
	template<class T>
	T& list<T>::at(size_t index) throw(std::out_of_range)
	{
		if(index < 0 || index >= size_)
		{
			throw std::out_of_range("invalid list<T> subscript");
		}
		else
		{
			return p_[index];
		}
	}

	template<class T>
	const T& list<T>::operator [](size_t index) const throw()
	{
		return p_[index];
	}
	template<class T>
	T& list<T>::operator [](size_t index) throw()
	{
		return p_[index];
	}
	
	template<class T>
	const T* list<T>::data() const throw()
	{
		return p_;
	}
	template<class T>
	T* list<T>::data() throw()
	{
		return p_;
	}

	template<class T>
	typename list<T>::const_iterator list<T>::cbegin() const throw()
	{
		return const_iterator(head_->item_ptr_[next_index_], prev_index_, next_index_);
	}
	template<class T>
	typename list<T>::const_iterator list<T>::begin() const throw()
	{
		return cbegin();
	}
	template<class T>
	typename list<T>::iterator list<T>::begin() throw()
	{
		return iterator(head_->item_ptr_[next_index_], prev_index_, next_index_);;
	}

	template<class T>
	typename list<T>::const_iterator list<T>::cend() const throw()
	{
		return const_iterator(tail_, prev_index_, next_index_);
	}
	template<class T>
	typename list<T>::const_iterator list<T>::end() const throw()
	{
		return cend();
	}
	template<class T>
	typename list<T>::iterator list<T>::end() throw()
	{
		return iterator(tail_, prev_index_, next_index_);
	}

	template<class T>
	typename list<T>::const_reverse_iterator list<T>::crbegin() const throw()
	{
		return const_reverse_iterator(tail_->item_ptr_[prev_index_], prev_index_, next_index_);
	}
	template<class T>
	typename list<T>::const_reverse_iterator list<T>::rbegin() const throw()
	{
		return crbegin();
	}
	template<class T>
	typename list<T>::reverse_iterator list<T>::rbegin() throw()
	{
		return reverse_iterator(tail_->item_ptr_[prev_index_], prev_index_, next_index_);
	}

	template<class T>
	typename list<T>::const_reverse_iterator list<T>::crend() const throw()
	{
		return const_reverse_iterator(head_, prev_index_, next_index_);
	}
	template<class T>
	typename list<T>::const_reverse_iterator list<T>::rend() const throw()
	{
		return crend();
	}
	template<class T>
	typename list<T>::reverse_iterator list<T>::rend() throw()
	{
		return reverse_iterator(head_, prev_index_, next_index_);
	}

	// STL中的=运算符中，对每个元素的复制，不一定用每个元素的=还是拷贝构造函数
	// 视right与*this的size大小而定
	template<class T>
	list<T>& list<T>::operator = (const list<T> &right)
	{
		if(this == &right)
		{
			return *this;
		}
		else if(right.size_ <= size_)
		{
			size_t i = 0;
			while(i < right.size_)
			{
				p_[i] = right.p_[i];
				++i;
			}
			while(i < size_)
			{
				(p_ + i)->~T();
				++i;
			}
			size_ = right.size_;
		}
		else if(right.size_ <= capacity_)
		{
			size_t i = 0;
			while(i < size_)
			{
				p_[i] = right.p_[i];
				++i;
			}
			while(i < right.size_)
			{
				new (p_ + i) T(*(right.p_ + i));
				++i;
			}
			size_ = right.size_;
		}
		else
		{
			for(size_t i = 0; i < size_; ++i)
			{
				(p_ + i)->~T();
			}
			operator delete[](p_);
			p_ = static_cast<T*>(operator new[](right.size_ * sizeof(T)));
			for(size_t i = 0; i < right.size_; ++i)
			{
				new (p_ + i) T(*(right.p_ + i));
			}
			size_ = right.size_;
			capacity_ = right.size_;
		}
		return *this;
	}


	template<class T>
	void list<T>::assign_n(size_t count, const T &val) throw()
	{
		clear();
		size_ = count;
		if(count > capacity_)
		{
			capacity_ = count;
		}
		std::uninitialized_fill(p_, p_ + count, val);
	}

	template<class T>
	typename list<T>::iterator list<T>::insert_n(const const_iterator _Where, size_t _Count, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast)
	{
		if(size_ + _Count > capacity_)	// 须要扩容
		{
			size_t offset = _Where.p_ - p_;	// 记录插入元素的偏移量
			// 新申请空间并分两段复制，空下需要插入的元素的位置
			size_t new_capacity = get_new_capacity(size_ + _Count);
			T * new_ptr = static_cast<T*>(operator new[] (new_capacity * sizeof(T)));
			std::uninitialized_copy(p_, p_ + offset, new_ptr);
			std::uninitialized_copy(p_ + offset, p_ + size_, new_ptr + offset + _Count);
			// 插入新的元素
			for(size_t i = 0; i < _Count; ++i)
			{
				new (new_ptr + offset + i) T(_Value);
			}
			// 销毁原来的空间
			for(size_t i = 0; i < size_; ++i)
			{
				p_[i].~T();
			}
			operator delete[](p_);
			// 更新list的属性
			p_ = new_ptr;
			capacity_ = new_capacity;
			size_ += _Count;
			return iterator(p_ + offset);
		}
		else	// 不须扩容
		{
			T *cur = const_cast<T*>(_Where.p_);
			T *last = p_ + size_ + _Count - 1;
			// 须要构造的部分
			while(last >= p_ + size_)
			{
				new (last) T(*(last - _Count));	
				--last;
			}
			// 须要复制的部分
			while(last >= cur + _Count)
			{
				*last = *(last - _Count);
				--last;
			}
			// 需要插入的部分
			while(last >= cur)
			{
				*last = _Value;
				--last;
			}
			size_ += _Count;
			return iterator(cur);
		}
	}
}

#endif

