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

		iterator erase(const const_iterator &_First, const const_iterator &_Last);
		iterator erase(const const_iterator &_Where);

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
		static size_t SEGMENT_LENGTH;
		size_t front_bin_index_;
		size_t back_bin_index_;
		iterator insert_n(const const_iterator _Where, size_t _Count, const T &_Value);
		void assign_n(size_t count, const T &val);

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
		// ��len=1ʱ����front_bin_index_��back_bin_index_��ʾ����ͬһ��bin��ʱ��Ҫ���⴦���жϵ����ĸ�������
		if(1 == right_map_size)
		{
			map_[0] = reinterpret_cast<T*>(operator new(SEGMENT_LENGTH * sizeof(T)));
			if(0 != front_bin_index_)	// front_bin_index_����Ĭ��ֵ��˵����һ��binȷʵ��front��Ч��bin
			{
				for(size_t j = front_bin_index_; j < SEGMENT_LENGTH; ++j)
				{
					new(map_.front() + j) T(_Right.map_.front()[j]);
				}
			}
			else	// back_bin_index_����Ĭ��ֵ�����ߣ�back_bin_index_��Ĭ��ֵ������ʱҲ�ɽ���������back_bin_index_��Ч��bin
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
		// ��len=1ʱ����front_bin_index_��back_bin_index_��ʾ����ͬһ��bin��ʱ��Ҫ���⴦���жϵ����ĸ�������
		if(1 == len)
		{
			if(0 != front_bin_index_)	// front_bin_index_����Ĭ��ֵ��˵����һ��binȷʵ��front��Ч��bin
			{
				for(size_t j = front_bin_index_; j < SEGMENT_LENGTH; ++j)
				{
					(map_.front() + j)->~T();
				}
			}
			else	// back_bin_index_����Ĭ��ֵ�����ߣ�back_bin_index_��Ĭ��ֵ������ʱҲ�ɽ���������back_bin_index_��Ч��bin
			{
				for(size_t j = 0; j <= back_bin_index_; ++j)
				{
					(map_.back() + j)->~T();
				}
				operator delete[](map_.back());
			}
		}
		else	// len!=1ʱ���������������[������Ȼ�����Ż�����һ��if�����Ƕ�׵�if��һ����֧����Ϊ�˴���ɶ��ԣ��������Ż�]
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
		else	// ���ڣ����Ա�֤��insert��Ԫ�أ�һ���ڷǿյ�deque���м䲿λ
		{
			// 1. �����µĿռ䣨����б�Ҫ����Ȼ���insertǰ�����һ��Ԫ�أ������һ����Ԫ
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
			// 2. ��[_Where, end - 2)��Ԫ��ȫ������ƶ�һλ
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
		return begin() + where_offset;
	}

	template<class T>
	typename deque<T>::iterator deque<T>::insert(const const_iterator &_Where, size_t _Count, const T &_Value)
	{
		return insert_n(_Where, _Count, _Value);
	}

	template<class T>template<class _Iter >
	typename deque<T>::iterator deque<T>::insert(const const_iterator &_Where, _Iter _First, _Iter  _Last)
	{
		assert(_First <= _Last);
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
			size_t orig_size = size();
			size_t where_offset = _Where - cbegin();
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
			// Ԥ��¼
			iterator orig_end_iter(begin() + orig_size);
			// IMP ����deque����������
			back_bin_index_ = (remain_num + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
			// 2. �Ѵ�_Where��end()������(����Ϊlast_length)����ƶ�_Count�����Ӻ���ǰ���θ���
			size_t last_length = orig_size - where_offset;
			// 2a. ��last_length <= _Count
			if(last_length <= _Count)
			// 2a.1 ͨ��placement new��ʹ�ÿ������캯����deque��[_Where, end)���Ƶ�[new_end - last_length, new_end)����������Ϊlast_length��˳��/����Կɣ������õ���
			// 2a.2 ������=Ϊ[_Where, end)��Ԫ�ظ���ֵ����ֵ����Ϊlast_length
			// 2a.3 ͨ��placement new��ʹ�ÿ������캯����[end, _Count - last_length)��ʼ��Ϊ��ֵ
			{
				iterator src_iter = orig_end_iter - 1;
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
				src_iter = orig_end_iter;
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
			// 2b.2 ������=����[_Where, end - _Count)���Ƶ�[_Where + _Count, end)����������Ϊlast_length - _Count��������
			// 2b.3 ͨ������=����[_Where, _Where + _Count)��Ԫ�ظ�����ֵ����ֵ����Ϊ_Count
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
				src_iter = begin() + (where_offset);
				while(src_iter <= dst_iter)
				{
					new(&*src_iter) T(*_First);
					++_First;
					++src_iter;
				}
			} // if
			return orig_end_iter;
		}
	}

	template<class T>
	typename deque<T>::iterator deque<T>::erase(const const_iterator &_First, const const_iterator &_Last)
	{
		int first_offset = _First - cbegin();
		// _First == _Last�Ĵ���
		if(_First == _Last)
		{
			return begin() + first_offset;
		}
		const_iterator orig_end_iter = cend();
		// ƽ��
		iterator iter1 = begin() + first_offset;
		const_iterator iter2 = _Last;
		while(iter2 != orig_end_iter)
		{
			*iter1 = *iter2;
			++iter1;
			++iter2;
		}
		iterator new_end_iter = iter1;
		while(orig_end_iter != iter1)
		{
			(*iter1).~T();
			//iter1->~T();	// TODO ��֪��Ϊʲô����д��������
			++iter1;
		}
		// ɾ������Ŀ���bin
		if(0 == new_end_iter.item_index_)	// new_end_iter���ڵ�binҲ��Ҫ��ɾ�������
		{
			map_.erase(new_end_iter.map_iter_, map_.cend());
		}
		else
		{
			map_.erase(new_end_iter.map_iter_ + 1, map_.cend());
		}
		// ����deque����
		back_bin_index_ = (new_end_iter.item_index_ + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
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
	typename deque<T>::iterator deque<T>::insert_n(const const_iterator _Where, size_t _Count, const T &_Value)	// ע�⣬��ʵ��ͨ�õ�insert_n���ٿ���ԭdequeΪ�յ����
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
			// Ԥ��¼
			iterator orig_end_iter(begin() + orig_size);
			// IMP ����deque����������
			back_bin_index_ = (remain_num + SEGMENT_LENGTH - 1) % SEGMENT_LENGTH;
			// 2. �Ѵ�_Where��end()������(����Ϊlast_length)����ƶ�_Count�����Ӻ���ǰ���θ���
			size_t last_length = orig_size - where_offset;
			// 2a. ��last_length <= _Count
			if(last_length <= _Count)
			// 2a.1 ͨ��placement new��ʹ�ÿ������캯����deque��[_Where, end)���Ƶ�[new_end - last_length, new_end)����������Ϊlast_length��˳��/����Կɣ������õ���
			// 2a.2 ������=Ϊ[_Where, end)��Ԫ�ظ���ֵ����ֵ����Ϊlast_length
			// 2a.3 ͨ��placement new��ʹ�ÿ������캯����[end, _Count - last_length)��ʼ��Ϊ��ֵ
			{
				iterator src_iter = orig_end_iter - 1;
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
				src_iter = orig_end_iter;
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
				src_iter = begin() + (where_offset);
				while(src_iter <= dst_iter)
				{
					new(&*src_iter) T(_Value);
					++src_iter;
				}
			} // if
			return orig_end_iter;
		} // if
	} // function

	template<class T>
	void deque<T>::assign_n(size_t count, const T &val)
	{
		clear();
		insert_n(cbegin(), count, val);
	}

} // namespace 

#endif