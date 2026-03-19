#ifndef XF_VECTOR_HPP
#define XF_VECTOR_HPP

#ifdef _MSC_VER
#pragma warning(disable:4290)	// for msvc's not fully supporting the exception specifications
#pragma warning(disable:4996)	// for msvc's safety concern about uninitialized_xxxx()
#endif

#include "_Vector_iterator.hpp"
#include "_Reverse_Iterator.hpp"
#include "memory.hpp"
#include <cassert>
#include <stdexcept>
#include <type_traits>
namespace xf
{

	template<class T>
	class vector
	{
	public:

		typedef _Vector_Iterator<T> iterator;
		typedef _Vector_Const_Iterator<T> const_iterator;
		typedef _Reverse_Iterator<iterator> reverse_iterator;
		typedef _Reverse_Iterator<const_iterator> const_reverse_iterator;

		vector();
		vector(const vector<T> &right);
		vector(size_t count);
		vector(size_t count, const T &val);
		template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type = 0> vector(_Iter first, _Iter last);
		vector(int count, const T& val) : p_(NULL), size_(count), capacity_(count)
		{
			p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
			xf::uninitialized_fill(p_, p_ + size_, val);
		}
		virtual ~vector();

		size_t capacity() const;
		size_t size() const;
		bool empty() const;
		void reserve(size_t capacity);
		void resize(size_t size, const T &new_val = T());
		void shrink_to_fit();	// �ͷŶ�����ڴ�

		static size_t max_size();

		void clear();
		void assign(size_t count, const T &val);
		template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type = 0>
		void assign(_Iter first, _Iter last);
		// ���ģ����ػ����������ⶨ�壬��֪��Ϊɶ
		void assign(int _Count, const T& _Value)
		{
			assign_n(_Count, _Value);
		}

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


		// TODO ���ﲻ��ΪʲôSTL�����ʱ��Ҫ����const_iterator������iterator������
		iterator erase(const const_iterator &_First, const const_iterator &_Last);
		iterator erase(const const_iterator &_Where);

		const T& at(size_t index) const throw(std::out_of_range);	// �ҳ���index��Ԫ�أ���Խ����
		T& at(size_t index) throw(std::out_of_range);				// �ҳ���index��Ԫ�أ���Խ����
		
		const T& operator [](size_t index) const;			// �ҳ���index��Ԫ�أ���Խ����
		T& operator [](size_t index);						// �ҳ���index��Ԫ�أ���Խ����

		const T* data() const;
		T* data();

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

		vector<T>& operator = (const vector<T> &right);

	private:
		size_t get_new_capacity() const;
		size_t get_new_capacity(size_t min_request_size) const;
		void assign_n(size_t count, const T &val);
		iterator insert_n(const const_iterator _Where, size_t _Count, const T &_Value);

		T *p_;
		size_t size_;
		size_t capacity_;

	};

	template<class T>
	vector<T>::vector() : p_(NULL), size_(0), capacity_(0) 
	{
	}

	template<class T>
	vector<T>::vector(const vector<T> &right) : p_(static_cast<T*>(operator new[](right.size_ * sizeof(T)))), size_(right.size_), capacity_(right.size_) 
	{
		// ͨ�����캯����p_������right.p_�ĸ���
		xf::uninitialized_copy(right.p_, right.p_ + size_, p_);
	}

	template<class T>
	vector<T>::vector(size_t count) : p_(NULL), size_(count), capacity_(count) 
	{
		p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
		for(size_t i = 0; i < size_; ++i)
		{
			new (p_ + i) T();	// ����������Ĭ�Ϲ��캯��
		}
	}


	template<class T>
	vector<T>::vector(size_t count, const T &val) : p_(NULL), size_(count), capacity_(count) 
	{
		p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
		xf::uninitialized_fill(p_, p_ + size_, val);	// construct elements
	}

	template<class T>template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type>
	vector<T>::vector(_Iter first, _Iter last) : p_(NULL), size_(0U), capacity_(0U)
	{
		size_ = xf::distance(first, last);
		capacity_ = size_;
		p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
		xf::uninitialized_copy(first, last, p_);	// construct elements
	}

