#ifndef XF_DEQUE_HPP
#define XF_DEQUE_HPP
#include "vector.hpp"
#include "_Deque_Common.hpp"
#include "_Deque_Iterator.hpp"
#include "_Reverse_Iterator.hpp"
#include "common_algorithm.hpp"
#include "memory.hpp"

#include <iostream>

#ifdef _MSC_VER
#include <crtdbg.h>
#endif

namespace xf
{

	// map_�Ǵ洢����ڴ��ĵ�ַ��
	// ��һ���ڴ�����Ч��ַΪ[front_bin_index_, SEGMENT_LENGTH - 1]
	// ���һ���ڴ�����Ч��ַΪ[0, back_bin_index_]
	// ��map_�г���һ���ڴ��ʱ��front_bin_index_��back_bin_index_����Ч
	// ��map_ֻ��һ���ڴ��ʱ��back_bin_index_��front_bin_index_��һ���ĸ�����Ч��
	// ��������Чʱ���ܱ�֤���ּ����ͨ����

	// ��deque��map_���˵������������£�
	// front_bin_index_��ʾdeque_��һ��Ԫ�����ڵ�map_��bin�е�������������Чʱ����������Ӧ��ǡ���ǵ�һ��Ԫ�ص�λ�á���Чʱ��Ĭ��ֵ���¡�
	// back_bin_index_��ʾdeque_���һ��Ԫ�����ڵ�map_��bin�е�������������Чʱ����������Ӧ��ǡ�������һ��Ԫ�ص�λ�á���Чʱ��Ĭ��ֵ���¡�
	// front_bin_index_ = 0
	// back_bin_index_ = SEGMENT_LENGTH - 1
	// Ĭ��ֵ�����ã���Ҫ������size()���������ͨ����

	template<class T>
	class deque
	{
	public:

		typedef _Deque_Iterator<T> iterator;
		typedef _Deque_Const_Iterator<T> const_iterator;
		typedef _Reverse_Iterator<iterator> reverse_iterator;
		typedef _Reverse_Iterator<const_iterator> const_reverse_iterator;

		deque();
		deque(const deque<T> & _Right);
		deque(size_t n);
		deque(size_t n, const T & _Value);
		template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type = 0> deque(_Iter begin, _Iter end);
		deque(int _Count, const T& _Value) : front_bin_index_(0), back_bin_index_(SEGMENT_LENGTH - 1), map_()
		{
			this->insert_n(this->begin(), _Count, _Value);
		}
		virtual ~deque();

		size_t size() const;
		bool empty() const;
		size_t max_size() const;

		void resize(size_t new_size, T new_value = T());
		void clear();

		iterator insert(const const_iterator &_Where, const T &_Value);
		iterator insert(const const_iterator &_Where, size_t _Count, const T &_Value);
		template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type = 0>
		iterator insert(const const_iterator &_Where, _Iter _First, _Iter _Last);
		iterator insert(const const_iterator &_Where, int _Count, const T& _Value)
		{
			return this->insert_n(_Where, _Count, _Value);
		}

		iterator erase(const const_iterator &_Where);
		iterator erase(const const_iterator &_First, const const_iterator &_Last);

		void assign(size_t count, const T &val);
		template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type = 0>
		void assign(_Iter _First, _Iter _Last);
		void assign(int _Count, const T& _Value)
		{
			return this->assign_n(_Count, _Value);
		}

		const T& front() const;
		T& front();
		const T& back() const;
		T& back();

		void push_front(const T &_Val);
		void push_back(const T &_Val);

		void pop_front();
		void pop_back();

		// iterator
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

		const T& at(size_t index) const throw(std::out_of_range);
		T& at(size_t index) throw(std::out_of_range);

		const T& operator [](size_t index) const;
		T& operator [](size_t index);

		deque<T>& operator = (const deque<T> & _Right);
		
	private:
		iterator insert_n(const const_iterator _Where, size_t _Count, const T &_Value);	
		void insert_back(const size_t where_offset, const T &_Value);
		void insert_front(const size_t where_offset, const T &_Value);
		void insert_n_back(const size_t where_offset, size_t _Count, const T &_Value);
		void insert_n_front(const size_t where_offset, size_t _Count, const T &_Value);
		template<class _Iter>void insert_back(const size_t where_offset, _Iter _First, _Iter _Last);
		template<class _Iter>void insert_front(const size_t where_offset, _Iter _First, _Iter _Last);
		
		void erase_front(const size_t where_offset);
		void erase_back(const size_t where_offset);
		void erase_front(const const_iterator &_First, const const_iterator &_Last);
		void erase_back(const const_iterator &_First, const const_iterator &_Last);

		void assign_n(size_t count, const T &val);

		static size_t SEGMENT_LENGTH;
		size_t front_bin_index_;
		size_t back_bin_index_;
		vector<T*> map_;
	};

	template<class T>
	size_t deque<T>::SEGMENT_LENGTH = DequeSegmentLength();

	template<class T>
	deque<T>::deque() : front_bin_index_(0), back_bin_index_(SEGMENT_LENGTH - 1), map_()
	{
		;
	}

