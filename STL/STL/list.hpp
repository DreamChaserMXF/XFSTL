#ifndef XF_LIST_HPP
#define XF_LIST_HPP

#pragma warning(disable:4290)	// for msvc's not fully supporting the exception specifications
#pragma warning(disable:4996)	// for msvc's safety concern about uninitialized_xxxx()

#include "_List_Iterator.hpp"
#include "_Reverse_Iterator.hpp"
#include "list_item.hpp"
#include <cassert>
#include "memory.hpp"
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

		list();
		list(const list<T> &right);
		list(size_t _Count);
		list(size_t _Count, const T &_Value);
		template<class _Iter> list(_Iter first, _Iter last);
		template<> list(int _Count, int _Value) : 
			head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(count), prev_index_(PREV_POS), next_index_(NEXT_POS)
		{
			head_->item_ptr_[prev_index_] = NULL;
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
		virtual ~list();
		void assign(size_t count, const T &val);
		template<class _Iter> 
		void assign(_Iter first, _Iter last);
		// 这个模板的特化不能在类外定义，不知道为啥
		template<> void assign<int>(int _Count, int _Value)
		{
			assign_n(_Count, static_cast<T>(_Value));
		}

		size_t size() const;
		bool empty() const;
		void clear();

		static size_t max_size();

		void push_front(const T &item);
		void pop_front();
		void push_back(const T &item);
		void pop_back();

		const T& front() const;
		T& front();
		const T& back() const;
		T& back();

		iterator insert(const const_iterator &_Where, const T &_Value);
		iterator insert(const const_iterator &_Where, size_t _Count, const T &_Value);
		template<class Iter>
		iterator insert(const const_iterator &_Where, Iter _First, Iter _Last);
		template<> iterator insert<int>(const const_iterator &_Where, int _Count, int _Value)
		{
			return insert_n(_Where, _Count, _Value);
		}
		
		iterator erase(const_iterator _First, const_iterator _Last);
		iterator erase(const const_iterator &_Where);

		void reverse();

		const_iterator cbegin() const;
		const_iterator begin() const;
		iterator begin();

		const_iterator cend() const;
		const_iterator end() const;
		iterator end();

		const_reverse_iterator crbegin() const;
		const_reverse_iterator rbegin() const;
		reverse_iterator rbegin();

		const_reverse_iterator crend() const;
		const_reverse_iterator rend() const;
		reverse_iterator rend();

		list<T>& operator = (const list<T> &right);

	private:
		void assign_n(size_t count, const T &val);
		iterator insert_n(const const_iterator _Where, size_t _Count, const T &_Value);
		T *p_;

		list_item<T> *head_;
		list_item<T> *tail_;
		size_t size_;
		PTR_POS prev_index_;
		PTR_POS next_index_;
	};


	template<class T>
	list<T>::list() :
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), size_(0), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		head_->item_ptr_[prev_index_] = NULL;
		head_->item_ptr_[next_index_] = tail_;
		tail_->item_ptr_[prev_index_] = head_;
		tail_->item_ptr_[next_index_] = NULL;
	}

	template<class T>
	list<T>::list(const list<T> &right) : 
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(right.size_), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		head_->item_ptr_[prev_index_] = NULL;
		// 逐个复制
		list_item<T> *p = right.head_->item_ptr_[right.next_index_];
		while(p != right.tail_)
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
	list<T>::list(size_t _Count) : 
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(_Count), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		head_->item_ptr_[prev_index_] = NULL;
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
	list<T>::list(size_t _Count, const T &_Value) : 
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(_Count), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		head_->item_ptr_[prev_index_] = NULL;
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
	list<T>::list(_Iter first, _Iter last) : 
		head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(0U), prev_index_(PREV_POS), next_index_(NEXT_POS)
	{
		head_->item_ptr_[prev_index_] = NULL;
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
	list<T>::~list()
	{
		// 循环销毁head_与tail_之间的所有节点
		for(const list_item<T> *p = head_->item_ptr_[next_index_];
			p != tail_; p = head_->item_ptr_[next_index_])
		{
			head_->item_ptr_[next_index_] = p->item_ptr_[next_index_];
			delete p;
		}
		operator delete(head_);
		operator delete(tail_);
		head_ = NULL;
		tail_ = NULL;
		size_ = 0;
	}

	template<class T>
	void list<T>::assign(size_t count, const T &val)
	{
		assign_n(count, val);
	}

	template<class T>
	template<class _Iter>
	void list<T>::assign(_Iter _First, _Iter _Last)
	{
		size_ = 0;
		// 先修改已有的节点
		list_item<T> *p = NULL;
		for(p = head_->item_ptr_[next_index_];
			p != tail_ && _First != _Last; p = p->item_ptr_[next_index_])
		{
			p->val_ = *_First++;
			++size_;
		}
		if(_First != _Last)	// 还未插入完毕的情况
		{
			p = tail_->item_ptr_[prev_index_];
			do
			{
				list_item<T> *new_item = new list_item<T>(*_First++, prev_index_, p, next_index_, NULL);
				p->item_ptr_[next_index_] = new_item;
				p = new_item;
				++size_;
			}while(_First != _Last);
			p->item_ptr_[next_index_] = tail_;
			tail_->item_ptr_[prev_index_] = p;
		}
		else if(p != tail_)	// 插入完毕，但还有多余元素在链表中 
		{
			list_item<T> *last = p->item_ptr_[prev_index_];
			do
			{
				last->item_ptr_[next_index_] = p->item_ptr_[next_index_];
				delete p;
				p = last->item_ptr_[next_index_];
			}while(p != tail_);
			tail_->item_ptr_[prev_index_] = last;
		}
	}

	template<class T>
	size_t list<T>::size() const
	{
		return size_;
	}

	template<class T>
	bool list<T>::empty() const
	{
		return (size_ == 0);
	}


	template<class T>
	size_t list<T>::max_size()
	{
		return static_cast<size_t>(-1) / sizeof(list_item<T>) - 1;	// 减1是减去头结点
	}

	template<class T>
	void list<T>::clear()
	{
		for(const list_item<T> *p = head_->item_ptr_[next_index_];
			p != tail_; p = head_->item_ptr_[next_index_])
		{
			head_->item_ptr_[next_index_] = p->item_ptr_[next_index_];
			delete p;
		}
		// 循环结束后head_的下一个指针指向tail_
		size_ = 0;
	}

	
	template<class T>
	void list<T>::push_front(const T &_Value)
	{
		// 添加新元素
		list_item<T> *first_node = head_->item_ptr_[next_index_];
		list_item<T> *new_item = new list_item<T>(_Value, prev_index_, head_, next_index_, first_node);
		first_node->item_ptr_[prev_index_] = new_item;
		head_->item_ptr_[next_index_] = new_item;
		++size_;
	}

	template<class T>
	void list<T>::pop_front()
	{
		--size_;
		list_item<T> *second_node = head_->item_ptr_[next_index_]->item_ptr_[next_index_];
		delete head_->item_ptr_[next_index_];
		second_node->item_ptr_[prev_index_] = head_;
		head_->item_ptr_[next_index_] = second_node;
	}

	template<class T>
	void list<T>::push_back(const T &_Value)
	{
		// 添加新元素
		list_item<T> *last_node = tail_->item_ptr_[prev_index_];
		list_item<T> *new_item = new list_item<T>(_Value, prev_index_, last_node, next_index_, tail_);
		last_node->item_ptr_[next_index_] = new_item;
		tail_->item_ptr_[prev_index_] = new_item;
		++size_;
	}

	template<class T>
	void list<T>::pop_back()
	{
		--size_;
		list_item<T> *last_second_node = tail_->item_ptr_[prev_index_]->item_ptr_[prev_index_];
		delete tail_->item_ptr_[prev_index_];
		last_second_node->item_ptr_[next_index_] = tail_;
		tail_->item_ptr_[prev_index_] = last_second_node;
	}

	template<class T>
	const T& list<T>::front() const
	{
		assert(size_ > 0);
		return head_->item_ptr_[next_index_]->val_;
	}
	template<class T>
	T& list<T>::front()
	{
		assert(size_ > 0);
		return head_->item_ptr_[next_index_]->val_;
	}
	template<class T>
	const T& list<T>::back() const
	{
		assert(size_ > 0);
		return tail_->item_ptr_[prev_index_]->val_;
	}
	template<class T>
	T& list<T>::back()
	{
		assert(size_ > 0);
		return tail_->item_ptr_[prev_index_]->val_;
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(const const_iterator &_Where, const T &_Value)
	{
		list_item<T> *new_ptr = new list_item<T>(_Value, _Where.prev_index_, _Where.p_->item_ptr_[_Where.prev_index_], _Where.next_index_, const_cast<list_item<T>*>(_Where.p_));
		_Where.p_->item_ptr_[_Where.prev_index_]->item_ptr_[_Where.next_index_] = new_ptr;
		const_cast<list_item<T>*>(_Where.p_)->item_ptr_[_Where.prev_index_] = new_ptr;
		++size_;
		return iterator(new_ptr, _Where.prev_index_, _Where.next_index_);
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(const const_iterator &_Where, size_t _Count, const T &_Value)
	{
		return insert_n(_Where, _Count, _Value);
	}

	template<class T>template<class Iter>
	typename list<T>::iterator list<T>::insert(const const_iterator &_Where, Iter _First, Iter _Last)
	{
		list_item<T> *last_ptr = _Where.p_->item_ptr_[_Where.prev_index_];
		list_item<T> *ret_prev = last_ptr;
		while(_First != _Last)
		{
			list_item<T> *new_ptr = new list_item<T>(*_First++, _Where.prev_index_, last_ptr, _Where.next_index_, NULL);
			last_ptr->item_ptr_[_Where.next_index_] = new_ptr;
			last_ptr = new_ptr;
			++size_;
		}
		last_ptr->item_ptr_[_Where.next_index_] = const_cast<list_item<T>*>(_Where.p_);
		const_cast<list_item<T>*>(_Where.p_)->item_ptr_[_Where.prev_index_] = last_ptr;
		return iterator(ret_prev->item_ptr_[_Where.next_index_], _Where.prev_index_, _Where.next_index_);
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(const_iterator _First, const_iterator _Last)
	{
		_First.p_->item_ptr_[_First.prev_index_]->item_ptr_[_First.next_index_] = const_cast<list_item<T>*>(_Last.p_);
		const_cast<list_item<T>*>(_Last.p_)->item_ptr_[_Last.prev_index_] = _First.p_->item_ptr_[_First.prev_index_];
		for(list_item<T> *p = _First.p_->item_ptr_[_Last.next_index_];
			p != _Last.p_; 
			p = p->item_ptr_[_Last.next_index_])
		{
			delete _First.p_;
			_First.p_ = p;
			--size_;
		}
		return iterator(const_cast<list_item<T>*>(_Last.p_), _Last.prev_index_, _Last.next_index_);
	}
	template<class T>
	typename list<T>::iterator list<T>::erase(const const_iterator &_Where)
	{
		list_item<T> *next_ptr = _Where.p_->item_ptr_[_Where.next_index_];
		_Where.p_->item_ptr_[_Where.prev_index_]->item_ptr_[_Where.next_index_] = next_ptr;
		next_ptr->item_ptr_[_Where.prev_index_] = _Where.p_->item_ptr_[_Where.prev_index_];
		delete _Where.p_;
		--size_;
		return iterator(next_ptr, _Where.prev_index_, _Where.next_index_);
	}

	template<class T>
	void list<T>::reverse()
	{
		// 交换head_和tail_
		list_item<T> *tmp_ptr = head_;
		head_ = tail_;
		tail_ = tmp_ptr;
		// 改写prev_index_和next_index_
		PTR_POS tmp_pos = prev_index_;
		prev_index_ = next_index_;
		next_index_ = tmp_pos;
	}

	template<class T>
	typename list<T>::const_iterator list<T>::cbegin() const
	{
		return const_iterator(head_->item_ptr_[next_index_], prev_index_, next_index_);
	}
	template<class T>
	typename list<T>::const_iterator list<T>::begin() const
	{
		return cbegin();
	}
	template<class T>
	typename list<T>::iterator list<T>::begin()
	{
		return iterator(head_->item_ptr_[next_index_], prev_index_, next_index_);;
	}

	template<class T>
	typename list<T>::const_iterator list<T>::cend() const
	{
		return const_iterator(tail_, prev_index_, next_index_);
	}
	template<class T>
	typename list<T>::const_iterator list<T>::end() const
	{
		return cend();
	}
	template<class T>
	typename list<T>::iterator list<T>::end()
	{
		return iterator(tail_, prev_index_, next_index_);
	}

	template<class T>
	typename list<T>::const_reverse_iterator list<T>::crbegin() const
	{
		return const_reverse_iterator(cend());
	}
	template<class T>
	typename list<T>::const_reverse_iterator list<T>::rbegin() const
	{
		return crbegin();
	}
	template<class T>
	typename list<T>::reverse_iterator list<T>::rbegin()
	{
		return reverse_iterator(end());
	}

	template<class T>
	typename list<T>::const_reverse_iterator list<T>::crend() const
	{
		return const_reverse_iterator(cbegin());
	}
	template<class T>
	typename list<T>::const_reverse_iterator list<T>::rend() const
	{
		return crend();
	}
	template<class T>
	typename list<T>::reverse_iterator list<T>::rend()
	{
		return reverse_iterator(begin());
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
		// 先修改已有的节点
		list_item<T> *p = NULL;
		list_item<T> *q = right.head_->item_ptr_[next_index_];
		for(p = head_->item_ptr_[next_index_];
			p != tail_ && q != right.tail_; p = p->item_ptr_[next_index_], q = q->item_ptr_[next_index_])
		{
			p->val_ = q->val_;
		}
		if(q != right.tail_)	// 还未赋值完毕的情况
		{
			p = tail_->item_ptr_[prev_index_];
			do
			{
				list_item<T> *new_item = new list_item<T>(q->val_, prev_index_, p, next_index_, NULL);
				p->item_ptr_[next_index_] = new_item;
				p = new_item;
				q = q->item_ptr_[next_index_];
			}while(q != right.tail_);
			p->item_ptr_[next_index_] = tail_;
			tail_->item_ptr_[prev_index_] = p;
		}
		else if(p != tail_)	// 赋值完毕，但还有多余元素在链表中 
		{
			list_item<T> *last = p->item_ptr_[prev_index_];
			do
			{
				last->item_ptr_[next_index_] = p->item_ptr_[next_index_];
				delete p;
				p = last->item_ptr_[next_index_];
			}while(p != tail_);
			tail_->item_ptr_[prev_index_] = last;
		}
		size_ = right.size_;
		return *this;
	}


	template<class T>
	void list<T>::assign_n(size_t _Count, const T &_Value)
	{
		size_ = 0;
		// 先修改已有的节点
		list_item<T> *p = NULL;
		for(p = head_->item_ptr_[next_index_];
			p != tail_ && size_ < _Count; p = p->item_ptr_[next_index_])
		{
			p->val_ = _Value;
			++size_;
		}
		if(size_ < _Count)	// 还未插入完毕的情况
		{
			p = tail_->item_ptr_[prev_index_];
			do
			{
				list_item<T> *new_item = new list_item<T>(_Value, prev_index_, p, next_index_, NULL);
				p->item_ptr_[next_index_] = new_item;
				p = new_item;
				++size_;
			}while(size_ < _Count);
			p->item_ptr_[next_index_] = tail_;
			tail_->item_ptr_[prev_index_] = p;
		}
		else if(p != tail_)	// 插入完毕，但还有多余元素在链表中 
		{
			list_item<T> *last = p->item_ptr_[prev_index_];
			do
			{
				last->item_ptr_[next_index_] = p->item_ptr_[next_index_];
				delete p;
				p = last->item_ptr_[next_index_];
			}while(p != tail_);
			tail_->item_ptr_[prev_index_] = last;
		}
	}

	template<class T>
	typename list<T>::iterator list<T>::insert_n(const const_iterator _Where, size_t _Count, const T &_Value)
	{
		list_item<T> *last_ptr = _Where.p_->item_ptr_[_Where.prev_index_];
		list_item<T> *ret_prev = last_ptr;
		for(size_t i = 0; i < _Count; ++i)
		{
			list_item<T> *new_ptr = new list_item<T>(_Value, _Where.prev_index_, last_ptr, _Where.next_index_, NULL);
			last_ptr->item_ptr_[_Where.next_index_] = new_ptr;
			last_ptr = new_ptr;
			++size_;
		}
		last_ptr->item_ptr_[_Where.next_index_] = const_cast<list_item<T>*>(_Where.p_);
		const_cast<list_item<T>*>(_Where.p_)->item_ptr_[_Where.prev_index_] = last_ptr;
		return iterator(ret_prev->item_ptr_[_Where.next_index_], _Where.prev_index_, _Where.next_index_);
	}
}

#endif

