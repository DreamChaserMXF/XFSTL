#ifndef XF_COMMON_HPP
#define XF_COMMON_HPP
#include <float.h>
namespace xf
{
	template<class T>
	void swap(T &v1, T &v2)
	{
		// 这里需要这样优化吗？
		//if(&v1 != &v2)
		//{
		//	T tmp = v1;
		//	v1 = v2;
		//	v2 = tmp;
		//}
		T tmp = v1;
		v1 = v2;
		v2 = tmp;
	}

	template<class T>
	void min(const T &v1, const T &v2)
	{
		return v1 < v2 ? v1 : v2;
	}

	template<class T>
	void max(const T &v1, const T &v2)
	{
		return v1 > v2 ? v1 : v2;
	}

	template<class T>
	int sgn(const T & _Value)
	{
		if(_Value < 0)
		{
			return -1;
		}
		else if(_Value > 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	//static int ceil(double d)
	//{
	//	if(d <= DBL_MIN)
	//	{
	//		return static_cast<int>(d);
	//	}
	//	else if(d >= DBL_MIN)
	//	{
	//		return static_cast<int>(d + 1.0 - DBL_MIN);
	//	}
	//	else
	//	{
	//		return 0;
	//	}
	//}
	//static int floor(double d)
	//{
	//	if(d >= DBL_MIN)
	//	{
	//		return static_cast<int>(d);
	//	}
	//	else if(d <= DBL_MIN)
	//	{
	//		return static_cast<int>(d - 1.0 + DBL_MIN);
	//	}
	//	else
	//	{
	//		return 0;
	//	}
	//}
}

#endif