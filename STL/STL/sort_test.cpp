#include <stdio.h>
#include "vector.hpp"
#include "sort.hpp"

static bool lessthan_func(const int &lhs, const int &rhs)
{
	return lhs < rhs;
}
static bool largerthan_func(const int &lhs, const int &rhs)
{
	return lhs > rhs;
}

class less_than_class
{
public:
	bool operator () (int a, int b) const
	{
		return a < b;
	}
};

class larger_than_class
{
public:
	bool operator () (int a, int b) const
	{
		return a > b;
	}
};


void sort_test()
{
	printf("\nsort test:\n");

	int a[] = {1,3,5,7,9,2,4,6,8,10};
	int b[] = {1,3,5,7,9,2,4,6,8,10};
	int length = sizeof(a) / sizeof(a[0]);
	xf::vector<int> va(a, a + length);
	xf::vector<int> vb(va);

	// vector sort
	sort(va.begin(), va.end());
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", va[i]);
	}
	printf("\n");

	sort(va.rbegin(), va.rend());
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", va[i]);
	}
	printf("\n");

	sort(vb.begin(), vb.end(), lessthan_func);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", vb[i]);
	}
	printf("\n");

	sort(vb.begin(), vb.end(), largerthan_func);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", vb[i]);
	}
	printf("\n");

	sort(vb.begin(), vb.end(), less_than_class());
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", vb[i]);
	}
	printf("\n");

	sort(vb.begin(), vb.end(), larger_than_class());
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", vb[i]);
	}
	printf("\n\n");


	// array sort
	xf::sort(a, a + length);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	xf::sort(b, b + length, lessthan_func);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", b[i]);
	}
	printf("\n");

	xf::sort(b, b + length, largerthan_func);
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", b[i]);
	}
	printf("\n");

	xf::sort(b, b + length, less_than_class());
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", b[i]);
	}
	printf("\n");

	xf::sort(b, b + length, larger_than_class());
	for(int i = 0; i < length; ++i)
	{
		printf("%d ", b[i]);
	}
	printf("\n");
}