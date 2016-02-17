#ifndef XF_VECTOR_H
#define XF_VECTOR_H

#pragma warning(disable:4290)	// for msvc's not fully supporting the exception specifications
#pragma warning(disable:4996)	// for msvc's safety concern about unintialized_copy()

#include "_Vector_iterator.hpp"
#include "_Vector_reverse_iterator.hpp"
#include <exception>
#include <stdexcept>
#include <memory>
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
		vector(size_t count) throw(std::bad_alloc, std::length_error);
		vector(size_t count, const T &val) throw(std::bad_alloc, std::length_error);
		template<class _Iter> vector(_Iter first, _Iter last) throw(std::bad_alloc, std::length_error);
		virtual ~vector() throw();

		size_t capacity() const throw();
		size_t size() const throw();
		void reserve(size_t capacity) throw(std::bad_alloc, std::length_error);
		void resize(size_t size) throw(std::bad_alloc, std::length_error);
		size_t max_size() const throw();

		void clear() throw();
		void assign(size_t count, const T &val) throw(std::length_error, std::bad_alloc);
		template<class _Iter> void assign(_Iter first, _Iter last) throw(std::length_error, std::bad_alloc);
		// ���ģ����ػ����������ⶨ�壬��֪��Ϊɶ
		template<> void assign<int>(int first, int last) throw(std::bad_cast, std::length_error, std::bad_alloc)
		{
			size_t count = first;
			T val = static_cast<T>(last);

			clear();
			size_ = count;
			if(count > capacity_)
			{
				reserve(count);
				capacity_ = count;
			}
			std::uninitialized_fill(p_, p_ + count, val);
		}

		void push_back(const T &item) throw(std::bad_alloc, std::length_error);
		void pop_back() throw(std::length_error);

		const T& front() const throw();
		const T& back() const throw();
		T& front();
		T& back();

		const T& at(size_t index) const throw(std::out_of_range);	// �ҳ���index��Ԫ�أ���Խ����
		T& at(size_t index) throw(std::out_of_range);				// �ҳ���index��Ԫ�أ���Խ����
		const T& operator [](size_t index) const throw();			// �ҳ���index��Ԫ�أ���Խ����
		T& operator [](size_t index) throw();						// �ҳ���index��Ԫ�أ���Խ����

		_Vector_const_iterator<T> begin() const throw();
		_Vector_const_iterator<T> end() const throw();
		_Vector_iterator<T> begin() throw();
		_Vector_iterator<T> end() throw();
		_Vector_reverse_const_iterator<T> rbegin() const throw();
		_Vector_reverse_const_iterator<T> rend() const throw();
		_Vector_reverse_iterator<T> rbegin() throw();
		_Vector_reverse_iterator<T> rend() throw();

		vector<T>& operator = (const vector<T> &right);

	private:
		T *p_;
		size_t size_;
		size_t capacity_;

//		static std::allocator<T> alc;
	};
	// initialize static member alc
	//template<class T>
	//std::allocator<T> vector<T>::alc;

	template<class T>
	vector<T>::vector() throw() : p_(NULL), size_(0), capacity_(0) 
	{
	}

	template<class T>
	vector<T>::vector(const vector<T> &right) throw(std::bad_alloc) try : p_(static_cast<T*>(operator new[](right.size_ * sizeof(T)))), size_(right.size_), capacity_(right.size_) 
	{
		// ͨ�����캯����p_������right.p_�ĸ���
		std::uninitialized_copy(right.p_, right.p_ + size_, p_);
	}
	catch(const std::bad_alloc)
	{
		p_ = NULL;
		throw;
	}

	template<class T>
	vector<T>::vector(size_t count) throw(std::bad_alloc, std::length_error) : p_(NULL), size_(count), capacity_(count) 
	{
		if(count > max_size())
		{
			throw std::length_error("too much memory to allocate");
		}
		//p_ = alc.allocate(capacity_);
		p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
		for(size_t i = 0; i < size_; ++i)
		{
//			alc.construct(p_ + i, NULL);	// ���ﵽ���ǲ��ǵ�����Ĭ�Ϲ��캯�������ǣ�ֻ�ǲ���Ϊ0�ĸ��ƹ��캯��
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

		//p_ = alc.allocate(capacity_);					// allocate memory
		p_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
		std::uninitialized_fill(p_, p_ + size_, val);	// construct elements
	}

	template<class T>template<class _Iter>
	vector<T>::vector(_Iter first, _Iter last) throw(std::bad_alloc, std::length_error) : p_(NULL), size_(last - first), capacity_(last - first) 
	{
		if(capacity_ > max_size())
		{
			throw std::length_error("too much memory to allocate");
		}
		//p_ = alc.allocate(capacity_);				// allocate memory
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
				//alc.destroy(--last);	// destruct elements
				(--last)->~T();
			}
			//alc.deallocate(p_, capacity_);	// release memory
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
			//T *buf = alc.allocate(new_capacity);
			T *buf = static_cast<T*>(operator new[](new_capacity * sizeof(T)));
			if(p_)
			{
				std::uninitialized_copy(p_, p_ + size_, buf);	// copy elements using copy constructor
				for(T *last = p_ + size_; last != p_; )
				{
					//alc.destroy(--last);	// destruct elements
					(--last)->~T();
				}
				//alc.deallocate(p_, capacity_);	// release memory
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
				//alc.destroy(p_ + i);	// destructor
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
			//alc.construct(p_ + i, NULL);
			new (p_ + i) T();
		}
		// ����size_
		size_ = new_size;
	}

	template<class T>
	size_t vector<T>::max_size() const throw()
	{
		return static_cast<size_t>(-1) / sizeof(T);
	}

	template<class T>
	void vector<T>::clear() throw()
	{
		for(size_t i = 0; i < size_; ++i)
		{
			//alc.destroy(p_ + i);
			(p_ + i)->~T();
		}
		size_ = 0;
	}

	template<class T>
	void vector<T>::assign(size_t count, const T &val) throw()
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
	template<class _Iter>
	void vector<T>::assign(_Iter first, _Iter last) throw()
	{
		clear();
		size_ = last - first;
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
			size_t new_capacity = (0 == capacity_) ? 1 : 2 * capacity_;
			reserve(new_capacity);
		}
		// �����Ԫ��
		//alc.construct(p_ + size_, item);
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
			//alc.destroy(p_ + size_);
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
				//alc.destroy(p_ + i);
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
				//alc.construct(p_ + i, *(right.p_ + i));
				new (p_ + i) T(*(right.p_ + i));
				++i;
			}
			size_ = right.size_;
		}
		else
		{
			for(size_t i = 0; i < size_; ++i)
			{
				//alc.destroy(p_ + i);
				(p_ + i)->~T();
			}
			//alc.deallocate(p_, capacity_);
			operator delete[](p_);
			//p_ = alc.allocate(right.size_);
			p_ = static_cast<T*>(operator new[](right.size_ * sizeof(T)));
			for(size_t i = 0; i < right.size_; ++i)
			{
				//alc.construct(p_ + i, *(right.p_ + i));
				new (p_ + i) T(*(right.p_ + i));
			}
			size_ = right.size_;
			capacity_ = right.size_;
		}
		return *this;
	}

}

#endif

