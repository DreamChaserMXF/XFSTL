#ifndef XF_VECTOR_H
#define XF_VECTOR_H

#pragma warning(disable:4290)	// for msvc's not fully supporting the exception specifications
#pragma warning(disable:4996)	// for msvc's safety concern about uninitialized_xxxx()

#include "_Vector_Iterator.hpp"
#include "_Reverse_Iterator.hpp"
#include <cassert>
#include <exception>
#include <stdexcept>
#include <memory>
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

		vector() throw();
		vector(const vector<T> &right) throw(std::bad_alloc);
		vector(size_t count) throw(std::bad_alloc, std::length_error);
		vector(size_t count, const T &val) throw(std::bad_alloc, std::length_error);
		template<class _Iter> vector(_Iter first, _Iter last) throw(std::bad_alloc, std::length_error);
		template<> vector(int count, int val) throw(std::bad_alloc, std::length_error) : p_(NULL), size_(count), capacity_(count) 
		{
			if(static_cast<size_t>(count) > max_size())
			{
				throw std::length_error("too much memory to allocate");
			}
			p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
			std::uninitialized_fill(p_, p_ + size_, static_cast<T>(val));	// construct elements
		}
		virtual ~vector() throw();

		size_t capacity() const throw();
		size_t size() const throw();
		bool empty() const throw();
		void reserve(size_t capacity) throw(std::bad_alloc, std::length_error);
		void resize(size_t size) throw(std::bad_alloc, std::length_error);
		void shrink_to_fit() throw(std::bad_alloc);	// 释放多余的内存

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


		// TODO 这里不懂为什么STL在设计时，要接受const_iterator而不是iterator做参数
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

		vector<T>& operator = (const vector<T> &right);

	private:
		size_t get_new_capacity() const throw(std::length_error);
		size_t get_new_capacity(size_t min_request_size) const throw(std::length_error);
		void assign_n(size_t count, const T &val) throw(std::length_error, std::bad_alloc);
		iterator insert_n(const const_iterator _Where, size_t _Count, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast);

		T *p_;
		size_t size_;
		size_t capacity_;

	};

	template<class T>
	vector<T>::vector() throw() : p_(NULL), size_(0), capacity_(0) 
	{
	}

	template<class T>
	vector<T>::vector(const vector<T> &right) throw(std::bad_alloc) : p_(static_cast<T*>(operator new[](right.size_ * sizeof(T)))), size_(right.size_), capacity_(right.size_) 
	{
		// 通过构造函数在p_处建立right.p_的副本
		std::uninitialized_copy(right.p_, right.p_ + size_, p_);
	}

	template<class T>
	vector<T>::vector(size_t count) throw(std::bad_alloc, std::length_error) : p_(NULL), size_(count), capacity_(count) 
	{
		if(count > max_size())
		{
			throw std::length_error("too much memory to allocate");
		}
		p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
		for(size_t i = 0; i < size_; ++i)
		{
			new (p_ + i) T();	// 调用真正的默认构造函数
		}
	}


	template<class T>
	vector<T>::vector(size_t count, const T &val) throw(std::bad_alloc, std::length_error) : p_(NULL), size_(count), capacity_(count) 
	{
		if(count > max_size())
		{
			throw std::length_error("too much memory to allocate");
		}

		p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
		std::uninitialized_fill(p_, p_ + size_, val);	// construct elements
	}

	template<class T>template<class _Iter>
	vector<T>::vector(_Iter first, _Iter last) throw(std::bad_alloc, std::length_error) : p_(NULL), size_(0U), capacity_(0U) 
	{
		_Iter tmp = first;
		while(tmp != last)
		{
			++tmp;
			++size_;
		}
		capacity_ = size_;
		if(capacity_ > max_size())
		{
			throw std::length_error("too much memory to allocate");
		}
		p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
		std::uninitialized_copy(first, last, p_);	// construct elements
	}

	template<class T>
	vector<T>::~vector() throw()
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
	size_t vector<T>::capacity() const throw()
	{
		return capacity_;
	}
	

	template<class T>
	size_t vector<T>::size() const throw()
	{
		return size_;
	}

	template<class T>
	bool vector<T>::empty() const throw()
	{
		return (size_ == 0);
	}

	template<class T>
	void vector<T>::reserve(size_t new_capacity) throw(std::bad_alloc, std::length_error)
	{
		// 小于0的情况可以不考虑，因为此时真正的capacity_不会改变
		if(new_capacity < 0)
		{
			return;
		}
		// 判断是否太大了
		if(new_capacity > max_size())
		{
			throw std::length_error("too much memory to allocate");
		}

		if(new_capacity > capacity_)
		{
			T *buf = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
			if(p_)
			{
				std::uninitialized_copy(p_, p_ + size_, buf);	// copy elements using copy constructor
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
	void vector<T>::resize(size_t new_size) throw(std::bad_alloc, std::length_error)
	{
		if(new_size > max_size())
		{
			throw std::length_error("too much memory to allocate");
		}
		// 变小的话，要把多余的元素清除掉
		if(new_size < size_)
		{
			for(size_t i = new_size; i < size_; ++i)
			{
				(p_ + i)->~T();
			}
		}
		// 变大且要扩容的情况
		else if(new_size > capacity_)
		{
			reserve(new_size);
		}
		// 现在容量够了
		// 对变大的地方进行初始化
		for(size_t i = size_; i < new_size; ++i)
		{
			new (p_ + i) T();
		}
		// 调整size_
		size_ = new_size;
	}

	// 释放多余的内存，使capacity_与size_相同
	template<class T>
	void vector<T>::shrink_to_fit() throw(std::bad_alloc)
	{
		if(size_ < capacity_)
		{
			T *new_ptr = static_cast<T*>(operator new [] (size_ * sizeof(T)));
			std::uninitialized_copy(p_, p_ + size_, new_ptr);
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
	size_t vector<T>::max_size() throw()
	{
		return static_cast<size_t>(-1) / sizeof(T);
	}

	template<class T>
	void vector<T>::clear() throw()
	{
		for(size_t i = 0; i < size_; ++i)
		{
			(p_ + i)->~T();
		}
		size_ = 0;
	}

	template<class T>
	void vector<T>::assign(size_t count, const T &val) throw()
	{
		assign_n(count, val);
	}

	template<class T>
	template<class _Iter>
	void vector<T>::assign(_Iter first, _Iter last) throw()
	{
		clear();
		// 计算新的size_
		_Iter tmp = first;
		while(tmp != last)
		{
			++tmp;
			++size_;
		}
		if(size_ > capacity_)
		{
			reserve(size_);
			capacity_ = size_;
		}
		std::uninitialized_copy(first, last, p_);
	}

	template<class T>
	void vector<T>::push_back(const T &item) throw(std::bad_alloc, std::length_error)
	{
		if(size_ == capacity_)
		{
			// 扩容
			size_t new_capacity = get_new_capacity();
			reserve(new_capacity);
		}
		// 添加新元素
		new (p_ + size_) T(item);
		++size_;
	}

	template<class T>
	void vector<T>::pop_back() throw(std::length_error)
	{
		if(0 == size_)
		{
			throw std::length_error("invalid vector<T> subscript");
		}
		else
		{
			--size_;
			(p_ + size_)->~T();
		}
	}

	template<class T>
	const T& vector<T>::front() const throw()
	{
		return *p_;
	}
	template<class T>
	const T& vector<T>::back() const throw()
	{
		return p_[size_ - 1];
	}
	template<class T>
	T& vector<T>::front() throw()
	{
		return *p_;
	}
	template<class T>
	T& vector<T>::back() throw()
	{
		return p_[size_ - 1];
	}

	template<class T>
	typename vector<T>::iterator vector<T>::insert(const const_iterator &_Where, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast)
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
			// 更新vector的属性
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
	typename vector<T>::iterator vector<T>::insert(const const_iterator &_Where, size_t _Count, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast)
	{
		return insert_n(_Where, _Count, _Value);
	}

	template<class T>template<class Iter>
	typename vector<T>::iterator vector<T>::insert(const const_iterator &_Where, Iter _First, Iter _Last) throw(std::bad_alloc, std::length_error, std::bad_cast)
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
			// 更新vector的属性
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
	typename vector<T>::iterator vector<T>::erase(const const_iterator &_First, const const_iterator &_Last) throw()
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
	typename vector<T>::iterator vector<T>::erase(const const_iterator &_Where) throw()
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
	const T& vector<T>::operator [](size_t index) const throw()
	{
		return p_[index];
	}
	template<class T>
	T& vector<T>::operator [](size_t index) throw()
	{
		return p_[index];
	}
	
	template<class T>
	const T* vector<T>::data() const throw()
	{
		return p_;
	}
	template<class T>
	T* vector<T>::data() throw()
	{
		return p_;
	}

	template<class T>
	typename vector<T>::const_iterator vector<T>::cbegin() const throw()
	{
		return const_iterator(p_);
	}
	template<class T>
	typename vector<T>::const_iterator vector<T>::begin() const throw()
	{
		return cbegin();
	}
	template<class T>
	typename vector<T>::iterator vector<T>::begin() throw()
	{
		return iterator(p_);
	}

	template<class T>
	typename vector<T>::const_iterator vector<T>::cend() const throw()
	{
		return const_iterator(p_ + size_);
	}
	template<class T>
	typename vector<T>::const_iterator vector<T>::end() const throw()
	{
		return cend();
	}
	template<class T>
	typename vector<T>::iterator vector<T>::end() throw()
	{
		return iterator(p_ + size_);
	}

	template<class T>
	typename vector<T>::const_reverse_iterator vector<T>::crbegin() const throw()
	{
		return const_reverse_iterator(cend());
	}
	template<class T>
	typename vector<T>::const_reverse_iterator vector<T>::rbegin() const throw()
	{
		return crbegin();
	}
	template<class T>
	typename vector<T>::reverse_iterator vector<T>::rbegin() throw()
	{
		return reverse_iterator(end());
	}

	template<class T>
	typename vector<T>::const_reverse_iterator vector<T>::crend() const throw()
	{
		return const_reverse_iterator(cbegin());
	}
	template<class T>
	typename vector<T>::const_reverse_iterator vector<T>::rend() const throw()
	{
		return crend();
	}
	template<class T>
	typename vector<T>::reverse_iterator vector<T>::rend() throw()
	{
		return reverse_iterator(begin());
	}

	// STL中的=运算符中，对每个元素的复制，不一定用每个元素的=还是拷贝构造函数
	// 视right与*this的size大小而定
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
	size_t vector<T>::get_new_capacity() const throw(std::length_error)
	{
		size_t new_capacity;
		if(0 == capacity_)
		{
			new_capacity = 1;
		}
		else if(capacity_ == max_size())
		{
			throw std::length_error("too much memory to allocte");
		}
		else if(2 * capacity_ <= max_size())
		{
			new_capacity = 2 * capacity_;
		}
		else
		{
			new_capacity = max_size();
		}
		return new_capacity;
	}

	template<class T>
	size_t vector<T>::get_new_capacity(size_t min_request_size) const throw(std::length_error)
	{
		size_t new_capacity = 0U;
		if(min_request_size > max_size())	// 检查边界
		{
			throw std::length_error("too much memory to allocte");
		}
		if(2 * capacity_ > max_size())		// 尝试申请更多
		{
			new_capacity = max_size();
		}
		else if(2 * capacity_ > min_request_size)	// 尝试申请更多
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
	void vector<T>::assign_n(size_t count, const T &val) throw()
	{
		clear();
		size_ = count;
		if(count > capacity_)
		{
			reserve(count);
			capacity_ = count;
		}
		std::uninitialized_fill(p_, p_ + count, val);
	}

	template<class T>
	typename vector<T>::iterator vector<T>::insert_n(const const_iterator _Where, size_t _Count, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast)
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
			// 更新vector的属性
			p_ = new_ptr;
			capacity_ = new_capacity;
			size_ += _Count;
			return iterator(p_ + offset);
		}
		else	// 不须扩容
		{
			const T *cur = _Where.p_;
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
			return iterator(const_cast<T*>(cur));
		}
	}
}

#endif