	template<class T>
	vector<T>::~vector()
	{
		if(p_)
		{
			for(T *last = p_ + size_; last != p_; )
			{
				(--last)->~T();
			}
			operator delete[](p_);
		}
	}

	template<class T>
	size_t vector<T>::capacity() const
	{
		return capacity_;
	}
	

	template<class T>
	size_t vector<T>::size() const
	{
		return size_;
	}

	template<class T>
	bool vector<T>::empty() const
	{
		return (size_ == 0);
	}

	template<class T>
	void vector<T>::reserve(size_t new_capacity)
	{
		if(new_capacity > capacity_)
		{
			T *buf = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
			if(p_)
			{
				xf::uninitialized_copy(p_, p_ + size_, buf);	// copy elements using copy constructor
				for(T *last = p_ + size_; last != p_; )
				{
					(--last)->~T();
				}
				operator delete[](p_);
			}
			p_ = buf;
			capacity_ = new_capacity;
		}
	}

	template<class T>
	void vector<T>::resize(size_t new_size, const T &new_val)
	{
		// ��С�Ļ���Ҫ�Ѷ����Ԫ�������
		if(new_size < size_)
		{
			for(size_t i = new_size; i < size_; ++i)
			{
				(p_ + i)->~T();
			}
		}
		// �����Ҫ���ݵ����
		else if(new_size > capacity_)
		{
			reserve(new_size);
		}
		// ������������
		// �Ա��ĵط����г�ʼ��
		for(size_t i = size_; i < new_size; ++i)
		{
			new (p_ + i) T(new_val);
		}
		// ����size_
		size_ = new_size;
	}

	// �ͷŶ�����ڴ棬ʹcapacity_��size_��ͬ
	template<class T>
	void vector<T>::shrink_to_fit()
	{
		if(size_ < capacity_)
		{
			T *new_ptr = static_cast<T*>(operator new [] (size_ * sizeof(T)));
			xf::uninitialized_copy(p_, p_ + size_, new_ptr);
			for(size_t i = 0; i < size_; ++i)
			{
				(p_ + i)->~T();
			}
			operator delete[](p_);

			p_ = new_ptr;
			capacity_ = size_;
		}
	}

	template<class T>
	size_t vector<T>::max_size()
	{
		return static_cast<unsigned int>(-1) / sizeof(T);
	}

	template<class T>
	void vector<T>::clear()
	{
		for(size_t i = 0; i < size_; ++i)
		{
			(p_ + i)->~T();
		}
		size_ = 0;
	}

	template<class T>
	void vector<T>::assign(size_t count, const T &val)
	{
		assign_n(count, val);
	}

	template<class T>
	template<class _Iter, typename std::enable_if<!std::is_integral<_Iter>::value, int>::type>
	void vector<T>::assign(_Iter first, _Iter last)
	{
		clear();
		// �����µ�size_
		size_ = xf::distance(first, last);
		if(size_ > capacity_)
		{
			reserve(size_);
			capacity_ = size_;
		}
		xf::uninitialized_copy(first, last, p_);
	}

	template<class T>
	void vector<T>::push_back(const T &item)
	{
		if(size_ == capacity_)
		{
			// ����
			size_t new_capacity = get_new_capacity();
			reserve(new_capacity);
		}
		// ������Ԫ��
		new (p_ + size_) T(item);
		++size_;
	}

	template<class T>
	void vector<T>::pop_back()
	{
		--size_;
		(p_ + size_)->~T();
	}

	template<class T>
	const T& vector<T>::front() const
	{
		return *p_;
	}
	template<class T>
	const T& vector<T>::back() const
	{
		return p_[size_ - 1];
	}
	template<class T>
	T& vector<T>::front()
	{
		return *p_;
	}
	template<class T>
	T& vector<T>::back()
	{
		return p_[size_ - 1];
	}

