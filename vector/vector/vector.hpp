#ifndef XF_VECTOR_H
#define XF_VECTOR_H
#include "_Iter.hpp"
#include <exception>


template<class T>
class vector
{
public:
	vector();
	vector(const vector &right);
	vector(int count);
	vector(int count, const T &val);
	vector(_Iter<T> &first, const _Iter<T> &last);
	virtual ~vector();

	int size() const;
	int capacity() const;

	void push_back(const T &item);
	void pop_back();
	T& at(int index) const;		// 找出第index个元素，有越界检查
	T& operator [](int index) const;	// 找出第index个元素，无越界检查

	void reserve(int capacity);
	void resize(int size);
	int max_size() const;

private:
	T *p_;
	int size_;
	int capacity_;
};


template<class T>
vector<T>::vector() : p_(NULL), size_(0), capacity_(0) 
{
	//p_ = new T[capacity_];
	//if(!p_)
	//{
	//	throw std::bad_alloc();
	//}
}

template<class T>
vector<T>::vector(const vector<T> &right) : p_(NULL), size_(right.size_), capacity_(right.capacity_) 
{
	p_ = new T[capacity_];
	if(!p_)
	{
		throw std::bad_alloc();
	}

	for(int i = 0; i < size_; ++i)
	{
		p_[i] = right.p_[i];
	}
}

template<class T>
vector<T>::vector(int count) : p_(NULL), size_(count), capacity_(count) 
{
	if(count < 0)
	{
		throw std::out_of_range("negative size for vector<T> initialization");
	}
	else if((size_t)count > max_size() * sizeof(T))
	{
		throw std::length_error("too much memory to allocate");
	}

	p_ = new T[capacity_];
	if(!p_)
	{
		throw std::bad_alloc();
	}

	for(int i = 0; i < size_; ++i)
	{
		p_[i] = T();
	}
}

template<class T>
vector<T>::vector(int count, const T &val) : p_(NULL), size_(count), capacity_(count) 
{
	if(count < 0)
	{
		throw std::out_of_range("negative size for vector<T> initialization");
	}
	else if(count > max_size() * sizeof(T))
	{
		throw std::length_error("too much memory to allocate");
	}

	p_ = new T[capacity_];
	if(!p_)
	{
		throw std::bad_alloc();
	}

	for(int i = 0; i < size_; ++i)
	{
		p_[i] = val;
	}
}

template<class T>
vector<T>::vector(_Iter<T> &first, const _Iter<T> &last) : p_(NULL), size_(last - first), capacity_(last - first) 
{
	p_ = new T[capacity_];
	if(!p_)
	{
		throw std::bad_alloc();
	}

	for(int i = 0, _Iter<T> iter = first; iter != last; ++iter, ++i)
	{
		p_[i] = *iter;
	}
}

template<class T>
vector<T>::~vector()
{
	if(p_)
	{
		delete []p_;
	}
}

template<class T>
int vector<T>::size() const
{
	return size_;
}

template<class T>
int vector<T>::capacity() const
{
	return capacity_;
}

template<class T>
void vector<T>::push_back(const T &item)
{
	if(size_ == capacity_)
	{
		// 扩容
		capacity_ = (0 == capacity_) ? 1 : 2 * capacity_;
		T *buf = new T[capacity_];
		if(!buf)
		{
			throw std::bad_alloc();
		}
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
	// 添加新元素
	p_[size_] = item;
	++size_;
}

template<class T>
void vector<T>::pop_back()
{
	if(0 == size_)
	{
		throw std::out_of_range("invalid vector<T> subscript");
	}
	else
	{
		--size_;
	}
}

template<class T>
T& vector<T>::at(int index) const
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
T& vector<T>::operator [](int index) const
{
	return p_[index];
}

template<class T>
void vector<T>::reserve(int capacity)
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
		if(!buf)
		{
			throw std::bad_alloc();
		}
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
void vector<T>::resize(int size)
{
	if(size < 0)
	{
		throw std::out_of_range("negative size for vector<T> resize");
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
	// 变得太多了，要扩容
	else if(size > capacity_)
	{
		reserve(size);
	}
	// 有足够容量之后，初始化扩大后的size
	for(int i = size_; i < size; ++i)
	{
		p_[i] = T();
	}
	// 调整size_
	size_ = size;
}

template<class T>
int vector<T>::max_size() const
{
	return ((1 << 30) - 1);
}

#endif

