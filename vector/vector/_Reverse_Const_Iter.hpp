#ifndef XF_REVERSE_CONST_ITER_H
#define XF_REVERSE_CONST_ITER_H

template<class T>
class _Reverse_Const_Iter : public _Const_Iter<T>
{
public:
	_Reverse_Const_Iter();
	explicit _Reverse_Const_Iter(T *p);
	_Reverse_Const_Iter(const _Reverse_Const_Iter<T> &iter);

	// Overwrite
	_Reverse_Const_Iter<T> operator ++();
	_Reverse_Const_Iter<T> operator ++(int);
	_Reverse_Const_Iter<T> operator --();
	_Reverse_Const_Iter<T> operator --(int);
	//TODO +n, -n
private:
};

template<class T>
_Reverse_Const_Iter<T>::_Reverse_Const_Iter() : _Const_Iter()
{
}

template<class T>
_Reverse_Const_Iter<T>::_Reverse_Const_Iter(T *p) : _Const_Iter(p)
{
}

template<class T>
_Reverse_Const_Iter<T>::_Reverse_Const_Iter(const _Reverse_Const_Iter<T> &iter) : _Const_Iter(iter)
{
}

template<class T>
_Reverse_Const_Iter<T> _Reverse_Const_Iter<T>::operator ++()
{
	--p_;
	return *this;
}

template<class T>
_Reverse_Const_Iter<T> _Reverse_Const_Iter<T>::operator ++(int)
{
	_Reverse_Const_Iter iter(*this);
	--p_;
	return iter;
}


template<class T>
_Reverse_Const_Iter<T> _Reverse_Const_Iter<T>::operator --()
{
	++p_;
	return *this;
}

template<class T>
_Reverse_Const_Iter<T> _Reverse_Const_Iter<T>::operator --(int)
{
	_Reverse_Const_Iter iter(*this);
	++p_;
	return iter;
}

#endif