	template<class T>
	deque<T>::deque(const deque<T> & _Right) : front_bin_index_(_Right.front_bin_index_), back_bin_index_(_Right.back_bin_index_), map_()
	{
		size_t right_map_size = _Right.map_.size();
		map_.resize(right_map_size);
		// ��len=1ʱ��front_bin_index_��back_bin_index_����Ч��Ҫͬʱ����
		if(1 == right_map_size)
		{
			map_[0] = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
			for(size_t j = front_bin_index_; j <= back_bin_index_; ++j)
			{
				new(map_.front() + j) T(_Right.map_.front()[j]);
			}
		}
		else
		{
			for(size_t i = 0; i < right_map_size; ++i)
			{
				map_[i] = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
				if(0 == i)	// �׸�bin
				{
					for(size_t j = front_bin_index_; j < SEGMENT_LENGTH; ++j)
					{
						new(map_.front() + j) T(_Right.map_.front()[j]);
					}
				}
				else if(i == right_map_size - 1)	// ĩ��bin
				{
					for(size_t j = 0; j <= back_bin_index_; ++j)
					{
						new(map_.back() + j) T(_Right.map_.back()[j]);
					}
				}
				else
				{
					for(size_t j = 0; j < SEGMENT_LENGTH; ++j)
					{
						new(map_[i] + j) T(_Right.map_[i][j]);
					}
				}
			}
		}
	}

