#ifndef XF_ITER_H
#define XF_ITER_H

template<class T>
class _Iter
{
public:
	//_Iter(){};
	_Iter(const _Iter<T> &iter);
	//T operator *();
	T operator *() const;
	//T* operator ->();
	T* operator ->() const;
	T* operator ++();
	T* operator ++(int);
	T* operator --();
	T* operator --(int);
	//TODO +n, -n, ==, !=
private:
	T* p_;
};


template<class T>
_Iter<T>::_Iter(const _Iter<T> &iter)
{
	p_ = iter->p_;
}
template<class T>
T _Iter<T>::operator *() const
{
	return *p;
}

template<class T>
T* _Iter<T>::operator ->() const
{
	return p;
}

template<class T>
T* _Iter<T>::operator ++()
{
	return ++p;
}

template<class T>
T* _Iter<T>::operator ++(int)
{
	return p++;
}


template<class T>
T* _Iter<T>::operator --()
{
	return ++p;
}

template<class T>
T* _Iter<T>::operator --(int)
{
	return p++;
}


#endif