#ifndef XF_DEQUE_HPP
#define XF_DEQUE_HPP
#include "vector.hpp"
#include "_Deque_Common.hpp"
#include "_Deque_Iterator.hpp"
#include "_Reverse_Iterator.hpp"
#include "common_algorithm.hpp"
#include <memory>
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
		template<> deque(int n, int _Value) : front_bin_index_(0), back_bin_index_((n + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH), map_()
		{
			size_t full_bins = n / SEGMENT_LENGTH;
			size_t remain_num = n % SEGMENT_LENGTH;
			map_.reserve(full_bins + sgn(remain_num));
			for(size_t i = 0; i < full_bins; ++i)
			{
				T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
				std::uninitialized_fill(p, p + SEGMENT_LENGTH, _Value);
				map_.push_back(p);
			}
			if(remain_num > 0)
			{
				T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
				std::uninitialized_fill(p, p + remain_num, _Value);
				map_.push_back(p);
			}
		}
		virtual ~deque();

		size_t size() const;
		bool empty() const;
		size_t max_size() const;

		void resize(size_t new_size, T new_value = T());

		iterator insert(const const_iterator &_Where, const T &_Value);
		iterator insert(const const_iterator &_Where, size_t _Count, const T &_Value);
		template<class Iter>
		iterator insert(const const_iterator &_Where, Iter _First, Iter _Last);
		template<> iterator insert<int>(const const_iterator &_Where, int _Count, int _Value)
		{
			return insert_n(_Where, _Count, _Value);
		}

		iterator erase(const const_iterator &_First, const const_iterator &_Last);
		iterator erase(const const_iterator &_Where);


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

		const T& at(size_t index) const;
		T& at(size_t index);

		const T& operator [](size_t index) const;
		T& operator [](size_t index);

		deque<T>& operator = (const deque<T> & _Right);
		
	private:
		static size_t SEGMENT_LENGTH;
		size_t front_bin_index_;
		size_t back_bin_index_;
		iterator insert_n(const const_iterator _Where, size_t _Count, const T &_Value);

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
		// 当len=1时，即front_bin_index_和back_bin_index_表示的是同一个bin的时候，要特殊处理，判断到底哪个有意义
		if(1 == right_map_size)
		{
			map_[0] = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
			if(0 != front_bin_index_)	// front_bin_index_不是默认值，说明第一个bin确实是front有效的bin
			{
				for(size_t j = front_bin_index_; j < SEGMENT_LENGTH; ++j)
				{
					new(map_.front() + j) T(_Right.map_.front()[j]);
				}
			}
			else	// back_bin_index_不是默认值，或者，back_bin_index_是默认值，但此时也可将其视作是back_bin_index_有效的bin
			{
				for(size_t j = 0; j <= back_bin_index_; ++j)
				{
					new(map_.back() + j) T(_Right.map_.back()[j]);
				}
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
			std::uninitialized_fill(p, p + SEGMENT_LENGTH, _Value);
			map_.push_back(p);
		}
		if(remain_num > 0)
		{
			T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
			std::uninitialized_fill(p, p + remain_num, _Value);
			map_.push_back(p);
		}
	}

	template<class T>
	template<class _Iter>
	deque<T>::deque(_Iter begin, _Iter end) : front_bin_index_(0), back_bin_index_(SEGMENT_LENGTH - 1), map_()
	{
		for(_Iter i = begin; i != end; ++i)
		{
			push_back(*i);
		}
	}

	template<class T>
	deque<T>::~deque()
	{
		size_t len = map_.size();
		// 当len=1时，即front_bin_index_和back_bin_index_表示的是同一个bin的时候，要特殊处理，判断到底哪个有意义
		if(1 == len)
		{
			if(0 != front_bin_index_)	// front_bin_index_不是默认值，说明第一个bin确实是front有效的bin
			{
				for(size_t j = front_bin_index_; j < SEGMENT_LENGTH; ++j)
				{
					(map_.front() + j)->~T();
				}
			}
			else	// back_bin_index_不是默认值，或者，back_bin_index_是默认值，但此时也可将其视作是back_bin_index_有效的bin
			{
				for(size_t j = 0; j <= back_bin_index_; ++j)
				{
					(map_.back() + j)->~T();
				}
				operator delete[](map_.back());
			}
		}
		else	// len!=1时的情况，正常处理[这里虽然可以优化掉上一条if语句中嵌套的if的一个分支，但为了代码可读性，不进行优化]
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
		return ((map_.size() - 2) * SEGMENT_LENGTH + (SEGMENT_LENGTH - front_bin_index_) + back_bin_index_ + 1);
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
	typename deque<T>::iterator deque<T>::insert(const const_iterator &_Where, const T &_Value)
	{
	
	}

	template<class T>
	typename deque<T>::iterator deque<T>::insert(const const_iterator &_Where, size_t _Count, const T &_Value)
	{
		return insert_n(_Where, _Count, _Value);
	}

	template<class T>template<class Iter>
	typename deque<T>::iterator deque<T>::insert(const const_iterator &_Where, Iter _First, Iter _Last)
	{
		
	}

	template<class T>
	typename deque<T>::iterator deque<T>::erase(const const_iterator &_First, const const_iterator &_Last)
	{
		// TODO _First == _Last的处理
		if(_First == _Last)
		{
			return begin() + (_First - cbegin());
		}
		const_iterator end_iter = cend();
		// 平移
		iterator iter1 = begin() + (_First - cbegin());
		const_iterator iter2 = _Last;
		while(iter2 != end_iter)
		{
			*iter1 = *iter2;
			++iter1;
			++iter2;
		}
		// 更新deque参数
		back_bin_index_ = (iter1.item_index_ + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
		// 销毁后面的对象
		vector<T*>::const_iterator last_map_iter = iter1.map_iter_ + 1;
		while(end_iter != iter1)
		{
			(*iter1).~T();
			//iter1->~T();	// TODO 不知道为什么这样写不被允许
			++iter1;
		}
		// 删除后面的空闲bin
		map_.erase(last_map_iter, map_.cend());
		return begin() + (_First - cbegin());
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
		return const_iterator(vector<const T*>::const_iterator(map_.cbegin().p_), front_bin_index_);
		// 上句为简写，隐去了类型转换，实际的类型转换见下句
		//return const_iterator(vector<const T*>::const_iterator(const_cast<T const * const *>(map_.cbegin().p_)), front_bin_index_);
		// 下句当_Deque_Const_Iterator中的构造函数改为vector<T*>时才有效，但那样改过后会有隐患，在编译层面上无法约束T对象不被更改
		//return const_iterator(map_.cbegin(), front_bin_index_);
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
			return const_iterator(vector<const T*>::const_iterator(map_.begin().p_), 0);
		}
		else
		{
			return ++const_iterator(vector<const T*>::const_iterator(map_.cend().p_) - 1, back_bin_index_);
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
	typename deque<T>::const_reverse_iterator deque<T>::crbegin() const throw()
	{
		return const_reverse_iterator(cend());
	}
	template<class T>
	typename deque<T>::const_reverse_iterator deque<T>::rbegin() const throw()
	{
		return crbegin();
	}
	template<class T>
	typename deque<T>::reverse_iterator deque<T>::rbegin() throw()
	{
		return reverse_iterator(end());
	}

	template<class T>
	typename deque<T>::const_reverse_iterator deque<T>::crend() const throw()
	{
		return const_reverse_iterator(cbegin());
	}
	template<class T>
	typename deque<T>::const_reverse_iterator deque<T>::rend() const throw()
	{
		return crend();
	}
	template<class T>
	typename deque<T>::reverse_iterator deque<T>::rend() throw()
	{
		return reverse_iterator(begin());
	}

	template<class T>
	const T& deque<T>::at(size_t index) const
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
	T& deque<T>::at(size_t index)
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
	typename deque<T>::iterator deque<T>::insert_n(const const_iterator _Where, size_t _Count, const T &_Value)	// 注意，先实现通用的insert_n，再考虑原deque为空的情况
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
				std::uninitialized_fill(p, p + SEGMENT_LENGTH, _Value);
				map_.push_back(p);
			}
			if(remain_num > 0)
			{
				T* p = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
				std::uninitialized_fill(p, p + remain_num, _Value);
				map_.push_back(p);
			}
			return begin();
		}
		else
		{
			// 0. 预记录的值
			size_t orig_size = size();
			size_t insert_index = _Where - cbegin();
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
			// 预记录
			iterator orig_end_iter(begin() + orig_size);
			// IMP 更改deque的索引参数
			back_bin_index_ = (remain_num + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
			// 2. 把从_Where到end()的区间(长度为last_length)向后移动_Count个，从后往前依次复制
			size_t last_length = orig_size - insert_index;
			// 2a. 若last_length <= _Count
			if(last_length <= _Count)
			// 2a.1 通过placement new，使用拷贝构造函数将deque的[_Where, end)复制到[new_end - last_length, new_end)，复制数量为last_length，顺序/倒序皆可，这里用倒序
			// 2a.2 用重载=为[_Where, end)个元素赋新值，赋值数量为last_length
			// 2a.3 通过placement new，使用拷贝构造函数对[end, _Count - last_length)初始化为新值
			{
				iterator src_iter = orig_end_iter - 1;
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
				src_iter = orig_end_iter;
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
				iterator src_iter = orig_end_iter - 1;
				iterator dst_iter = iterator(map_.end() - 1, back_bin_index_);
				for(size_t i = 0; i < _Count; ++i)
				{
					new(&*dst_iter) T(*src_iter);
					--src_iter;
					--dst_iter;
				}
				// 2b.2
				src_iter = orig_end_iter - _Count;
				dst_iter = orig_end_iter;
				while((const_iterator)src_iter >= _Where)
				{
					*dst_iter = *src_iter;
					--src_iter;
					--dst_iter;
				}
				// 2b.3
				src_iter = begin() + (_Where - cbegin());
				while(src_iter <= dst_iter)
				{
					new(&*src_iter) T(_Value);
					++src_iter;
				}
			} // if
			return orig_end_iter;
		} // function
	} // class
} // namespace 

#endif