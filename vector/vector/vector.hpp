#ifndef XF_VECTOR_H
#define XF_VECTOR_H

#pragma warning(disable:4290)	// for msvc's not fully supporting the exception specifications

#include "_Vector_iterator.hpp"
#include "_Vector_reverse_iterator.hpp"
#include <exception>

namespace xf
{

	template<class T>
	class vector
	{
	public:

		typedef _Vector_iterator<T> iterator;
		typedef _Vector_const_iterator<T> const_iterator;
		typedef _Vector_reverse_iterator<T> reverse_iterator;
		typedef _Vector_reverse_const_iterator<T> reverse_const_iterator;

		vector() throw();
		vector(const vector<T> &right) throw(std::bad_alloc);
		vector(int count) throw(std::bad_alloc, std::length_error);
		vector(int count, const T &val) throw(std::bad_alloc, std::length_error);
		template<class _Iter> vector(_Iter first, _Iter last) throw(std::bad_alloc, std::length_error);
		virtual ~vector() throw();

		int capacity() const throw();
		int size() const throw();
		void reserve(int capacity) throw(std::bad_alloc, std::length_error);
		void resize(int size) throw(std::bad_alloc, std::length_error);
		int max_size() const throw();

		void push_back(const T &item) throw(std::bad_alloc, std::length_error);
		void pop_back() throw(std::length_error);
		const T& at(int index) const throw(std::out_of_range);	// 找出第index个元素，有越界检查
		const T& operator [](int index) const throw();			// 找出第index个元素，无越界检查
		T& at(int index) throw(std::out_of_range);				// 找出第index个元素，有越界检查
		T& operator [](int index) throw();						// 找出第index个元素，无越界检查

		_Vector_const_iterator<T> begin() const throw();
		_Vector_const_iterator<T> end() const throw();
		_Vector_iterator<T> begin() throw();
		_Vector_iterator<T> end() throw();
		_Vector_reverse_const_iterator<T> rbegin() const throw();
		_Vector_reverse_const_iterator<T> rend() const throw();
		_Vector_reverse_iterator<T> rbegin() throw();
		_Vector_reverse_iterator<T> rend() throw();

	private:
		T *p_;
		int size_;
		int capacity_;
	};


	template<class T>
	vector<T>::vector() throw() : p_(NULL), size_(0), capacity_(0) 
	{
	}

	template<class T>
	vector<T>::vector(const vector<T> &right) throw(std::bad_alloc) try : p_(new T[right.capacity_]), size_(right.size_), capacity_(right.capacity_) 
	{
		for(int i = 0; i < size_; ++i)
		{
			p_[i] = right.p_[i];
		}
	}
	catch(const std::bad_alloc)
	{
		p_ = NULL;
		throw;
	}

	template<class T>
	vector<T>::vector(int count) throw(std::bad_alloc, std::length_error) : p_(NULL), size_(count), capacity_(count) 
	{
		if(count < 0)
		{
			throw std::length_error("negative size for vector<T> initialization");
		}
		else if((size_t)count > max_size() * sizeof(T))
		{
			throw std::length_error("too much memory to allocate");
		}
		p_ = new T[capacity_];
		for(int i = 0; i < size_; ++i)
		{
			p_[i] = T();
		}
	}


	template<class T>
	vector<T>::vector(int count, const T &val) throw(std::bad_alloc, std::length_error) : p_(NULL), size_(count), capacity_(count) 
	{
		if(count < 0)
		{
			throw std::length_error("negative size for vector<T> initialization");
		}
		else if((size_t)count > max_size() * sizeof(T))
		{
			throw std::length_error("too much memory to allocate");
		}

		p_ = new T[capacity_];
		for(int i = 0; i < size_; ++i)
		{
			p_[i] = val;
		}
	}
	//template<class _Iter> vector(_Iter &first, _Iter &last) throw(std::bad_alloc, std::length_error);
	template<class T>template<class _Iter>
	vector<T>::vector(_Iter first, _Iter last) throw(std::bad_alloc, std::length_error) : p_(NULL), size_(last - first), capacity_(last - first) 
	{
		if(capacity_ < 0)
		{
			throw std::length_error("negative size for vector<T> initialization");
		}
		else if((size_t)capacity_ > max_size() * sizeof(T))
		{
			throw std::length_error("too much memory to allocate");
		}
		p_ = new T[capacity_];
		for(int i = 0; first != last; ++first, ++i)
		{
			p_[i] = *first;
		}
	}

