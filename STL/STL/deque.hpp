#ifndef XF_DEQUE_HPP
#define XF_DEQUE_HPP
#include "vector.hpp"
#include "_Deque_Common.hpp"
#include "_Deque_Iterator.hpp"
#include "_Reverse_Iterator.hpp"
#include "common_algorithm.hpp"
#include "memory.hpp"

namespace xf
{

	// map_是存储多个内存块的地址表
	// 第一个内存块的有效地址为[front_bin_index_, SEGMENT_LENGTH - 1]
	// 最后一个内存块的有效地址为[0, back_bin_index_]
	// 当map_有超过一个内存块时，front_bin_index_和back_bin_index_均有效
	// 当map_只有一个内存块时，back_bin_index_和front_bin_index_不一定哪个是有效的
	// 但当其无效时，能保证各种计算的通用性

	// 对deque的map_两端的索引定义如下：
	// front_bin_index_表示deque_第一个元素所在的map_的bin中的索引，当其有效时，该索引对应的恰好是第一个元素的位置。无效时，默认值见下。
	// back_bin_index_表示deque_最后一个元素所在的map_的bin中的索引，当其有效时，该索引对应的恰好是最后一个元素的位置。无效时，默认值见下。
	// front_bin_index_ = 0
	// back_bin_index_ = SEGMENT_LENGTH - 1
	// 默认值的设置，主要考虑了size()函数计算的通用性

	template<class T>
	class deque
	{
	public:

		typedef typename _Deque_Iterator<T> iterator;
		typedef typename _Deque_Const_Iterator<T> const_iterator;
		typedef typename _Reverse_Iterator<iterator> reverse_iterator;
		typedef typename _Reverse_Iterator<const_iterator> const_reverse_iterator;

		deque();
		deque(const deque<T> & _Right);
		deque(size_t n);
		deque(size_t n, const T & _Value);
		template<class _Iter> deque(_Iter begin, _Iter end);
		template<> deque(int _Count, int _Value) : front_bin_index_(0), back_bin_index_(SEGMENT_LENGTH - 1), map_()
		{
			insert_n(begin(), _Count, _Value);
		}
		virtual ~deque();

		size_t size() const;
		bool empty() const;
		size_t max_size() const;

		void resize(size_t new_size, T new_value = T());
		void clear();

		iterator insert(const const_iterator &_Where, const T &_Value);
		iterator insert(const const_iterator &_Where, size_t _Count, const T &_Value);
		template<class _Iter>
		iterator insert(const const_iterator &_Where, _Iter _First, _Iter _Last);
		template<> iterator insert<int>(const const_iterator &_Where, int _Count, int _Value)
		{
			return insert_n(_Where, _Count, _Value);
		}

		iterator erase(const const_iterator &_Where);
		iterator erase(const const_iterator &_First, const const_iterator &_Last);

		void assign(size_t count, const T &val);
		template<class _Iter>
		void assign(_Iter _First, _Iter _Last);
		template<> void assign<int>(int _Count, int _Value)
		{
			return assign_n(_Count, _Value);
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
		// 当len=1时，front_bin_index_和back_bin_index_都有效，要同时考虑
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
				if(0 == i)	// 首个bin
				{
					for(size_t j = front_bin_index_; j < SEGMENT_LENGTH; ++j)
					{
						new(map_.front() + j) T(_Right.map_.front()[j]);
					}
				}
				else if(i == right_map_size - 1)	// 末个bin
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
	template<class _Iter>
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
		// 当len=1时，即front_bin_index_和back_bin_index_表示的是同一个bin的时候，要特殊处理，判断到底哪个有意义
		if(1 == len)
		{
			for(size_t j = front_bin_index_; j <= back_bin_index_; ++j)
			{
				(map_.front() + j)->~T();
			}
			operator delete[](map_.front());
		}
		else	// len!=1时的情况，正常处理
		{
			for(size_t i = 0; i < len; ++i)
			{
				if(0 == i)	// 首个bin
				{
					for(size_t j = front_bin_index_; j < SEGMENT_LENGTH; ++j)
					{
						(map_.front() + j)->~T();
					}
					operator delete[](map_.front());
				}
				else if(i == len - 1)	// 末个bin
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
			insert(end(), insert_count, new_value);
		}
		else if(erase_count > 0)
		{
			erase(end() - erase_count, end());
		}
	}

	template<class T>
	void deque<T>::clear()
	{
		resize(0);
	}

	template<class T>
	typename deque<T>::iterator deque<T>::insert(const const_iterator &_Where, const T &_Value)
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
		else	// 现在，可以保证，insert的元素，一定在非空的deque的中间部位
		{
			// 插入时，判断移动前半段元素还是移动后半段元素
			if(where_offset * 2 < size())	
			{
				insert_front(where_offset, _Value);	// 位置靠前，就移动前半段
			}
			else
			{
				insert_back(where_offset, _Value);	// 否则，移动后半段
			}
			
		}
		return begin() + where_offset;
	}

