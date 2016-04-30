#ifndef XF_DEQUE_HPP
#define XF_DEQUE_HPP
#include "vector.hpp"
#include "_Deque_Const_Iterator.hpp"
#include "_Deque_Iterator.hpp"
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

		typedef _Deque_Iterator<T> iterator;
		typedef _Deque_Const_Iterator<T> const_iterator;
		typedef _Reverse_Iterator<iterator> reverse_iterator;
		typedef _Reverse_Iterator<const_iterator> const_reverse_iterator;

		deque();
		deque(const deque<T> & _Right);
		deque(size_t n);
		deque(size_t n, const T & _Value);
		template<class _Iter>
		deque(_Iter begin, _Iter end);
		template<>
		deque(int n, int _Value)
		{
		
		}
		virtual ~deque();

		size_t size() const;
		bool empty() const;
		size_t max_size() const;

		void resize(size_t size);

		void insert(const const_iterator &_Where, const T &_Value);
		iterator insert(const const_iterator &_Where, size_t _Count, const T &_Value);
		template<class Iter>
		iterator insert(const const_iterator &_Where, Iter _First, Iter _Last);
		template<> iterator insert<int>(const const_iterator &_Where, int _Count, int _Value)
		{
			return insert_n(_Where, _Count, _Value);
		}


		const T& front(const T &_Val) const;
		T& front(const T &_Val);
		const T& back(const T &_Val) const;
		T& back(const T &_Val);

		void push_front(const T &_Val);
		void push_back(const T &_Val);

		void pop_front(const T &_Val);
		void pop_back(const T &_Val);



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
	size_t deque<T>::SEGMENT_LENGTH = 64;

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
	deque<T>::deque(size_t n) : front_bin_index_(0), back_bin_index_(n % SEGMENT_LENGTH), map_()
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
	deque<T>::deque(size_t n, const T & _Value) : front_bin_index_(0), back_bin_index_(n % SEGMENT_LENGTH), map_()
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
	T& deque<T>::operator [](size_t index)
	{
		// 先计算deque中第index个元素相对于map_第一个bin中首元素的偏移量
		size_t full_index = index + front_bin_index_;
		// 然后类似二维数组那样，返回值
		return map_[full_index / SEGMENT_LENGTH][full_index % SEGMENT_LENGTH];
	}

}

#endif