	template<class T>
	deque<T>::deque(size_t n) : front_bin_index_(0), back_bin_index_((n + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH), map_()
	{
		size_t full_bins = n / SEGMENT_LENGTH;
		size_t remain_num = n % SEGMENT_LENGTH;
		map_.reserve(full_bins + sgn(remain_num));
		for(size_t i = 0; i < full_bins; ++i)
		{
			map_.push_back(new T[SEGMENT_LENGTH]);
		}
		if(remain_num > 0)
		{
			T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
			for(size_t i = 0; i < remain_num; ++i)
			{
				new(p + i) T();
			}
			map_.push_back(p);
		}
	}

	template<class T>
	deque<T>::deque(size_t n, const T & _Value) : front_bin_index_(0), back_bin_index_((n + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH), map_()
	{
		size_t full_bins = n / SEGMENT_LENGTH;
		size_t remain_num = n % SEGMENT_LENGTH;
		map_.reserve(full_bins + sgn(remain_num));
		for(size_t i = 0; i < full_bins; ++i)
		{
			T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
			xf::uninitialized_fill(p, p + SEGMENT_LENGTH, _Value);
			map_.push_back(p);
		}
		if(remain_num > 0)
		{
			T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
			xf::uninitialized_fill(p, p + remain_num, _Value);
			map_.push_back(p);
		}
	}

	template<class T>
	template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type>
	deque<T>::deque(_Iter begin, _Iter end) : front_bin_index_(0), back_bin_index_(SEGMENT_LENGTH - 1), map_()
	{
		for(_Iter iter = begin; iter != end; ++iter)
		{
			push_back(*iter);
		}
	}

	template<class T>
	deque<T>::~deque()
	{
		size_t len = map_.size();
		// ��len=1ʱ����front_bin_index_��back_bin_index_��ʾ����ͬһ��bin��ʱ��Ҫ���⴦�����жϵ����ĸ�������
		if(1 == len)
		{
			for(size_t j = front_bin_index_; j <= back_bin_index_; ++j)
			{
				(map_.front() + j)->~T();
			}
			operator delete[](map_.front());
		}
		else	// len!=1ʱ���������������
		{
			for(size_t i = 0; i < len; ++i)
			{
				if(0 == i)	// �׸�bin
				{
					for(size_t j = front_bin_index_; j < SEGMENT_LENGTH; ++j)
					{
						(map_.front() + j)->~T();
					}
					operator delete[](map_.front());
				}
				else if(i == len - 1)	// ĩ��bin
				{
					for(size_t j = 0; j <= back_bin_index_; ++j)
					{
						(map_.back() + j)->~T();
					}
					operator delete[](map_.back());
				}
				else
				{
					delete [](map_[i]);
				}
			}
		}
	}

	template<class T>
	size_t deque<T>::size() const
	{
		return ((static_cast<int>(map_.size()) - 2) * SEGMENT_LENGTH + (SEGMENT_LENGTH - front_bin_index_) + back_bin_index_ + 1);
	}

	template<class T>
	bool deque<T>::empty() const
	{
		return map_.size() == 0;
	}

	template<class T>
	size_t deque<T>::max_size() const
	{
		return static_cast<unsigned int>(-1) / sizeof(T);
	}

	template<class T>
	void deque<T>::resize(size_t new_size, T new_value)
	{
		int insert_count = new_size - size();
		int erase_count = -insert_count;
		if(insert_count > 0)
		{
			this->insert(this->end(), insert_count, new_value);
		}
		else if(erase_count > 0)
		{
			this->erase(this->end() - erase_count, this->end());
		}
	}

	template<class T>
	void deque<T>::clear()
	{
		resize(0);
	}

	template<class T>
	typename deque<T>::iterator deque<T>::insert(const typename deque<T>::const_iterator &_Where, const T &_Value)
	{
		size_t where_offset = _Where - cbegin();
		if(_Where == cend())
		{
			push_back(_Value);
		}
		else if(_Where == cbegin())
		{
			push_front(_Value);
		}
		else	// ���ڣ����Ա�֤��insert��Ԫ�أ�һ���ڷǿյ�deque���м䲿λ
		{
			// ����ʱ���ж��ƶ�ǰ���Ԫ�ػ����ƶ�����Ԫ��
			if(where_offset * 2 < size())	
			{
				insert_front(where_offset, _Value);	// λ�ÿ�ǰ�����ƶ�ǰ���
			}
			else
			{
				insert_back(where_offset, _Value);	// �����ƶ�����
			}
			
		}
		return begin() + where_offset;
	}

	template<class T>
	typename deque<T>::iterator deque<T>::insert(const typename deque<T>::const_iterator &_Where, size_t _Count, const T &_Value)
	{
		return insert_n(_Where, _Count, _Value);
	}

	template<class T>template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type>
	typename deque<T>::iterator deque<T>::insert(const typename deque<T>::const_iterator &_Where, _Iter _First, _Iter _Last)
	{
		size_t _Count = xf::distance(_First, _Last);
		// ���²��ָı���insert_n
		if(empty())
		{
			assert(_Where == cbegin() || _Where == cend());
			back_bin_index_ = (_Count + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
			size_t full_bins = _Count / SEGMENT_LENGTH;
			size_t remain_num = _Count % SEGMENT_LENGTH;
			map_.reserve(full_bins + sgn(remain_num));
			_Iter _Next;
			for(size_t i = 0; i < full_bins; ++i)
			{
				T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
				_Next = _First + SEGMENT_LENGTH;
				xf::uninitialized_copy(_First, _Next, p);
				_First = _Next;
				//std::uninitialized_fill(p, p + SEGMENT_LENGTH, _Value);
				map_.push_back(p);
			}
			if(remain_num > 0)
			{
				T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
				xf::uninitialized_copy(_First, _Last, p);
				//std::uninitialized_fill(p, p + remain_num, _Value);
				map_.push_back(p);
			}
			return begin();
		}
		else
		{
			// 0. Ԥ��¼��ֵ
			size_t where_offset = _Where - cbegin();
			if(where_offset * 2 < size())
			{
				insert_front(where_offset, _First, _Last);
			}
			else
			{
				insert_back(where_offset, _First, _Last);
			}
			
			return begin() + where_offset;
		}
	}

	template<class T>
	typename deque<T>::iterator deque<T>::erase(const typename deque<T>::const_iterator &_Where)
	{
		const size_t where_offset = _Where - cbegin();
		if(where_offset * 2 + 1 < size())
		{
			erase_front(where_offset);
		}
		else
		{
			erase_back(where_offset);
		}
		return begin() + where_offset;
	}
	template<class T>
	typename deque<T>::iterator deque<T>::erase(const typename deque<T>::const_iterator &_First, const typename deque<T>::const_iterator &_Last)
	{
		int first_offset = _First - cbegin();
		// _First == _Last�Ĵ���
		if(_First == _Last)
		{
			return begin() + first_offset;
		}
		else if(first_offset < cend() - _Last)
		{
			erase_front(_First, _Last);
		}
		else
		{
			erase_back(_First, _Last);
		}
		return begin() + first_offset;
	}

	template<class T>
	void deque<T>::assign(size_t count, const T &val)
	{
		this->clear();
		this->insert_n(this->begin(), count, val);
	}
	template<class T>template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type>
	void deque<T>::assign(_Iter _First, _Iter _Last)
	{
		this->clear();
		this->insert(this->begin(), _First, _Last);
	}


	template<class T>
	const T& deque<T>::front() const
	{
		return map_.front()[front_bin_index_];
	}
	template<class T>
	T& deque<T>::front()
	{
		return map_.front()[front_bin_index_];
	}

	template<class T>
	const T& deque<T>::back() const
	{
		return map_.back()[back_bin_index_];
	}
	template<class T>
	T& deque<T>::back()
	{
		return map_.back()[back_bin_index_];
	}

	template<class T>
	void deque<T>::push_front(const T &_Val)
	{
		if(0 == front_bin_index_)
		{
			T *p = reinterpret_cast<T*>(operator new[](SEGMENT_LENGTH * sizeof(T)));
			front_bin_index_ = SEGMENT_LENGTH - 1;
			new(p + front_bin_index_) T(_Val);
			map_.insert(map_.begin(), p);
		}
		else
		{
			--front_bin_index_;
			new(map_.front() + front_bin_index_) T(_Val);
		}
	}
	
	template<class T>
	void deque<T>::push_back(const T &_Val)
	{
		if(SEGMENT_LENGTH - 1 == back_bin_index_)
		{
			T *p = reinterpret_cast<T*>(operator new[](SEGMENT_LENGTH * sizeof(T)));
			new(p) T(_Val);
			map_.push_back(p);
			back_bin_index_ = 0;
		}
		else
		{
			++back_bin_index_;
			new(map_.back() + back_bin_index_) T(_Val);
		}
	}

	template<class T>
	void deque<T>::pop_front()
	{
		map_.front()[front_bin_index_].~T();	// ���ٸ�Ԫ��
		++front_bin_index_;						// �����׿�ָ��
		if(SEGMENT_LENGTH == front_bin_index_)	// �ж��Ƿ��׸�bin�ѿ�
		{
			operator delete[] (map_.front());
			map_.erase(map_.begin());
			front_bin_index_ = 0;
		}
	}

	template<class T>
	void deque<T>::pop_back()
	{
		map_.back()[back_bin_index_].~T();	// ���ٸ�Ԫ��
		if(0 == back_bin_index_)			// �ж��Ƿ�ĩ��bin�ѿ�
		{
			operator delete[] (map_.back());
			map_.pop_back();
			back_bin_index_ = SEGMENT_LENGTH;
		}
		--back_bin_index_;
	}
	
	template<class T>
	typename deque<T>::const_iterator deque<T>::cbegin() const
	{
		return const_iterator(map_.cbegin(), front_bin_index_);
	}
	template<class T>
	typename deque<T>::const_iterator deque<T>::begin() const
	{
		return cbegin();
	}
	template<class T>
	typename deque<T>::iterator deque<T>::begin()
	{
		return iterator(map_.begin(), front_bin_index_);
	}
	template<class T>
	typename deque<T>::const_iterator deque<T>::cend() const
	{
		if(empty())
		{
			return const_iterator(map_.cbegin(), 0);
		}
		else
		{
			return ++const_iterator(map_.cend() - 1, back_bin_index_);
		}
	}
	template<class T>
	typename deque<T>::const_iterator deque<T>::end() const
	{
		return cend();
	}
	template<class T>
	typename deque<T>::iterator deque<T>::end()
	{
		if(empty())
		{
			return iterator(map_.begin(), 0);
		}
		else
		{
			return ++iterator(map_.end() - 1, back_bin_index_);
		}
	}

	template<class T>
	typename deque<T>::const_reverse_iterator deque<T>::crbegin() const
	{
		return const_reverse_iterator(cend());
	}
	template<class T>
	typename deque<T>::const_reverse_iterator deque<T>::rbegin() const
	{
		return crbegin();
	}
	template<class T>
	typename deque<T>::reverse_iterator deque<T>::rbegin()
	{
		return reverse_iterator(end());
	}

	template<class T>
	typename deque<T>::const_reverse_iterator deque<T>::crend() const
	{
		return const_reverse_iterator(cbegin());
	}
	template<class T>
	typename deque<T>::const_reverse_iterator deque<T>::rend() const
	{
		return crend();
	}
	template<class T>
	typename deque<T>::reverse_iterator deque<T>::rend()
	{
		return reverse_iterator(begin());
	}

	template<class T>
	const T& deque<T>::at(size_t index) const throw(std::out_of_range)
	{
		if(index >= size())
		{
			throw std::out_of_range("invalid deque<T> subscript");
		}
		else
		{
			// �ȼ���deque�е�index��Ԫ�������map_��һ��bin����Ԫ�ص�ƫ����
			size_t offset = index + front_bin_index_;
			// Ȼ�����ƶ�ά��������������ֵ
			return map_[offset / SEGMENT_LENGTH][offset % SEGMENT_LENGTH];
		}
	}
	template<class T>
	T& deque<T>::at(size_t index) throw(std::out_of_range)
	{
		if(index >= size())
		{
			throw std::out_of_range("invalid deque<T> subscript");
		}
		else
		{
			// �ȼ���deque�е�index��Ԫ�������map_��һ��bin����Ԫ�ص�ƫ����
			size_t offset = index + front_bin_index_;
			// Ȼ�����ƶ�ά��������������ֵ
			return map_[offset / SEGMENT_LENGTH][offset % SEGMENT_LENGTH];
		}
	}

	template<class T>
	const T& deque<T>::operator [](size_t index) const
	{
		// �ȼ���deque�е�index��Ԫ�������map_��һ��bin����Ԫ�ص�ƫ����
		size_t offset = index + front_bin_index_;
		// Ȼ�����ƶ�ά��������������ֵ
		return map_[offset / SEGMENT_LENGTH][offset % SEGMENT_LENGTH];
	}

	template<class T>
	T& deque<T>::operator [](size_t index)
	{
		// �ȼ���deque�е�index��Ԫ�������map_��һ��bin����Ԫ�ص�ƫ����
		size_t offset = index + front_bin_index_;
		// Ȼ�����ƶ�ά��������������ֵ
		return map_[offset / SEGMENT_LENGTH][offset % SEGMENT_LENGTH];
	}

	template<class T>
	void deque<T>::insert_back(const size_t where_offset, const T &_Value)
	{
		// 1. �����µĿռ䣨����б�Ҫ����Ȼ���insert֮ǰ�����һ��Ԫ�أ������һ����Ԫ
		if(SEGMENT_LENGTH - 1 == back_bin_index_)
		{
			T *p = reinterpret_cast<T*>(operator new[](SEGMENT_LENGTH * sizeof(T)));
			new(p) T(back());
			map_.push_back(p);
			back_bin_index_ = 0;
		}
		else
		{
			new(map_.back() + back_bin_index_ + 1) T(back());
			++back_bin_index_;
		}
		// 2. ��[_Where, end - 2]��Ԫ��ȫ������ƶ�һλ
		iterator copy_iter = end() - 2;	// ����copy_iterָ��insert֮ǰ�����һ��Ԫ��
		iterator prev_iter = copy_iter;
		iterator insert_position = begin() + where_offset;
		while(copy_iter != insert_position)
		{
			--prev_iter;
			*copy_iter = *prev_iter;
			copy_iter = prev_iter;
		}
		// 3. Ϊ�µ�Ԫ�ظ�ֵ
		*insert_position = _Value;
	}

	template<class T>
	void deque<T>::insert_front(const size_t where_offset, const T &_Value)
	{
		// 1. �����µĿռ䣨����б�Ҫ����Ȼ���insert֮ǰ�����һ��Ԫ�أ������һ����Ԫ
		if(0 == front_bin_index_)
		{
			T *p = reinterpret_cast<T*>(operator new[](SEGMENT_LENGTH * sizeof(T)));
			new(p) T(front());
			map_.insert(map_.begin(), p);
			front_bin_index_ = SEGMENT_LENGTH - 1;
		}
		else
		{
			new(map_.back() + front_bin_index_ - 1) T(front());
			--front_bin_index_;
		}
		// 2. ��[begin, _Where)��Ԫ��ȫ����ǰ�ƶ�һλ
		iterator copy_iter = begin();
		iterator next_iter = copy_iter;
		iterator insert_position = begin() + where_offset;
		while(copy_iter != insert_position)
		{
			++next_iter;
			*copy_iter = *next_iter;
			copy_iter = next_iter;
		}
		// 3. Ϊ�µ�Ԫ�ظ�ֵ
		*insert_position = _Value;
	}

	template<class T>
	typename deque<T>::iterator deque<T>::insert_n(const typename deque<T>::const_iterator _Where, size_t _Count, const T &_Value)
	{
		if(empty())
		{
			assert(_Where == cbegin() || _Where == cend());
			back_bin_index_ = (_Count + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
			size_t full_bins = _Count / SEGMENT_LENGTH;
			size_t remain_num = _Count % SEGMENT_LENGTH;
			map_.reserve(full_bins + sgn(remain_num));
			for(size_t i = 0; i < full_bins; ++i)
			{
				T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
				xf::uninitialized_fill(p, p + SEGMENT_LENGTH, _Value);
				map_.push_back(p);
			}
			if(remain_num > 0)
			{
				T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
				xf::uninitialized_fill(p, p + remain_num, _Value);
				map_.push_back(p);
			}
			return begin();
		}
		else
		{
			// 0. Ԥ��¼��ֵ
			size_t orig_size = size();
			size_t where_offset = _Where - cbegin();
			if(where_offset * 2 < size())
			{
				insert_n_front(where_offset, _Count, _Value);
			}
			else
			{
				insert_n_back(where_offset, _Count, _Value);
			}
			return begin() + where_offset;
		} // if
	} // function

	template<class T>
	void deque<T>::insert_n_back(const size_t where_offset, size_t _Count, const T &_Value)
	{
		size_t orig_size = size();
		// 1. ���ж�Ҫ����Ķ��ⳤ�ȣ��������deque�����Ӧ��������_Count��δ��ʼ�����ڴ�ռ�
		int new_count = _Count - (SEGMENT_LENGTH - 1 - back_bin_index_);
		size_t remain_num = 0;	// �����������һ��bin��Ӧ��ʣ���Ԫ������
		if(new_count > 0)
		{
			remain_num = new_count % SEGMENT_LENGTH;
			size_t new_bins = (new_count / SEGMENT_LENGTH + sgn(remain_num));
			for(size_t i = 0; i < new_bins; ++i)
			{
				map_.push_back(reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T))));
			}
		}
		else
		{
			remain_num = back_bin_index_ + 1 + _Count;
		}
		// IMP ����deque����������
		back_bin_index_ = (remain_num + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
		// Ԥ��¼
		const iterator orig_end(begin() + orig_size);
		// 2. �ƶ�ԭ��Ԫ�أ����ڿճ���λ�ø�����ֵ
		size_t last_length = orig_size - where_offset;
		// 2a. ��last_length <= _Count
		if(last_length <= _Count)
		// 2a.1 ͨ��placement new��ʹ�ÿ������캯����deque��[_Where, orig_end)���Ƶ�[new_end - last_length, new_end)����������Ϊlast_length��˳��/����Կɣ������õ���
		// 2a.2 ������=Ϊ[_Where, end)��Ԫ�ظ���ֵ����ֵ����Ϊlast_length
		// 2a.3 ͨ��placement new��ʹ�ÿ������캯����[orig_end, orig_end + _Count - last_length)��ʼ��Ϊ��ֵ
		{
			iterator src_iter = orig_end - 1;
			iterator dst_iter = iterator(map_.end() - 1, back_bin_index_);
			for(size_t i = 0; i < last_length; ++i)
			//while(src_iter != _Where)	// ������ô�ã���Ϊ_Whereָ���Ԫ��ҲӦ�ñ�����
			{
				new(&*dst_iter) T(*src_iter);	// 2a.1
				*src_iter = _Value;				// 2a.2
				--dst_iter;
				--src_iter;
			}
			// 2a.3
			src_iter = orig_end;
			while(src_iter <= dst_iter)
			{
				new(&*src_iter) T(_Value);
				++src_iter;
			}
		}

		// 2b. ��last_length > _Count
		else
		// 2b.1 ͨ��placement newʹ�ÿ������캯������[end - _Count, end)���Ƶ�[new_end - _Count, new_end)����������Ϊ_Count����������Կɣ������õ���
		// 2b.2 ������=����[_Where, end - _Count)���Ƶ�[_Where + _Count, end)����������Ϊlast_length - _Count��������
		// 2b.3 ͨ������=����[_Where, _Where + _Count)��Ԫ�ظ�����ֵ����ֵ����Ϊ_Count
		{
			// 2b.1
			iterator src_iter = orig_end - 1;
			iterator dst_iter = end() - 1;
			for(size_t i = 0; i < _Count; ++i)
			{
				new(&*dst_iter) T(*src_iter);
				--src_iter;
				--dst_iter;
			}
			// 2b.2
			size_t move_length = last_length - _Count;
			for(size_t i = 0; i < move_length; ++i)
			{
				*dst_iter = *src_iter;
				--src_iter;
				--dst_iter;
			}
			// 2b.3
			src_iter = begin() + where_offset;
			while(src_iter <= dst_iter)
			{
				*src_iter = _Value;
				++src_iter;
			}
		} // if
	}

	template<class T>
	void deque<T>::insert_n_front(const size_t where_offset, size_t _Count, const T &_Value)
	{
		// 1. ���ж�Ҫ����Ķ��ⳤ�ȣ��������deque����ǰ�棬Ӧ��������_Count��δ��ʼ�����ڴ�ռ�
		int new_count = _Count - front_bin_index_;
		size_t remain_num = 0;	// ���������һ��bin��Ӧ��ʣ���Ԫ������
		if(new_count > 0)
		{
			remain_num = new_count % SEGMENT_LENGTH;
			size_t new_bins = (new_count / SEGMENT_LENGTH + sgn(remain_num));
			for(size_t i = 0; i < new_bins; ++i)
			{
				map_.insert(map_.cbegin(), reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T))));
			}
		}
		else
		{
			remain_num = SEGMENT_LENGTH - front_bin_index_ + _Count;
		}
		// IMP ����deque����������
		front_bin_index_ = (SEGMENT_LENGTH - remain_num) % SEGMENT_LENGTH;
		// Ԥ��¼
		const iterator orig_begin(begin() + _Count);
		// 2. �ƶ�ԭ��Ԫ�أ����ڿճ���λ�ø�����ֵ
		// 2a. ��where_offset <= _Count
		if(where_offset <= _Count)
		// 2a.1 ͨ��placement new��ʹ�ÿ������캯����deque��[orig_begin, orig_begin + where_offset)���Ƶ�[new_begin, new_begin + where_offset)����������Ϊwhere_offset��˳��/����Կɣ�����������
		// 2a.2 ͨ������=����[orig_begin, orig_begin + where_offset)����ֵ
		// 2a.3 ͨ��placement new��ʹ�ÿ������캯����[new_begin + where_offset, orig_begin)��Ԫ�ظ���ֵ����ֵ����Ϊ_Count - where_offset
		{
			iterator src_iter = orig_begin;
			iterator dst_iter = begin();
			for(size_t i = 0; i < where_offset; ++i)
			{
				new(&*dst_iter) T(*src_iter);	// 2a.1
				*src_iter = _Value;				// 2a.2
				++dst_iter;
				++src_iter;
			}
			// 2a.3
			while(dst_iter < orig_begin)
			{
				new(&*dst_iter) T(_Value);
				++dst_iter;
			}
		}
		// 2b. ��where_offset > _Count
		else
		// 2b.1 ͨ��placement newʹ�ÿ������캯������[orig_begin, orig_begin + _Count)���Ƶ�[new_begin, orig_begin)����������Ϊ_Count����������Կɣ�����������
		// 2b.2 ������=����[orig_begin + _Count, orig_begin + where_offset)���Ƶ�[orig_begin, new_begin + where_offset)����������Ϊwhere_offset - _Count��������
		// 2b.3 ͨ������=����[new_begin + where_offset, orig_begin + where_offset)��Ԫ�ظ�����ֵ����ֵ����Ϊ_Count
		{
			// 2b.1
			iterator src_iter = orig_begin;
			iterator dst_iter = begin();
			for(size_t i = 0; i < _Count; ++i)
			{
				new(&*dst_iter) T(*src_iter);
				++src_iter;
				++dst_iter;
			}
			// 2b.2
			src_iter = orig_begin + _Count;
			dst_iter = orig_begin;
			size_t move_length = where_offset - _Count;
			for(size_t i = 0; i < move_length; ++i)
			{
				*dst_iter = *src_iter;
				++src_iter;
				++dst_iter;
			}
			// 2b.3
			src_iter = begin() + where_offset;
			while(dst_iter < src_iter)
			{
				*dst_iter = _Value;
				++dst_iter;
			}
		} // if
	}

	template<class T>template<class _Iter>
	void deque<T>::insert_back(const size_t where_offset, _Iter _First, _Iter _Last)
	{
		size_t orig_size = size();
		size_t _Count = distance(_First, _Last);
		// 1. ���ж�Ҫ����Ķ��ⳤ�ȣ��������deque�����Ӧ��������_Count��δ��ʼ�����ڴ�ռ�
		int new_count = _Count - (SEGMENT_LENGTH - 1 - back_bin_index_);
		size_t remain_num = 0;	// �����������һ��bin��Ӧ��ʣ���Ԫ������
		if(new_count > 0)
		{
			remain_num = new_count % SEGMENT_LENGTH;
			size_t new_bins = (new_count / SEGMENT_LENGTH + sgn(remain_num));
			for(size_t i = 0; i < new_bins; ++i)
			{
				map_.push_back(reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T))));
			}
		}
		else
		{
			remain_num = back_bin_index_ + 1 + _Count;
		}
		// IMP ����deque����������
		back_bin_index_ = (remain_num + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
		// Ԥ��¼
		const iterator orig_end(begin() + orig_size);
		// 2. �Ѵ�_Where��end()������(����Ϊlast_length)����ƶ�_Count�����Ӻ���ǰ���θ���
		const size_t last_length = orig_size - where_offset;
		// 2a. ��last_length <= _Count
		if(last_length <= _Count)
		// 2a.1 ͨ��placement new��ʹ�ÿ������캯����deque��[_Where, orig_end)���Ƶ�[new_end - last_length, new_end)����������Ϊlast_length��˳��/����Կɣ������õ���
		// 2a.2 ������=Ϊ[_Where, end)��Ԫ�ظ���ֵ����ֵ����Ϊlast_length
		// 2a.3 ͨ��placement new��ʹ�ÿ������캯����[orig_end, _Count - last_length)��ʼ��Ϊ��ֵ
		{
			iterator src_iter = orig_end - 1;
			iterator dst_iter = iterator(map_.end() - 1, back_bin_index_);
			for(size_t i = 0; i < last_length; ++i)
			//while(src_iter != _Where)	// ������ô�ã���Ϊ_Whereָ���Ԫ��ҲӦ�ñ�����
			{
				new(&*dst_iter) T(*src_iter);	// 2a.1
				*src_iter = *_First;			// 2a.2
				++_First;
				--dst_iter;
				--src_iter;
			}
			// 2a.3
			src_iter = orig_end;
			while(src_iter <= dst_iter)
			{
				new(&*src_iter) T(*_First);
				++_First;
				++src_iter;
			}
		}

		// 2b. ��last_length > _Count
		else
		// 2b.1 ͨ��placement newʹ�ÿ������캯������[end - _Count, end)���Ƶ�[new_end - _Count, new_end)����������Ϊ_Count����������Կɣ������õ���
		// 2b.2 ������=����[_Where, orig_end - _Count)���Ƶ�[_Where + _Count, end)����������Ϊlast_length - _Count��������
		// 2b.3 ͨ������=����[_Where, _Where + _Count)��Ԫ�ظ�����ֵ����ֵ����Ϊ_Count
		{
			// 2b.1
			iterator src_iter = orig_end - 1;
			iterator dst_iter = end() - 1;
			for(size_t i = 0; i < _Count; ++i)
			{
				new(&*dst_iter) T(*src_iter);
				--src_iter;
				--dst_iter;
			}
			// 2b.2
			const size_t move_length = last_length - _Count;
			for(size_t i = 0; i < move_length; ++i)
			{
				*dst_iter = *src_iter;
				--src_iter;
				--dst_iter;
			}
			// 2b.3
			src_iter = begin() + where_offset;
			while(src_iter <= dst_iter)
			{
				new(&*src_iter) T(*_First);
				++_First;
				++src_iter;
			}
		} // if
	}

	template<class T>template<class _Iter>
	void deque<T>::insert_front(const size_t where_offset, _Iter _First, _Iter _Last)
	{
		// 1. ���ж�Ҫ����Ķ��ⳤ�ȣ��������deque����ǰ�棬Ӧ��������_Count��δ��ʼ�����ڴ�ռ�
		size_t _Count = distance(_First, _Last);
		int new_count = _Count - front_bin_index_;
		size_t remain_num = 0;	// ���������һ��bin��Ӧ��ʣ���Ԫ������
		if(new_count > 0)
		{
			remain_num = new_count % SEGMENT_LENGTH;
			size_t new_bins = (new_count / SEGMENT_LENGTH + sgn(remain_num));
			for(size_t i = 0; i < new_bins; ++i)
			{
				map_.insert(map_.cbegin(), reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T))));
			}
		}
		else
		{
			remain_num = SEGMENT_LENGTH - front_bin_index_ + _Count;
		}
		// IMP ����deque����������
		front_bin_index_ = (SEGMENT_LENGTH - remain_num) % SEGMENT_LENGTH;
		// Ԥ��¼
		const iterator orig_begin(begin() + _Count);
		// 2. �ƶ�ԭ��Ԫ�أ����ڿճ���λ�ø�����ֵ
		// 2a. ��where_offset <= _Count
		if(where_offset <= _Count)
		// 2a.1 ͨ��placement new��ʹ�ÿ������캯����deque��[orig_begin, orig_begin + where_offset)���Ƶ�[new_begin, new_begin + where_offset)����������Ϊwhere_offset��˳��/����Կɣ�����������
		// 2a.2 ͨ��placement new��ʹ�ÿ������캯����[new_begin + where_offset, orig_begin)��Ԫ�ظ���ֵ����ֵ����Ϊ_Count - where_offset
		// 2a.3 ͨ������=����[orig_begin, orig_begin + where_offset)����ֵ
		{
			iterator src_iter = orig_begin;
			iterator dst_iter = begin();
			for(size_t i = 0; i < where_offset; ++i)
			{
				new(&*dst_iter) T(*src_iter);	// 2a.1
				++dst_iter;
				++src_iter;
			}
			while(dst_iter < orig_begin)
			{
				new(&*dst_iter) T(*_First);	// 2a.2
				++_First;
				++dst_iter;
			}
			// 2a.3
			while(_First != _Last)
			{
				*dst_iter = *_First;
				++_First;
				++dst_iter;
			}
		}
		// 2b. ��where_offset > _Count
		else
		// 2b.1 ͨ��placement newʹ�ÿ������캯������[orig_begin, orig_begin + _Count)���Ƶ�[new_begin, orig_begin)����������Ϊ_Count����������Կɣ�����������
		// 2b.2 ������=����[orig_begin + _Count, orig_begin + where_offset)���Ƶ�[orig_begin, new_begin + where_offset)����������Ϊwhere_offset - _Count��������
		// 2b.3 ͨ������=����[new_begin + where_offset, orig_begin + where_offset)��Ԫ�ظ�����ֵ����ֵ����Ϊ_Count
		{
			// 2b.1
			iterator src_iter = orig_begin;
			iterator dst_iter = begin();
			for(size_t i = 0; i < _Count; ++i)
			{
				new(&*dst_iter) T(*src_iter);
				++src_iter;
				++dst_iter;
			}
			// 2b.2
			src_iter = orig_begin + _Count;
			dst_iter = orig_begin;
			size_t move_length = where_offset - _Count;
			for(size_t i = 0; i < move_length; ++i)
			{
				*dst_iter = *src_iter;
				++src_iter;
				++dst_iter;
			}
			// 2b.3
			while(_First != _Last)
			{
				*dst_iter = *_First;
				++_First;
				++dst_iter;
			}
		} // if
	}

	template<class T>
	void deque<T>::erase_front(const size_t where_offset)
	{
		// ƽ��
		iterator iter = begin() + where_offset;
		iterator prev_iter = iter;
		for(size_t i = 0; i < where_offset; ++i)
		{
			--prev_iter;
			*iter = *prev_iter;
			iter = prev_iter;
		}
		// ���ٵ�һ��Ԫ��
		(*iter).~T();
		// ���³�Ա����������������ٵ�һ��bin
		++front_bin_index_;
		if(SEGMENT_LENGTH == front_bin_index_)
		{
			front_bin_index_ = 0;
			operator delete[](map_.front());
			map_.erase(map_.cbegin());
		}
	}
	template<class T>
	void deque<T>::erase_back(const size_t where_offset)
	{
		// ƽ��
		iterator iter = begin() + where_offset;
		iterator next_iter = iter;
		size_t move_length = size() - where_offset - 1;
		for(size_t i = 0; i < move_length; ++i)
		{
			std::cout << i << std::endl;
			++next_iter;
			*iter = *next_iter;
			iter = next_iter;
		}
		// �������һ��Ԫ��
		(*iter).~T();
		// ���³�Ա��������������������һ��bin
		if(0 == back_bin_index_)
		{
			back_bin_index_ = SEGMENT_LENGTH - 1;
			operator delete[](map_.back());
			map_.erase(map_.cend());
		}
		else
		{
			--back_bin_index_;
		}
	}
	template<class T>
	void deque<T>::erase_front(const typename deque<T>::const_iterator &_First, const typename deque<T>::const_iterator &_Last)
	{
		size_t first_offset = _First - cbegin();
		size_t last_offset = _Last - cbegin();
		size_t erase_count = last_offset - first_offset;
		//const_iterator orig_begin = cbegin();
		// ƽ��
		iterator iter_src = begin() + first_offset;
		iterator iter_dst = begin() + last_offset;
		for(size_t i = 0; i < first_offset; ++i)
		{
			--iter_dst;
			--iter_src;
			*iter_dst = *iter_src;
		}
		iterator new_begin_iter = iter_dst;
		while(iter_src < iter_dst)
		{
			(*iter_src).~T();
			++iter_src;
		}
		// ɾ��ǰ��Ŀ���bin
		// erase��dequeΪ�յ�ʱ��Ҫ�����е�bin��ɾ��
		if(new_begin_iter == cend())
		{
			for(typename vector<T*>::iterator map_iter = map_.begin();
				map_iter != map_.end();
				++map_iter)
			{
				operator delete[](*map_iter);
			}
			map_.clear();
			back_bin_index_ = SEGMENT_LENGTH - 1;
			front_bin_index_ = 0;
		}
		else 
		{
			typename vector<T*>::iterator map_iter = map_.begin();
			while(map_iter < new_begin_iter.map_iter_)
			{
				operator delete[](*map_iter);
				++map_iter;
			}
			map_.erase(map_.cbegin(), new_begin_iter.map_iter_);
			front_bin_index_ = new_begin_iter.item_index_;
		}
	}
	template<class T>
	void deque<T>::erase_back(const typename deque<T>::const_iterator &_First, const typename deque<T>::const_iterator &_Last)
	{
		int first_offset = _First - cbegin();
		const iterator orig_end = end();
		// ƽ��
		iterator iter1 = begin() + first_offset;
		const_iterator iter2 = _Last;
		while(iter2 != orig_end)
		{
			*iter1 = *iter2;
			++iter1;
			++iter2;
		}
		iterator new_end_iter = iter1;	// Ԥ��¼
		while(iter1 != orig_end)
		{
			(*iter1).~T();
			++iter1;
		}
		// ɾ������Ŀ���bin
		// new_end_iter���ڵ�binҲ��Ҫ��ɾ������������֣���һ����erase��dequeΪ�յ��������һ����new_end_iter�������ڵ�binû��Ԫ�أ�
		if(new_end_iter == cbegin())
		{
			for(typename vector<T*>::iterator map_iter = map_.begin();
				map_iter != map_.end();	++map_iter)
			{
				operator delete[](*map_iter);
			}
			map_.clear();
			back_bin_index_ = SEGMENT_LENGTH - 1;
			front_bin_index_ = 0;
		}
		else 
		{
			if(0 == new_end_iter.item_index_)	
			{
				for(typename vector<T*>::iterator map_iter = new_end_iter.map_iter_;
				map_iter != map_.end();	++map_iter)
				{
					operator delete[](*map_iter);
				}
				map_.erase(new_end_iter.map_iter_, map_.cend());
			}
			else	// new_end_iter���ڵ�bin����Ԫ��
			{
				for(typename vector<T*>::iterator map_iter = new_end_iter.map_iter_ + 1;
				map_iter != map_.end();	++map_iter)
				{
					operator delete[](*map_iter);
				}
				map_.erase(new_end_iter.map_iter_ + 1, map_.cend());
			}
			back_bin_index_ = (new_end_iter.item_index_ + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
		}
	}

	template<class T>
	void deque<T>::assign_n(size_t count, const T &val)
	{
		clear();
		insert_n(cbegin(), count, val);
	}

} // namespace 

#endif