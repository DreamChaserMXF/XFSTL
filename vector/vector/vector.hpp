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
		void shrink_to_fit() throw(std::bad_alloc);	// �ͷŶ�����ڴ�

		static size_t max_size()throw();

		void clear() throw();
		void assign(size_t count, const T &val) throw(std::length_error, std::bad_alloc);
		template<class _Iter> 
		void assign(_Iter first, _Iter last) throw(std::length_error, std::bad_alloc);
		// ���ģ����ػ����������ⶨ�壬��֪��Ϊɶ
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


		// TODO ���ﲻ��ΪʲôSTL�����ʱ��Ҫ����const_iterator������iterator������
		iterator erase(const const_iterator &_First, const const_iterator &_Last) throw();
		iterator erase(const const_iterator &_Where) throw();

		const T& at(size_t index) const throw(std::out_of_range);	// �ҳ���index��Ԫ�أ���Խ����
		T& at(size_t index) throw(std::out_of_range);				// �ҳ���index��Ԫ�أ���Խ����
		
		const T& operator [](size_t index) const throw();			// �ҳ���index��Ԫ�أ���Խ����
		T& operator [](size_t index) throw();						// �ҳ���index��Ԫ�أ���Խ����

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
		// ͨ�����캯����p_������right.p_�ĸ���
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
			new (p_ + i) T();	// ����������Ĭ�Ϲ��캯��
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
		// С��0��������Բ����ǣ���Ϊ��ʱ������capacity_����ı�
		if(new_capacity < 0)
		{
			return;
		}
		// �ж��Ƿ�̫����
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
			new (p_ + i) T();
		}
		// ����size_
		size_ = new_size;
	}

	// �ͷŶ�����ڴ棬ʹcapacity_��size_��ͬ
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
		// �����µ�size_
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
			// ����
			size_t new_capacity = get_new_capacity();
			reserve(new_capacity);
		}
		// �����Ԫ��
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
		if(size_ == capacity_)	// ��Ҫ����
		{
			size_t offset = _Where.p_ - p_;	// ��¼����Ԫ�ص�ƫ����
			// ������ռ䲢�����θ��ƣ�������Ҫ�����Ԫ�ص�λ��
			size_t new_capacity = get_new_capacity();
			T * new_ptr = static_cast<T*>(operator new[] (new_capacity * sizeof(T)));
			std::uninitialized_copy(p_, p_ + offset, new_ptr);
			std::uninitialized_copy(p_ + offset, p_ + size_, new_ptr + offset + 1);
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
	typename vector<T>::iterator vector<T>::insert(const const_iterator &_Where, size_t _Count, const T &_Value) throw(std::bad_alloc, std::length_error, std::bad_cast)
	{
		return insert_n(_Where, _Count, _Value);
	}

	template<class T>template<class Iter>
	typename vector<T>::iterator vector<T>::insert(const const_iterator &_Where, Iter _First, Iter _Last) throw(std::bad_alloc, std::length_error, std::bad_cast)
	{
		assert(_First < _Last);	// ����Ҫ��Ҫassert����һ_Iterû�ж���С�ں���ô�죿
		size_t count = _Last - _First;
		if(size_ + count > capacity_)	// ��Ҫ����
		{
			size_t offset = _Where.p_ - p_;	// ��¼����Ԫ�ص�ƫ����
			// ������ռ䲢�����θ��ƣ�������Ҫ�����Ԫ�ص�λ��
			size_t new_capacity = get_new_capacity(size_ + count);
			T * new_ptr = static_cast<T*>(operator new[] (new_capacity * sizeof(T)));
			std::uninitialized_copy(p_, p_ + offset, new_ptr);
			std::uninitialized_copy(p_ + offset, p_ + size_, new_ptr + offset + count);
			// �����µ�Ԫ��
			for(size_t i = 0; i < count; ++i)
			{
				new (new_ptr + offset + i) T(*_First);
				++_First;
			}
			assert(_First == _Last);
			// ����ԭ���Ŀռ�
			for(size_t i = 0; i < size_; ++i)
			{
				p_[i].~T();
			}
			operator delete[](p_);
			// ����vector������
			p_ = new_ptr;
			capacity_ = new_capacity;
			size_ += count;
			return iterator(p_ + offset);
		}
		else	// ��������
		{
			T *cur = const_cast<T*>(_Where.p_);
			T *last = p_ + size_ + count - 1;
			// ��Ҫ����Ĳ���
			while(last >= p_ + size_)
			{
				new (last) T(*(last - count));	
				--last;
			}
			// ��Ҫ���ƵĲ���
			while(last >= cur + count)
			{
				*last = *(last - count);
				--last;
			}
			// ��Ҫ����Ĳ���
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
		if(min_request_size > max_size())	// ���߽�
		{
			throw std::length_error("too much memory to allocte");
		}
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
		if(size_ + _Count > capacity_)	// ��Ҫ����
		{
			size_t offset = _Where.p_ - p_;	// ��¼����Ԫ�ص�ƫ����
			// ������ռ䲢�����θ��ƣ�������Ҫ�����Ԫ�ص�λ��
			size_t new_capacity = get_new_capacity(size_ + _Count);
			T * new_ptr = static_cast<T*>(operator new[] (new_capacity * sizeof(T)));
			std::uninitialized_copy(p_, p_ + offset, new_ptr);
			std::uninitialized_copy(p_ + offset, p_ + size_, new_ptr + offset + _Count);
			// �����µ�Ԫ��
			for(size_t i = 0; i < _Count; ++i)
			{
				new (new_ptr + offset + i) T(_Value);
			}
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
			const T *cur = _Where.p_;
			T *last = p_ + size_ + _Count - 1;
			// ��Ҫ����Ĳ���
			while(last >= p_ + size_)
			{
				new (last) T(*(last - _Count));	
				--last;
			}
			// ��Ҫ���ƵĲ���
			while(last >= cur + _Count)
			{
				*last = *(last - _Count);
				--last;
			}
			// ��Ҫ����Ĳ���
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