	template<class T>
	typename vector<T>::iterator vector<T>::insert(const const_iterator &_Where, const T &_Value)
	{
		if(size_ == capacity_)	// ��Ҫ����
		{
			size_t offset = _Where.p_ - p_;	// ��¼����Ԫ�ص�ƫ����
			// ������ռ䲢�����θ��ƣ�������Ҫ�����Ԫ�ص�λ��
			size_t new_capacity = get_new_capacity();
			T * new_ptr = static_cast<T*>(operator new[] (new_capacity * sizeof(T)));
			xf::uninitialized_copy(p_, p_ + offset, new_ptr);	// ǰ��
			xf::uninitialized_copy(p_ + offset, p_ + size_, new_ptr + offset + 1);	// ���
			// �����µ�Ԫ��
			new (new_ptr + offset) T(_Value);
			// ����ԭ���Ŀռ�
			for(size_t i = 0; i < size_; ++i)
			{
				p_[i].~T();
			}
			operator delete[](p_);
			// ����vector������
			p_ = new_ptr;
			capacity_ = new_capacity;
			++size_;
			return iterator(p_ + offset);
		}
		else	// ��������
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
	typename vector<T>::iterator vector<T>::insert(const const_iterator &_Where, size_t _Count, const T &_Value)
	{
		return insert_n(_Where, _Count, _Value);
	}

	template<class T>template<class Iter, typename std::enable_if<!std::is_integral<Iter>::value, int>::type>
	typename vector<T>::iterator vector<T>::insert(const const_iterator &_Where, Iter _First, Iter _Last)
	{
		//assert(_First < _Last);	// ����Ҫ��Ҫassert����һ_Iterû�ж���С�ں���ô�죿
		size_t where_offset = _Where - cbegin();
		size_t _Count = xf::distance(_First, _Last);
		if(size_ + _Count > capacity_)	// ��Ҫ����
		{
			size_t offset = _Where.p_ - p_;	// ��¼����Ԫ�ص�ƫ����
			// ������ռ䲢�ֱ��Ʋ����ǰ��Ρ�����㡢��������
			size_t new_capacity = get_new_capacity(size_ + _Count);
			T * new_ptr = static_cast<T*>(operator new[] (new_capacity * sizeof(T)));
			xf::uninitialized_copy(p_, p_ + offset, new_ptr);
			xf::uninitialized_copy(_First, _Last, new_ptr + offset);
			xf::uninitialized_copy(p_ + offset, p_ + size_, new_ptr + offset + _Count);
			//// �����µ�Ԫ��
			//for(size_t i = 0; i < count; ++i)
			//{
			//	new (new_ptr + offset + i) T(*_First);
			//	++_First;
			//}
			//assert(_First == _Last);
			// ����ԭ���Ŀռ�
			for(size_t i = 0; i < size_; ++i)
			{
				p_[i].~T();
			}
			operator delete[](p_);
			// ����vector������
			p_ = new_ptr;
			capacity_ = new_capacity;
			size_ += _Count;
			return iterator(p_ + offset);
		}
		else	// ��������
		{
			// �������εĳ���
			size_t last_segment_length = cend() - _Where;
			// ����last_segment_length��_Count�Ĵ�С������insert�ľ��岽��
			if(_Count >= last_segment_length)
			{
				// 1. ���裺�ƶ�����ʽ������
				// 2. ���裺���룻��ʽ����ֵ
				// 3. ���裺���룻��ʽ������
				T *old_end_element = p_ + size_ - 1;
				T *new_end_element = p_ + size_ + _Count - 1;
				for(size_t i = 0; i < last_segment_length; ++i)
				{
					new (new_end_element) T(*old_end_element);	// 1.
					*old_end_element = *_First;					// 2.
					++_First;
					--new_end_element;
					--old_end_element;
				}
				uninitialized_copy(_First, _Last, p_ + size_);	// 3.
			}
			else
			{
				// 1. ���裺�ƶ�����ʽ������
				// 2. ���裺�ƶ�����ʽ����ֵ
				// 3. ���裺���룻��ʽ����ֵ
				T *old_end_element = p_ + size_ - 1;
				T *new_end_element = p_ + size_ + _Count - 1;
				for(size_t i = 0; i < _Count; ++i)	// 1.
				{
					new (new_end_element) T(*old_end_element);	
					--new_end_element;
					--old_end_element;
				}
				while(old_end_element >= _Where.p_)	// 2.
				{
					*new_end_element = *old_end_element;
					--new_end_element;
					--old_end_element;
				}
				while(++old_end_element <= new_end_element)	// 3.
				{
					*old_end_element = *_First;
					++_First;
				}
				
			}
			size_ += _Count;
		}

		return begin() + where_offset;
	}

	template<class T>
	typename vector<T>::iterator vector<T>::erase(const const_iterator &_First, const const_iterator &_Last)
	{
		assert(_First <= _Last);
		if(_First == _Last)
		{
			return begin() + (_First - cbegin());
		}
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
	typename vector<T>::iterator vector<T>::erase(const const_iterator &_Where)
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
	const T& vector<T>::at(size_t index) const throw(std::out_of_range)
	{
		if(index < 0 || index >= size_)
		{
			throw std::out_of_range("invalid vector<T> subscript");
		}
		else
		{
			return p_[index];
		}
	}
	template<class T>
	T& vector<T>::at(size_t index) throw(std::out_of_range)
	{
		if(index < 0 || index >= size_)
		{
			throw std::out_of_range("invalid vector<T> subscript");
		}
		else
		{
			return p_[index];
		}
	}

	template<class T>
	const T& vector<T>::operator [](size_t index) const
	{
		return p_[index];
	}
	template<class T>
	T& vector<T>::operator [](size_t index)
	{
		return p_[index];
	}
	
	template<class T>
	const T* vector<T>::data() const
	{
		return p_;
	}
	template<class T>
	T* vector<T>::data()
	{
		return p_;
	}

	template<class T>
	typename vector<T>::const_iterator vector<T>::cbegin() const
	{
		return const_iterator(p_);
	}
	template<class T>
	typename vector<T>::const_iterator vector<T>::begin() const
	{
		return cbegin();
	}
	template<class T>
	typename vector<T>::iterator vector<T>::begin()
	{
		return iterator(p_);
	}

	template<class T>
	typename vector<T>::const_iterator vector<T>::cend() const
	{
		return const_iterator(p_ + size_);
	}
	template<class T>
	typename vector<T>::const_iterator vector<T>::end() const
	{
		return cend();
	}
	template<class T>
	typename vector<T>::iterator vector<T>::end()
	{
		return iterator(p_ + size_);
	}

	template<class T>
	typename vector<T>::const_reverse_iterator vector<T>::crbegin() const
	{
		return const_reverse_iterator(cend());
	}
	template<class T>
	typename vector<T>::const_reverse_iterator vector<T>::rbegin() const
	{
		return crbegin();
	}
	template<class T>
	typename vector<T>::reverse_iterator vector<T>::rbegin()
	{
		return reverse_iterator(end());
	}

	template<class T>
	typename vector<T>::const_reverse_iterator vector<T>::crend() const
	{
		return const_reverse_iterator(cbegin());
	}
	template<class T>
	typename vector<T>::const_reverse_iterator vector<T>::rend() const
	{
		return crend();
	}
	template<class T>
	typename vector<T>::reverse_iterator vector<T>::rend()
	{
		return reverse_iterator(begin());
	}

	// STL�е�=������У���ÿ��Ԫ�صĸ��ƣ���һ����ÿ��Ԫ�ص�=���ǿ������캯��
	// ��right��*this��size��С����
	template<class T>
	vector<T>& vector<T>::operator = (const vector<T> &right)
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
	size_t vector<T>::get_new_capacity() const
	{
		size_t new_capacity;
		if(0 == capacity_)
		{
			new_capacity = 1;
		}
		else if(2 * capacity_ <= max_size())
		{
			new_capacity = 2 * capacity_;
		}
		else if(capacity_ == max_size())
		{
			throw std::length_error("already reached max size of vector");
		}
		else
		{
			new_capacity = max_size();
		}
		return new_capacity;
	}

	template<class T>
	size_t vector<T>::get_new_capacity(size_t min_request_size) const
	{
		size_t new_capacity = 0U;
		if(2 * capacity_ > max_size())		// �����������
		{
			new_capacity = max_size();
		}
		else if(2 * capacity_ > min_request_size)	// �����������
		{
			new_capacity = 2 * capacity_;
		}
		else
		{
			new_capacity = min_request_size;
		}
		return new_capacity;
	}

	template<class T>
	void vector<T>::assign_n(size_t count, const T &val)
	{
		clear();
		size_ = count;
		if(count > capacity_)
		{
			reserve(count);
			capacity_ = count;
		}
		xf::uninitialized_fill(p_, p_ + count, val);
	}

	// ���ú���������������count value�Ͳ��룬�Լ�����������ĺ���ģ����ػ��汾
	template<class T>
	typename vector<T>::iterator vector<T>::insert_n(const const_iterator _Where, size_t _Count, const T &_Value)
	{
		if(size_ + _Count > capacity_)	// ��Ҫ����
		{
			size_t offset = _Where.p_ - p_;	// ��¼����Ԫ�ص�ƫ����
			// ������ռ䲢�ֱ��Ʋ����ǰ��Ρ�����㡢��������
			size_t new_capacity = get_new_capacity(size_ + _Count);
			T * new_ptr = static_cast<T*>(operator new[] (new_capacity * sizeof(T)));
			xf::uninitialized_copy(p_, p_ + offset, new_ptr);
			xf::uninitialized_fill(new_ptr + offset, new_ptr + offset + _Count, _Value);
			xf::uninitialized_copy(p_ + offset, p_ + size_, new_ptr + offset + _Count);
			//// �����µ�Ԫ��
			//for(size_t i = 0; i < _Count; ++i)
			//{
			//	new (new_ptr + offset + i) T(_Value);
			//}
			// ����ԭ���Ŀռ�
			for(size_t i = 0; i < size_; ++i)
			{
				p_[i].~T();
			}
			operator delete[](p_);
			// ����vector������
			p_ = new_ptr;
			capacity_ = new_capacity;
			size_ += _Count;
			return iterator(p_ + offset);
		}
		else	// ��������
		{
			// �������εĳ���
			size_t last_segment_length = cend() - _Where;
			// ����last_segment_length��_Count�Ĵ�С������insert�ľ��岽��
			if(_Count >= last_segment_length)
			{
				// 1. ���裺�ƶ�����ʽ������
				// 2. ���裺���룻��ʽ����ֵ
				// 3. ���裺���룻��ʽ������
				T *old_end_element = p_ + size_ - 1;
				T *new_end_element = p_ + size_ + _Count - 1;
				for(size_t i = 0; i < last_segment_length; ++i)
				{
					new (new_end_element) T(*old_end_element);	// 1.
					*old_end_element = _Value;					// 2.
					--new_end_element;
					--old_end_element;
				}
				// 3.
				uninitialized_fill(p_ + size_, new_end_element + 1, _Value);
			}
			else
			{
				// 1. ���裺�ƶ�����ʽ������
				// 2. ���裺�ƶ�����ʽ����ֵ
				// 3. ���裺���룻��ʽ����ֵ
				T *old_end_element = p_ + size_ - 1;
				T *new_end_element = p_ + size_ + _Count - 1;
				for(size_t i = 0; i < _Count; ++i)	// 1.
				{
					new (new_end_element) T(*old_end_element);	
					--new_end_element;
					--old_end_element;
				}
				while(old_end_element >= _Where.p_)	// 2.
				{
					*new_end_element = *old_end_element;
					--new_end_element;
					--old_end_element;
				}
				while(++old_end_element <= new_end_element)	// 3.
				{
					*old_end_element = _Value;
				}
				
			}
			size_ += _Count;
			return iterator(_Where.p_);
		}
	}
}

#endif