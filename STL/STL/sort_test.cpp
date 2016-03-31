#include <stdio.h>
#include "vector.hpp"
#include "sort.hpp"

bool my_lessthan(const int &lhs, const int &rhs)
{
	return lhs < rhs;
}
bool my_largerthan(const int &lhs, const int &rhs)
{
	return lhs > rhs;
}


void sort_test()
{
	int a[] = {1,3,5,7,9,2,4,6,8,10};
	int b[] = {1,3,5,7,9,2,4,6,8,10};
	int length = sizeof(a) / sizeof(a[0]);
	xf::vector<int> va(a, a + length);
	xf::vector<int> vb(va);

	sort(va.begin(), va.end());
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", va[i]);
	}
	printf("\n");

	sort(vb.begin(), vb.end(), my_lessthan);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", vb[i]);
	}
	printf("\n");

	sort(vb.begin(), vb.end(), my_largerthan);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", vb[i]);
	}
	printf("\n");

	xf::sort(a, a + length);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	xf::sort(b, b + length, my_lessthan);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", b[i]);
	}
	printf("\n");

	xf::sort(b, b + length, my_largerthan);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", b[i]);
	}
	printf("\n");
}