	template<class T>
	vector<T>::~vector() throw()
	{
		if(p_)
		{
			delete []p_;
		}
	}

	template<class T>
	int vector<T>::capacity() const throw()
	{
		return capacity_;
	}

	template<class T>
	int vector<T>::size() const throw()
	{
		return size_;
	}



	template<class T>
	void vector<T>::reserve(int capacity) throw(std::bad_alloc, std::length_error)
	{
		// 小于0的情况可以不考虑，因为此时真正的capacity_不会改变
		if(capacity < 0)
		{
			return;
		}
		// 判断是否太大了
		if((size_t)capacity > max_size() * sizeof(T))
		{
			throw std::length_error("too much memory to allocate");
		}

		if(capacity > capacity_)
		{
			capacity_ = capacity;
			T *buf = new T[capacity_];
			// 复制
			if(p_)
			{
				for(int i = 0; i < size_; ++i)
				{
					buf[i] = p_[i];
				}
				delete []p_;
			}
			p_ = buf;
		}
	}

	template<class T>
	void vector<T>::resize(int size) throw(std::bad_alloc, std::length_error)
	{
		if(size < 0)
		{
			throw std::length_error("negative size for vector<T> resize");
		}
		else if((size_t)size > max_size() * sizeof(T))
		{
			throw std::length_error("too much memory to allocate");
		}
		// 变小的话，要把多余的元素清除掉
		if(size < size_)
		{
			for(int i = size; i < size_; ++i)
			{
				p_[i] = T();
			}
		}
		// 变大且要扩容的情况
		else if(size > capacity_)
		{
			reserve(size);
		}
		// 变大后，初始化扩大后的size
		for(int i = size_; i < size; ++i)
		{
			p_[i] = T();
		}
		// 调整size_
		size_ = size;
	}

	template<class T>
	int vector<T>::max_size() const throw()
	{
		return ((1 << 30) - 1);
	}


	template<class T>
	void vector<T>::push_back(const T &item) throw(std::bad_alloc, std::length_error)
	{
		if(size_ == capacity_)
		{
			// 扩容
			int new_capacity = (0 == capacity_) ? 1 : 2 * capacity_;
			reserve(new_capacity);
		}
		// 添加新元素
		p_[size_] = item;
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
		}
	}

	
	template<class T>
	const T& vector<T>::at(int index) const throw(std::out_of_range)
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
	const T& vector<T>::operator [](int index) const throw()
	{
		return p_[index];
	}
	template<class T>
	T& vector<T>::at(int index) throw(std::out_of_range)
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
	T& vector<T>::operator [](int index) throw()
	{
		return p_[index];
	}
	

	template<class T>
	_Vector_const_iterator<T> vector<T>::begin() const throw()
	{
		return _Vector_const_iterator<T>(p_);
	}
	template<class T>
	_Vector_const_iterator<T> vector<T>::end() const throw()
	{
		return _Vector_const_iterator<T>(p_ + size_);
	}
	template<class T>
	_Vector_iterator<T> vector<T>::begin() throw()
	{
		return _Vector_iterator<T>(p_);
	}
	template<class T>
	_Vector_iterator<T> vector<T>::end() throw()
	{
		return _Vector_iterator<T>(p_ + size_);
	}

	template<class T>
	_Vector_reverse_const_iterator<T> vector<T>::rbegin() const throw()
	{
		return _Vector_reverse_const_iterator<T>(p_ + size_ - 1);
	}
	template<class T>
	_Vector_reverse_const_iterator<T> vector<T>::rend() const throw()
	{
		return _Vector_reverse_const_iterator<T>(p_ - 1);
	}
	template<class T>
	_Vector_reverse_iterator<T> vector<T>::rbegin() throw()
	{
		return _Vector_reverse_iterator<T>(p_ + size_ - 1);
	}
	template<class T>
	_Vector_reverse_iterator<T> vector<T>::rend() throw()
	{
		return _Vector_reverse_iterator<T>(p_ - 1);
	}

}

#endif