	template<class T>
	typename deque<T>::iterator deque<T>::insert(const const_iterator &_Where, size_t _Count, const T &_Value)
	{
		return insert_n(_Where, _Count, _Value);
	}

	template<class T>template<class _Iter >
	typename deque<T>::iterator deque<T>::insert(const const_iterator &_Where, _Iter _First, _Iter _Last)
	{
		size_t _Count = xf::distance(_First, _Last);
		// 以下部分改编自insert_n
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
			// 0. 预记录的值
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
	typename deque<T>::iterator deque<T>::erase(const const_iterator &_Where)
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
	typename deque<T>::iterator deque<T>::erase(const const_iterator &_First, const const_iterator &_Last)
	{
		int first_offset = _First - cbegin();
		// _First == _Last的处理
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
		clear();
		insert_n(begin(), count, val);
	}
	template<class T>template<class _Iter>
	void deque<T>::assign(_Iter _First, _Iter _Last)
	{
		clear();
		insert(begin(), _First, _Last);
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
		map_.front()[front_bin_index_].~T();	// 销毁该元素
		++front_bin_index_;						// 更新首块指针
		if(SEGMENT_LENGTH == front_bin_index_)	// 判断是否首个bin已空
		{
			operator delete[] (map_.front());
			map_.erase(map_.begin());
			front_bin_index_ = 0;
		}
	}

	template<class T>
	void deque<T>::pop_back()
	{
		map_.back()[back_bin_index_].~T();	// 销毁该元素
		if(0 == back_bin_index_)			// 判断是否末个bin已空
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
			// 先计算deque中第index个元素相对于map_第一个bin中首元素的偏移量
			size_t offset = index + front_bin_index_;
			// 然后类似二维数组那样，返回值
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
			// 先计算deque中第index个元素相对于map_第一个bin中首元素的偏移量
			size_t offset = index + front_bin_index_;
			// 然后类似二维数组那样，返回值
			return map_[offset / SEGMENT_LENGTH][offset % SEGMENT_LENGTH];
		}
	}

	template<class T>
	const T& deque<T>::operator [](size_t index) const
	{
		// 先计算deque中第index个元素相对于map_第一个bin中首元素的偏移量
		size_t offset = index + front_bin_index_;
		// 然后类似二维数组那样，返回值
		return map_[offset / SEGMENT_LENGTH][offset % SEGMENT_LENGTH];
	}

	template<class T>
	T& deque<T>::operator [](size_t index)
	{
		// 先计算deque中第index个元素相对于map_第一个bin中首元素的偏移量
		size_t offset = index + front_bin_index_;
		// 然后类似二维数组那样，返回值
		return map_[offset / SEGMENT_LENGTH][offset % SEGMENT_LENGTH];
	}

	template<class T>
	void deque<T>::insert_back(const size_t where_offset, const T &_Value)
	{
		// 1. 申请新的空间（如果有必要），然后把insert之前的最后一个元素，向后复制一个单元
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
		// 2. 将[_Where, end - 2]的元素全部向后移动一位
		iterator copy_iter = end() - 2;	// 现在copy_iter指向insert之前的最后一个元素
		iterator prev_iter = copy_iter;
		iterator insert_position = begin() + where_offset;
		while(copy_iter != insert_position)
		{
			--prev_iter;
			*copy_iter = *prev_iter;
			copy_iter = prev_iter;
		}
		// 3. 为新的元素赋值
		*insert_position = _Value;
	}

	template<class T>
	void deque<T>::insert_front(const size_t where_offset, const T &_Value)
	{
		// 1. 申请新的空间（如果有必要），然后把insert之前的最后一个元素，向后复制一个单元
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
		// 2. 将[begin, _Where)的元素全部向前移动一位
		iterator copy_iter = begin();
		iterator next_iter = copy_iter;
		iterator insert_position = begin() + where_offset;
		while(copy_iter != insert_position)
		{
			++next_iter;
			*copy_iter = *next_iter;
			copy_iter = next_iter;
		}
		// 3. 为新的元素赋值
		*insert_position = _Value;
	}

