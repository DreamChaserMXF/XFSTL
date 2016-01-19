#ifndef XF_CONST_ITER_H
#define XF_CONST_ITER_H

template<class T>
class _Const_Iter
{
public:
	_Const_Iter();
	explicit _Const_Iter(T *p);
	_Const_Iter(const _Const_Iter<T> &iter);

	const T operator *() const;
	const T* operator ->() const;
	_Const_Iter<T> operator ++();
	_Const_Iter<T> operator ++(int);
	_Const_Iter<T> operator --();
	_Const_Iter<T> operator --(int);
	//TODO +n, -n
	bool operator == (const _Const_Iter<T> &iter) const;
	bool operator != (const _Const_Iter<T> &iter) const;
protected:
	T* p_;
};

template<class T>
_Const_Iter<T>::_Const_Iter() : p_(NULL)
{
	
}

template<class T>
_Const_Iter<T>::_Const_Iter(T *p)
{
	p_ = p;
}
template<class T>
_Const_Iter<T>::_Const_Iter(const _Const_Iter<T> &iter)
{
	p_ = iter.p_;
}

template<class T>
const T _Const_Iter<T>::operator *() const
{
	return *p_;
}

template<class T>
const T* _Const_Iter<T>::operator ->() const
{
	return p_;
}

template<class T>
_Const_Iter<T> _Const_Iter<T>::operator ++()
{
	++p_;
	return *this;
}

template<class T>
_Const_Iter<T> _Const_Iter<T>::operator ++(int)
{
	_Const_Iter<T> iter(*this);
	++p_;
	return iter;
}

template<class T>
_Const_Iter<T> _Const_Iter<T>::operator --()
{
	--p_;
	return *this;
}

template<class T>
_Const_Iter<T> _Const_Iter<T>::operator --(int)
{
	_Const_Iter<T> iter(*this);
	--p_;
	return iter;
}

template<class T>
bool _Const_Iter<T>::operator == (const _Const_Iter<T> &iter) const
{
	return p_ == iter.p_;
}

template<class T>
bool _Const_Iter<T>::operator != (const _Const_Iter<T> &iter) const
{
	return p_ != iter.p_;
}

#endif