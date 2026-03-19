#ifndef XF_LIST_HPP
#define XF_LIST_HPP

#ifdef _MSC_VER
#pragma warning(disable:4290)	// for msvc's not fully supporting the exception specifications
#pragma warning(disable:4996)	// for msvc's safety concern about uninitialized_xxxx()
#endif

#include "_List_Iterator.hpp"
#include "_Reverse_Iterator.hpp"
#include "list_item.hpp"
#include <cassert>
#include <type_traits>
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
		template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type = 0> list(_Iter first, _Iter last);
		list(int _Count, const T& _Value) :
			head_(static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)))), tail_(head_), size_(_Count), prev_index_(PREV_POS), next_index_(NEXT_POS)
		{
			head_->item_ptr_[prev_index_] = NULL;
			for(size_t i = 0; i < size_; ++i)
			{
				list_item<T> *new_item = new list_item<T>(static_cast<T>(_Value), prev_index_, tail_, next_index_, NULL);
				tail_->item_ptr_[next_index_] = new_item;
				tail_ = new_item;
			}
			// ����ټ�һ��β��
			list_item<T> *new_item = static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)));
			new_item->item_ptr_[prev_index_] = tail_;
			new_item->item_ptr_[next_index_] = NULL;
			tail_->item_ptr_[next_index_] = new_item;
			tail_ = new_item;
		}
		virtual ~list();
		void assign(size_t count, const T &val);
		template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type = 0>
		void assign(_Iter first, _Iter last);
		// ���ģ����ػ����������ⶨ�壬��֪��Ϊɶ
		void assign(int _Count, const T& _Value)
		{
			assign_n(_Count, _Value);
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
		template<class Iter, typename std::enable_if<!std::is_integral<Iter>::value, int>::type = 0>
		iterator insert(const const_iterator &_Where, Iter _First, Iter _Last);
		iterator insert(const const_iterator &_Where, int _Count, const T& _Value)
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

		void sort();
		template<class _Comparer>
		void sort(const _Comparer &comparer);

		list<T>& operator = (const list<T> &right);

	private:
		void assign_n(size_t count, const T &val);
		iterator insert_n(const const_iterator _Where, size_t _Count, const T &_Value);

		void merge_sort(list_item<T> *head, list_item<T> *tail, size_t length);
		template<class _Comparer>
		void merge_sort(list_item<T> *head, list_item<T> *tail, size_t length, const _Comparer &comparer);

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
		// �������
		list_item<T> *p = right.head_->item_ptr_[right.next_index_];
		while(p != right.tail_)
		{
			list_item<T> *new_item = new list_item<T>(p->val_, prev_index_, tail_, next_index_, NULL);
			tail_->item_ptr_[next_index_] = new_item;
			tail_ = new_item;
			p = p->item_ptr_[right.next_index_];
		}
		// ����ټ�һ��β��
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
		// ����ټ�һ��β��
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
		// ����ټ�һ��β��
		list_item<T> *new_item = static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)));
		new_item->item_ptr_[prev_index_] = tail_;
		new_item->item_ptr_[next_index_] = NULL;
		tail_->item_ptr_[next_index_] = new_item;
		tail_ = new_item;
	}

	template<class T>template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type>
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
		// ����ټ�һ��β��
		list_item<T> *new_item = static_cast<list_item<T>*>(operator new(sizeof(list_item<T>)));
		new_item->item_ptr_[prev_index_] = tail_;
		new_item->item_ptr_[next_index_] = NULL;
		tail_->item_ptr_[next_index_] = new_item;
		tail_ = new_item;
	}

	template<class T>
	list<T>::~list()
	{
		// ѭ������head_��tail_֮������нڵ�
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
	template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type>
	void list<T>::assign(_Iter _First, _Iter _Last)
	{
		size_ = 0;
		// ���޸����еĽڵ�
		list_item<T> *p = NULL;
		for(p = head_->item_ptr_[next_index_];
			p != tail_ && _First != _Last; p = p->item_ptr_[next_index_])
		{
			p->val_ = *_First++;
			++size_;
		}
		if(_First != _Last)	// ��δ������ϵ����
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
		else if(p != tail_)	// ������ϣ������ж���Ԫ���������� 
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
		return static_cast<unsigned int>(-1) / sizeof(list_item<T>) - 1;	// -1 is for the head node
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
		// ѭ��������head_����һ��ָ��ָ��tail_
		size_ = 0;
	}

	
	template<class T>
	void list<T>::push_front(const T &_Value)
	{
		// ������Ԫ��
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
		// ������Ԫ��
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

	template<class T>template<class Iter, typename std::enable_if<!std::is_integral<Iter>::value, int>::type>
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
		// ����head_��tail_
		list_item<T> *tmp_ptr = head_;
		head_ = tail_;
		tail_ = tmp_ptr;
		// ��дprev_index_��next_index_
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

	template<class T>
	void list<T>::sort()
	{
		// ������ù鲢����
		merge_sort(head_, tail_, size_);
	}

	template<class T>template<class _Comparer>
	void list<T>::sort(const _Comparer &comparer)
	{
		// ������ù鲢����
		merge_sort(head_, tail_, size_, comparer);
	}


	// STL�е�=������У���ÿ��Ԫ�صĸ��ƣ���һ����ÿ��Ԫ�ص�=���ǿ������캯��
	// ��right��*this��size��С����
	template<class T>
	list<T>& list<T>::operator = (const list<T> &right)
	{
		if(this == &right)
		{
			return *this;
		}
		// ���޸����еĽڵ�
		list_item<T> *p = NULL;
		list_item<T> *q = right.head_->item_ptr_[next_index_];
		for(p = head_->item_ptr_[next_index_];
			p != tail_ && q != right.tail_; p = p->item_ptr_[next_index_], q = q->item_ptr_[next_index_])
		{
			p->val_ = q->val_;
		}
		if(q != right.tail_)	// ��δ��ֵ��ϵ����
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
		else if(p != tail_)	// ��ֵ��ϣ������ж���Ԫ���������� 
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
		// ���޸����еĽڵ�
		list_item<T> *p = NULL;
		for(p = head_->item_ptr_[next_index_];
			p != tail_ && size_ < _Count; p = p->item_ptr_[next_index_])
		{
			p->val_ = _Value;
			++size_;
		}
		if(size_ < _Count)	// ��δ������ϵ����
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
		else if(p != tail_)	// ������ϣ������ж���Ԫ���������� 
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

	template<class T>
	void list<T>::merge_sort(list_item<T> *head, list_item<T> *tail, size_t length)
	{
		// Ҫ�ϲ�������ֻ��0����1��Ԫ��
		//if(head->item_ptr_[next_index_] == tail || head->item_ptr_[next_index_] == tail->item_ptr_[prev_index_])
		if(length <= 1)
		{
			return;
		}
		size_t half_length = length / 2;
		list_item<T> *p = head;
		for(size_t i = 0; i < half_length; ++i)
		{
			p = p->item_ptr_[next_index_];
		}
		// ��(head, tail)��Ϊ(head, p]��[q, tail)���Σ����й鲢����
		// 1. ���
		merge_sort(p, tail, length - half_length);
		list_item<T> *q = p->item_ptr_[next_index_];
		merge_sort(head, q, half_length);
		// 2. �ϲ�
		// ��ʱq�Ѿ�ָ���˺������ĵ�һ��Ԫ�أ�����pָ���������ĵ�һ��Ԫ��
		const list_item<T> *left_tail = q;
		p = head->item_ptr_[next_index_];
		list_item<T> *last = head;
		// �ҳ���С�ģ���head�����
		while(p != left_tail || q != tail)
		{
			if(q == tail || (p != left_tail &&  p->val_ < q->val_))
			{
				// ��p�ڵ����last����
				last->item_ptr_[next_index_] = p;
				p->item_ptr_[prev_index_] = last;
				last = p;
				p = p->item_ptr_[next_index_];
			}
			else
			{
				// ��q�ڵ����last����
				last->item_ptr_[next_index_] = q;
				q->item_ptr_[prev_index_] = last;
				last = q;
				q = q->item_ptr_[next_index_];
			}
		}
		// ��last��tail������
		last->item_ptr_[next_index_] = tail;
		tail->item_ptr_[prev_index_] = last;
	}

	template<class T>template<class _Comparer>
	void list<T>::merge_sort(list_item<T> *head, list_item<T> *tail, size_t length, const _Comparer &comparer)
	{
		// Ҫ�ϲ�������ֻ��0����1��Ԫ��
		if(length <= 1)
		{
			return;
		}
		size_t half_length = length / 2;
		list_item<T> *p = head;
		for(size_t i = 0; i < half_length; ++i)
		{
			p = p->item_ptr_[next_index_];
		}
		// ��(head, tail)��Ϊ(head, p]��[q, tail)���Σ����й鲢����
		// 1. ���
		merge_sort(p, tail, length - half_length, comparer);
		list_item<T> *q = p->item_ptr_[next_index_];
		merge_sort(head, q, half_length, comparer);
		// 2. �ϲ�
		// ��ʱq�Ѿ�ָ���˺������ĵ�һ��Ԫ�أ�����pָ���������ĵ�һ��Ԫ��
		const list_item<T> *left_tail = q;
		p = head->item_ptr_[next_index_];
		list_item<T> *last = head;
		// �ҳ���С�ģ���head�����
		while(p != left_tail || q != tail)
		{
			if(q == tail || (p != left_tail &&  comparer(p->val_, q->val_)))
			{
				// ��p�ڵ����last����
				last->item_ptr_[next_index_] = p;
				p->item_ptr_[prev_index_] = last;
				last = p;
				p = p->item_ptr_[next_index_];
			}
			else
			{
				// ��q�ڵ����last����
				last->item_ptr_[next_index_] = q;
				q->item_ptr_[prev_index_] = last;
				last = q;
				q = q->item_ptr_[next_index_];
			}
		}
		// ��last��tail������
		last->item_ptr_[next_index_] = tail;
		tail->item_ptr_[prev_index_] = last;
	}

}

#endif