	template<class T>
	typename deque<T>::iterator deque<T>::insert_n(const const_iterator _Where, size_t _Count, const T &_Value)
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
			// 0. 预记录的值
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
		// 1. 先判断要申请的额外长度，申请后，在deque的最后，应该至少有_Count个未初始化的内存空间
		int new_count = _Count - (SEGMENT_LENGTH - 1 - back_bin_index_);
		size_t remain_num = 0;	// 计算插入后最后一个bin中应该剩余的元素数量
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
		// IMP 更改deque的索引参数
		back_bin_index_ = (remain_num + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
		// 预记录
		const iterator orig_end(begin() + orig_size);
		// 2. 移动原有元素，并在空出的位置赋予新值
		size_t last_length = orig_size - where_offset;
		// 2a. 若last_length <= _Count
		if(last_length <= _Count)
		// 2a.1 通过placement new，使用拷贝构造函数将deque的[_Where, orig_end)复制到[new_end - last_length, new_end)，复制数量为last_length，顺序/倒序皆可，这里用倒序
		// 2a.2 用重载=为[_Where, end)个元素赋新值，赋值数量为last_length
		// 2a.3 通过placement new，使用拷贝构造函数对[orig_end, orig_end + _Count - last_length)初始化为新值
		{
			iterator src_iter = orig_end - 1;
			iterator dst_iter = iterator(map_.end() - 1, back_bin_index_);
			for(size_t i = 0; i < last_length; ++i)
			//while(src_iter != _Where)	// 不能这么用，因为_Where指向的元素也应该被复制
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

		// 2b. 若last_length > _Count
		else
		// 2b.1 通过placement new使用拷贝构造函数，将[end - _Count, end)复制到[new_end - _Count, new_end)，复制数量为_Count，倒序、正序皆可，这里用倒序
		// 2b.2 用重载=，将[_Where, end - _Count)复制到[_Where + _Count, end)，复制数量为last_length - _Count，倒序复制
		// 2b.3 通过重载=，对[_Where, _Where + _Count)的元素赋予新值，赋值数量为_Count
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
		// 1. 先判断要申请的额外长度，申请后，在deque的最前面，应该至少有_Count个未初始化的内存空间
		int new_count = _Count - front_bin_index_;
		size_t remain_num = 0;	// 计算插入后第一个bin中应该剩余的元素数量
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
		// IMP 更改deque的索引参数
		front_bin_index_ = (SEGMENT_LENGTH - remain_num) % SEGMENT_LENGTH;
		// 预记录
		const iterator orig_begin(begin() + _Count);
		// 2. 移动原有元素，并在空出的位置赋予新值
		// 2a. 若where_offset <= _Count
		if(where_offset <= _Count)
		// 2a.1 通过placement new，使用拷贝构造函数将deque的[orig_begin, orig_begin + where_offset)复制到[new_begin, new_begin + where_offset)，复制数量为where_offset，顺序/倒序皆可，这里用正序
		// 2a.2 通过重载=，对[orig_begin, orig_begin + where_offset)赋新值
		// 2a.3 通过placement new，使用拷贝构造函数对[new_begin + where_offset, orig_begin)的元素赋新值，赋值数量为_Count - where_offset
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
		// 2b. 若where_offset > _Count
		else
		// 2b.1 通过placement new使用拷贝构造函数，将[orig_begin, orig_begin + _Count)复制到[new_begin, orig_begin)，复制数量为_Count，倒序、正序皆可，这里用正序
		// 2b.2 用重载=，将[orig_begin + _Count, orig_begin + where_offset)复制到[orig_begin, new_begin + where_offset)，复制数量为where_offset - _Count，正序复制
		// 2b.3 通过重载=，对[new_begin + where_offset, orig_begin + where_offset)的元素赋予新值，赋值数量为_Count
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
		// 1. 先判断要申请的额外长度，申请后，在deque的最后，应该至少有_Count个未初始化的内存空间
		int new_count = _Count - (SEGMENT_LENGTH - 1 - back_bin_index_);
		size_t remain_num = 0;	// 计算插入后最后一个bin中应该剩余的元素数量
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
		// IMP 更改deque的索引参数
		back_bin_index_ = (remain_num + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
		// 预记录
		const iterator orig_end(begin() + orig_size);
		// 2. 把从_Where到end()的区间(长度为last_length)向后移动_Count个，从后往前依次复制
		const size_t last_length = orig_size - where_offset;
		// 2a. 若last_length <= _Count
		if(last_length <= _Count)
		// 2a.1 通过placement new，使用拷贝构造函数将deque的[_Where, orig_end)复制到[new_end - last_length, new_end)，复制数量为last_length，顺序/倒序皆可，这里用倒序
		// 2a.2 用重载=为[_Where, end)个元素赋新值，赋值数量为last_length
		// 2a.3 通过placement new，使用拷贝构造函数对[orig_end, _Count - last_length)初始化为新值
		{
			iterator src_iter = orig_end - 1;
			iterator dst_iter = iterator(map_.end() - 1, back_bin_index_);
			for(size_t i = 0; i < last_length; ++i)
			//while(src_iter != _Where)	// 不能这么用，因为_Where指向的元素也应该被复制
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

		// 2b. 若last_length > _Count
		else
		// 2b.1 通过placement new使用拷贝构造函数，将[end - _Count, end)复制到[new_end - _Count, new_end)，复制数量为_Count，倒序、正序皆可，这里用倒序
		// 2b.2 用重载=，将[_Where, orig_end - _Count)复制到[_Where + _Count, end)，复制数量为last_length - _Count，倒序复制
		// 2b.3 通过重载=，对[_Where, _Where + _Count)的元素赋予新值，赋值数量为_Count
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
		// 1. 先判断要申请的额外长度，申请后，在deque的最前面，应该至少有_Count个未初始化的内存空间
		size_t _Count = distance(_First, _Last);
		int new_count = _Count - front_bin_index_;
		size_t remain_num = 0;	// 计算插入后第一个bin中应该剩余的元素数量
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
		// IMP 更改deque的索引参数
		front_bin_index_ = (SEGMENT_LENGTH - remain_num) % SEGMENT_LENGTH;
		// 预记录
		const iterator orig_begin(begin() + _Count);
		// 2. 移动原有元素，并在空出的位置赋予新值
		// 2a. 若where_offset <= _Count
		if(where_offset <= _Count)
		// 2a.1 通过placement new，使用拷贝构造函数将deque的[orig_begin, orig_begin + where_offset)复制到[new_begin, new_begin + where_offset)，复制数量为where_offset，顺序/倒序皆可，这里用正序
		// 2a.2 通过placement new，使用拷贝构造函数对[new_begin + where_offset, orig_begin)的元素赋新值，赋值数量为_Count - where_offset
		// 2a.3 通过重载=，对[orig_begin, orig_begin + where_offset)赋新值
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
		// 2b. 若where_offset > _Count
		else
		// 2b.1 通过placement new使用拷贝构造函数，将[orig_begin, orig_begin + _Count)复制到[new_begin, orig_begin)，复制数量为_Count，倒序、正序皆可，这里用正序
		// 2b.2 用重载=，将[orig_begin + _Count, orig_begin + where_offset)复制到[orig_begin, new_begin + where_offset)，复制数量为where_offset - _Count，正序复制
		// 2b.3 通过重载=，对[new_begin + where_offset, orig_begin + where_offset)的元素赋予新值，赋值数量为_Count
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
		// 平移
		iterator iter = begin() + where_offset;
		iterator prev_iter = iter;
		for(size_t i = 0; i < where_offset; ++i)
		{
			--prev_iter;
			*iter = *prev_iter;
			iter = prev_iter;
		}
		// 销毁第一个元素
		(*iter).~T();
		// 更新成员变量，并视情况销毁第一个bin
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
		// 平移
		iterator iter = begin() + where_offset;
		iterator next_iter = iter;
		size_t move_length = size() - where_offset - 1;
		for(size_t i = 0; i < move_length; ++i)
		{
			++next_iter;
			*iter = *next_iter;
			iter = next_iter;
		}
		// 销毁最后一个元素
		(*iter).~T();
		// 更新成员变量，并视情况销毁最后一个bin
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
	void deque<T>::erase_front(const const_iterator &_First, const const_iterator &_Last)
	{
		size_t first_offset = _First - cbegin();
		size_t last_offset = _Last - cbegin();
		size_t erase_count = last_offset - first_offset;
		//const_iterator orig_begin = cbegin();
		// 平移
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
		// 删除前面的空闲bin
		// erase后deque为空的时，要把所有的bin都删掉
		if(new_begin_iter == cend())
		{
			for(vector<T*>::iterator map_iter = map_.begin();
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
			vector<T*>::iterator map_iter = map_.begin();
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
	void deque<T>::erase_back(const const_iterator &_First, const const_iterator &_Last)
	{
		int first_offset = _First - cbegin();
		const iterator orig_end = end();
		// 平移
		iterator iter1 = begin() + first_offset;
		const_iterator iter2 = _Last;
		while(iter2 != orig_end)
		{
			*iter1 = *iter2;
			++iter1;
			++iter2;
		}
		iterator new_end_iter = iter1;	// 预记录
		while(iter1 != orig_end)
		{
			(*iter1).~T();
			++iter1;
		}
		// 删除后面的空闲bin
		// new_end_iter所在的bin也需要被删除的情况（两种：第一种是erase后deque为空的情况，另一种是new_end_iter本身所在的bin没有元素）
		if(new_end_iter == cbegin())
		{
			for(vector<T*>::iterator map_iter = map_.begin();
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
				for(vector<T*>::iterator map_iter = new_end_iter.map_iter_;
				map_iter != map_.end();	++map_iter)
				{
					operator delete[](*map_iter);
				}
				map_.erase(new_end_iter.map_iter_, map_.cend());
			}
			else	// new_end_iter所在的bin还有元素
			{
				for(vector<T*>::iterator map_iter = new_end_iter.map_iter_ + 1;
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