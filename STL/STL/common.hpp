#ifndef XF_COMMON_HPP
#define XF_COMMON_HPP

namespace xf
{
	template<class T>
	void swap(T &v1, T &v2)
	{
		// ������Ҫ�����Ż���
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
}

#endif