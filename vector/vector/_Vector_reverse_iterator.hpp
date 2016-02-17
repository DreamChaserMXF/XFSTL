#ifndef _VECTOR_REVERSE_ITERATOR
#define _VECTOR_REVERSE_ITERATOR

#include "_Vector_reverse_const_iterator.hpp"
namespace xf
{
	template<class T>
	class _Vector_reverse_iterator : public _Vector_reverse_const_iterator<T>
	{
	public:
		_Vector_reverse_iterator() throw();
		explicit _Vector_reverse_iterator(T *p) throw();	// �������explicit����_Vector_reverse_iterator�Ϳ���ֱ�Ӻ�ָ�������Ƚ���
		//_Vector_reverse_iterator(const _Vector_reverse_iterator<T> &iter) throw();
		_Vector_iterator<T> base() throw();
		T& operator *() const throw();
		T* operator ->() const throw();
	};

	template<class T>
	_Vector_reverse_iterator<T>::_Vector_reverse_iterator() throw() : _Vector_reverse_const_iterator()
	{
	}

	template<class T>
	_Vector_reverse_iterator<T>::_Vector_reverse_iterator(T *p) throw() : _Vector_reverse_const_iterator(p)
	{
	}

	//template<class T>
	//_Vector_reverse_iterator<T>::_Vector_reverse_iterator(const _Vector_reverse_iterator<T> &iter) throw() : _Vector_reverse_const_iterator(iter)
	//{
	//}

	template<class T>
	_Vector_iterator<T> _Vector_reverse_iterator<T>::base() throw()
	{
		return _Vector_iterator<T>(p_ + 1);
	}

	template<class T>
	T& _Vector_reverse_iterator<T>::operator *() const throw()
	{
		return *p_;
	}

	template<class T>
	T* _Vector_reverse_iterator<T>::operator ->() const throw()
	{
		return p_;
	}

}
#endif